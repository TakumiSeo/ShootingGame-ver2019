#include <iostream>
#include "beam.hpp"
#include "textureHolder.hpp"

Beam::Beam()
{
  m_BeamPower = BEAM_POWER;
  m_Sprite = Sprite(TextureHolder::
      GetTexture("../Resources/graphics/kousen2.PNG"));
  m_Sprite.setScale(0.08f, 0.08f);
  m_Sprite.setOrigin(0, 0);
}

void Beam::shoot(float startX, float startY,
                  float targetX, float targetY)
{
  // Keep track of the beam
  m_InFlightBoss = true;
  m_Position.x = startX + 20;
  m_Position.y = startY + 40;

  float gradient = 0;
  // in this case,
  // float ratioXY = m_BeamSpeed;

  m_BeamDistanceY = m_BeamSpeed;
  m_BeamDistanceX = 0;

  if (targetY < startY)
  {
      m_BeamDistanceY *= +1;
  }
  //
  // Set a max range of 1000 pixels
  float range = 1000;
  m_MinX = startX - range;
  m_MaxX = startX + range;
  m_MinY = startY - range;
  m_MaxY = startY + range;

  // Position the bullet ready to be drawn
  m_BeamShape.setPosition(m_Position);
}

float Beam::getBeamPower()
{
  return m_BeamPower;
}
void Beam::stop()
{
  m_InFlightBoss = false;
}

bool Beam::isInFlightBoss()
{
  return m_InFlightBoss;
}

FloatRect Beam::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

RectangleShape Beam::getShape()
{
    return m_BeamShape;
}

Sprite Beam::getSprite()
{
  return m_Sprite;
}

void Beam::update(float elapsedTime)
{
    // Update the bullet position variables
    m_Position.x += m_BeamDistanceX * elapsedTime;
    m_Position.y += m_BeamDistanceY * elapsedTime;
    //std::cout << "("<<m_Position.x<<","<<m_Position.y<<")"<<elapsedTime<< '\n';

    // Move the bullet
    // m_BulletShape.setPosition(m_Position);
    m_Sprite.setPosition(m_Position);

    // Has the bullet gone out of range?
    if (m_Position.x < m_MinX || m_Position.x > m_MaxX ||
        m_Position.y < m_MinY || m_Position.y > m_MaxY)
    {
        m_InFlightBoss = false;
    }

}
