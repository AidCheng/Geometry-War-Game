#pragma once
#include <math.h>

class Vec2
{
public:
    float x = 0;
    float y = 0;

    Vec2();
    Vec2(float xin, float yin);

    bool operator == (const Vec2& rhs) const;
    bool operator != (const Vec2& rhs) const;

    Vec2 operator + (const Vec2& rhs) const;
    Vec2 operator - (const Vec2& rhs) const;
    Vec2 operator * (const float rhs) const;
    Vec2 operator / (const float rhs) const;

    void operator += (const Vec2& rhs);
    void operator -= (const Vec2& rhs);
    void operator *= (const float rhs);
    void operator /= (const float rhs);

    float squaredSum();

    float dist(const Vec2& rhs) const;
    void normalize();    

    void print() const;
};