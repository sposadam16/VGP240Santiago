#include "LightTypes.h"
#include "MaterialManager.h"
#include "Camera.h"

#include <cmath>


X::Color DirectionalLight::ComputeLightColor(const Vector3& position, const Vector3& normal)
{
	Camera* camera = Camera::Get();
	MaterialManager* mm = MaterialManager::Get();

	//calculate ambient color

	X::Color ambient = mAmbient * mm->GetMaterialAmbient();

	Vector3 L = -mDirection;
	float dot = X::Math::Max(MathHelper::Dot(L, normal), 0.0f);
	X::Color diffuse = mDiffuse * mm->GetMaterialDiffuse() * dot;

	//calculate specular color	
	Vector3 viewDirection = MathHelper::Normalize(camera->GetPosition() - position);
	Vector3 reflectedLight = MathHelper::Normalize(L + viewDirection);
	float specularAngle = X::Math::Max(MathHelper::Dot(reflectedLight, normal), 0.0f);
	float falloff = std::pow(specularAngle, mm->GetMaterialShininess());
	X::Color specular = mSpecular * mm->GetMaterialSpecular() * falloff;

	return ambient + diffuse + specular;

}
void DirectionalLight::SetDirection(const Vector3& direction)
{
	mDirection = MathHelper::Normalize(direction);
}


X::Color PointLight::ComputeLightColor(const Vector3& position, const Vector3& normal)
{
	Camera* camera = Camera::Get();
	MaterialManager* mm = MaterialManager::Get();


	//calculate ambient color
	Vector3 L = mPosition - position;
	float distance = MathHelper::Magnitude(L);
	L /= distance;

	//calculate iL
	float attenuation = 1.0f / (mKConstant + (mKLinear * distance) + (mKQuadratic * distance * distance));
	float iL = X::Math::Clamp(attenuation, 0.0f, 1.0f);


	//ambient color
	X::Color ambient = mAmbient * mm->GetMaterialAmbient();
	//diffuse color
	float dot = X::Math::Max(MathHelper::Dot(L, normal), 0.0f);
	X::Color diffuse = mDiffuse * mm->GetMaterialDiffuse() * dot * iL;

	//calculate specular color	
	Vector3 viewDirection = MathHelper::Normalize(camera->GetPosition() - position); 
	Vector3 reflectedLight = MathHelper::Normalize(L + viewDirection);
	float specularAngle = X::Math::Max(MathHelper::Dot(reflectedLight, normal), 0.0f);
	float falloff = std::pow(specularAngle, mm->GetMaterialShininess());
	X::Color specular = mSpecular * mm->GetMaterialSpecular() * falloff * iL;

	return ambient + diffuse + specular;
}
void PointLight::SetPosition(const Vector3& position)
{
	mPosition = position;
}
void PointLight::SetAttenuation(float kConstant, float kLinear, float kQuadratic)
{
	mKConstant = kConstant;
	mKLinear = kLinear;
	mKQuadratic = kQuadratic;
}

X::Color SpotLight::ComputeLightColor(const Vector3& position, const Vector3& normal)
{
	Camera* camera = Camera::Get();
	MaterialManager* mm = MaterialManager::Get();


	//calculate ambient color
	Vector3 L = mPosition - position;
	float distance = MathHelper::Magnitude(L);
	L /= distance;

	//ambient color
	X::Color ambient = mAmbient * mm->GetMaterialAmbient();

	//check to see if position is in the cone
	Vector3 lightDir = -L;//light direction to the point
	float dotDir = MathHelper::Dot(lightDir, mDirection);
	if (dotDir < mCosAngle)
	{
		return ambient;
	}

	//calculate iL
	float spot = pow(dotDir, mDecay);
	float attenuation = spot / (mKConstant + (mKLinear * distance) + (mKQuadratic * distance * distance));
	float iL = X::Math::Clamp(attenuation, 0.0f, 1.0f);


	//diffuse color
	float dot = X::Math::Max(MathHelper::Dot(L, normal), 0.0f);
	X::Color diffuse = mDiffuse * mm->GetMaterialDiffuse() * dot * iL;

	//calculate specular color	
	Vector3 viewDirection = MathHelper::Normalize(camera->GetPosition() - position);
	Vector3 reflectedLight = MathHelper::Normalize(L + viewDirection);
	float specularAngle = X::Math::Max(MathHelper::Dot(reflectedLight, normal), 0.0f);
	float falloff = std::pow(specularAngle, mm->GetMaterialShininess());
	X::Color specular = mSpecular * mm->GetMaterialSpecular() * falloff * iL;

	return ambient + diffuse + specular;
}
void SpotLight::SetPosition(const Vector3& position)
{
	mPosition = position;

}
void SpotLight::SetDirection(const Vector3& direction)
{
	mDirection = MathHelper::Normalize(direction);
}
void SpotLight::SetAttenuation(float kConstant, float kLinear, float kQuadratic)
{
	mKConstant = kConstant;
	mKLinear = kLinear;
	mKQuadratic = kQuadratic;
}
void SpotLight::SetAngle(float angle)
{
	mCosAngle = cos(angle);
}
void SpotLight::SetDecay(float decay)
{
	mDecay = decay;
}