#pragma once
#include "Vertex.h"
enum class Topology
{
	Point,
	Line,
	Triangle
};

enum class CullMode
{
	None,
	Back,
	Front
};
class PrimitivesManager
{
public:
	static PrimitivesManager* Get();

	void OnNewFrame();
	void SetCullMode(CullMode mode);
	void SetCorrectUV(bool correctUV);

	//Start accepting Vertices

	bool BeginDraw(Topology topology, bool applyTransform);

	void AddVertex(const Vertex& v);

	void EndDraw();

private:
	PrimitivesManager();

	bool mApplyTransform = false;
	std::vector<Vertex> mVertexBuffer;
	Topology mTopology = Topology::Point;
	CullMode mCullMode = CullMode::None;
	bool mbDrawBegin = false;
	bool mCorrectUV = false;
};

