#pragma once
#include "Config.hpp"
#include "Vec2.hpp"
#include "EntityManager.hpp"

#include <SFML/Graphics.hpp>

class Game
{
    const int           m_scorePerVertices = 100;

    sf::RenderWindow    m_window;
    EntityManager       m_entityManager;
    sf::Font            m_font;
    sf::Text            m_text;
    PlayerConfig         m_playerConfig;
    EnemyConfig          m_enemyConfig;
    BulletConfig         m_bulletConfig;

    int     m_score = 0;
    int     m_currentFrame = 0;
    int     m_lastEnemySpawnTime = 0;
    bool    m_paused = false;
    bool    m_running = true;            

    std::shared_ptr<Entity> m_player;

    void init(const std::string& config);
    void setPaused();
    
    void config(const std::string& path);
    void configWindow(std::ifstream& fin);
    void configPlayer(std::ifstream& fin);
    void configEnemy(std::ifstream& fin);

    void sMovement();
    void sUserInput();
    void sLifespan();
    void sRender();
    void sEnemySpawner();
    void sCollision();

    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> entity);
    void spawnBullet(std::shared_ptr<Entity> entry, const Vec2 mousePos);
    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

    void updateSpeed(std::shared_ptr<Entity> e);
    void handleDeadEnemy(std::shared_ptr<Entity> enemy);
    void updatePosition(std::shared_ptr<Entity> entity);
    
public:
    Game(const std::string& config);
    void run();
};