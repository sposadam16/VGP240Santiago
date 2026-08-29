#pragma once
#include "Command.h"

class CmdSetShadeMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetShadeMode";
	}
	const char* GetDescription() override
	{
		return "SetShadeMOde(<shadeMode>)\n"
		"\n"
		"- sets the lighting shade mode"
		"- flat: per face lighthing"
		"- gouraud: per vertex lighting"
		"- phong: per pixel lighting";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

