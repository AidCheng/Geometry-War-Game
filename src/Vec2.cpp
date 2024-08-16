#include"../include/Vec2.hpp"

Vec2::Vec2()
{
    // pass
};

Vec2::Vec2(float xin, float yin)
    : x(xin), y(yin)
{
    // pass    
}

bool Vec2::operator == (const Vec2& rhs) const
{
    return (x == rhs.x && y == rhs.y);
}

bool Vec2::operator != (const Vec2& rhs) const
{
    return !(x == rhs.x && y == rhs.y);
}

Vec2 Vec2::operator + (const Vec2& rhs) const
{
    return Vec2(x+rhs.x, y+rhs.y); 
}

Vec2 Vec2::operator - (const Vec2& rhs) const
{
    return Vec2(x-rhs.x, y-rhs.y); 
}

Vec2 Vec2::operator * (const float rhs) const
{
    return Vec2(x * rhs, y * rhs); 
}

Vec2 Vec2::operator / (const float rhs) const
{
    return Vec2(x/rhs, y/rhs); 
} 

void Vec2::operator += (const Vec2& rhs)  
{
    x += rhs.x;
    y += rhs.y;
}

void Vec2::operator -= (const Vec2& rhs) 
{
    x -= rhs.x;
    y -= rhs.y;
}

void Vec2::operator *= (const float rhs) 
{
    x *= rhs;
    y *= rhs;
}

void Vec2::operator /= (const float rhs) 
{
    x /= rhs;
    y /= rhs;
}

float Vec2::squaredSum()
{
    return x*x+y*y;
}

float Vec2::dist (const Vec2& rhs) const
{
    return sqrtf( powf((rhs.x - x),2) + powf((rhs.y - y),2));
}


