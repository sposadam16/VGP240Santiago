#include "CmdSetColor.h"
#include "Rasterizer.h"

bool CmdSetColor::Execute(const std::vector<std::string>& params)
{
	if (params.size() != 3) {
		return false;
	}
	float r = std::stof(params[0]);
	float g = std::stof(params[1]);
	float b = std::stof(params[2]);
	Rasterizer::Get()->SetColor({r, g, b, 1.0f});
	return true;
}
