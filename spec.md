# Project SPEC

## File Structure

- Geo-War
    - src
        - main.cpp
        - Game.cpp
        - Vec2.cpp
        - Entity.cpp
        - EntityManager.cpp
        - Components.h

## Feature Requirements

- Player
    - represented by a *shape*
    - spawns in the centre of the game
    - move by a speed read from the config file
    - confined within the window
    - shoot a bullet to the direction where *the mouse is clicked*
        - the speed, size and life span is in the config file


- Special Ability
    - design your own
    - fired when the right button clicked
    - the ability MUST:
        - Multiple entities (bullets etc.)
        - Entities have some unique **graphic effect**
        - A unique game mechanic is intro via *a new component*
        - 'A cooldown timer' needed

// Create a robot that generates temporary razer toward the closest enemy
// The razar shoots once with a cooldown time
// The robot is destroyed when collide with any enemies after 5 times;
// 30s cooldown time for a new robot, two robot **cannot exist** at the same time

- Enemies
    - spawn in random location every X(defined in conf) frames
    - cannot overlap the sides of the screen
    - have random number of vertices, between a minimum and maximum (conf)
    - shape radius (conf)
    - random spawn *spawn color*
    - random speed upon spawning, between a *min and max* (conf)
    - when reach the edge of the window, should bounce off  
    - BEHAVIOUR:
        - When large enemy collide with a *bullet or playerl*, destroyed
        - Then spawn N small enemies in its place (N = vertices)
        - Each small enemy must have the same shape and colour
        - The small enemies travel outward at angles at a fixed interval equals to (360 / vertices)
        - The small enemies have **half of the radius to the original entity**

## Collision

- Bullet <-> Shape
    - The bullet destroyed first
    - Then the shape

## Scoring

- Each time an enemy spawns, given a score component of N * 100 (N = vertices)
- If player kills an enemy, the score is increased
- Score should displayed on the top left corner with the specified font from *config*

## Drawing

- All entities should be given a slow rotation

## Key Input
- 'P' := pause
- 'ESC' := exit

## Configuration File

```conf
Window [Width] [Height] [FrameLimit] [FullScreen]
Font [Font] [Size] [R] [G] [B]
Player [ShapeRadius] [Collision Radius] [Speed] [FillColor(R,G,B)] [OutlineColor(R,G,B)] [OutlineThickness] [ShapeVertices(N)]
Enemy [SR] [CR] [MinSpeed] [MaxSpeed] [OutlineColor(R,G,B)] [OutlineThickness] [MinVertices] [MaxVertices] [SmallShapeLifespan] [SpawnInterval(Frame:int)]
Bullet [SR] [CR] [Speed] [FC] [OC] [OT] [Vertices] [Lifespan]
```

