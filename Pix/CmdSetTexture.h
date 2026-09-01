#pragma once

#include "Command.h"

class CmdSetTexture : public Command
{
public:
    const char* GetName() override
    {
        return "SetTexture";
    }

    const char* GetDescription() override
    {
        return
            "SetTexture(fileName)\n"
            "\n"
            "- sets texture to use when using uv coordinates";
    }

    bool Execute(const std::vector<std::string>& params) override;
};