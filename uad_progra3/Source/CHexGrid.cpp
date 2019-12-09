
#include "../Include/CHexGrid.h"

CHexGrid::CHexGrid(int cols, int rows, float cellsize, bool pointy)
{
	m_cols = cols;
	m_rows = rows;
	size = cellsize;
	isPointy = pointy;
	createCellGeometry(CHexCell(CVector3(0.0f, 0.0f, 0.0f),cellsize, pointy));
	faces = 4;
	//dinamic array creation
	cellArray = new CHexCell*[m_rows];
	for (int i = 0; i < m_rows; i++)
	{
		cellArray[i] = new CHexCell[m_cols];
	}

	CVector3 temp = { 0.0f, 0.0f, 0.0f };

	if (pointy)
	{
		float w = sqrtf(3.0f) * cellsize;
		float h = 2.0f * cellsize;
		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < m_cols; j++)
			{
				cellArray[i][j].initialize(temp, cellsize, pointy);
				cellArray[i][j].mSize = cellsize;
				cellArray[i][j].bPointy = pointy;
				temp.X += w;
			}			
			if (i % 2)
			{
				temp.X = 0.0f;
			}
			else
			{
				temp.X = w / 2;
			}
			temp.Z += h * (3.0f / 4.0f);
		}
	}
	else
	{
		float w = 2.0f * cellsize;
		float h = sqrtf(3.0f) * cellsize;
		for (int j = 0; j < m_cols; j++)
		{
			for (int i = 0; i < m_rows; i++)
			{
				cellArray[i][j].initialize(temp, cellsize, pointy);
				cellArray[i][j].mSize = cellsize;
				cellArray[i][j].bPointy = pointy;
				temp.Z += h;
			}
			if (j % 2)
			{
				temp.Z = 0.0f;
			}
			else
			{
				temp.Z = h / 2.0f;
			}
			temp.X += w * (3.0f / 4.0f);
		}
	}
}

CHexGrid::~CHexGrid()
{
	if (cellArray != nullptr)
	{
		for (int i = 0; i < m_cols; i++)
		{
			delete [] cellArray[i];
		}
		delete [] cellArray;
	}
}

void CHexGrid::createCellGeometry(CHexCell cell)
{

	CVector3 v1, v2, v3, v1v2, v1v3, norm;
	//Vertex Data
	//				X					|					Y				|				Z
	m_vertexData[0] = cell.p1.getX();	m_vertexData[1] = cell.p1.getY();	m_vertexData[2] = cell.p1.getZ();
	m_vertexData[3] = cell.p2.getX();	m_vertexData[4] = cell.p2.getY();	m_vertexData[5] = cell.p2.getZ();
	m_vertexData[6] = cell.p3.getX();	m_vertexData[7] = cell.p3.getY();	m_vertexData[8] = cell.p3.getZ();
	m_vertexData[9] = cell.p4.getX();	m_vertexData[10] = cell.p4.getY();	m_vertexData[11] = cell.p4.getZ();
	m_vertexData[12] = cell.p5.getX();	m_vertexData[13] = cell.p5.getY();	m_vertexData[14] = cell.p5.getZ();
	m_vertexData[15] = cell.p6.getX();	m_vertexData[16] = cell.p6.getY();	m_vertexData[17] = cell.p6.getZ();

	//UVs
	//			X			|			Y
	m_vertexUVs[0] = 0.0f;	m_vertexUVs[1] = 0.0f;
	m_vertexUVs[2] = 0.0f;	m_vertexUVs[3] = 0.0f;
	m_vertexUVs[4] = 0.0f;	m_vertexUVs[5] = 0.0f;
	m_vertexUVs[6] = 0.0f;	m_vertexUVs[7] = 0.0f;

	//Face index
	m_faceIndices[0] = 0;	m_faceIndices[1] = 1;	m_faceIndices[2] = 2;
	m_faceIndices[3] = 2;	m_faceIndices[4] = 3;	m_faceIndices[5] = 5;
	m_faceIndices[6] = 3;	m_faceIndices[7] = 4;	m_faceIndices[8] = 5;
	m_faceIndices[9] = 5;	m_faceIndices[10] = 0;	m_faceIndices[11] = 2;

	//Normals
	for (int i = 0; i < 4; i++)
	{
		// Vertex 1
		v1.setValues(
			m_vertexData[m_faceIndices[i * 3]],
			m_vertexData[m_faceIndices[i * 3] + 1],
			m_vertexData[m_faceIndices[i * 3] + 2]);

		// Vertex 2
		v2.setValues(
			m_vertexData[m_faceIndices[(i * 3) + 1]],
			m_vertexData[m_faceIndices[(i * 3) + 1] + 1],
			m_vertexData[m_faceIndices[(i * 3) + 1] + 2]
		);

		// Vertex 3
		v3.setValues(
			m_vertexData[m_faceIndices[(i * 3) + 2]],
			m_vertexData[m_faceIndices[(i * 3) + 2] + 1],
			m_vertexData[m_faceIndices[(i * 3) + 2] + 2]
		);

		// Vector from v1 to v2
		v1v2 = v2 - v1;

		// Vector from v1 to v3
		v1v3 = v3 - v1;

		norm = v1v2.cross(v1v3);
		norm.normalize();

		m_normalData[i * 3] = norm.X;
		m_normalData[(i * 3) + 1] = norm.Y;
		m_normalData[(i * 3) + 2] = norm.Z;
	}

	//Normal Index
	//			X				|				Y				|			Z
	m_faceNormalIndices[0] = 0;	m_faceNormalIndices[1] = 0;		m_faceNormalIndices[2] = 0;
	m_faceNormalIndices[3] = 0;	m_faceNormalIndices[4] = 0;		m_faceNormalIndices[5] = 0;
	m_faceNormalIndices[6] = 0;	m_faceNormalIndices[7] = 0;		m_faceNormalIndices[8] = 0;
	m_faceNormalIndices[9] = 0;	m_faceNormalIndices[10] = 0;	m_faceNormalIndices[11] = 0;
}