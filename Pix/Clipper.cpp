#include "Clipper.h"
#include "Viewport.h"

const short BIT_INSIDE = 0; //0000
const short BIT_LEFT = 1 << 0; //0001
const short BIT_RIGHT = 1 << 1; //0010
const short BIT_BOTTOM = 1 << 2; //0100
const short BIT_TOP = 1 << 3; //1000

// Generate a bit code that signifies where the point is
// if cpde is not , it is utside of the screen in one of the 8 regions
//compare code with other points code to confirm if the line crosses screen

short GetOutputCode(float x, float y) {
	Viewport* vp = Viewport::Get();
	short code = BIT_INSIDE;
	if (x < vp->GetMinX()) {
		code |= BIT_LEFT;
	}
	else if (x > vp->GetMaxX()) {
		code |= BIT_RIGHT;

	}
	if (y < vp->GetMinY()) {
		code |= BIT_TOP;

	}
	else if (y > vp->GetMaxY()) {
		code |= BIT_BOTTOM;
	}
	return code;
}
enum ClipEdge {
	CE_LEFT,
	CE_TOP,
	CE_RIGHT,
	CE_BOTTOM,
	CE_COUNT // we can use this to iterate enum
};
bool IsInFront(ClipEdge edge, const Vector3& pos)
{
	Viewport* vp = Viewport::Get();
	switch (edge)
	{
	case CE_LEFT: return pos.x > vp->GetMinX();
		break;
	case CE_TOP: return pos.y > vp->GetMinY();
		break;
	case CE_RIGHT: return pos.x < vp->GetMaxX();
		break;
	case CE_BOTTOM: return pos.y < vp->GetMaxY();
		break;
	default:
		break;
	}
	return false;
}

Vertex ComputeIntersection(ClipEdge edge, const Vertex& a, const Vertex& b)
{
	Viewport* vp = Viewport::Get();
	float t = 0.0f;
	switch (edge)
	{
	case CE_LEFT: t = (vp->GetMinX() - a.pos.x) / (b.pos.x - a.pos.x);
		break;
	case CE_TOP: t = (vp->GetMinY() - a.pos.y) / (b.pos.y - a.pos.y);
		break;
	case CE_RIGHT: t = (vp->GetMaxX() - a.pos.x) / (b.pos.x - a.pos.x);
		break;
	case CE_BOTTOM: t = (vp->GetMaxY() - a.pos.y) / (b.pos.y - a.pos.y);
		break;
	default:
		break;
	}
	return LerpVertex(a, b, t);
}
Clipper* Clipper::Get()
{
	static Clipper sInstance;
	return &sInstance;
}

Clipper::Clipper(){}

void Clipper::OnNewFrame() {
	mIsClipping = false;
}

bool Clipper::ClipPoint(const Vertex& v) {
	if (!mIsClipping)
	{
		return false;
	}
	Viewport* vp = Viewport::Get();
	float minX = vp->GetMinX();
	float maxX = vp->GetMaxX();
	float minY = vp->GetMinY();
	float maxY = vp->GetMaxY();

	return v.pos.x < minX || v.pos.x > maxX ||
		   v.pos.y < minY || v.pos.y > maxY;
}
bool Clipper::ClipLine(Vertex& a, Vertex& b) {
	if (!mIsClipping)
	{
		return false;
	}
	Viewport* vp = Viewport::Get();
	float minX = vp->GetMinX();
	float maxX = vp->GetMaxX();
	float minY = vp->GetMinY();
	float maxY = vp->GetMaxY();
	// we need coes for each point
	short codeA = GetOutputCode(a.pos.x, a.pos.y);
	short codeB = GetOutputCode(b.pos.x, b.pos.y);

	while (true)
	{
		if (!(codeA | codeB)) {
			//both are 0000, so both are in the viewport
			break;
		}
		else if (codeA & codeB) {
			//both are along the samne edge, so they will never cross the viewport
			break;
		}
		float t = 0.0f;
		short outCode = codeB > codeA ? codeB : codeA;
		if (outCode & BIT_TOP)			{ t = (minY - a.pos.y) / (b.pos.y - a.pos.y); }
		else if (outCode & BIT_BOTTOM)  { t = (maxY - a.pos.y) / (b.pos.y - a.pos.y); }
		else if (outCode & BIT_LEFT)    { t = (minX - a.pos.x) / (b.pos.x - a.pos.x); }
		else if (outCode & BIT_RIGHT)   { t = (maxX - a.pos.x) / (b.pos.x - a.pos.x); }

		if (outCode == codeA) {
			a = LerpVertex(a, b, t);
			codeA = GetOutputCode(a.pos.x, a.pos.y);
		}
		else {
			b = LerpVertex(a, b, t);
			codeB = GetOutputCode(b.pos.x, b.pos.y);
		}
	}
	return (codeA | codeB);
}
bool Clipper::ClipTriangle(std::vector<Vertex>& v) {
	if (!mIsClipping)
	{
		return false;
	}
	std::vector<Vertex> newVertices;
	for (int i = 0; i < CE_COUNT; ++i) {
		newVertices.clear();
		ClipEdge edge = (ClipEdge)i;
		for (size_t n = 0; n < v.size(); ++n)
		{
			//get loop to initial index
			//nPO= n plus one 
			size_t nPO = (n + 1) % v.size();
			//Current vertex
			const Vertex& vN = v[n];
			//next vertex (n plus one)
			const Vertex& vNPO = v[nPO];

			// which points  are inside or outside

			bool nIsInFront = IsInFront(edge, vN.pos);
			bool nPOIsInFront = IsInFront(edge, vNPO.pos);

			//Case 1 both are in front
			if (nIsInFront && nPOIsInFront)
			{
				//save npo as both are in the viewport
				newVertices.push_back(vNPO);

			}
			//case 2
			else if (!nIsInFront && !nPOIsInFront)
			{
				//dont save anything
			}
			else if (nIsInFront && !nPOIsInFront)
			{
				//only save the intersection
				newVertices.push_back(ComputeIntersection(edge, vN, vNPO));
			}
			else if (!nIsInFront && nPOIsInFront)
			{
				//only save the intersection
				newVertices.push_back(ComputeIntersection(edge, vN, vNPO));
				newVertices.push_back(vNPO);

			}
		}
		v = newVertices;
	}
	return newVertices.empty();
}


bool Clipper::IsClipping() const {
	return mIsClipping;
}
void Clipper::SetClipping(bool enable)
{
	mIsClipping = enable;

}
