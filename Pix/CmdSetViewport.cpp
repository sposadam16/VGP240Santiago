#include "CmdSetViewport.h"
#include "Viewport.h"

bool CmdSetViewport::Execute(const std::vector<std::string>& params) {
	if (params.size() < 4) {
		return false;
	}
	float x = stof(params[0]);
	float y = stof(params[1]);
	float width = stof(params[2]);
	float height = stof(params[3]);
	bool show = params.size() >= 5 && params[4] == "true";

	Viewport::Get()->SetViewport(x, y, width, height);
	Viewport::Get()->ShowViewport(show);
	return true;
}
