#include "Graphics.h"
#include "Clipper.h"
#include "Viewport.h"

void Graphics::NewFrame()
{
	Viewport::Get()->OnNewFrame();
	Clipper::Get()->OnNewFrame();
}