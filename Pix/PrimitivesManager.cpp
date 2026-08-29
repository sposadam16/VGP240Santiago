#include "PrimitivesManager.h"
#include "Rasterizer.h"
#include "Clipper.h"
#include "MatrixStack.h"
#include "Camera.h"
#include "LightManager.h"

extern float gResolutionX;
extern float gResolutionY;

namespace 
{
	Matrix4 GetScreenTranform()
	{
		const float hw = gResolutionX * 0.5f;
		const float hh = gResolutionY * 0.5f;
		return {
			hw  , 0.0f, 0.0f, 0.0f,
			0.0f, -hh , 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			hw  , hh  , 0.0f, 1.0f
		};
	}

	Vector3 CreateFaceNormal(const std::vector<Vertex>& triangle) 
	{
		const Vector3& a = triangle[0].pos;
		const Vector3& b = triangle[1].pos;
		const Vector3& c = triangle[2].pos;

		Vector3 norm = MathHelper::Normalize(MathHelper::Cross((b - a), (c - a)));
		return norm;
	}

	bool CullTriangle(CullMode mode, const std::vector<Vertex>& triangle)
	{
		if (mode == CullMode::None)
		{
			return false;
		}
		Vector3 faceNormal = CreateFaceNormal(triangle);
		if (mode == CullMode::Back)
		{
			return faceNormal.z > 0.0f;
		}
		if (mode == CullMode::Front)
		{
			return faceNormal.z < 0.0f;
		}
		return false;
	}
}

PrimitivesManager::PrimitivesManager()
{
}
PrimitivesManager* PrimitivesManager::Get()
{
	static PrimitivesManager sInstance;
	return &sInstance;
}
void PrimitivesManager::OnNewFrame() {
	mCullMode = CullMode::Back;
}
void PrimitivesManager::SetCullMode(CullMode mode)
{
	mCullMode = mode;
}

bool PrimitivesManager::BeginDraw(Topology topology, bool applyTransform)
{
	mVertexBuffer.clear();
	mTopology = topology;
	mApplyTransform = applyTransform;
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
	Matrix4 matWorld = MatrixStack::Get()->GetTransform();
	Matrix4 matView = Camera::Get()->GetViewMatrix();
	Matrix4 matProj = Camera::Get()->GetProjectionMatrix();
	Matrix4 matScreen = GetScreenTranform();
	//Matrix4 matFinal = matWorld * matView * matProj * matScreen;
	Matrix4 matNDSpace = matView * matProj;

	ShadeMode shadeMode = Rasterizer::Get()->GetShadeMode();
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
				mVertexBuffer[i]
			};
			if (mApplyTransform)
			{
				//local
				if (MathHelper::CheckEqual(MathHelper::MagnitudeSquared(triangle[0].norm), 0.0f))
				{

					Vector3 faceNorm = CreateFaceNormal(triangle);
					for (size_t t = 0; t < triangle.size(); ++t)
					{
						triangle[t].norm = faceNorm;

					}

				}
					// world space
					for (size_t t = 0; t < triangle.size(); ++t)
					{
						triangle[t].pos = MathHelper::TransformCoord(triangle[t].pos, matWorld);
						triangle[t].worldPos = triangle[t].pos;
						triangle[t].norm = MathHelper::TransformCoord(triangle[t].norm, matWorld);

					}
					if (shadeMode == ShadeMode::Flat)
					{
						X::Color lightColor = LightManager::Get()->ComputeLightColor(triangle[0].pos, triangle[0].norm);
						triangle[0].color *= lightColor;
						triangle[1].color *= lightColor;
						triangle[2].color *= lightColor;
					}
					else if (shadeMode == ShadeMode::Gouraud)
					{
						for (size_t t = 0; t < triangle.size(); ++t)
						{
							triangle[t].color *= LightManager::Get()->ComputeLightColor(triangle[t].pos, triangle[t].norm);

						}
					}
					// NDC space

					for (size_t t = 0; t < triangle.size(); ++t)
					{
						triangle[t].pos = MathHelper::TransformCoord(triangle[t].pos, matNDSpace);

					}
					if (CullTriangle(mCullMode, triangle))
					{
						continue;
					}

					// Screen space
					for (size_t t = 0; t < triangle.size(); ++t)
					{
						triangle[t].pos = MathHelper::TransformCoord(triangle[t].pos, matScreen);

						MathHelper::FlattenVectorScreenCoord(triangle[t].pos);
					}
				}
				if (!Clipper::Get()->ClipTriangle(triangle))
				{
					for (size_t t = 2; t < triangle.size(); ++t)
					{
						Rasterizer::Get()->DrawTriangle(triangle[0], triangle[t - 1], triangle[t]);
					}

				}
			}
			break;
		}
	}
	
}
