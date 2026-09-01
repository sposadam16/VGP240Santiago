#pragma once

#include "Command.h"

class CmdSetAddressMode : public Command
{
public:
    const char* GetName() override
    {
        return "SetAddressMode";
    }

    const char* GetDescription() override
    {
        return
            "SetAddressMode(mode)\n"
            "\n"
            "- sets address mode for uv coordinates\n"
            "- <border> sets a color if outside of 0-1\n"
            "- <clamp> maintains edge color if outside of 0-1\n"
            "- <wrap> repeats uv color if outside of 0-1\n"
            "- <mirror> flips and repeats uv color if outside of 0-1\n";
    }

    bool Execute(const std::vector<std::string>& params) override;
};
