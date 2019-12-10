#pragma once
#include "CQuadTreeNode.h"

class CQuadTree
{
public:
	CQuadTree();
	~CQuadTree();

	int m_limitSubdiv;
	int m_limitTris;
	CQuadTreeNode * m_root;

	void Subdivide(CHexCell** container, AABB_2D BoundingBox, int rows, int columns, int trilimit, int sublimit);

	bool loadTreeGeometry(COpenGLRenderer * ObjectRenderer, unsigned int & CMSID);
};