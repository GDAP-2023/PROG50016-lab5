#pragma once

#ifndef _ENGINE_MATH_H_
#define _ENGINE_MATH_H_

#include "json.hpp"

#include <SDL_rect.h>

union Vec2
{
	struct {
		float x;
		float y;
	};
	SDL_FPoint data;

	Vec2();
	explicit Vec2(float value);
	Vec2(float _x, float _y);
	static Vec2 Zero;
	static Vec2 UnitX;
	static Vec2 UnitY;
	Vec2 operator-() const;
	Vec2& operator+=(const Vec2& rhs);
	Vec2& operator-=(const Vec2& rhs);


	bool operator==(const Vec2& rhs) const;
	bool operator!=(const Vec2& rhs) const;

	// Cursed shader-programmer zone starts
	Vec2& operator*=(const Vec2& rhs);
	Vec2& operator/=(const Vec2& rhs);
	// Cursed shader-programmer zone ends

	Vec2& operator*=(const float& f);
	Vec2& operator/=(const float& f);

	Vec2 operator+(const Vec2& rhs) const;
	Vec2 operator-(const Vec2& rhs) const;

	// Cursed shader-programmer zone starts
	Vec2 operator*(const Vec2& rhs) const;
	Vec2 operator/(const Vec2& rhs) const;
	// Cursed shader-programmer zone ends

	Vec2 operator*(const float& f) const;
	Vec2 operator/(const float& f) const;

	float Magnitude() const;
	float MagnitudeSquared() const;
	void Normalize();
	float Dot(const Vec2& rhs) const;
	static float Dot(const Vec2& lhs, const Vec2& rhs);

	// Only because Roy asked me to :(
	float Distance(const Vec2& rhs) const;
	static float Distance(const Vec2& lhs, const Vec2& rhs);
};

inline Vec2 vec2_from_json(json::JSON& node) {
	if (node.length() == 2) {
		return Vec2((float) node[0].ToFloat(), (float) node[1].ToFloat());
	}
	LOG("ERROR: Vec2::Load() - node is not a Vec2 or does not have 2 elements");

	return Vec2::Zero;
}

// Exercise for the viewer :)
union IVec2
{
	struct {
		int x;
		int y;
	};
	SDL_Point data;
};

#endif