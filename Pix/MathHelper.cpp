#include "MathHelper.h"
#include <cmath>
bool MathHelper::CheckEqual(float a, float b) {
	return abs(a - b) < 0.001f;
}

float MathHelper::MagnitudeSquared(const Vector2& v) {
	return v.x * v.x + v.y * v.y;
}
float MathHelper::MagnitudeSquared(const Vector3& v) {
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

float MathHelper::Magnitude(const Vector2& v) {
	return sqrt(MagnitudeSquared(v));
}
float MathHelper::Magnitude(const Vector3& v) {
	return sqrt(MagnitudeSquared(v));
}

Vector2 MathHelper::Normalize(const Vector2& v) {
	return v / Magnitude(v);
}
Vector3 MathHelper::Normalize(const Vector3& v) {
	return v / Magnitude(v);
}

float MathHelper::Dot(const Vector2& a, const Vector2& b) {
	return a.x * b.x + a.y * b.y;
}
float MathHelper::Dot(const Vector3& a, const Vector3& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
Vector3 MathHelper::Cross(const Vector3& a, const Vector3& b) {
	return {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}
Vector3 MathHelper::TransformCoord(const Vector3& v, const Matrix4& m) {
	const float w = ((v.x * m._14) + (v.y * m._24) + (v.z * m._34) + (m._44));
	const float invW = 1.0f / w;

	return{
		((v.x * m._11) + (v.y * m._21) + (v.z * m._31) + (m._41)) * invW,
		((v.x * m._12) + (v.y * m._22) + (v.z * m._32) + (m._42)) * invW,
		((v.x * m._13) + (v.y * m._23) + (v.z * m._33) + (m._43)) * invW
	};
}
Vector3 MathHelper::TransformNormal(const Vector3& v, const Matrix4& m) {
	return {
		(v.x * m._11) + (v.y * m._21) + (v.z * m._31),
		(v.x * m._12) + (v.y * m._22) + (v.z * m._32),
		(v.x * m._13) + (v.y * m._23) + (v.z * m._33)
	};
}

Matrix4 MathHelper::Transpose(const Matrix4& m) {
	return {
		m._11, m._21, m._31, m._41,
		m._12, m._22, m._32, m._42,
		m._13, m._23, m._33, m._43,
		m._14, m._24, m._34, m._44

	};
}
Matrix4 MathHelper::Inverse(const Matrix4& m) {
	const float det = Determinant(m);
	const float invDet = 1.0 / det;
	return Adjoint(m) * invDet;
}

Matrix4 MathHelper::Adjoint(const Matrix4& m) {
	return{
		+(m._22 * ((m._33 * m._44) - (m._43 * m._34)) - m._23 * ((m._32 * m._44) - (m._42 * m._34)) + m._24 * ((m._32 * m._43) - (m._42 * m._33))),
		-(m._12 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._32 * m._44) - (m._42 * m._34)) + m._14 * ((m._32 * m._43) - (m._42 * m._33))),
		+(m._12 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._22 * m._44) - (m._42 * m._24)) + m._14 * ((m._22 * m._43) - (m._42 * m._23))),
		-(m._12 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._22 * m._34) - (m._32 * m._24)) + m._14 * ((m._22 * m._33) - (m._32 * m._23))),

		-(m._21 * ((m._33 * m._44) - (m._43 * m._34)) - m._31 * ((m._23 * m._44) - (m._24 * m._43)) + m._41 * ((m._23 * m._34) - (m._24 * m._33))),
		+(m._11 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._31 * m._44) - (m._41 * m._34)) + m._14 * ((m._31 * m._43) - (m._41 * m._33))),
		-(m._11 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._43) - (m._41 * m._23))),
		+(m._11 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._21 * m._34) - (m._31 * m._24)) + m._14 * ((m._21 * m._33) - (m._31 * m._23))),

		+(m._21 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._22 * m._44) - (m._42 * m._24)) + m._41 * ((m._22 * m._34) - (m._32 * m._24))),
		-(m._11 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._12 * m._44) - (m._42 * m._14)) + m._41 * ((m._12 * m._34) - (m._32 * m._14))),
		+(m._11 * ((m._22 * m._44) - (m._42 * m._24)) - m._12 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._42) - (m._41 * m._22))),
		-(m._11 * ((m._22 * m._34) - (m._32 * m._24)) - m._21 * ((m._12 * m._34) - (m._32 * m._14)) + m._31 * ((m._12 * m._24) - (m._22 * m._14))),

		-(m._21 * ((m._32 * m._43) - (m._42 * m._33)) - m._31 * ((m._22 * m._43) - (m._42 * m._23)) + m._41 * ((m._22 * m._33) - (m._32 * m._23))),
		+(m._11 * ((m._32 * m._43) - (m._42 * m._33)) - m._12 * ((m._31 * m._43) - (m._41 * m._33)) + m._13 * ((m._31 * m._42) - (m._41 * m._32))),
		-(m._11 * ((m._22 * m._43) - (m._42 * m._23)) - m._12 * ((m._21 * m._43) - (m._41 * m._23)) + m._13 * ((m._21 * m._42) - (m._41 * m._22))),
		+(m._11 * ((m._22 * m._33) - (m._32 * m._23)) - m._12 * ((m._21 * m._33) - (m._31 * m._23)) + m._13 * ((m._21 * m._32) - (m._31 * m._22)))

	};
}
float MathHelper::Determinant(const Matrix4& m) {
	float det = 0;
	det += (m._11 * (m._22 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._32 * m._44 - (m._42 * m._34)) + m._24 * (m._32 * m._43 - (m._42 * m._33))));
	det -= (m._12 * (m._21 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._43 - (m._41 * m._33))));
	det += (m._13 * (m._21 * (m._32 * m._44 - (m._42 * m._34)) - m._22 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._42 - (m._41 * m._32))));
	det -= (m._14 * (m._21 * (m._32 * m._43 - (m._42 * m._33)) - m._22 * (m._31 * m._43 - (m._41 * m._33)) + m._23 * (m._31 * m._42 - (m._41 * m._32))));
	return det;
}