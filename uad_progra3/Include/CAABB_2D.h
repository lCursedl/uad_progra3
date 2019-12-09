#pragma once
#include "MathHelper.h"

class AABB_2D
{
public:
	AABB_2D();
	AABB_2D(CVector3 * data);
	~AABB_2D();

	void getCorners(CVector3 * data);
	void setCorners(CVector3 * data);
	bool pointsInside(CVector3 * data);

	unsigned int VAO;

	float Vertices[12];
	float VertexUV[4];
	unsigned short FaceIndex[6];
	float Normal[6];
	unsigned short FaceNormalIndex[6];
	CVector3 m_points[4];
};