#include <iostream>
#include "enemybeam.hpp"
#include "textureHolder.hpp"

EnemyBeam::EnemyBeam()
{
  m_BeamPower = BEAM_POWER;
  m_Sprite = Sprite(TextureHolder::
      GetTexture("../Resources/graphics/teki.PNG"));
  m_Sprite.setScale(0.02f, 0.02f);
  m_Sprite.setOrigin(0, 0);
}

void EnemyBeam::shoot(float startX, float startY,
                  float targetX, float targetY)
{
  // Keep track of the beam
  m_InFlightEnemy = true;
  m_Position.x = startX + 20;
  m_Position.y = startY + 40;

  float gradient = 0;
  // in this case,
  // float ratioXY = m_BeamSpeed;

  m_EnemyBeamDistanceY = m_EnemyBeamSpeed;
  m_EnemyBeamDistanceX = 0;

  if (targetY < startY)
  {
      m_EnemyBeamDistanceY *= +1;
  }
  //
  // Set a max range of 1000 pixels
  float range = 1000;
  m_MinX = startX - range;
  m_MaxX = startX + range;
  m_MinY = startY - range;
  m_MaxY = startY + range;

  // Position the bullet ready to be drawn
  m_EnemyBeamShape.setPosition(m_Position);
}

float EnemyBeam::getBeamPower()
{
  return m_BeamPower;
}
void EnemyBeam::stop()
{
  m_InFlightEnemy = false;
}

bool EnemyBeam::isInFlightEnemy()
{
  return m_InFlightEnemy;
}

FloatRect EnemyBeam::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

RectangleShape EnemyBeam::getShape()
{
    return m_EnemyBeamShape;
}

Sprite EnemyBeam::getSprite()
{
  return m_Sprite;
}

void EnemyBeam::update(float elapsedTime)
{
    // Update the bullet position variables
    m_Position.x += m_EnemyBeamDistanceX * elapsedTime;
    m_Position.y += m_EnemyBeamDistanceY * elapsedTime;
    // std::cout << "("<<m_Position.x<<","<<m_Position.y<<")"<<elapsedTime<< '\n';

    // Move the bullet
    // m_BulletShape.setPosition(m_Position);
    m_Sprite.setPosition(m_Position);

    // Has the bullet gone out of range?
    if (m_Position.x < m_MinX || m_Position.x > m_MaxX ||
        m_Position.y < m_MinY || m_Position.y > m_MaxY)
    {
        m_InFlightEnemy = false;
    }

}
