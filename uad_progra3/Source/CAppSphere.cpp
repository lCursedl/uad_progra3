#define PI 3.14159265359
#include "../stdafx.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include <cmath>

#include "../Include/Globals.h"
#include "../Include/CAppSphere.h"
#include "../Include/CWideStringHelper.h"
#include "../Include/CTextureLoader.h"

CAppSphere::CAppSphere() :CAppSphere(CGameWindow::DEFAULT_WINDOW_WIDTH, CGameWindow::DEFAULT_WINDOW_HEIGHT)
{}

CAppSphere::CAppSphere(int windows_width, int window_height) :
	CApp(windows_width, window_height),
	m_sphereShaderProgramID {0},
	m_sphereVertexArrayObject {0},
	m_sphereTextureID {0},
	m_sectorCount {3},
	m_stackCount {2}
{
	cout << "Constructor: CAppSphere(int window_width, int window_height)" << endl;
}

CAppSphere::~CAppSphere()
{
	cout << "Destructor: ~CAppSphere()" << endl;
	// Free memory allocated in this class instance here
	// =================================================
	//
	// =================================================
	if (m_sphereTextureID > 0 && getOpenGLRenderer() != nullptr)
	{
		getOpenGLRenderer()->deleteTexture(&m_sphereTextureID);
	}
	if (m_sphereVertexArrayObject > 0 && getOpenGLRenderer() != nullptr)
	{
		getOpenGLRenderer()->freeGraphicsMemoryForObject(&m_sphereVertexArrayObject);
	}
}

void CAppSphere::initialize()
{
	float x, y, z, xy;
	float nx, ny, nz;

	float sectorStep = 2 * PI / m_sectorCount;
	float stackStep = PI / m_stackCount;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= m_stackCount; ++i)
	{
		stackAngle = PI / 2 - i * stackStep;
		xy = m_radius * cosf(stackAngle);
		z = m_radius * sinf(stackAngle);

		for (int j = 0; j <= m_sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;
			x = xy * cosf(sectorAngle);
			y = xy * sinf(sectorAngle);
		}
	}

}

void CAppSphere::update(double deltaTime)
{
}

void CAppSphere::run()
{
}

void CAppSphere::render()
{
}

void CAppSphere::onMouseMove(float deltax, float deltaY)
{
}