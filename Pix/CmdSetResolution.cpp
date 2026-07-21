#include "CmdSetResolution.h"

#include <XEngine.h>

#include <exception>

float gResolutionX = 0.0f;
float gResolutionY = 0.0f;

bool CmdSetResolution::Execute(const std::vector<std::string>& params)
{
	// Width and height are required; pixel size and grid visibility are optional.
	if (params.size() < 2 || params.size() > 4)
		return false;

	int width;
	int height;
	int pixelSize = 1;
	try
	{
		width = std::stoi(params[0]);
		height = std::stoi(params[1]);
		if (params.size() > 2)
			pixelSize = std::stoi(params[2]);
	}
	catch (const std::exception&)
	{
		return false;
	}

	if (width <= 0 || height <= 0 || pixelSize <= 0)
		return false;

	bool showGrid = false;
	if (params.size() > 3)
	{
		if (params[3] == "true")
			showGrid = true;
		else if (params[3] != "false")
			return false;
	}

	// Cache resolution
	gResolutionX = (float)width;
	gResolutionY = (float)height;

	X::InitRenderTexture(width, height, pixelSize);

	if (showGrid && pixelSize > 1)
		X::DrawScreenGrid(pixelSize, X::Colors::DarkGray);

	return true;
}
