#include "../Include/CAABB_2D.h"

AABB_2D::AABB_2D(){}

AABB_2D::AABB_2D(CVector3 * data)
{
	m_points[0] = *data;
	data++;
	m_points[1] = *data;
	data++;
	m_points[2] = *data;
	data++;
	m_points[3] = *data;
}

AABB_2D::~AABB_2D(){}

void AABB_2D::getCorners(CVector3 * data)
{
	*data = m_points[0];
	data++;
	*data = m_points[1];
	data++;
	*data = m_points[2];
	data++;
	*data = m_points[3];
}

void AABB_2D::setCorners(CVector3 * data)
{
	for (int i = 0; i < 4; i++)
	{
		m_points[i] = data[i];
	}
	//Vertex Data
	Vertices[0] = m_points[0].getX();	Vertices[1] = m_points[0].getY();	Vertices[2] = m_points[0].getZ();
	Vertices[3] = m_points[1].getX();	Vertices[4] = m_points[1].getY();	Vertices[5] = m_points[1].getZ();
	Vertices[6] = m_points[2].getX();	Vertices[7] = m_points[2].getY();	Vertices[8] = m_points[2].getZ();
	Vertices[9] = m_points[3].getX();	Vertices[10] = m_points[3].getY();	Vertices[11] = m_points[3].getZ();

	//UV
	VertexUV[0] = 0.0f;		VertexUV[1] = 0.0f;
	VertexUV[2] = 0.0f;		VertexUV[3] = 0.0f;

	//Face Index
	FaceIndex[0] = 0; FaceIndex[1] = 1; FaceIndex[2] = 2;
	FaceIndex[3] = 2; FaceIndex[4] = 1; FaceIndex[5] = 3;

	//Normal
	Normal[0] = 0.f;	Normal[1] = 0.f;	Normal[2] = 0.f;
	Normal[3] = 0.f;	Normal[4] = 0.f;	Normal[5] = 0.f;

	//Normal Index
	FaceNormalIndex[0] = 0; FaceNormalIndex[1] = 0; FaceNormalIndex[2] = 0;
	FaceNormalIndex[3] = 0; FaceNormalIndex[4] = 0; FaceNormalIndex[5] = 0;
}

bool AABB_2D::pointsInside(CVector3 * data)
{
	CVector3 p1, p2, p3, p4, p5, p6;
	p1 = *data;
	data++;
	p2 = *data;
	data++;
	p3 = *data;
	data++;
	p4 = *data;
	data++;
	p5 = *data;
	data++;
	p6 = *data;

	if ((((p1.getX() > m_points[0].getX()) && (p1.getX() < m_points[3].getX())) && ((p1.getZ() > m_points[0].getZ()) && (p1.getZ() < m_points[3].getZ()))))
	{
		return true;
	}

	if ((((p2.getX() > m_points[0].getX()) && (p2.getX() < m_points[3].getX())) && ((p2.getZ() > m_points[0].getZ()) && (p2.getZ() < m_points[3].getZ()))))
	{
		return true;
	}

	if ((((p3.getX() > m_points[0].getX()) && (p3.getX() < m_points[3].getX())) && ((p3.getZ() > m_points[0].getZ()) && (p3.getZ() < m_points[3].getZ()))))
	{
		return true;
	}

	if ((((p4.getX() > m_points[0].getX()) && (p4.getX() < m_points[3].getX())) && ((p4.getZ() > m_points[0].getZ()) && (p4.getZ() < m_points[3].getZ()))))
	{
		return true;
	}

	if ((((p5.getX() > m_points[0].getX()) && (p5.getX() < m_points[3].getX())) && ((p5.getZ() > m_points[0].getZ()) && (p5.getZ() < m_points[3].getZ()))))
	{
		return true;
	}

	if ((((p6.getX() > m_points[0].getX()) && (p6.getX() < m_points[3].getX())) && ((p6.getZ() > m_points[0].getZ()) && (p6.getZ() < m_points[3].getZ()))))
	{
		return true;
	}

	return false;
}