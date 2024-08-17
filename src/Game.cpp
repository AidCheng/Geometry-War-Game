#include "Game.hpp"

#include <iostream>
#include <fstream>

// TODO: scoring system

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

void Game::setPaused()
{
    if(m_paused)
    {
        m_paused = false;
    } else {
        m_paused = true;
    }
}

void Game::run()
{
    // some system need to be functioning when paused
    while(m_running)
    {
        m_entityManager.update();

        if(!m_paused)
        {
            sEnemySpawner();
            std::cout<<"spawner"<<std::endl;
            sMovement();
            std::cout<<"Movement"<<std::endl;
            sCollision();
            std::cout<<"Collision"<<std::endl;
            sLifespan();
        } 
        sUserInput();
        std::cout<<"Input"<<std::endl;
        sRender();
        std::cout<<"Render"<<std::endl<<std::endl;
    }
}


// movement system with bounds check
void Game::sMovement()
{
    for(auto e: m_entityManager.getEntities())
    {
        if(e->tag() == "player")
        {
            updateSpeed(e);
        }
        
        // update position with bounds check
        updatePosition(e);
    }
}

// update position for the entity and check bounds
void Game::updatePosition(std::shared_ptr<Entity> e)
{
    float leftBound = e->cCollision->radius;
    float upBound = e->cCollision->radius;
    float rightBound = m_window.getSize().x - leftBound; 
    float lowBound = m_window.getSize().y - upBound;


    Vec2 newPos = e->cTransform->position;
    float newX = e -> cTransform -> position.x += e -> cTransform -> velocity.x;
    float newY = e -> cTransform -> position.y += e -> cTransform -> velocity.y;

    // check horizontal bounds
    if(!(newX <= leftBound || newX >= rightBound))
    {
        // only update the position when NOT out of bounds
        newPos.x = newX; 
    } 
        else if(e->tag() != "player")
    {
        // reverse velocity on non-player entities when out of bounds
        e->cTransform->velocity.x = -e->cTransform->velocity.x;
    }

    // check vertical bounds
    if(!(newY <= upBound || newY >= lowBound))
    {
        newPos.y = newY;
    } 
        else if(e->tag() != "player")
    {
        e->cTransform->velocity.y = -e->cTransform->velocity.y;
    }

    // update position info stored in the component
    e->cTransform->position = newPos;
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


// handles all the user input, does not contain the logic of handling
void Game::sUserInput()
{ 

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

            case sf::Keyboard::P:
                setPaused();  
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

        // mouse control
        if(event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                spawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
            }

            if (event.mouseButton.button == sf::Mouse::Right)
            {
                spawnSpecialWeapon(m_player);
            }
        }
    }
}

void Game::sLifespan()
{
    //TODO: impl lifespan system, then change opacity of the entity in the render system
    for(auto e:m_entityManager.getEntities())
    {
        // ignore entities with infinite lifespan
        if(e->cLifeSpan == nullptr)
        {
            continue;;
        } 

        // destroy entities with 0 remaining lifespan
        if(e->cLifeSpan->remaining-- == 0)
        {
            e->destroy();
        }
    }

}

