
#ifndef Boss_hpp
#define Boss_hpp

#include <SFML/Graphics.hpp>
#include <math.h>       /* atan2 */

using namespace sf;

class Boss
{
private:
  const float START_SPEED = 500;
  const float START_HEALTH = 1500;
  const float BEAM_POWER = 100;

  Vector2f m_Position;

  // What size is the current arena
  IntRect m_Space;

  Sprite m_Sprite;

  Texture m_Texture;

  Vector2f m_Resolution;

  int m_LimitSize;

  // Which directions is the player currently moving in
  //bool m_UpPressed;
  //bool m_DownPressed;
  bool m_LeftPressed;
  bool m_RightPressed;

  int m_Health;

  //Is it still is Alive
  bool m_AliveBoss = true;

  int m_BeamPower;

  float m_Speed;


public:
  Boss();

  bool hit(int beamOfPlane);

  bool isAliveBoss();

  void spawn(IntRect space, Vector2f resolution, int limitSize);
  // How long ago was the player last hit
  Time getLastHitTime();

  // Where is the player
  FloatRect getPosition();

  // Where is the center of the player?
  Vector2f getCenter();

  // Which angle is the player facing?
  //float getRotation();

  // Send a copy of the sprite to main
  Sprite getSprite();

  // How much health has the player currently got?
  int getHealth();

  // The next four functions move the player
  void moveLeft();

  void moveRight();

  // Stop the player moving in a specific direction
  void stopLeft();

  void stopRight();

  // We will call this function once every frame
  void update(float elapsedTime, Vector2i mousePosition, IntRect space);

  void upgradeHealth();

  void resetPlayerStats();

};
#endif
