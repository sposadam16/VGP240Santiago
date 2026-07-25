#include "PrimitivesManager.h"
#include "Rasterizer.h"
#include "Clipper.h"

PrimitivesManager::PrimitivesManager()
{
}
PrimitivesManager* PrimitivesManager::Get()
{
	static PrimitivesManager sInstance;
	return &sInstance;
}
bool PrimitivesManager::BeginDraw(Topology topology)
{
	mVertexBuffer.clear();
	mTopology = topology;
	mbDrawBegin = true;
	return true;
}

void PrimitivesManager::AddVertex(const Vertex& v)
{
	if (mbDrawBegin) {

		mVertexBuffer.push_back(v);
	}
}

void PrimitivesManager::EndDraw() {

	if (!mbDrawBegin) {
		return;

	}
	switch (mTopology)
	{
	case Topology::Point: {
		for (uint32_t i = 0; i < mVertexBuffer.size(); ++i)
		{
			if (!Clipper::Get()->ClipPoint(mVertexBuffer[i])) {
				Rasterizer::Get()->DrawPoint(mVertexBuffer[i]);
			}
		}
		break;
	}
	case Topology::Line: {
		for (uint16_t i = 1; i < mVertexBuffer.size(); i += 2) {
			if (!Clipper::Get()->ClipLine(mVertexBuffer[i - 1], mVertexBuffer[i])) {
				Rasterizer::Get()->DrawLine(mVertexBuffer[i - 1], mVertexBuffer[i]);
			}
		}
		break;
	}
	case Topology::Triangle: {
		for (uint16_t i = 2; i < mVertexBuffer.size(); i += 3) {
			std::vector<Vertex> triangle = {
				mVertexBuffer[i - 2],
				mVertexBuffer[i - 1],
				mVertexBuffer[i ]
			};
			if (!Clipper::Get()->ClipTriangle(triangle))
			{
				for (size_t t = 2; t < triangle.size(); ++t)
				{
				Rasterizer::Get()->DrawTriangle(triangle[0], triangle[t -1], triangle[t]);
				}
					
			}
		}
		break;
	}
	}
}
