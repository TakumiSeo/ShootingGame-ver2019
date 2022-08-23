#include "enemy.hpp"
#include "textureHolder.hpp"
#include <cstdlib>
#include <ctime>
#include <math.h>       /* atan2 */

using namespace std;

Enemy::Enemy()
{
  m_Health = START_HEALTH;

  m_Sprite = Sprite(TextureHolder::GetTexture("../Resources/graphics/teki2.PNG"));
  m_Sprite.setScale(0.08f, 0.08f);
  m_Sprite.setOrigin(0,0);
}

void Enemy::spawn(IntRect space, Vector2f resolution, int distance, int NumEnemy)
{
  m_Position.x = ((space.width)/NumEnemy)*distance + (100);
  m_Position.y = 2 * ((space.height)/5) + 40;

  m_Space.left = space.left;
  m_Space.width = space.width;
  m_Space.top = space.top;
  m_Space.height = space.height;

  m_Resolution.x = resolution.x;
  m_Resolution.y = resolution.y;

  m_Sprite.setPosition(m_Position);

}


bool Enemy::hit(int beamOfPlane)
{
    m_Health -= beamOfPlane;

    if (m_Health < 0)
    {
        // dead
        m_AliveEnemy = false;
        //m_Sprite.setTexture(TextureHolder::GetTexture("../Resources/graphics/ishi.png"));

        return true;
    }

    // injured but not dead yet
    return false;
}
void Enemy::resetPlayerStats()
{
    m_Health = START_HEALTH;
}


bool Enemy::isAliveEnemy()
{
    return m_AliveEnemy;
}

FloatRect Enemy::getPosition()
{
    return m_Sprite.getGlobalBounds();
}


Sprite Enemy::getSprite()
{
    return m_Sprite;
}

Vector2f Enemy::getCenter()
{
    return m_Position;
}

//
// void Enemy::update(float elapsedTime, Vector2f playerLocation)
// {
//     float playerX = playerLocation.x;
//     float playerY = playerLocation.y;
//
//     // Update the zombie position variables
//     if (playerX > m_Position.x)
//     {
//         m_Position.x = m_Position.x +
//         m_Speed * elapsedTime;
//     }
//
//     if (playerY > m_Position.y)
//     {
//         m_Position.y = m_Position.y +
//         m_Speed * elapsedTime;
//     }
//
//     if (playerX < m_Position.x)
//     {
//         m_Position.x = m_Position.x -
//         m_Speed * elapsedTime;
//     }
//
//     if (playerY < m_Position.y)
//     {
//         m_Position.y = m_Position.y -
//         m_Speed * elapsedTime;
//     }
//
//     // Move the sprite
//     m_Sprite.setPosition(m_Position);
//
//     // Face the sprite in the correct direction
//     float angle = (atan2(playerY - m_Position.y,
//                          playerX - m_Position.x)
//                    * 180) / 3.141;
//
//     m_Sprite.setRotation(angle);
//
//
//
// }
