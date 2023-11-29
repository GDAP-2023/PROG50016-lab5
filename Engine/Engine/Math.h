#pragma once

#ifndef _MATH_H_
#define _MATH_H_

#include <SDL_rect.h>

typedef union Vec2
{
    struct {
        float x;
        float y;
    };
    SDL_FPoint data;

    Vec2();
    Vec2(float value);
    Vec2(float _x, float _y);
    static Vec2 Zero;
    static Vec2 UnitX;
    static Vec2 UnitY;
    Vec2 operator-() const;
    Vec2& operator+=(const Vec2 &rhs);
    Vec2& operator-=(const Vec2 &rhs);
    
    // Cursed shader-programmer zone starts
    Vec2& operator*=(const Vec2 &rhs);
    Vec2& operator/=(const Vec2 &rhs);
    // Cursed shader-programmer zone ends

    Vec2& operator*=(const float &f);
    Vec2& operator/=(const float &f);

    Vec2 operator+(const Vec2 &rhs) const;
    Vec2 operator-(const Vec2 &rhs) const;
    
    // Cursed shader-programmer zone starts
    Vec2 operator*(const Vec2 &rhs) const;
    Vec2 operator/(const Vec2 &rhs) const;
    // Cursed shader-programmer zone ends

    Vec2 operator*(const float &f) const;
    Vec2 operator/(const float &f) const;

    float Magnitude() const;
    float MagnitudeSquared() const;
    void Normalize();
    float Dot(const Vec2 &rhs) const;
    static float Dot(const Vec2 &lhs, const Vec2 &rhs);
};

// Exercise for the viewer :)
typedef union IVec2
{
    struct {
        int x;
        int y;
    };
    SDL_Point data;
};

#endif