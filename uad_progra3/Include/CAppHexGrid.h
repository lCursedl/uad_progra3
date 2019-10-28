#pragma once

#ifndef CAPPHEXGRID_H
#define CAPPHEXGRID_H

#include "Globals.h"
#include "CApp.h"
#include "CHexGrid.h"

class CAppHexGrid : public CApp
{
public:
	CAppHexGrid();
	CAppHexGrid(int window_width, int window_height);
	~CAppHexGrid();

	void initialize();
	void update(double delta_time);
	void run();
	void render();

	bool initializeMenu() { return false; }

	void onF3(int mods);

	void moveCamera(float direction);

private:

	bool m_initialized;

	double m_currentDeltaTime;

	CVector3 m_objectPosition;

	double m_objectRotation;

	double m_rotationSpeed;

	/*------------------*/

	unsigned int m_colorModelShaderId;
	unsigned int m_texturedModelShaderId;

	unsigned int m_textureID;

	unsigned int m_gridVAO;

	int m_renderPolygonMode;

	int numFacesCell;

	CHexGrid * p_Grid;
};

#endif // !CAPPHEXGRID_H