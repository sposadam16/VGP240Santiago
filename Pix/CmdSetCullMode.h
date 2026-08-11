#pragma once
#include "Command.h"

class CmdSetCullMode : public Command
{
public:
    const char* GetName() override {
        return "SetCullMode";
    }
    const char* GetDescription() override {
        return
            "SetCullMode(cullMode)\n"
            "\n"
            "- sets cull mode for rendering\n"
            "- <none>  : no cull mode used\n"
            "- <back>  : cull faces pointed away from camera\n"
            "- <front> : cull faces pointed at the camera\n";
    }
    bool Execute(const std::vector<std::string>& params) override;
private:

};

