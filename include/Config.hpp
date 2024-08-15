#pragma once

typedef struct PlayerConfig
{
    int shapeRadius, collisionRadius, 
        fillRed, fillGreen, fillBlue, 
        outlineRed, outlineGreen, outlineBlue,
        outlineThickness, vertices;

    float speed;
} PlayerConfig;

typedef struct EnemyConfig
{
    int shapeRadius, collisionRadius,
        outlineRed, outlineGreen, outlineBlue,
        minVertices, maxVertices, outlineThickness,
        smallEnemyLifespan, spawnInterval;

    float minSpeed, maxSpeed; 
} EnemyConfig;

typedef struct BulletConfig
{
    int shapeRadius, collisionRadius,
        fillRed, fillGreen, fillBlue,
        outlineRed, outlineGreen, outlineBlue,
        outlineThickness, vertices, lifespan;

    float speed;    
} BulletConfig;