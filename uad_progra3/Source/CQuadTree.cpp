#include "../Include/CQuadTree.h"

CQuadTree::CQuadTree()
{
	m_root = nullptr;
}

CQuadTree::~CQuadTree(){}

void CQuadTree::Subdivide(CHexCell** container, AABB_2D BoundingBox, int rows, int columns, int limit)
{
	if (m_root == nullptr)
	{
		m_root = new CQuadTreeNode();
		m_limitSubdiv = limit;
		m_root->setLimits(BoundingBox);
		m_root->firstsubdivide(m_limitSubdiv, BoundingBox, container, rows, columns);
	}
}

bool CQuadTree::loadTreeGeometry(COpenGLRenderer * ObjectRenderer, unsigned int & CMSID)
{
	if (m_root != nullptr)
	{
		m_root->loadNodeToGeometry(ObjectRenderer, CMSID);
		return true;
	}
	return false;
}
