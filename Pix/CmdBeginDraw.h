#pragma once
#include "Command.h"	
class CmdBeginDraw : public Command
{
public:
	const char* GetName() override { return "BeginDraw"; }
	
	const char* GetDescription() override 
	{
		return "BeginDraw (Topology)\n"
			"\n"
			"- start storing vertices\n"
			"- topology(point,line,triangle)\n";

	; }
	bool Execute(const std::vector<std::string>& params) override;
};

