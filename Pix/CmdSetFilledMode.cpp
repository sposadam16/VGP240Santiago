#include "CmdSetFilledMode.h"
#include "Rasterizer.h"

bool CmdSetFilledMode::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1) {
		return false;
	}
	 
	FillMode fillMode = FillMode::Wireframe;
	if (params[0] == "WireFrame")
	{
		fillMode = FillMode::Wireframe;
	}
	else if (params[0] == "solid")
	{
		fillMode = FillMode::Solid;
	}
	else
	{
		return false;
	}

	Rasterizer::Get()->SetFillMode(fillMode);
	return true;
}