#pragma once

#include "Vec2.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <string>

class CTransform
{
public:
    Vec2 position;
    Vec2 velocity = {0,0};
    float angle    =  0;

    CTransform(Vec2 position, Vec2 velocity, float angle)
        : angle(angle)
        , position(position)
        , velocity(velocity) 
        {}
};

class CShape
{
public:
    sf::CircleShape circle; 
    CShape(float radius, int points, const sf::Color& fill,
          const sf::Color& outline, float thickness)
          : circle(radius, points)
    {
        circle.setFillColor(fill);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(thickness);
        circle.setOrigin(radius, radius);
    }
};

class CCollision
{
public:
    float radius;
    CCollision(float radius): radius (radius) {}
};

class CScore
{
public:
    int score;
    CScore(int score): score (score) {}
};

class CLifeSpan
{
public:
    float total = 0.0;
    float remaining = 0.0;
    CLifeSpan(int total): total(total), remaining(total) {}
};

class CInput
{
public:
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool shoot = false;

    CInput() {}
};