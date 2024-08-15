#include "Game.hpp"

#include <iostream>
#include <fstream>

Game::Game(const std::string& config)
{
    init(config);
}

void Game::init(const std::string& path)
{
    // TODO: read in config file, use premade Config variables
    std::ifstream fin(path);

    // set up default window parameters
    m_window.create(sf::VideoMode(1280, 720), "GEO-WAR");
    m_window.setFramerateLimit(60);

    spawnPlayer();
};

void Game::setPaused(bool paused)
{

}

void Game::run()
{
    // TODO: add pause functino
    //       some system need to be functioning when paused
    while(m_window.isOpen() && m_running)
    {
        m_entityManager.update();

        if(!m_paused)
        {
            sEnemySpawner();
            sMovement();
            sCollision();
        } 
        sUserInput();
        sRender();
    }
}

void Game::sMovement()
{
    // TODO: impl all entity movement in this function
    auto e = m_player;
    updateSpeed(m_player);
    e -> cTransform -> position.x += e -> cTransform -> velocity.x;
    e -> cTransform -> position.y += e -> cTransform -> velocity.y;

}

void Game::updateSpeed(std::shared_ptr<Entity> e)
{
    const float speed = 5;
    e -> cTransform ->velocity = {0,0};

    // update speed
    // move up
    if(e->cInput->up)
    {
        e->cTransform->velocity.y -= speed;
    }

    // move down
    if(e->cInput->down)
    {
        e->cTransform->velocity.y += speed;
    }

    // move left
    if(e->cInput->left)
    {
        e->cTransform->velocity.x -= speed;
    } 

    // move right
    if(e->cInput->right)
    {
        e->cTransform->velocity.x += speed;
    }      
}


void Game::sUserInput()
{
    /* TODO: handle user input here
             should ONLY be setting player's input component variables here
             should NOT impl the movement logic
             the movement system WILL READ the variables set in the function
    */
    
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        // window closed
        if(event.type == sf::Event::Closed)
        {
            m_running = false;
        }

        // handle pressed key
        if(event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::W: 
                m_player->cInput->up = true;
                break;

            case sf::Keyboard::S:
                m_player->cInput->down=true;
                break;            

            case sf::Keyboard::A:
                m_player->cInput->left=true;
                break;            

            case sf::Keyboard::D:
                m_player->cInput->right=true;
                break;            

            default:
                break;
            }
        }

        // handle released key
        if(event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::W: 
                m_player->cInput->up = false;
                break;
            
            case sf::Keyboard::S:
                m_player->cInput->down=false;
                break;            

            case sf::Keyboard::A:
                m_player->cInput->left=false;
                break;            

            case sf::Keyboard::D:
                m_player->cInput->right=false;
                break;            

            default:
                break;
            }
        }
    }
}

void Game::sLifespan()
{

}

//rendering system
void Game::sRender()
{
    // clear the previous frame
    m_window.clear();

    for(auto e: m_entityManager.getEntities())
    {
        e -> updateShape();
    }

    // draw the new frame
    // draw player
    for(auto e: m_entityManager.getEntities())
    {
        m_window.draw(e -> cShape -> circle);
    }
    
    m_window.display();
}

void Game::sEnemySpawner()
{
    if(!(((m_currentFrame++)-m_lastEnemySpawnTime) == 60))
    {
        return;
    }

    spawnEnemy();
    m_currentFrame = m_lastEnemySpawnTime; 
}

void Game::sCollision()
{

}

////////////////////////
void Game::spawnPlayer()
{
    auto entity = m_entityManager.addEntity("Player"); 

    float mx = m_window.getSize().x / 2.0f;
    float my = m_window.getSize().y / 2.0f;

    // Set the spawn position 200,200, with speed 1, 1 at angle of 0  
    // TODO: implement using PlayerConfig
    entity -> cTransform = std::make_shared<CTransform>(Vec2(mx, my), Vec2(1.0f, 1.0f), 0.0f);

    // set the entity's shape have radius 32, 8 vertices
    entity -> cShape = std::make_shared<CShape> (50.0f, 5, sf::Color(255,255,255), sf::Color(255,255,255), 2.0f);

    // Add input component to the player
    entity -> cInput = std::make_shared<CInput>();

    m_player = entity;
}

// spawn an enemy at a random position
void Game::spawnEnemy()
{
    //TODO: the enemy must spawned completely within the bounds of the window
    auto entity = m_entityManager.addEntity("Enemy"); 

    float enemyX = rand() % m_window.getSize().x;
    float enemyY = rand() % m_window.getSize().y;
    
    // Set the spawn position 200,200, with speed 1, 1 at angle of 0  
    // TODO: implement using PlayerConfig
    entity -> cTransform = std::make_shared<CTransform> (Vec2(enemyX,enemyY), Vec2(1.0f, 1.0f), 0.0f);

    // set the entity's shape have radius 32, 8 vertices
    entity -> cShape = std::make_shared<CShape> (32.0f, (rand() % 9)+1, sf::Color(0,0,255), sf::Color(255,255,255), 2.0f);

    // Add input component to the player
    entity -> cInput = std::make_shared<CInput>();
}

// spawn samll enemies when enemy died
void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{

}

// spawn bullet
void Game::spawnBullet(std::shared_ptr<Entity> entry, const Vec2& mousePos)
{

}

// spawn special skill
void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity) 
{

}




