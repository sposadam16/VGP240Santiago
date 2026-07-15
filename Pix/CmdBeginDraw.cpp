#include "CmdBeginDraw.h"
#include "PrimitivesManager.h"

bool CmdBeginDraw::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1) {
		return false;
	}
	Topology topology = Topology::Point;
	if(params[0] == "point") {
		topology = Topology::Point;
	}
	else if (params[0] == "line") {
		topology = Topology::Line;
	}
	else if (params[0] == "triangle") {
		topology = Topology::Triangle;
	}
	else {
		return false;
	}
	PrimitivesManager::Get()->BeginDraw(topology);
	return true;
}