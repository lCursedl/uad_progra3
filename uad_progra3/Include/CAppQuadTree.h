#pragma once

#ifndef CAPPQUADTREE_H
#define CAPPQUADTREE_H

#include "Globals.h"
#include "CApp.h"
#include "CHexGrid.h"
#include "CQuadTree.h"

class CAppQuadTree : public CApp
{
public:
	CAppQuadTree();
	CAppQuadTree(int window_width, int window_height);
	~CAppQuadTree();

	void initialize();
	void update(double delta_time);
	void run();
	void render();

	bool initializeMenu() { return false; }

	void onArrowUp(int mods);
	void onArrowDown(int mods);
	void onArrowLeft(int mods);
	void onArrowRight(int mods);

	bool StartGridThread();

private:

	CHexGrid * mGrid;

	DWORD ThreadID[2];

	HANDLE GridThread;

	bool m_initialized;

	CVector3 m_objectPosition;

	double m_currentDeltaTime;

	double m_objectRotation;

	double m_rotationSpeed;

	int m_renderPolygonMode;

	AABB_2D mainBB;

	CQuadTree QT;

	void onF3(int mods);

	void moveCamera(float direction);

	unsigned int m_VAO;
	unsigned int AABB_VAO;
	unsigned int m_colorModelShaderID;
	unsigned int m_textureModelShaderID;
};
#endif // !CAPPQUADTREE_H