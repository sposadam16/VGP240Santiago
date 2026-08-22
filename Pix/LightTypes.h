#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
public:

	X::Color ComputeLightColor(const Vector3& position, const Vector3& normal) override;
	void SetDirection(const Vector3& direction);

private:
	Vector3 mDirection = { 0.0f,0.0f,1.0f };
};

class PointLight : public Light
{
public:

	X::Color ComputeLightColor(const Vector3& position, const Vector3& normal)override;
	void SetPosition(const Vector3& position);
	void SetAttenuation(float kConstant, float kLinear, float kQuadratic);

private:
	Vector3 mPosition = { 0.0f, 0.0f, 0.0f };
	float mKConstant = 1.0f;
	float mKLinear = 1.0f;
	float mKQuadratic = 1.0f;

};

class SpotLight : public Light
{
public:

	X::Color ComputeLightColor(const Vector3& position, const Vector3& normal)override;
	void SetPosition(const Vector3& position);
	void SetDirection(const Vector3& direction);
	void SetAttenuation(float kConstant, float kLinear, float kQuadratic);
	void SetAngle(float angle);
	void SetDecay(float decay);
private:
	Vector3 mPosition = { 0.0f, 0.0f, 0.0f };
	Vector3 mDirection = { 0.0f,0.0f,1.0f };
	float mKConstant = 1.0f;
	float mKLinear = 1.0f;
	float mKQuadratic = 1.0f;
	float mCosAngle = cos(X::Math::kPiByTwo);
	float mDecay = 0.0f;

};