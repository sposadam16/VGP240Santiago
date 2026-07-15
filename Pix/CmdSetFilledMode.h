#pragma once
#include "Command.h"
class CmdSetFilledMode : public Command
{
	public:
		const char* GetName() { return "SetFillMode"; }
		const char* GetDescription()
		{
			return "SetFilledMode(fillmode)\n"
				"\n"
				"- sets the fill mode (wireframe, solid)\n";
		}
		bool Execute(const std::vector<std::string>& params);
};

