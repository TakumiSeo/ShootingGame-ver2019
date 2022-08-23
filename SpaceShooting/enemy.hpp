//
//  zombie.hpp
//  Zombie Arena
//
//  Created by Brendan Lyng on 30/10/2018.
//  Copyright © 2018 Brendan Lyng. All rights reserved.
//

#ifndef enemy_hpp
#define enemy_hpp

#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy
{
private:
    // How fast is each zombie type?
    // const float BLOATER_SPEED = 40;
    // const float CHASER_SPEED = 80;
    // const float CRAWLER_SPEED = 20;
    //
    // How tough is each zombie type
    const float START_HEALTH = 300;


    // Make each zombie vary its speed slightly
    // const int MAX_VARIANCE = 30;
    // const int OFFSET = 101 - MAX_VARIANCE;

    // Where is this zombie?
    Vector2f m_Position;

    IntRect m_Space;

    // A sprite for the zombie
    Sprite m_Sprite;

    Vector2f m_Resolution;

    // How fast can this one run/crawl?
    float m_Speed;

    // How much health has it got?
    float m_Health;

    // Is it still alive?
    bool m_AliveEnemy=true;

    // Public prototypes go here
public:

    Enemy();

    // Handle when a bullet hits a zombie
    bool hit(int beamOfPlane);

    // Find out if the zombie is alive
    bool isAliveEnemy();

    // Spawn a new zombie
    void spawn(IntRect space, Vector2f resolution, int distance, int NumEnemy);

    // Return a rectangle that is the position in the world
    FloatRect getPosition();

    // Get a copy of the sprite to draw
    Sprite getSprite();

    Vector2f getCenter();

    void resetPlayerStats();

    // Update the zombie each frame
    //void update(float elapsedTime, Vector2f playerLocation);
};

#endif /* zombie_hpp */