//rendering system
void Game::sRender()
{
    // TODO:
    // clear the previous frame
    m_window.clear();

    // update shape data
    for(auto e: m_entityManager.getEntities())
    {
        e -> updateShape();
    }

    // draw the entities 
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

// collision system
void Game::sCollision()
{   
    // looping all the bullet and enemies
    for(auto bullet: m_entityManager.getEntities("bullet"))
    {
        for(auto e: m_entityManager.getEntities("enemy"))
        {
            // calculate and compare the distance2 to determine whether collided
            auto diffVec = e->cTransform->position - bullet->cTransform->position;
            float sqrSum = diffVec.squaredSum();
            float minDistance2 = powf(bullet->cCollision->radius
                                    + e->cCollision->radius, 2);
            if(sqrSum <= minDistance2)
            {
                bullet->destroy();
                handleDeadEnemy(e);
                break;
            }
        }
    }
}

void Game::handleDeadEnemy(std::shared_ptr<Entity> enemy)
{
    if(enemy->cLifeSpan == nullptr)
    {   
        spawnSmallEnemies(enemy);
    }
    enemy->destroy();
}

////////////////////////
void Game::spawnPlayer()
{
    auto entity = m_entityManager.addEntity("player"); 

    float mx = m_window.getSize().x / 2.0f;
    float my = m_window.getSize().y / 2.0f;
    // Vec2 position = {mx, my}

    // TODO: implement using PlayerConfig
    entity -> cTransform = std::make_shared<CTransform>(Vec2(mx, my), Vec2(0.0f, 0.0f), 0.0f);
    entity -> cCollision = std::make_shared<CCollision>(50.0f);

    // set the entity's shape have radius 32, 8 vertices
    entity -> cShape = std::make_shared<CShape> (50.0f, 5, sf::Color(255,255,255), sf::Color(255,255,255), 2.0f);

    // Add input component to the player
    entity -> cInput = std::make_shared<CInput>();

    m_player = entity;
}

// spawn an enemy at a random position
void Game::spawnEnemy()
{
    auto entity = m_entityManager.addEntity("enemy");

    //TODO: the enemy must spawned completely within the bounds of the window
    float enemyX = rand() % m_window.getSize().x;
    float enemyY = rand() % m_window.getSize().y;
    Vec2 position = {enemyX, enemyY};

    float speedX = -(rand()%6)+3;
    float speedY = -(rand()%6)+3;
    Vec2 speed = {speedX, speedY};

    float radius = rand()%40 + 15;

    // Set the spawn position 200,200, with speed 1, 1 at angle of 0  
    // TODO: implement using EnemyConfig
    entity -> cTransform = std::make_shared<CTransform> (position, speed, 0.0f);

    // set the entity's shape have radius 32, 8 vertices
    entity -> cShape = std::make_shared<CShape> (radius, (rand() % 6)+3, sf::Color(0,0,255), sf::Color(255,255,255), 2.0f);
    entity -> cCollision = std::make_shared<CCollision> (32.0f);
}


// position calculator for small enemy spawning
Vec2 calculatePosition(Vec2 center, float angle, float radius)
{
    float x = center.x + 0.5 * (radius * cosf(angle));
    float y = center.y - 0.5 * (radius * sinf(angle));
    return Vec2(x,y);
}

// spawn samll enemies when enemy died
void Game::spawnSmallEnemies(std::shared_ptr<Entity> deadEntity)
{
    float vertices = deadEntity->cShape->circle.getPointCount();
    float radius = deadEntity ->cShape->circle.getRadius();
    float collisionRadius = (deadEntity->cCollision->radius)/2;
    auto fColor = deadEntity->cShape->circle.getFillColor();
    auto oColor = deadEntity->cShape->circle.getOutlineColor();

    for (int i = 0; i < vertices; i++) 
    {
        // calculate new position
        auto position = calculatePosition(deadEntity->cTransform->position,
                                          i/vertices * M_PI* 2.0, radius);
        // calculate speed
        Vec2 speed = {cosf(i* M_PI * 2.0 / vertices), -sinf(i * M_PI * 2.0 / vertices)};

        // create new enemy
        auto e = m_entityManager.addEntity("enemy");
        e -> cTransform = std::make_shared<CTransform> (position, speed, 0.0f);
        e -> cShape = std::make_shared<CShape> (8.0f, vertices, fColor, oColor,2.0f);
        e -> cCollision = std::make_shared<CCollision> (collisionRadius);
        // TODO: TOTAL LIFE SPAN
        e -> cLifeSpan = std::make_shared<CLifeSpan>(60);
    }
}

// spawn bullet
void Game::spawnBullet(std::shared_ptr<Entity> entry, const Vec2 target)
{

    //TODO: calculate the spawn point of the bullet
    auto bullet = m_entityManager.addEntity("bullet");
    // bullet position
    // float bx = target.x;
    // float by = target.y;
    auto velocity = (target - entry->cTransform->position);
    velocity.normalize();
    velocity *= 15.0f;

    Vec2 position = entry->cTransform->position;

    // configure bullet components
    bullet->cTransform = std::make_shared<CTransform> (position, velocity, 0);
    bullet->cShape = std::make_shared<CShape> (10.0f, 8, sf::Color(255,255,255), sf::Color(255,255,255), 1.0f);
    bullet->cCollision = std::make_shared<CCollision> (10.0f);
    bullet->cLifeSpan = std::make_shared<CLifeSpan> (240);
}

// spawn special skill
void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity) 
{

}




