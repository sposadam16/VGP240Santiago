#pragma once

#include "Command.h"

class CmdSetCorrectUV : public Command
{
public:
    const char* GetName() override
    {
        return "SetCorrectUV";
    }

    const char* GetDescription() override
    {
        return
            "SetCorrectUV(correctUV)\n"
            "\n"
            "- enables/disables uv correction when using textures";
    }

    bool Execute(const std::vector<std::string>& params) override;
};

