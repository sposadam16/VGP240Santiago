#include "CmdVarInt.h"

#include "VariableCache.h"
bool CmdVarInt::Execute(const std::vector<std::string>& params)
{
	// Need at leaset 3 params for name, =, value
	if (params.size() < 3)
		return false;

	auto vc = VariableCache::Get();
	if (!vc->IsVarName(params[0]) || params[1] != "=")
		return false;

	const int value = std::stoi(params[2]);
	const float speed = params.size() > 3 ? std::stof(params[3]) : 0.01f;
	const int min = params.size() > 4 ? std::stoi(params[4]) : -FLT_MAX;
	const int max = params.size() > 5 ? std::stoi(params[5]) : FLT_MAX;

	// Register variable
	vc->AddInt(params[0], value, speed, min, max);
	return true;
}