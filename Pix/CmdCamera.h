#pragma once

#include "Command.h"
class CmdSetCameraPosition : public Command
{
public:
		const char* GetName() override
		{
			return "SetCameraPosition";
		}
		const char* GetDescription() override
		{
			return "Sets the camera position(x, y, z).\n"
				"\n"
				"  sets The camera position in the scene.\n";

		}
		bool Execute(const std::vector<std::string>& params) override;
};
class CmdSetCameraDirection : public Command
{
public:
		const char* GetName() override
		{
			return "SetCameraDirection";
		}
		const char* GetDescription() override
		{
			return "Sets the camera direction(x, y, z).\n"
				"\n"
				"  sets The camera direction in the scene, normalize when set.\n";

		}
		bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetCameraNear : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraNear";
	}
	const char* GetDescription() override
	{
		return "Sets the camera Near(Near Plane).\n"
			"\n"
			"  sets the near plane distance for the camera.\n";

	}
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetCameraFar : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraFar";
	}
	const char* GetDescription() override
	{
		return "Sets the camera Far(Far Plane).\n"
			"\n"
			"  sets the far plane distance for the camera.\n";

	}
	bool Execute(const std::vector<std::string>&params) override;
};

class CmdSetCameraFOV : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraFOV";
	}
	const char* GetDescription() override
	{
		return "Sets the camera FOV(Field of View).\n"
			"\n"
			"  sets the camera field of view in degrees.\n";

	}
	bool Execute(const std::vector<std::string>& params) override;
};