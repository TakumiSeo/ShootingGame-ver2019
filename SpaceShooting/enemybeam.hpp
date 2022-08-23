#ifndef tekibeam_hpp
#define tekibeam_hpp
#include <SFML/Graphics.hpp>

using namespace sf;

class EnemyBeam
{
private:
  const float BEAM_POWER = 30;
  // where is the beam
  Vector2f m_Position;

  // What the beam looks like
  RectangleShape m_EnemyBeamShape;

  //sprite
  Sprite m_Sprite;

  //Texture
  Texture m_Texture;

  bool m_InFlightEnemy = false;

  // How fast does a beam ?
  float m_EnemyBeamSpeed = 500;

  float m_EnemyBeamDistanceX;
  float m_EnemyBeamDistanceY;

  float m_XTarget;
  float m_YTarget;


  // Some boundaries so the bullet doesn't fly forever
  float m_MaxX;
  float m_MinX;
  float m_MaxY;
  float m_MinY;

  // beam power
  float m_BeamPower;

public:
  EnemyBeam();

  // stop the beam
  void stop();

  // Return the value of m_Flight
  bool isInFlightEnemy();

  // Lanch a new beam
  void shoot(float startX, float startY,
              float xTarget, float yTarget);

  // tell the calling code where the beam int he world
  FloatRect getPosition();

  // Return the actual shape (for drawing)
  RectangleShape getShape();

  // Send a copy of sprite to main
  Sprite getSprite();

  // update
  void update(float elapsedTime);

  // get a beam beam power
  float getBeamPower();
};
#endif
