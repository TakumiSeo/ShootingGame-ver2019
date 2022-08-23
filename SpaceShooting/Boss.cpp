#include<iostream>
#include<cstdlib>
#include<ctime>
#include "Boss.hpp"
#include "textureHolder.hpp"
Boss::Boss()
{
m_Speed = START_SPEED;
m_Health = START_HEALTH;
// Bossのビームに入れる
m_BeamPower = BEAM_POWER;

m_Sprite =
          Sprite(TextureHolder::GetTexture("../Resources/graphics/tekibig.PNG"));
//m_Texture.loadFromFile("../Resources/graphics/hikouki.PNG");
m_Sprite.setScale(0.15f, 0.15f);
//m_Sprite.setTexture(m_Texture);

m_Sprite.setOrigin(0, 0);
}

void Boss::spawn(IntRect space, Vector2f resolution, int limitSize)
{
  m_Position.x = space.width / 2;
  m_Position.y = 50;

  // Copy the details of the arena to the player's m_Arena
  m_Space.left = space.left;
  m_Space.width = space.width;
  m_Space.top = space.top;
  m_Space.height = space.height;

  m_LimitSize = limitSize;
  // Store the resolution for future use
  m_Resolution.x = resolution.x;
  m_Resolution.y = resolution.y;
}

bool Boss::hit(int beamOfPlane)
{
  m_Health -= beamOfPlane;
  std::cout << m_Health << '\n';

  if(m_Health < 0)
  {
    m_AliveBoss = false;

    //m_Sprite =
              //Sprite(TextureHolder::GetTexture("../Resources/graphics/ishi.PNG"));
    //m_Sprite.setScale(0.15f, 0.15f);

    return true;
  }

  return false;

}

void Boss::resetPlayerStats()
{
    m_Speed = START_SPEED;
    m_Health = START_HEALTH;
}

bool Boss::isAliveBoss()
{
  return m_AliveBoss;
}

FloatRect Boss::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

Vector2f Boss::getCenter()
{
    return m_Position;
}
Sprite Boss::getSprite()
{
    return m_Sprite;
}

int Boss::getHealth()
{
    return m_Health;
}

void Boss::moveLeft()
{
    m_LeftPressed = true;
}

void Boss::moveRight()
{
    m_RightPressed = true;
}

void Boss::stopLeft()
{
    m_LeftPressed = false;
}

void Boss::stopRight()
{
    m_RightPressed = false;
}



void Boss::update(float elapsedTime, Vector2i mousePosition, IntRect space)
{


    if (m_RightPressed)
    {
        m_Position.x -= m_Speed * elapsedTime;
        //std::cout <<elapsedTime<<","<< '\n';
        srand(static_cast<unsigned int>(time(0)));
        int judge = rand()%2;
    }
    if (m_LeftPressed)
    {
        m_Position.x += m_Speed * elapsedTime;
        srand(static_cast<unsigned int>(time(0)));
        int judge = rand()%2;
    }

    if(!m_RightPressed && !m_LeftPressed)
    {
          srand(static_cast<unsigned int>(time(0)));
          int judge = rand()%2;
          //std::cout << judge << '\n';
          if(judge == 0)
          {
            m_Position.x += m_Speed * 0.003;
          }
          else
          {
            m_Position.x -= m_Speed * 0.003;
          }
    }

        if (m_Position.x > m_Space.width - m_LimitSize)
        {
            m_Position.x = m_Space.width - m_LimitSize;
        }

        if (m_Position.x < m_Space.left + m_LimitSize)
        {
            m_Position.x = m_Space.left + m_LimitSize;
        }

    m_Sprite.setPosition(m_Position);

    // Keep the player in the arena


    float angle = 0;
    m_Sprite.setRotation(angle);

}
