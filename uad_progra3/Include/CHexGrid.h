#pragma once

#include "CHexCell.h"

class CHexGrid
{
public:
	CHexGrid(int cols, int rows, float cellsize, bool pointy);
	~CHexGrid();

	void createCellGeometry(CHexCell cell);

	int m_cols;
	int m_rows;
	int faces;
	CHexCell ** cellArray;

	float m_vertexData[18];
	float m_vertexUVs[8];
	unsigned short m_faceIndices[12];
	float m_normalData[12];
	unsigned short m_faceNormalIndices[12];

};