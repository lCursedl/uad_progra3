#include "..\Include\CAppQuadTree.h"

DWORD WINAPI ThreadCreateGrid(LPVOID p);

CAppQuadTree::CAppQuadTree() :
	CAppQuadTree(CGameWindow::DEFAULT_WINDOW_WIDTH, CGameWindow::DEFAULT_WINDOW_HEIGHT)
{
}

CAppQuadTree::CAppQuadTree(int window_width, int window_height) :
	CApp(window_width, window_height),
	m_currentDeltaTime{ 0.0 },
	m_objectRotation{0.0},
	m_objectPosition{0.0f, 0.0f, 0.0f},
	m_rotationSpeed{DEFAULT_ROTATION_SPEED},
	m_VAO{0},
	AABB_VAO{0},
	m_renderPolygonMode{0}
{
	drawHexGrid = true;
	drawQuadTree = true;
	std::cout << "Constructor: CAppQuadTree(int window_width, int window_height)\n";
}

CAppQuadTree::~CAppQuadTree()
{
	std::cout << "Destructor: ~CAppQuadTree()\n";
	if (m_VAO > 0)
	{
		getOpenGLRenderer()->freeGraphicsMemoryForObject(&m_VAO);
	}
	if (m_textureModelShaderID > 0)
	{
		getOpenGLRenderer()->deleteTexture(&m_textureModelShaderID);
	}
	if (mGrid != nullptr)
	{
		delete mGrid;
	}
}

void CAppQuadTree::initialize()
{
	m_colorModelShaderID = getOpenGLRenderer()->getShaderProgramID(SHADER_PROGRAM_COLOR_OBJECT);

	if (m_colorModelShaderID == 0)
	{
		cout << "ERROR: Unable to load color shader\n";
		return;
	}

	// Get shader for textured objects
	// -------------------------------------------------------------------------------------------------------------

	m_textureModelShaderID = getOpenGLRenderer()->getShaderProgramID(SHADER_PROGRAM_TEXTURED_OBJECT);

	if (m_textureModelShaderID == 0)
	{
		cout << "ERROR: Unable to load texture shader\n";
		return;
	}

	/*GridThread = CreateThread(NULL, 0, ThreadCreateGrid, this, 0, &ThreadID[0]);
	if (WaitForSingleObject(GridThread, INFINITE) != WAIT_OBJECT_0)
	{
		std::cout << "Error al esperar thread.\n";
	}*/

	mGrid = new CHexGrid(2, 2, 1.0f, false);
	bool loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
		&m_colorModelShaderID,
		&m_VAO,
		mGrid->m_vertexData,
		6,
		mGrid->m_normalData,
		4,
		mGrid->m_vertexUVs,
		8,
		mGrid->m_faceIndices,
		4,
		mGrid->m_faceNormalIndices,
		4,
		mGrid->m_faceIndices,
		4);

	float minX = 0.0f;
	float maxX = 0.0f;
	float minZ = 0.0f;
	float maxZ = 0.0f;

	for (int i = 0; i < mGrid->m_rows; i++)
	{
		for (int j = 0; j < mGrid->m_cols; j++)
		{
			for (int k = 1; k < 7; k++)
			{
				CVector3 corner = mGrid->cellArray[i][j].getCorner(k);
				if (corner.X < minX)
				{
					minX = corner.X;
				}
				if (corner.X > maxX)
				{
					maxX = corner.X;
				}
				if (corner.Z < minZ)
				{
					minZ = corner.Z;
				}
				if (corner.Z > maxZ)
				{
					maxZ = corner.Z;
				}
			}
		}
	}

	CVector3 boundaries[4];
	boundaries[0] = CVector3(minX, 0.0f, minZ);
	boundaries[1] = CVector3(maxX, 0.0f, minZ);
	boundaries[2] = CVector3(minX, 0.0f, maxZ);
	boundaries[3] = CVector3(maxX, 0.0f, maxZ);

	mainBB.setCorners(boundaries);

	QT.Subdivide(mGrid->cellArray, mainBB, mGrid->m_rows, mGrid->m_cols, 6, 5);
	if (!QT.loadTreeGeometry(getOpenGLRenderer(), m_colorModelShaderID))
	{
		std::cout << "Error loading QuadTree's AABB to memory.\n";
	}

	if (!loaded)
	{
		cout << "Error loading cell to graphics memory\n";
		mGrid->faces = 0;
		if (m_VAO > 0)
		{
			getOpenGLRenderer()->freeGraphicsMemoryForObject(&m_VAO);
			m_VAO = 0;
		}
	}
	else
	{
		m_initialized = true;
	}
}

void CAppQuadTree::update(double delta_time)
{
	if (delta_time <= 0.0f)
	{
		return;
	}
	m_currentDeltaTime = delta_time;
}

