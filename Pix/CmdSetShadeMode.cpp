#include "CmdSetShadeMode.h"
#include "Rasterizer.h"

bool CmdSetShadeMode::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	ShadeMode shadeMode = ShadeMode::Flat;
	if (params[0] == "flat")
	{
		shadeMode = ShadeMode::Flat;
	}
	else if (params[0] == "gouraud")
	{
		shadeMode = ShadeMode::Gouraud;
	}
	else if (params[0] == "phong")
	{
		shadeMode = ShadeMode::Phong;
	}
	else {
		return false;
	}

	Rasterizer::Get()->SetShadeMode(shadeMode);
	return true;
}
