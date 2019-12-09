
#include "../Include/CCamera.h"

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}

void CCamera::updateFramebufferSize(int w, int h)
{
}

void CCamera::moveForward(float deltaMove)
{
}

void CCamera::moveUp(float deltaMove)
{
}

void CCamera::strafe(float deltaMove)
{
}

void CCamera::orbitAroundLookAt(float deltaMove)
{
}

bool CCamera::isAABBvisible(AABB_2D & aabb)
{
	if (!m_cacheValid)
	{
		recalculateViewMatrix();
		recalculateViewFrustum();
	}

	// If the AABB is either completely visible (all corners inside the frustum), or intersecting (at least one corner inside the frustum)
	return (
		m_viewFrustum.isAABBVisible(aabb) == CFrustum::FRUSTUM_VISIBILITY_TEST_RESULT::INTERSECT ||
		m_viewFrustum.isAABBVisible(aabb) == CFrustum::FRUSTUM_VISIBILITY_TEST_RESULT::INSIDE
		);
}

void CCamera::recalculateViewMatrix()
{
}

void CCamera::recalculateProjectionMatrix()
{
}

void CCamera::recalculateViewFrustum()
{
}
