#pragma once
#include "CQuadTreeNode.h"

class CQuadTree
{
public:
	CQuadTree();
	~CQuadTree();

	int m_limitSubdiv;
	CQuadTreeNode * m_root;

	void Subdivide(CHexCell** container, AABB_2D BoundingBox, int rows, int columns, int limit);

	bool loadTreeGeometry(COpenGLRenderer * ObjectRenderer, unsigned int & CMSID);
};