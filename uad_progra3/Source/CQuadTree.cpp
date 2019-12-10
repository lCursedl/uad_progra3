#include "../Include/CQuadTree.h"

CQuadTree::CQuadTree()
{
	m_root = nullptr;
}

CQuadTree::~CQuadTree(){}

void CQuadTree::Subdivide(CHexCell** container, AABB_2D BoundingBox, int rows, int columns, int trilimit, int sublimit)
{
	if (m_root == nullptr)
	{
		m_root = new CQuadTreeNode();
		m_limitTris = trilimit;
		m_limitSubdiv = sublimit;
		m_root->setLimits(BoundingBox);
		m_root->firstsubdivide(m_limitTris, BoundingBox, container, rows, columns, 0, m_limitSubdiv);
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
