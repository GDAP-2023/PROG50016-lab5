#pragma once
class Vector2 {
public:
	float x, y=0;

	Vector2() : x(0), y(0) {}
	Vector2(float x, float y) : x(x), y(y) {}

	// Overload the - operator to get the difference between two vectors
	Vector2 operator-(const Vector2& rhs) const {
		return Vector2(x - rhs.x, y - rhs.y);
	}

	float LengthSquared() const {
		return x * x + y * y;
	}
};