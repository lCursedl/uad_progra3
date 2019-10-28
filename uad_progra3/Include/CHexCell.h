#pragma once

#include "MathHelper.h"

class CHexCell
{
public:
	//Class constructor, true for pointy/false for flat
	CHexCell();
	CHexCell(CVector3 pos ,float size, bool p_or_f);
	~CHexCell();

	void initialize(CVector3 pos, float size, bool p_or_f);

	CVector3 m_center, p1, p2, p3, p4, p5, p6;

private:
	//Function to calculate points, true for pointy, false for flat
	CVector3 calcPoint(CVector3 center, int numpoint, float cellsize, bool pointy);
};