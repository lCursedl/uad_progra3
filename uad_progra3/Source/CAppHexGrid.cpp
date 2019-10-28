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
		cout << "ERROR: Unable to load color shader" << endl;
		return;
	}

	// Get shader for textured objects
	// -------------------------------------------------------------------------------------------------------------

	m_texturedModelShaderId = getOpenGLRenderer()->getShaderProgramID(SHADER_PROGRAM_TEXTURED_OBJECT);

	if (m_texturedModelShaderId == 0)
	{
		cout << "ERROR: Unable to load texture shader" << endl;
		return;
	}
	cout << "Creating HexGrid data\n";
	p_Grid = new CHexGrid(5, 5, 1.0f, true);
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
		float color[3] = { 1.0f, 1.0f, 1.0f };
		double totalDegreesRotatedRadians = m_objectRotation * 3.14159 / 180.0;
		MathHelper::Matrix4 modelMatrix;
		if (m_gridVAO > 0 && p_Grid->faces > 0)
		{
			for (int i = 0; i < p_Grid->m_rows; i++)
			{
				for (int j = 0; j < p_Grid->m_cols; j++)
				{
					modelMatrix = MathHelper::SimpleModelMatrixRotationTranslation((float)totalDegreesRotatedRadians, p_Grid->cellArray[i][j].m_center);
					getOpenGLRenderer()->renderObject(
						&m_colorModelShaderId,
						&m_gridVAO,
						0,
						p_Grid->faces,
						color,
						&modelMatrix,
						COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES,
						false);
				}
			}
		}
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