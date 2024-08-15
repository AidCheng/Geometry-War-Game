#pragma once

#include <memory>
#include <string>
#include "Components.hpp"

class Entity
{
    friend class EntityManager;

    std::string m_tag   = "Default";
    size_t      m_id      = 0;
    bool        m_alive = true;

    Entity(const std::string& tag, size_t id)
        : m_tag(tag), m_id (id) {}

public:
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CShape> cShape;
    std::shared_ptr<CScore> cScore;
    std::shared_ptr<CCollision> cCollision;
    std::shared_ptr<CLifeSpan> cLifeSpan;
    std::shared_ptr<CInput> cInput;
    
    std::string tag();
    size_t getId();
    bool isAlive();
    void destroy();
};