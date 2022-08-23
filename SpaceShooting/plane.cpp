//
//  Player.cpp
//  Zombie Arena
//

//#include "stdafx.h" // <- Visual Studio only
#include "plane.hpp"
#include "textureHolder.hpp"

Plane::Plane()
{
    m_Speed = START_SPEED;
    m_Health = START_HEALTH;
    m_MaxHealth = START_HEALTH;

    // Associate a texture with the sprite
    // !!Watch this space!!
    m_Sprite =
              Sprite(TextureHolder::GetTexture("../Resources/graphics/hikouki.PNG"));
    //m_Texture.loadFromFile("../Resources/graphics/hikouki.PNG");
    m_Sprite.setScale(0.15f, 0.15f);
    //m_Sprite.setTexture(m_Texture);

    m_Sprite.setOrigin(0, 0);
}

void Plane::spawn(IntRect space, Vector2f resolution, int limitSize) {
    // Place the player in the middle of the arena
    m_Position.x = space.width / 2;
    m_Position.y = space.height;
    // Copy the details of the arena to the player's m_Arena
    m_Space.left = space.left;
    m_Space.width = space.width;
    m_Space.top = space.top;
    m_Space.height = space.height;

    // Remember how big the tiles are in this arena
    m_LimitSize = limitSize;

    // Store the resolution for future use
    m_Resolution.x = resolution.x;
    m_Resolution.y = resolution.y;
}

bool Plane::hit(Time timeHit, float beamFromEnemy)
{
  if(timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200)
  {

    m_LastHit = timeHit;
    m_Health -= beamFromEnemy;
    return true;
  }
  else
  {
    return false;
  }
}
void Plane::resetPlayerStats()
{
    m_Speed = START_SPEED;
    m_Health = START_HEALTH;
    m_MaxHealth = START_HEALTH;
}

Time Plane::getLastHitTime()
{
    return m_LastHit;
}
FloatRect Plane::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

Vector2f Plane::getCenter()
{
    return m_Position;
}
Sprite Plane::getSprite()
{
    return m_Sprite;
}

int Plane::getHealth()
{
    return m_Health;
}

void Plane::moveLeft()
{
    m_LeftPressed = true;
}

void Plane::moveRight()
{
    m_RightPressed = true;
}

void Plane::stopLeft()
{
    m_LeftPressed = false;
}

void Plane::stopRight()
{
    m_RightPressed = false;
}
void Plane::update(float elapsedTime, Vector2i mousePosition)
{

    if (m_RightPressed)
    {
        m_Position.x += m_Speed * elapsedTime;
    }

    if (m_LeftPressed)
    {
        m_Position.x -= m_Speed * elapsedTime;
    }

    m_Sprite.setPosition(m_Position);

    // Keep the player in the arena
    if (m_Position.x > m_Space.width - m_LimitSize)
    {
        m_Position.x = m_Space.width - m_LimitSize;
    }

    if (m_Position.x < m_Space.left + m_LimitSize)
    {
        m_Position.x = m_Space.left + m_LimitSize;
    }

    float angle = 0;
    m_Sprite.setRotation(angle);

}

void Plane::upgradeSpeed()
{
    // 20% speed upgrade
    m_Speed += (START_SPEED * .2);
}

void Plane::upgradeHealth()
{
    // 20% max health upgrade
    m_MaxHealth += (START_HEALTH * .2);

}

void Plane::increaseHealthLevel(int amount)
{
    m_Health += amount;

    // But not beyond the maximum
    if (m_Health > m_MaxHealth)
    {
        m_Health = m_MaxHealth;
    }
}
