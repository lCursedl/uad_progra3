
#include "../Include/CHexCell.h"

CHexCell::CHexCell()
{
}

CHexCell::CHexCell(CVector3 pos, float size, bool p_or_f)
{
	m_center = pos;
	p1 = calcPoint(pos, 1, size, p_or_f);
	p2 = calcPoint(pos, 2, size, p_or_f);
	p3 = calcPoint(pos, 3, size, p_or_f);
	p4 = calcPoint(pos, 4, size, p_or_f);
	p5 = calcPoint(pos, 5, size, p_or_f);
	p6 = calcPoint(pos, 6, size, p_or_f);
	mCellModel = nullptr;
	m_modelScale = 0.0f;
}

CHexCell::~CHexCell(){}

void CHexCell::initialize(CVector3 pos, float size, bool p_or_f)
{
	m_center = pos;
	/*p1 = calcPoint(m_center, 1, size, p_or_f);
	p2 = calcPoint(m_center, 2, size, p_or_f);
	p3 = calcPoint(m_center, 3, size, p_or_f);
	p4 = calcPoint(m_center, 4, size, p_or_f);
	p5 = calcPoint(m_center, 5, size, p_or_f);
	p6 = calcPoint(m_center, 6, size, p_or_f);*/
	m_modelScale = 0.0f;
	mCellModel = nullptr;
}

CVector3 CHexCell::calcPoint(CVector3 center, int numpoint, float cellsize, bool pointy)
{
	CVector3 point;
	float angle;
	float angleR;
	if (pointy)
	{
		angle = 60 * numpoint - 30;
	}
	else
	{
		angle = 60 * numpoint;
	}
	angleR = angle * PI_OVER_180;
	point.X = center.X + cellsize * cos(angleR);
	point.Z = center.Y + cellsize * sin(angleR);
	return point;
}