void CAppQuadTree::run()
{
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

void CAppQuadTree::render()
{
	CGameMenu *menu = getMenu();
	if (menu != NULL && menu->isInitialized() && menu->isActive())
	{
		/*
		*/
	}
	else
	{
		float color[3] = { 0.0f, 0.3f, 0.0f };
		float modelcolor[3] = { 0.0f, 1.0f, 0.0f };
		double totalDegreesRotatedRadians = m_objectRotation * PI_OVER_180;
		MathHelper::Matrix4 HexMatrix;
		if (drawHexGrid)
		{
			if (m_VAO > 0 && mGrid->faces > 0)
			{
				for (int i = 0; i < mGrid->m_rows; i++)
				{
					for (int j = 0; j < mGrid->m_cols; j++)
					{
						HexMatrix = MathHelper::SimpleModelMatrixRotationTranslation(0.0f, mGrid->cellArray[i][j].m_center);
						getOpenGLRenderer()->renderObject(
							&m_colorModelShaderID,
							&m_VAO,
							0,
							mGrid->faces,
							color,
							&HexMatrix,
							COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES,
							false);
						if (mGrid->cellArray[i][j].mCellModel != nullptr)
						{

							MathHelper::Matrix4 sm = MathHelper::ScaleMatrix(mGrid->cellArray[i][j].m_modelScale, mGrid->cellArray[i][j].m_modelScale, mGrid->cellArray[i][j].m_modelScale);

							MathHelper::Matrix4 tm = MathHelper::TranslationMatrix(mGrid->cellArray[i][j].m_center.X, mGrid->cellArray[i][j].m_center.Y, mGrid->cellArray[i][j].m_center.Z);

							MathHelper::Matrix4 ry;

							if (mGrid->cellArray[i][j].m_modelrotation[1] != 0.0f)
							{
								ry = MathHelper::RotAroundY((float)mGrid->cellArray[i][j].m_modelrotation[1] * PI_OVER_180);
							}
							else
							{
								ry = MathHelper::RotAroundY(0.0f * PI_OVER_180);
							}

							MathHelper::Matrix4 RandS = MathHelper::Multiply(ry, sm);

							MathHelper::Matrix4 ModelMatrix = MathHelper::Multiply(RandS, tm);

							unsigned int tempVAO = mGrid->cellArray[i][j].mCellModel->getGraphicsMemoryObjectId();
							getOpenGLRenderer()->renderObject(
								&m_colorModelShaderID,
								&tempVAO,
								0,
								mGrid->cellArray[i][j].mCellModel->getNumFaces(),
								modelcolor,
								&ModelMatrix,
								COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES,
								false);
						}
					}
				}
			}
		}
		if (drawQuadTree)
		{
			QT.m_root->render(nullptr, getOpenGLRenderer(), m_colorModelShaderID);
		}		
	}
}

void CAppQuadTree::onArrowUp(int mods)
{
	std::cout << "Pressed Up/W\n";
}

void CAppQuadTree::onArrowDown(int mods)
{
	std::cout << "Pressed Down/S\n";
}

void CAppQuadTree::onArrowLeft(int mods)
{
	std::cout << "Pressed Left/A\n";
}

void CAppQuadTree::onArrowRight(int mods)
{
	std::cout << "Pressed Right/D\n";
}

bool CAppQuadTree::StartGridThread()
{
	mGrid = new CHexGrid(12, 12, 1.0f, true);
	bool loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
		&m_colorModelShaderID,
		&m_VAO,
		mGrid->m_vertexData,
		6,
		mGrid->m_normalData,
		4,
		mGrid->m_vertexUVs,
		8,
		mGrid->m_faceIndices,
		4,
		mGrid->m_faceNormalIndices,
		4,
		mGrid->m_faceIndices,
		4
	);
	if (!loaded)
	{
		cout << "Error loading cell to graphics memory\n";
		mGrid->faces = 0;
		if (m_VAO > 0)
		{
			getOpenGLRenderer()->freeGraphicsMemoryForObject(&m_VAO);
			m_VAO = 0;
		}
	}
	else
	{
		m_VAO = 1;
		m_initialized = true;
	}
	return m_initialized;
}

void CAppQuadTree::onF3(int mods)
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

void CAppQuadTree::onF4(int mods)
{
	if (mods & KEY_MOD_SHIFT)
	{
		drawHexGrid = true;
	}
	else
	{
		drawHexGrid = false;
	}
}

void CAppQuadTree::onF5(int mods)
{
	if (mods & KEY_MOD_SHIFT)
	{
		drawQuadTree = true;
	}
	else
	{
		drawQuadTree = false;
	}
}

void CAppQuadTree::moveCamera(float direction)
{
	if (getOpenGLRenderer() != nullptr)
	{
		getOpenGLRenderer()->simpleCameraZoom(direction);
	}
}

DWORD WINAPI ThreadCreateGrid(LPVOID p)
{
	CAppQuadTree * appQuadTree = (CAppQuadTree *)p;
	if (appQuadTree->StartGridThread())
	{
		return 0;
	}
	return -1;
}