#pragma once

#ifndef CAPPHEXGRID_H
#define CAPPHEXGRID_H

#include "Globals.h"
#include "../Dependencies/JSON/nlohmann/json.hpp"
#include <fstream>
#include "CApp.h"
#include "CHexGrid.h"
#include "C3DModel_Obj.h"

using json = nlohmann::json;

struct ModelParams
{
	std::string ModelName;
	std::string ModelPath;
	C3DModel * pModel;

	ModelParams(std::string name, std::string path, C3DModel * model)
	{
		ModelName = name;
		ModelPath = path;
		pModel = model;
	}
	~ModelParams()
	{
		if (pModel != nullptr)
		{
			delete pModel;
		}
	}
};

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

	void onF2(int mods);
	void onF3(int mods);

	void moveCamera(float direction);
	void onMouseMove(float deltaX, float deltaY);


private:
	std::vector<ModelParams*> m_Model;

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



	json Data;

	unsigned int DataCols;
	unsigned int DataRows;
	float DataSize;
	bool DataCelltype;
	std::string sDataCelltype;
};
#endif // !CAPPHEXGRID_H