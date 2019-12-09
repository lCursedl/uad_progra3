#pragma once

#include "MathHelper.h"
#include "C3DModel.h"

class CHexCell
{
public:
	//Class constructor, true for pointy/false for flat
	CHexCell();
	CHexCell(CVector3 pos ,float size, bool p_or_f);
	~CHexCell();

	void initialize(CVector3 pos, float size, bool p_or_f);

	CVector3 m_center, p1, p2, p3, p4, p5, p6;

	C3DModel * mCellModel;

	float mSize;

	bool bPointy;

	float m_modelScale;

	float m_modelrotation[3];

	int getTriangleCount();

	CVector3 getCorner(int num);

private:
	//Function to calculate points, true for pointy, false for flat
	CVector3 calcPoint(CVector3 center, int numpoint, float cellsize, bool pointy);
};