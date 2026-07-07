#pragma once
struct Vector2
{
	float x, y;
	//initialize vector
	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(float s) : x(s), y(s) {}
	Vector2(float x, float y) : x(x), y(y) {}
	Vector2(const Vector2& v) : x(v.x), y(v.y) {}
	// common operators
	Vector2 operator-() const { return Vector2(-x, -y); }
	Vector2 operator+(const Vector2& rhs) const { return (x + rhs.x, y + rhs.y); }
	Vector2 operator-(const Vector2& rhs) const { return (x - rhs.x, y - rhs.y); }
	Vector2 operator*(float s) const { return (x * s, y * s); }
	Vector2 operator/(float s) const { return (x / s, y / s); }

	//Common inline operators

	Vector2& operator+=(const Vector2& rhs) { x += rhs.x; y += rhs.y; return *this; }
	Vector2& operator-=(const Vector2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
	Vector2& operator*=(float s) { x *= s; y *= s; return *this; }
	Vector2& operator/=(float s) { x /= s; y /= s; return *this; }

};