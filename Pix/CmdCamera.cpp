#include "CmdCamera.h"
#include "Camera.h"
#include "VariableCache.h"

bool CmdSetCameraPosition::Execute(const std::vector<std::string>& params) 
{
	if (params.size() < 3)
	{
		return false;
	}
	VariableCache* vc = VariableCache::Get();
	const float x = vc->GetFloat(params[0]);
	const float y = vc->GetFloat(params[1]);
	const float z = vc->GetFloat(params[2]);
	Camera::Get()->SetPosition({ x, y, z });
	return true;
}
bool CmdSetCameraDirection::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 3)
	{
		return false;
	}
	VariableCache* vc = VariableCache::Get();
	const float x = vc->GetFloat(params[0]);
	const float y = vc->GetFloat(params[1]);
	const float z = vc->GetFloat(params[2]);
	Camera::Get()->SetDirection({ x, y, z });
	return true;
}
bool CmdSetCameraNear::Execute(const std::vector<std::string>& params) 
{
	if (params.size() < 1)
	{
		return false;
	}
	const float nearPlane = VariableCache::Get()->GetFloat(params[0]);
	Camera::Get()->SetNearPlane(nearPlane);
	return true;
}
bool CmdSetCameraFar::Execute(const std::vector<std::string>& params) 
{
	if (params.size() < 1)
	{
		return false;
	}
	const float farPlane = VariableCache::Get()->GetFloat(params[0]);
	Camera::Get()->SetFarPlane(farPlane);
	return true;
}
bool CmdSetCameraFOV::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}
	const float fovDegrees = VariableCache::Get()->GetFloat(params[0]);
	Camera::Get()->SetFOV(fovDegrees * MathHelper::DegToRad);
	return true;
}