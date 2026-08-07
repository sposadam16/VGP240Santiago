#pragma once
#include "Command.h"
class CmdPushTranslation : public Command
{
public:
	const char* GetName() override 
	{ 
		return "PushTranslation";
	}
	const char* GetDescription() override 
	{ 
		return "Push a translation matrix onto the stack.\n";
		"\n"
			"pushes a tranlation matrix onto the stack.\n";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushRotationX : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationX";
	}
	const char* GetDescription() override
	{
		return "Push a rotation matrix around the X axis onto the stack.\n";
		"\n"
			"pushes a rotation matrix around the X axis onto the stack.\n";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushRotationY : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationY";
	}
	const char* GetDescription() override
	{
		return "Push a rotation matrix around the Y axis onto the stack.\n";
		"\n"
			"pushes a rotation matrix around the Y axis onto the stack.\n";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushRotationZ : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationZ";
	}
	const char* GetDescription() override
	{
		return "Push a rotation matrix around the Z axis onto the stack.\n";
		"\n"
			"pushes a rotation matrix around the Z axis onto the stack.\n";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushScaling : public Command
{
public:
	const char* GetName() override
	{
		return "PushScaling";
	}
	const char* GetDescription() override
	{
		return "Push a scaling matrix onto the stack.\n";
		"\n"
			"pushes a scaling matrix onto the stack.\n";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPopMatrix : public Command
{
public:
	const char* GetName() override
	{
		return "PopMatrix";
	}
	const char* GetDescription() override
	{
		return "Pop a matrix from the stack.\n";
		"\n"
			"pops a matrix from the stack.\n";
	}
	bool Execute(const std::vector<std::string>& params) override;
};