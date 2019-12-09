
#include "../Include/CQuadTreeNode.h"

CQuadTreeNode::CQuadTreeNode()
{
	pData = nullptr;
}

CQuadTreeNode::~CQuadTreeNode(){}

void CQuadTreeNode::subdivide(int limit, AABB_2D parentBounds, std::vector<CHexCell*> cells)
{
	int tricount = 0;
	for (int i = 0; i < cells.size(); i++)
	{
		tricount += cells[i]->getTriangleCount();
	}
	if (cells.size() == 1 || tricount <= limit)
	{
		//Copiar elementos de cells a mData
		if (mData.size() > 0)
		{
			mData = cells;
		}		
		h1 = h2 = h3 = h4 = nullptr;
	}
	else
	{
		CVector3 corners[4];
		AABB_2D childBounds[4];

		parentBounds.getCorners(corners);
		corners[1].X /= 2;
		corners[3].X /= 2;
		corners[2].Z /= 2;
		corners[3].Z /= 2;
		childBounds[0].setCorners(corners);

		parentBounds.getCorners(corners);
		corners[0].X /= 2;
		corners[2].X /= 2;
		corners[2].Z /= 2;
		corners[3].Z /= 2;
		childBounds[1].setCorners(corners);

		parentBounds.getCorners(corners);
		corners[1].X /= 2;
		corners[3].X /= 2;
		corners[0].Z /= 2;
		corners[1].Z /= 2;
		childBounds[2].setCorners(corners);

		parentBounds.getCorners(corners);
		corners[0].X /= 2;
		corners[2].X /= 2;
		corners[1].Z /= 2;
		corners[0].Z /= 2;
		childBounds[3].setCorners(corners);

		h1 = new CQuadTreeNode();
		h1->setBounds(childBounds[0]);
		h2 = new CQuadTreeNode();
		h2->setBounds(childBounds[1]);
		h3 = new CQuadTreeNode();
		h3->setBounds(childBounds[2]);
		h4 = new CQuadTreeNode();
		h4->setBounds(childBounds[3]);

		std::vector<CHexCell *> childCells[4];
		for (int i = 0; i < cells.size(); ++i)
		{
			CHexCell *cell = cells[i];
			CVector3 corners[6];
			for (int x = 0; x < 6; x++)
			{
				corners[x] = cell->getCorner(x + 1);
			}
			
			//Obtener esquinas de la celda
			if (childBounds[0].pointsInside(corners))
			{
				childCells[0].push_back(cell);
			}
			if (childBounds[1].pointsInside(corners))
			{
				childCells[1].push_back(cell);
			}
			if (childBounds[2].pointsInside(corners))
			{
				childCells[2].push_back(cell);
			}
			if (childBounds[3].pointsInside(corners))
			{
				childCells[3].push_back(cell);
			}
		}
		h1->subdivide(limit, childBounds[0], childCells[0]);
		h2->subdivide(limit, childBounds[1], childCells[1]);		
		h3->subdivide(limit, childBounds[2], childCells[2]);
		h4->subdivide(limit, childBounds[3], childCells[3]);
		//h2,h3,h4
	}
}

void CQuadTreeNode::firstsubdivide(int limit, AABB_2D parentBounds, CHexCell** cells, int r, int c)
{
	int tricount = 0;
	for (int i = 0; i < r; i++)
	{
		for (int j  = 0; j < c; j++)
		{
			tricount += cells[i][j].getTriangleCount();
		}		
	}
	if ( (r * c) == 1 || tricount <= limit)
	{
		//Copiar elementos de cells a mData
		pData = cells;
		h1 = h2 = h3 = h4 = nullptr;
	}
	else
	{
		CVector3 corners[4];
		AABB_2D childBounds[4];

		parentBounds.getCorners(corners);
		corners[1].X /= 2;
		corners[3].X /= 2;
		corners[2].Z /= 2;
		corners[3].Z /= 2;
		childBounds[0].setCorners(corners);		

		parentBounds.getCorners(corners);
		corners[0].X /= 2;
		corners[2].X /= 2;
		corners[2].Z /= 2;
		corners[3].Z /= 2;
		childBounds[1].setCorners(corners);

		parentBounds.getCorners(corners);
		corners[1].X /= 2;
		corners[3].X /= 2;
		corners[0].Z /= 2;
		corners[1].Z /= 2;
		childBounds[2].setCorners(corners);

		parentBounds.getCorners(corners);
		corners[0].X /= 2;
		corners[2].X /= 2;
		corners[1].Z /= 2;
		corners[0].Z /= 2;
		childBounds[3].setCorners(corners);

		h1 = new CQuadTreeNode();
		h1->setBounds(childBounds[0]);
		h2 = new CQuadTreeNode();
		h2->setBounds(childBounds[1]);
		h3 = new CQuadTreeNode();
		h3->setBounds(childBounds[2]);
		h4 = new CQuadTreeNode();
		h4->setBounds(childBounds[3]);

		std::vector<CHexCell *> childCells[4];
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				CHexCell *cell = &cells[i][j];
				CVector3 corners[6];
				for (int  x = 0; x < 6; x++)
				{
					corners[x] = cell->getCorner(x + 1);
				}
				
				//Obtener esquinas de la celda
				if (childBounds[0].pointsInside(corners))
				{
					childCells[0].push_back(cell);
				}
				if (childBounds[1].pointsInside(corners))
				{
					childCells[1].push_back(cell);
				}
				if (childBounds[2].pointsInside(corners))
				{
					childCells[2].push_back(cell);
				}
				if (childBounds[3].pointsInside(corners))
				{
					childCells[3].push_back(cell);
				}
				//Igual para 1...3
			}			
		}
		h1->subdivide(limit, childBounds[0], childCells[0]);
		h2->subdivide(limit, childBounds[1], childCells[1]);
		h3->subdivide(limit, childBounds[2], childCells[2]);
		h4->subdivide(limit, childBounds[3], childCells[3]);
		//h2,h3,h4
	}
}

