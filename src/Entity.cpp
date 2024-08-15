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
