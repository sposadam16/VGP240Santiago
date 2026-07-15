#pragma once
#include "Command.h"

class CmdVertex : public Command
{
	public:
		const char* GetName() override { return "Vertex"; }
		const char* GetDescription() override
		{
			return "Vertex (x,y)\n"
				"Vertex (x,y,z)\n"
				"Vertex(x,y,r,g,b)\n"
				"Vertex(x,y,z,r,g,b)\n"
				"\n"
				" - Adds vertex to the primitives manager before render\n";
		}
		bool Execute(const std::vector<std::string>& params) override;	
};

