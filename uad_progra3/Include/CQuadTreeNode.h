#pragma once

#ifndef CQUADTREENODE_H
#define CQUADTREENODE_H

#include "Globals.h"
#include "CAABB_2D.h"
#include "CHexGrid.h"
#include "CCamera.h"
#include <vector>
#include "COpenGLRenderer.h"

class CQuadTreeNode
{
public:
	CQuadTreeNode();
	~CQuadTreeNode();

	void subdivide(int limit, AABB_2D parentBounds, std::vector<CHexCell*> cells);
	void firstsubdivide(int limit, AABB_2D parentBounds, CHexCell** cells, int r, int c);
	void render(CCamera *cam, COpenGLRenderer * Renderer, unsigned int & ColorModelShaderID);

	void setBounds(AABB_2D data);
	void getBounds();
	void setLimits(AABB_2D data);

	bool loadNodeToGeometry(COpenGLRenderer * Renderer, unsigned int & ColorModelShaderID);

private:

	CQuadTreeNode * h1;
	CQuadTreeNode * h2;
	CQuadTreeNode * h3;
	CQuadTreeNode * h4;

	AABB_2D m_bounds;
	std::vector<CHexCell *> mData;
	CHexCell** pData;
};
#endif // !CQUADTREENODE_H