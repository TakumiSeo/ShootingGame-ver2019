//
//  bullet.hpp
//  Zombie Arena
//
//

#ifndef bullet_hpp
#define bullet_hpp

#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet
{
private:

    const float BULLETSPEED = 1000;
    const int BEAM_POWER = 100;
    // Where is the bullet?
    Vector2f m_Position;

    // What each bullet looks like
    RectangleShape m_BulletShape;

    // Sprite
    Sprite m_Sprite;

    // Texture
    Texture m_Texture;

    // Is this bullet currently whizzing through the air?
    bool m_InFlight = false;

    // How fast does a bullet travel?


    // What fraction of 1 pixel does the bullet travel horizontally and vertically each frame?
    // These values will be derived from m_BulletSpeed
    float m_BulletDistanceX;
    float m_BulletDistanceY;

    // Where is this bullet headed to?
    float m_XTarget;
    float m_YTarget;

    // Some boundaries so the bullet doesn't fly forever
    float m_MaxX;
    float m_MinX;
    float m_MaxY;
    float m_MinY;

    float m_BulletSpeed;
    float m_BeamPower;


public:
    // The constructor
    Bullet();

    // Stop the bullet
    void stop();

    // Returns the value of m_InFlight
    bool isInFlight();

    // Launch a new bullet
    void shoot(float startX, float startY,
               float xTarget, float yTarget);

    // Tell the calling code where the bullet is in the world
    FloatRect getPosition();

    // Return the actual shape (for drawing)
    RectangleShape getShape();

    // Send a copy of the sprite to main
    Sprite getSprite();

    // Update the bullet each frame
    void update(float elapsedTime);

    // get the power of the beam
    int getBeamPower();

};


#endif /* bullet_hpp */