void CQuadTreeNode::render(CCamera * cam, COpenGLRenderer * Renderer, unsigned int & ColorModelShaderID)
{
	if (pData != nullptr)
	{
		float color[3] = { 0.0f, 0.3f, 0.0f };
		MathHelper::Matrix4 AABBMatrix;
		double totalDegreesRotatedRadians = 0.0f * PI_OVER_180;
		CVector3 Position = { 0.0f, 0.0f, 0.0f };//{ m_bounds.m_points[4].getX() / 2, 0.0f, m_bounds.m_points[4].getZ() / 2 };
		AABBMatrix = MathHelper::SimpleModelMatrixRotationTranslation(totalDegreesRotatedRadians, Position);
		Renderer->renderObject(
			&ColorModelShaderID,
			&m_bounds.VAO,
			0,
			2,
			color,
			&AABBMatrix,
			COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES,
			false);
	}
	else if (h1 != nullptr && h2 != nullptr && h3 != nullptr && h4 != nullptr)
	{
		h1->render(cam, Renderer, ColorModelShaderID);
		h2->render(cam, Renderer, ColorModelShaderID);
		h3->render(cam, Renderer, ColorModelShaderID);
		h4->render(cam, Renderer, ColorModelShaderID);
		float color[3] = { 0.0f, 0.3f, 0.0f };
		double totalDegreesRotatedRadians = 0.0f * PI_OVER_180;
		MathHelper::Matrix4 AABBMatrix;
		CVector3 Position = { 0.0f, 0.0f, 0.0f };//{m_bounds.m_points[3].getX() / 2, 0.0f, m_bounds.m_points[3].getZ() / 2};
		AABBMatrix = MathHelper::SimpleModelMatrixRotationTranslation(totalDegreesRotatedRadians, Position);
		Renderer->renderObject(
			&ColorModelShaderID,
			&m_bounds.VAO,
			0,
			2,
			color,
			&AABBMatrix,
			COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES,
			false);
	}
	else if (mData.size() > 0)
	{
		float color[3] = { 0.0f, 0.3f, 0.0f };
		MathHelper::Matrix4 AABBMatrix;
		double totalDegreesRotatedRadians = 0.0f * PI_OVER_180;
		CVector3 Position = { 0.0f, 0.0f, 0.0f };//{ m_bounds.m_points[4].getX() / 2, 0.0f, m_bounds.m_points[4].getZ() / 2 };
		AABBMatrix = MathHelper::SimpleModelMatrixRotationTranslation(totalDegreesRotatedRadians, Position);
		Renderer->renderObject(
			&ColorModelShaderID,
			&m_bounds.VAO,
			0,
			2,
			color,
			&AABBMatrix,
			COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES,
			false);
	}
}

void CQuadTreeNode::setBounds(AABB_2D data)
{
	m_bounds = data;
}

void CQuadTreeNode::getBounds(){}

void CQuadTreeNode::setLimits(AABB_2D data)
{
	m_bounds = data;
}

bool CQuadTreeNode::loadNodeToGeometry(COpenGLRenderer *  Renderer, unsigned int & ColorModelShaderID)
{
	bool loaded = Renderer->allocateGraphicsMemoryForObject(
		&ColorModelShaderID,
		&m_bounds.VAO,
		m_bounds.Vertices,
		4,
		m_bounds.Normal,
		2,
		m_bounds.VertexUV,
		4,
		m_bounds.FaceIndex,
		2,
		m_bounds.FaceNormalIndex,
		2,
		m_bounds.FaceIndex,
		2);
	if (!loaded)
	{
		Renderer->freeGraphicsMemoryForObject(&m_bounds.VAO);
	}
	return loaded;
}
