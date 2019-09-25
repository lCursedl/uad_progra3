#pragma once

#ifndef CAPPSPHERE_H
#define CAPPSPHERE_H

#include "Globals.h"
#include "CApp.h"
#include "CVector3.h"

class CAppSphere : public CApp
{
private:

	unsigned int m_sphereShaderProgramID;
	unsigned int m_sphereVertexArrayObject;
	unsigned int m_sphereTextureID;
	int m_sectorCount;
	int m_stackCount;
	float m_radius;

protected:

	bool initializeMenu() { return false; }

public:
	CAppSphere();
	CAppSphere(int windows_width, int window_height);
	~CAppSphere();

	void initialize();

	void update(double deltaTime);

	void run();

	void render();

	void onMouseMove(float deltax, float deltaY);
};

#endif // !CAPPSPHERE_H