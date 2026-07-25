#include "CmdSetClipping.h"
#include "Clipper.h"

bool CmdSetClipping::Execute(const std::vector<std::string>& params) 
{
	if (params.size() < 1) {

	return false;
	}
	bool enable = params[0] == "true";
	Clipper::Get()->SetClipping(enable);
	return true;
}