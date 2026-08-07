#include "Graphics.h"
#include "Clipper.h"
#include "Viewport.h"
#include "MatrixStack.h"
#include "Camera.h"

void Graphics::NewFrame()
{
	Viewport::Get()->OnNewFrame();
	Clipper::Get()->OnNewFrame();
	MatrixStack::Get()->OnNewFrame();
	Camera::Get()->OnNewFrame();
}