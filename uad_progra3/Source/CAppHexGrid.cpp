#include "../stdafx.h"
#include "../Include/CAppHexGrid.h"

#include "../Include/CWideStringHelper.h"
#include "../Include/CTextureLoader.h"


CAppHexGrid::CAppHexGrid() :
	CAppHexGrid(CGameWindow::DEFAULT_WINDOW_WIDTH, CGameWindow::DEFAULT_WINDOW_HEIGHT)
{
}

CAppHexGrid::CAppHexGrid(int window_width, int window_height) :
	CApp(window_width, window_height),
	m_currentDeltaTime{ 0.0 },
	m_objectRotation{0.0},
	m_objectPosition{0.0f, 0.0f, 0.0f},
	m_rotationSpeed{DEFAULT_ROTATION_SPEED},
	m_gridVAO{0},
	m_renderPolygonMode{0}
{
	std::cout << "Constructor: CAppHexGrid(int window_width, int window_height)\n";
}

CAppHexGrid::~CAppHexGrid()
{
	std::cout << "Destructor: ~CAppHexGrid()\n";
	if (m_textureID > 0)
	{
		getOpenGLRenderer()->deleteTexture(&m_textureID);
	}

	if (m_gridVAO > 0)
	{
		getOpenGLRenderer()->freeGraphicsMemoryForObject(&m_gridVAO);
	}

	if (p_Grid != nullptr)
	{
		delete p_Grid;
	}
	if (m_Model.size() != 0)
	{
		for (int i = 0; i < m_Model.size(); i++)
		{
			delete m_Model[i]->pModel;
		}
	}
}

void CAppHexGrid::initialize()
{
	// Initialize app-specific stuff here
	// ==================================
	//
	// Get shader for color objects
	// -------------------------------------------------------------------------------------------------------------

	m_colorModelShaderId = getOpenGLRenderer()->getShaderProgramID(SHADER_PROGRAM_COLOR_OBJECT);

	if (m_colorModelShaderId == 0)
	{
		cout << "ERROR: Unable to load color shader\n";
		return;
	}

	// Get shader for textured objects
	// -------------------------------------------------------------------------------------------------------------

	m_texturedModelShaderId = getOpenGLRenderer()->getShaderProgramID(SHADER_PROGRAM_TEXTURED_OBJECT);

	if (m_texturedModelShaderId == 0)
	{
		cout << "ERROR: Unable to load texture shader\n";
		return;
	}

	ifstream in_file("hexgrid_cfg.json", ifstream::binary);
	Data << in_file;
	DataCols = Data["HexGrid"]["numCols"];
	DataRows = Data["HexGrid"]["numRows"];
	DataSize = Data["HexGrid"]["cellSize"];
	sDataCelltype = Data["HexGrid"]["orientation"].get<std::string>();
	if (sDataCelltype == "pointy")
	{
		DataCelltype = true;
	}
	else
	{
		DataCelltype = false;
	}

	int objects_present = (int)Data.count("Models");
	if (objects_present > 0 && (Data["Models"].type() == json::value_t::array))
	{
		std::string objName = "";
		std::string objFileName = "";
		C3DModel * Model;
		ModelParams * ptrModel;
		for (json::iterator it = Data["Models"].begin(); it < Data["Models"].end(); ++it)
		{
			objName = it.value().value("name", objName);
			objFileName = it.value().value("filename", objFileName);
			objFileName = "Resources/MEDIA/" + objFileName;

			
			Model = new C3DModel_Obj();
			ptrModel = new ModelParams(objName, objFileName, Model->load(objFileName.c_str(), getOpenGLRenderer()));
			m_Model.push_back(ptrModel);
			//m_gameObjects.push_back(Model->load(objFileName.c_str(), getOpenGLRenderer()));
		}
	}

	cout << "Creating HexGrid data\n";
	p_Grid = new CHexGrid(DataCols, DataRows, DataSize, DataCelltype);
	bool loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
		&m_colorModelShaderId,
		&m_gridVAO,
		p_Grid->m_vertexData,
		6,
		p_Grid->m_normalData,
		4,
		p_Grid->m_vertexUVs,
		8,
		p_Grid->m_faceIndices,
		4,
		p_Grid->m_faceNormalIndices,
		4,
		p_Grid->m_faceIndices,
		4
	);

	int instances_present = (int)Data.count("ModelInstances");
	if (instances_present > 0 && (Data["ModelInstances"].type() == json::value_t::array))
	{
		std::string objName = "";
		int row;
		int col;
		float scale;
		float rotation[3];
		json jrotation;
		for (json::iterator it = Data["ModelInstances"].begin(); it < Data["ModelInstances"].end(); ++it)
		{
			objName = it.value().value("model", objName);
			row = it.value().value("row", row);
			col = it.value().value("column", col);
			scale = it.value().value("scale", scale);
			jrotation = it.value();
			int i = 0;
			for (json::iterator it2 = jrotation["rotation"].begin(); it2 < jrotation["rotation"].end(); ++it2)
			{
				rotation[i] = it2.value();
				i++;
			}
			i = 0;
			for (int i = 0; i < m_Model.size(); i++)
			{
				if (objName == m_Model[i]->ModelName)
				{
					p_Grid->cellArray[row][col].mCellModel = m_Model[i]->pModel;
					p_Grid->cellArray[row][col].m_modelScale = scale;
					p_Grid->cellArray[row][col].m_modelrotation[0] = rotation[0];
					p_Grid->cellArray[row][col].m_modelrotation[1] = rotation[1];
					p_Grid->cellArray[row][col].m_modelrotation[2] = rotation[2];
				}
			}
		}
	}

	in_file.close();

	if (!loaded)
	{
		cout << "Error loading cell to graphics memory\n";
		p_Grid->faces = 0;
		if (m_gridVAO > 0)
		{
			getOpenGLRenderer()->freeGraphicsMemoryForObject(&m_gridVAO);
			m_gridVAO = 0;
		}
	}
	else
	{
		m_initialized = true;
	}
}

