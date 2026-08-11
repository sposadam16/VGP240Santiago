#include "CmdSetCullMode.h"
#include "PrimitivesManager.h"


bool CmdSetCullMode::Execute(const std::vector<std::string>& params)
{
    if (params.size() < 1)
    {
        return false;
    }

    CullMode mode = CullMode::None;
    if (params[0] == "none") { mode = CullMode::None; }
    else if (params[0] == "back") { mode = CullMode::Back; }
    else if (params[0] == "front") { mode = CullMode::Front; }
    else { return false; }

    PrimitivesManager::Get()->SetCullMode(mode);
    return true;
}
