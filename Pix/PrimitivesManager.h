#pragma once
#include "Vertex.h"
enum class Topology
{
	Point,
	Line,
	Triangle
};

class PrimitivesManager
{
public:
	static PrimitivesManager* Get();

	//Start accepting Vertices
	bool BeginDraw(Topology topology);

	void AddVertex(const Vertex& v);

	void EndDraw();

private:
	PrimitivesManager();
	std::vector<Vertex> mVertexBuffer;
	Topology mTopology = Topology::Point;
	bool mbDrawBegin = false;
};

