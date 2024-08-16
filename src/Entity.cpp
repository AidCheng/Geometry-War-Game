#include "Entity.hpp"

size_t Entity::getId()
{
    return m_id;
}

std::string Entity::tag()
{
    return m_tag;
}

bool Entity::isAlive()
{
    return m_alive;
}

void Entity::destroy()
{
    m_alive = false;
}

void Entity::updateShape()
{
    if(cLifeSpan != nullptr)
    {
        auto fcolor = cShape->circle.getFillColor();
        auto ocolor = cShape->circle.getOutlineColor(); 

        fcolor.a = lifeSpanRatio() * 255;
        ocolor.a = lifeSpanRatio() * 255;

        cShape->circle.setFillColor(fcolor);
        cShape->circle.setOutlineColor(ocolor);
    }

    cShape -> circle.setPosition(sf::Vector2f(cTransform -> position.x, cTransform -> position.y));
    cShape -> circle.setRotation(cTransform->angle++);
}

float Entity::lifeSpanRatio()
{
    return cLifeSpan->remaining / cLifeSpan->total;
}