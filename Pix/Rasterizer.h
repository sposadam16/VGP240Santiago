#pragma once

#include <XEngine.h>
#include "Vertex.h"
enum class FillMode
{
	Wireframe,
	Solid
};
enum class ShadeMode
{
	Flat,		//per face lighting
	Gouraud,	//per vertex lighting
	Phong		//per pixel lighting
};
class Rasterizer
{
public:
	static Rasterizer* Get();

public:
	void SetColor(X::Color color);
	void SetFillMode(FillMode fillMode);
	void SetShadeMode(ShadeMode shadeMode);
	ShadeMode GetShadeMode() const;


	void DrawPoint(int x, int y);

	void DrawPoint(const Vertex& v);
	void DrawLine(const Vertex& a, const Vertex& b);
	void DrawTriangle(const Vertex& a, const Vertex& b, const Vertex& c);
private:
	void DrawFilledTriangle(const Vertex& a, const Vertex& b, const Vertex& c);
	FillMode mFillMode = FillMode::Solid;
	X::Color mColor = X::Colors::White;
	ShadeMode mShadeMode = ShadeMode::Phong;
};