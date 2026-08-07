#include "Camera.h"

extern float gResolutionX;
extern float gResolutionY;

Camera* Camera::Get()
{
	static Camera sInstance;
	return &sInstance;
}
void Camera::OnNewFrame()
{
	mPosition = {0.0f, 0.0f, 0.0f};
	mDirection = {0.0f, 0.0f, 1.0f};
	mNearPlane = 0.01f;
	mFarPlane = 100.0f;
	mFOV = 1.57f;
}
void Camera::SetPosition(const Vector3& pos) 
{
	mPosition = pos;
}
void Camera::SetDirection(const Vector3& dir) 
{
	mDirection = MathHelper::Normalize(dir);
}
void Camera::SetNearPlane(float nearPlane)
{
	mNearPlane = nearPlane;
}
void Camera::SetFarPlane(float farPlane) 
{
	mFarPlane = farPlane;
}
void Camera::SetFOV(float fov) 
{
	mFOV = fov;
}
Matrix4 Camera::GetViewMatrix() const 
{
	const Vector3 l = mDirection;
	const Vector3 r = MathHelper::Normalize(MathHelper::Cross({ 0.0f, 1.0f, 0.0f }, l));
	const Vector3 u = MathHelper::Normalize(MathHelper::Cross(l,r));
	float a = -MathHelper::Dot(r, mPosition);
	float b = -MathHelper::Dot(u, mPosition);
	float c = -MathHelper::Dot(l, mPosition);
	return {
		r.x, u.x, l.x, 0.0f,
		r.y, u.y, l.y, 0.0f,
		r.z, u.z, l.z, 0.0f,
		a  ,   b,   c, 1.0f
	};

}
Matrix4 Camera::GetProjectionMatrix() const 
{
	const float a = gResolutionX / gResolutionY;
	const float d = 1.0f / tanf(mFOV * 0.5f);
	const float w = d / a;
	const float zn = mNearPlane;
	const float zf = mFarPlane;
	const float q = zf / (zf - zn);
	return {
		w, 0.0f, 0.0f, 0.0f,
		0.0f, d, 0.0f, 0.0f,
		0.0f, 0.0f, q, 1.0f,
		0.0f, 0.0f, -zn * q, 0.0f
	};
}
const Vector3& Camera::GetPosition() const 
{
	return mPosition;
}
const Vector3& Camera::GetDirection() const 
{
	return mDirection;
}