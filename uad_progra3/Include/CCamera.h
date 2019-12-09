#pragma once
#include "CAABB_2D.h"
#include "CFrustum.h"

class CCamera
{
public:
	CCamera();
	~CCamera();

	void updateFramebufferSize(int w, int h);
	void moveForward(float deltaMove);
	void moveUp(float deltaMove);
	void strafe(float deltaMove);
	void orbitAroundLookAt(float deltaMove);
	bool isAABBvisible(AABB_2D &aabb);

private:
	CVector3 m_worldUP;
	CVector3 m_eyePos;
	CVector3 m_lookAt;
	CVector3 m_up;
	CVector3 m_right;

	int m_frameBufferWidth;
	int m_frameBufferHeight;
	float m_fieldOfView;
	float m_nearPlane;
	float m_farPlane;

	void recalculateViewMatrix();
	void recalculateProjectionMatrix();
	void recalculateViewFrustum();

	MathHelper::Matrix4 m_projectionMatrix;
	MathHelper::Matrix4 m_viewMatrix;

	CFrustum m_viewFrustum;

	bool m_cacheValid;
};