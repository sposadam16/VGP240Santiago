#pragma once

#include "Command.h"

class CmdSetUseFilter : public Command
{
public:
    const char* GetName() override
    {
        return "SetUseFilter";
    }

    const char* GetDescription() override
    {
        return
            "SetUseFilter(useFilter)\n"
            "\n"
            "- enable/disable using bilinear filter on textures";
    }

    bool Execute(const std::vector<std::string>& params) override;
};

