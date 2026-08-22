#include "CmdLights.h"
#include "LightManager.h"
#include "VariableCache.h"

bool CmdSetLightAmbient::Execute(const std::vector<std::string>& params) 
{
	if (params.size() < 3)
	{
		return false;
	}
	VariableCache* vc = VariableCache::Get();
	float r = vc->GetFloat(params[0]);
	float g = vc->GetFloat(params[1]);
	float b = vc->GetFloat(params[2]);
	LightManager::Get()->SetLightAmbient({ r, g, b, 1.0f });

	return true;

}
bool CmdSetLightDiffuse::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 3)
	{
		return false;
	}
	VariableCache* vc = VariableCache::Get();
	float r = vc->GetFloat(params[0]);
	float g = vc->GetFloat(params[1]);
	float b = vc->GetFloat(params[2]);
	LightManager::Get()->SetLightDiffuse({ r, g, b, 1.0f });

	return true;
}
bool CmdSetLightSpecular::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 3)
	{
		return false;
	}
	VariableCache* vc = VariableCache::Get();
	float r = vc->GetFloat(params[0]);
	float g = vc->GetFloat(params[1]);
	float b = vc->GetFloat(params[2]);
	LightManager::Get()->SetLightSpecular({ r, g, b, 1.0f });

	return true;
}

bool CmdAddDirectionalLight::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 3)
	{
		return false;
	}
	VariableCache* vc = VariableCache::Get();
	float x = vc->GetFloat(params[0]);
	float y = vc->GetFloat(params[1]);
	float z = vc->GetFloat(params[2]);
	LightManager::Get()->AddDirectionalLight({ x, y, z});
	return true;
}

bool CmdAddPointLight::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 3)
	{
		return false;
	}
	VariableCache* vc = VariableCache::Get();
	float x = vc->GetFloat(params[0]);
	float y = vc->GetFloat(params[1]);
	float z = vc->GetFloat(params[2]);
	float kConstant = (params.size() > 3) ? vc->GetFloat(params[3]) : 1.0f;
	float kLinear = (params.size() > 4) ? vc->GetFloat(params[4]) : 0.0f;
	float kQuadratic = (params.size() > 5) ? vc->GetFloat(params[5]) : 0.0f;
	LightManager::Get()->AddPointLight({ x, y, z }, kConstant, kLinear, kQuadratic);
	return true;
}

bool CmdAddSpotLight::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 3)
	{
		return false;
	}
	VariableCache* vc = VariableCache::Get();
	float x = vc->GetFloat(params[0]);
	float y = vc->GetFloat(params[1]);
	float z = vc->GetFloat(params[2]);
	float kConstant = (params.size() > 3) ? vc->GetFloat(params[3]) : 1.0f;
	float kLinear = (params.size() > 4) ? vc->GetFloat(params[4]) : 0.0f;
	float kQuadratic = (params.size() > 5) ? vc->GetFloat(params[5]) : 0.0f;
	LightManager::Get()->AddPointLight({ x, y, z }, kConstant, kLinear, kQuadratic);
	return true;
}
