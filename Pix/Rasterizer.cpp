#include "Rasterizer.h"


void DrawLineHorizontal(const Vertex& left, const Vertex& right) {
	float dx = right.pos.x - left.pos.x;
	int startX = static_cast<int>(left.pos.x);
	int endX = static_cast<int>(right.pos.x);
	for(int x= startX; x <= endX; ++x) {
		float t = static_cast<float>(x - startX) / dx;
		Vertex v = LerpVertex(left, right, t);
		Rasterizer::Get()->DrawPoint(v);
	}
}
void DrawLineVertical(const Vertex& low, const Vertex& high) {
	float dy = high.pos.y - low.pos.y;
	int startY = static_cast<int>(low.pos.y);
	int endY = static_cast<int>(high.pos.y);
	for(int y= startY; y <= endY; ++y) {
		float t = static_cast<float>(y - startY) / dy;
		Vertex v = LerpVertex(low, high, t);
		Rasterizer::Get()->DrawPoint(v);
	}
}

Rasterizer* Rasterizer::Get()
{
	static Rasterizer sInstance;
	return &sInstance;
}

void Rasterizer::SetColor(X::Color color)
{
	mColor = color;
}

void Rasterizer::DrawPoint(int x, int y)
{
	X::DrawPixel(x, y, mColor);
}

void Rasterizer::DrawPoint(const Vertex& v)
{
	X::DrawPixel(v.pos.x, v.pos.y, v.color);
}

void Rasterizer::DrawLine(const Vertex& a, const Vertex& b) {
	float dx = b.pos.x - a.pos.x;
	float dy = b.pos.y - a.pos.y; 

	if(MathHelper::CheckEqual(dx,0.0f) || abs (dy / dx) > 1.0f) {
		if(a.pos.y < b.pos.y) {
			DrawLineVertical(a, b);
		} else {
			DrawLineVertical(b, a);
		}
	} else {
		if(a.pos.x < b.pos.x) {
			DrawLineHorizontal(a, b);
		} else {
			DrawLineHorizontal(b, a);
		}
	}
}
void Rasterizer::SetFillMode (FillMode fillMode) {
	mFillMode = fillMode;
}
void Rasterizer::DrawTriangle(const Vertex& a, const Vertex& b, const Vertex& c) {
	switch (mFillMode)
	{
	case FillMode::Wireframe: {

		DrawLine(a, b);
		DrawLine(b, c);
		DrawLine(c, a);
	}
		break;
	case FillMode::Solid: {

		std::vector<Vertex> sortedVertices = { a, b, c };
		std::sort(sortedVertices.begin(),sortedVertices.end(), [](const Vertex& lhs, const Vertex& rhs) {
			return lhs.pos.y < rhs.pos.y;
		});
		DrawFilledTriangle(sortedVertices[0], sortedVertices[1], sortedVertices[2]);
	}
		break;
	default:
		break;
	}

}
void Rasterizer::DrawFilledTriangle(const Vertex& a, const Vertex& b, const Vertex& c) {

	float dy = c.pos.y - a.pos.y;	
	if (MathHelper::CheckEqual(a.pos.y, b.pos.y)) {
		int startY = static_cast<int>(a.pos.y);
		int endY = static_cast<int>(c.pos.y);
		for (int y = startY; y <= endY; ++y) {
			float t = static_cast<float>(y - startY) / dy;
			Vertex aSide = LerpVertex(a, c, t);
			Vertex bSide = LerpVertex(b, c, t);
			DrawLine(aSide, bSide);
		}
	}
	else if (MathHelper::CheckEqual(b.pos.y, c.pos.y)) {
		int startY = static_cast<int>(a.pos.y);
		int endY = static_cast<int>(c.pos.y);
		for (int y = startY; y <= endY; ++y) {
			float t = static_cast<float>(y - startY) / dy;
			Vertex bSide = LerpVertex(a, b, t);
			Vertex cSide = LerpVertex(a, c, t);
			DrawLine(bSide, cSide);
		}
	}

	else {
		float t = (b.pos.y - a.pos.y) / dy;
		Vertex splitVertex = LerpVertex(a, c, t);
		DrawFilledTriangle(a, b, splitVertex);

		DrawFilledTriangle(b, splitVertex, c);
	}
}


