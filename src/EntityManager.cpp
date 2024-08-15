#include "EntityManager.hpp"

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
    auto e = std::shared_ptr<Entity> (new Entity(tag, m_totalEntities++)); 
    m_toAdd.push_back(e);
    return e;
}

void EntityManager::update(){
    // Add temporarily stored entities
    for(auto e: m_toAdd){
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }
    m_toAdd.clear();

    // Remove entities NOT ALIVE
    for(auto e: m_entities)
    {
        if(e->isAlive())
        {
            continue;
        } else {
            auto& taggedVec = m_entityMap[e->tag()];
           
            // Remove from Map
            taggedVec.erase(std::remove(taggedVec.begin(),
                                        taggedVec.end(),
                                        e), 
                                        taggedVec.end());
        } 
        // Remove from Vector
        m_entities.erase(std::remove_if(m_entities.begin(),
                                        m_entities.end(),
                                        [](std::shared_ptr<Entity> e){
                                            return !e->isAlive();}),
                                        m_entities.end());
    }
}

EntityVec& EntityManager::getEntities()
{
    EntityVec& copiedVec = m_entities; 
    return copiedVec;
}

EntityVec& EntityManager::getEntities(const std::string& tag)
{
    EntityVec& copiedVec = m_entityMap[tag]; 
    return copiedVec;
}