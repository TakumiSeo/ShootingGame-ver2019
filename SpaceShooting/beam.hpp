#ifndef beam_hpp
#define beam_hpp
#include <SFML/Graphics.hpp>

using namespace sf;

class Beam
{
private:
  const float BEAM_POWER = 100;
  // where is the beam
  Vector2f m_Position;

  // What the beam looks like
  RectangleShape m_BeamShape;

  //sprite
  Sprite m_Sprite;

  //Texture
  Texture m_Texture;

  bool m_InFlightBoss = false;

  // How fast does a beam ?
  float m_BeamSpeed = 1000;

  float m_BeamDistanceX;
  float m_BeamDistanceY;

  float m_XTarget;
  float m_YTarget;


  // Some boundaries so the bullet doesn't fly forever
  float m_MaxX;
  float m_MinX;
  float m_MaxY;
  float m_MinY;

  float m_BeamPower;

public:
  Beam();

  // stop the beam
  void stop();

  // Return the value of m_Flight
  bool isInFlightBoss();

  // Lanch a new beam
  void shoot(float startX, float startY,
              float xTarget, float yTarget);

  // tell the calling code where the beam int he world
  FloatRect getPosition();

  // Return the actual shape (for drawing)
  RectangleShape getShape();

  // Send a copy of sprite to main
  Sprite getSprite();

  // get a beam power
  float getBeamPower();

  // update
  void update(float elapsedTime);
};
#endif
