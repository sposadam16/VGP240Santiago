#pragma once
#include "Command.h"

class CmdSetColor : public Command
{
public: 
	const char* GetName() override { return "SetColor"; }
	const char* GetDescription() override {
		return
			"Set Color(r,g,b)\n"; 
			"\n"; 
			"Sets the Color of the next pixel using red,green and blue\n"; 
			"Values are from 0.0 to 1.0\n"; 
	}

	bool Execute(const std::vector<std::string>& params) override;
};

