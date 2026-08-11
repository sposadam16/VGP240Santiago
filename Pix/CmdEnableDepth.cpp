#include "CmdEnableDepth.h"

#include "Rasterizer.h"
#include "DepthBuffer.h"
#include "VariableCache.h"

bool CmdEnableDepth::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
	return false;
	}
	
	bool enable = VariableCache::Get()->GetBool(params[0]);
	DepthBuffer::Get()->SetEnabled(enable);
	return true;
}