#include "CmdEndDraw.h"
#include "PrimitivesManager.h"

bool CmdEndDraw::Execute(const std::vector<std::string>& params)
{
	PrimitivesManager::Get()->EndDraw();
	return true;
}