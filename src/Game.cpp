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
   
    config(path);
    // set up default window parameters
    // m_window.create(sf::VideoMode(1280, 720), "GEO-WAR", sf::Style::Fullscreen);
    // m_window.setFramerateLimit(60);

    spawnPlayer();
};

void Game::config(const std::string& path)
{
    std::ifstream fin(path);
    std::string target;
    while(fin >> target)
    {
        if(target == "Window")
        {
            configWindow(fin);
        }

        if(target == "Player")
        {
            configPlayer(fin);
        }

        if(target == "Enemy")
        {
            configEnemy(fin);
        }
    }
}

void Game::configWindow(std::ifstream& fin)
{
    int width, height, frameLimit;
    bool isFullScreen;
    fin >> width >> height >> frameLimit >> isFullScreen;

    // create screen
    if(isFullScreen)
    {
        m_window.create(sf::VideoMode(width, height), "GEOWAR", sf::Style::Fullscreen);
    } else {
        m_window.create(sf::VideoMode(width, height), "GEOWAR");
    }

    m_window.setFramerateLimit(frameLimit);
}

void Game::configPlayer(std::ifstream& fin)
{
    fin >> m_playerConfig.shapeRadius >> m_playerConfig.collisionRadius  
       >> m_playerConfig.speed >> m_playerConfig.fillRed >> m_playerConfig.fillGreen >> m_playerConfig.fillBlue
       >> m_playerConfig.outlineRed >> m_playerConfig.outlineGreen >> m_playerConfig.outlineBlue
       >> m_playerConfig.outlineThickness >> m_playerConfig.vertices;
}

void Game::configEnemy(std::ifstream& fin)
{
    fin >> m_enemyConfig.shapeRadius >> m_enemyConfig.collisionRadius  
       >> m_enemyConfig.minSpeed >> m_enemyConfig.maxSpeed
       >> m_enemyConfig.outlineRed >> m_enemyConfig.outlineGreen >> m_enemyConfig.outlineBlue >> m_enemyConfig.outlineThickness
       >> m_enemyConfig.minVertices >> m_enemyConfig.maxVertices
       >> m_enemyConfig.smallEnemyLifespan >> m_enemyConfig.spawnInterval;
}



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
            std::cout << m_score << std::endl;
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


// update the speed of the player entity based on input 
void Game::updateSpeed(std::shared_ptr<Entity> e)
{
    float speed = m_playerConfig.speed;
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

            case sf::Keyboard::Escape:
                m_running = false;
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
    int spawnInterval = m_enemyConfig.spawnInterval;
    if(!(((m_currentFrame++)-m_lastEnemySpawnTime) == spawnInterval))
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

    // TODO: player life system
}

void Game::handleDeadEnemy(std::shared_ptr<Entity> enemy)
{
    if(enemy->cLifeSpan == nullptr)
    {   
        spawnSmallEnemies(enemy);
    }

    // update player scores
    m_score += enemy->cScore->score;
    enemy->destroy();
}

////////////////////////
void Game::spawnPlayer()
{
    // data preparation
    float mx = m_window.getSize().x / 2.0f;
    float my = m_window.getSize().y / 2.0f;
    Vec2 centre = {mx, my};
    Vec2 initSpeed = {0,0};
    float initAngle = 0.0f;
    float shapeRadius = m_playerConfig.shapeRadius;
    float collisionRadius = m_playerConfig.collisionRadius;
    float thickness = m_playerConfig.outlineThickness; 

    int fillR = m_playerConfig.fillRed;
    int fillG = m_playerConfig.fillGreen;
    int fillB = m_playerConfig.fillBlue;
    std::cout << fillR << fillG << fillB << std::endl;
    sf::Color fill(fillR, fillG, fillB);

    int outlineR = m_playerConfig.outlineRed;
    int outlineG = m_playerConfig.outlineGreen;
    int outlineB = m_playerConfig.outlineBlue;
    sf::Color outline(outlineR, outlineG, outlineB);

    int vertices = m_playerConfig.vertices;

    auto entity = m_entityManager.addEntity("player"); 
    // TODO: implement using PlayerConfig
    entity -> cTransform = std::make_shared<CTransform>(centre);
    entity -> cCollision = std::make_shared<CCollision>(collisionRadius);
    // set the entity's shape have radius 32, 8 vertices
    entity -> cShape = std::make_shared<CShape> (shapeRadius, vertices, fill, outline, thickness);
    // Add input component to the player
    entity -> cInput = std::make_shared<CInput>();

    m_player = entity;
}

