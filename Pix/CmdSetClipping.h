#pragma once
#include "Command.h"
class CmdSetClipping : public Command
{
public:
	const char* GetName() override
	{
		return "SetClipping";
	}
	const char* GetDescription() override
	{
		return "SetClippingEnable)\n";
		"\n";
		"- Enables/disables clipping outside viewport";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