void CAppHexGrid::update(double delta_time)
{
	if (delta_time <= 0.0f)
	{
		return;
	}
	m_currentDeltaTime = delta_time;
}

void CAppHexGrid::run()
{
	// Check if CGameWindow object AND Graphics API specific Window library have been initialized
	if (canRun())
	{
		// Create the Window 
		if (getGameWindow()->create(CAPP_PROGRA3_HEXGRID_WINDOW_TITLE))
		{
			// ALWAYS call initialize AFTER creating the window
			initialize();

			// Set initial clear screen color
			getOpenGLRenderer()->setClearScreenColor(0.25f, 0.0f, 0.75f);

			if (m_initialized)
			{
				getOpenGLRenderer()->setWireframePolygonMode();

				// Enter main loop
				cout << "Entering Main loop" << endl;
				getGameWindow()->mainLoop(this);
			}
		}
	}
}

void CAppHexGrid::render()
{
	CGameMenu *menu = getMenu();
	if (menu != NULL && menu->isInitialized() && menu->isActive())
	{

	}
	else
	{
		float color[3] = { 0.0f, 0.3f, 0.0f };
		float modelcolor[3] = {0.0f, 1.0f, 0.0f};
		double totalDegreesRotatedRadians = m_objectRotation * PI_OVER_180;
		MathHelper::Matrix4 HexMatrix;
		if (m_gridVAO > 0 && p_Grid->faces > 0)
		{
			for (int i = 0; i < p_Grid->m_rows; i++)
			{
				for (int j = 0; j < p_Grid->m_cols; j++)
				{
					HexMatrix = MathHelper::SimpleModelMatrixRotationTranslation(0.0f, p_Grid->cellArray[i][j].m_center);
					getOpenGLRenderer()->renderObject(
						&m_colorModelShaderId,
						&m_gridVAO,
						0,
						p_Grid->faces,
						color,
						&HexMatrix,
						COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES,
						false);
					if (p_Grid->cellArray[i][j].mCellModel != nullptr)
					{

						MathHelper::Matrix4 sm = MathHelper::ScaleMatrix(p_Grid->cellArray[i][j].m_modelScale, p_Grid->cellArray[i][j].m_modelScale, p_Grid->cellArray[i][j].m_modelScale);

						MathHelper::Matrix4 tm = MathHelper::TranslationMatrix(p_Grid->cellArray[i][j].m_center.X, p_Grid->cellArray[i][j].m_center.Y, p_Grid->cellArray[i][j].m_center.Z);

						MathHelper::Matrix4 ry;

						if (p_Grid->cellArray[i][j].m_modelrotation[1] != 0.0f)
						{
							ry = MathHelper::RotAroundY((float)p_Grid->cellArray[i][j].m_modelrotation[1] * PI_OVER_180);
						}
						else
						{
							ry = MathHelper::RotAroundY(0.0f * PI_OVER_180);
						}

						MathHelper::Matrix4 RandS = MathHelper::Multiply(ry, sm);

						MathHelper::Matrix4 ModelMatrix = MathHelper::Multiply(RandS, tm);

						unsigned int tempVAO = p_Grid->cellArray[i][j].mCellModel->getGraphicsMemoryObjectId();
						getOpenGLRenderer()->renderObject(
							&m_colorModelShaderId,
							&tempVAO,
							0,
							p_Grid->cellArray[i][j].mCellModel->getNumFaces(),
							modelcolor,
							&ModelMatrix,
							COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES,
							false);
					}
				}
			}
		}
	}
}
//Ya esta feliz profe!. :D atte: ram, gus y robert
void CAppHexGrid::onF2(int mods)
{
	if (m_renderPolygonMode == 0)
	{
		getOpenGLRenderer()->setFillPolygonMode();
		m_renderPolygonMode = 1;
	}
	else
	{
		getOpenGLRenderer()->setWireframePolygonMode();
		m_renderPolygonMode = 0;
	}
}

void CAppHexGrid::onF3(int mods)
{
	if (mods & KEY_MOD_SHIFT)
	{
		moveCamera(-1.0f);
	}
	else
	{
		moveCamera(1.0f);
	}
}

void CAppHexGrid::moveCamera(float direction)
{
	if (getOpenGLRenderer() != nullptr)
	{
		getOpenGLRenderer()->simpleCameraZoom(direction);
	}
}

void CAppHexGrid::onMouseMove(float deltaX, float deltaY)
{
	if (deltaX < 100.0f && deltaY < 100.0f)
	{
		float moveX = -deltaX * DEFAULT_CAMERA_MOVE_SPEED;
		float moveZ = -deltaY * DEFAULT_CAMERA_MOVE_SPEED;

		float currPos[3];
		for (int i = 0; i < p_Grid->m_rows; i++)
		{
			for (int j = 0; j < p_Grid->m_cols; j++)
			{
				p_Grid->cellArray[i][j].m_center.getValues(currPos);
				currPos[0] += moveX;
				currPos[2] += moveZ;
				p_Grid->cellArray[i][j].m_center.setValues(currPos);
			}
		}
	}
}