// spawn an enemy at a random position
void Game::spawnEnemy()
{
    // data preparation
    int shapeRadius = m_enemyConfig.shapeRadius; 
    int collisionRadius = m_enemyConfig.collisionRadius; 
    // vertices 
    int minVertices = m_enemyConfig.minVertices;
    int maxVertices = m_enemyConfig.maxVertices;
    int vertices = rand() % (maxVertices + 1) + minVertices; 
    // speed 
    int angle = rand();
    float speedScalar = rand() % (1 + int(m_enemyConfig.maxSpeed)) + m_enemyConfig.minSpeed; 
    float speedX = speedScalar * cosf(angle);
    float speedY = - speedScalar * sinf(angle);
    Vec2 speed = {speedX, speedY};
    // position
    float enemyX = rand() % (m_window.getSize().x - collisionRadius) + collisionRadius;
    float enemyY = rand() % (m_window.getSize().y - collisionRadius) + collisionRadius;
    Vec2 position = {enemyX, enemyY};

    int outlineRed = m_enemyConfig.outlineRed;
    int outlineGreen = m_enemyConfig.outlineGreen;
    int outlineBlue = m_enemyConfig.outlineBlue;
    int outlineThickness = m_enemyConfig.outlineThickness;
    std::cout << outlineRed << outlineGreen << outlineBlue;
    const auto fillColor = sf::Color(0,0,0);
    auto outlineColor = sf::Color(outlineRed,outlineGreen,outlineBlue);

    auto entity = m_entityManager.addEntity("enemy");
    entity -> cTransform = std::make_shared<CTransform> (position, speed);
    entity -> cShape = std::make_shared<CShape> (shapeRadius, vertices, fillColor, outlineColor, outlineThickness);
    entity -> cCollision = std::make_shared<CCollision> (collisionRadius);
    entity -> cScore = std::make_shared<CScore> (m_scorePerVertices * vertices); 

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
    int lifeSpan = m_enemyConfig.smallEnemyLifespan;
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
        Vec2 speed = {cosf(i* M_PI * 2.0 / vertices) + deadEntity->cTransform->velocity.x, 
                      -sinf(i * M_PI * 2.0 / vertices) + deadEntity->cTransform->velocity.y};

        // create new enemy
        auto e = m_entityManager.addEntity("enemy");
        e -> cTransform = std::make_shared<CTransform> (position, speed, 0.0f);
        e -> cShape = std::make_shared<CShape> (8.0f, vertices, fColor, oColor,2.0f);
        e -> cCollision = std::make_shared<CCollision> (collisionRadius);
        e -> cScore = std::make_shared<CScore> (m_scorePerVertices * vertices); 
        e -> cLifeSpan = std::make_shared<CLifeSpan>(lifeSpan);
    }
}

// spawn bullet
void Game::spawnBullet(std::shared_ptr<Entity> entry, const Vec2 target)
{

    //TODO: calculate the spawn point of the bullet
    auto bullet = m_entityManager.addEntity("bullet");

    // bullet velocity 
    auto velocity = (target - entry->cTransform->position);
    velocity.normalize();
    velocity *= 15.0f;

    // bullet position
    Vec2 position = entry->cTransform->position;

    // bullet components
    bullet->cTransform = std::make_shared<CTransform> (position, velocity, 0);
    bullet->cShape = std::make_shared<CShape> (10.0f, 8, sf::Color(255,255,255), sf::Color(255,255,255), 1.0f);
    bullet->cCollision = std::make_shared<CCollision> (10.0f);
    bullet->cLifeSpan = std::make_shared<CLifeSpan> (240);
}

// spawn special skill
void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity) 
{

}




