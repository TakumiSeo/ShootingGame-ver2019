// #include "stdafx.h" <- Visual Studio only
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>
#include <fstream>
#include "plane.hpp"
#include "textureHolder.hpp"
#include "bullet.hpp"
#include "Boss.hpp"
#include "beam.hpp"
#include "enemy.hpp"
#include "enemybeam.hpp"
#define defNumEnemy 7
using namespace sf;

int main()
{
    TextureHolder holder;
    // The game will always be in one of four states
    enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };

    // Start with the GAME_OVER state
    State state = State::GAME_OVER;

    // Get the screen resolution and create an SFML window
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    RenderWindow window(VideoMode(resolution.x, resolution.y),
                        "Zombie Arena", Style::Fullscreen);

    // Create a an SFML View for the main action
    View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

    // Here is our clock for timing everything
    Clock clock;

    // How long has the PLAYING state been active
    Time gameTimeTotal;
    Time gameTimeTotalBoss;
    Time gameTimeTotalEnemy;
    // Background
    Texture Backgroundtex;
    Backgroundtex.loadFromFile("../Resources/graphics/star2.jpg");
    Sprite BackgroundSp;
    BackgroundSp.setTexture(Backgroundtex);
    BackgroundSp.setPosition(-200,-200);
    // end Background

    // Where is the mouse in relation to world coordinates
    Vector2f mouseWorldPosition;

    // Where is the mouse in relation to screen coordinates
    Vector2i mouseScreenPosition;

    // Create an instance of the Player class
    Plane plane;

    // Create an instance of the Boss class
    Boss boss;
    int NumBoss = 1;
    // create an instance of boss beam
    Beam beam;
    float BossBeamPower = beam.getBeamPower();

    // Create an instance of the the Enemy class
    Enemy enemy;
    int NumEnemy = 7;
    std::vector<Enemy> enemyList;
    for(int i = 0; i < NumEnemy; ++i)
    {
      enemyList.push_back(enemy);
    }


    // The boundaries of the arena
    IntRect space;

    // create instance of Beam from plane
    Bullet bullets;
    float fireRate = 1;
    int beamOfPlane = bullets.getBeamPower();
    std::cout << beamOfPlane << '\n';

    // generate enemys instance
    EnemyBeam enemybeam;
    std::vector<EnemyBeam> enemybeamList;
    for(int i = 0; i < NumEnemy; ++i)
    {
      enemybeamList.push_back(enemybeam);
    }
    float EnemyBeamPower = enemybeam.getBeamPower();

    Time lastPressed;
    Time lastPressedBoss;
    Time lastPressedEnemy;

    // For home / gameover screen

    Sprite spriteGameOver;
    Texture textureGameOver = TextureHolder::GetTexture("../Resources/graphics/sennkann.jpeg");
    spriteGameOver.setTexture(textureGameOver);
    spriteGameOver.setPosition(0,0);
    spriteGameOver.setScale(resolution.x/1024,resolution.y/768);

    // Load the font
    Font font;
    font.loadFromFile("../Resources/Fonts/KenneyFuture.ttf");

    //PAUSED
    Text pausedText;
    pausedText.setFont(font);
    pausedText.setCharacterSize(155);
    pausedText.setFillColor(Color::White);
    pausedText.setString("Press Space \nto continue");

    FloatRect pausedRect = pausedText.getLocalBounds();
    pausedText.setOrigin(pausedRect.left+pausedRect.width/2.0f,pausedRect.top+pausedRect.height/2.0f);
    pausedText.setPosition(resolution.x/2, resolution.y/2);

    // Game Over
    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(90);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setString("Space Shooting game");
    Text gameOverText2;
    gameOverText2.setFont(font);
    gameOverText2.setCharacterSize(50);
    gameOverText2.setFillColor(sf::Color::Black);
    gameOverText2.setString("Press Enter to play");

    FloatRect gameOverRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(gameOverRect.left+gameOverRect.width/2.0f, gameOverRect.top+gameOverRect.height/2.0f);
    gameOverText.setPosition(resolution.x/2, resolution.y/2);

    FloatRect gameOverRect2 = gameOverText2.getLocalBounds();
    gameOverText2.setOrigin(gameOverRect2.left+gameOverRect2.width/2.0f, gameOverRect2.top+gameOverRect2.height/2.0f);
    gameOverText2.setPosition(resolution.x/2, resolution.y/2 + 100);

    //health Bar
    RectangleShape healthBar;
    healthBar.setFillColor(Color::Blue);
    healthBar.setPosition(resolution.x * 0+ 10, resolution.y*0 + 10);
    healthBar.setScale(0.4f,0.4f);


    // The main game loop
    while (window.isOpen())
    {
        /*
         ************
         Handle input
         ************
         */
        // Handle events
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                // Pause a game while playing
                if (event.key.code == Keyboard::Return &&
                    state == State::PLAYING)
                {
                    state = State::PAUSED;
                    std::cout << "eeeeeeeeeee" << '\n';
                }

                // Restart while paused
                else if (event.key.code == Keyboard::Return &&
                         state == State::PAUSED)
                {
                    state = State::PLAYING;
                    // Reset the clock so there isn't a frame jump
                    clock.restart();
                }

                // Start a new game while in GAME_OVER state
                else if (event.key.code == Keyboard::Return &&
                         state == State::GAME_OVER)
                {
                  std::cout << "1eeeeeeeeeee" << '\n';

                    state = State::LEVELING_UP;
                    plane.resetPlayerStats();
                    boss.resetPlayerStats();
                    //boss.isAliveBoss() = true;

                    for(int i = 0; i < defNumEnemy; i++)
                    {
                      enemyList[i].resetPlayerStats();
                      //enemyList[i].isAliveEnemy() = true;
                    }

                    NumEnemy = defNumEnemy;
                }

            } //End if (event.type == Event::KeyPressed)
        }// End event polling


        // Handle the player quitting
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Handle controls while playing
        if (state == State::PLAYING)
        {

            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                plane.moveLeft();
                boss.moveLeft();
            }
            else
            {
                plane.stopLeft();
                boss.stopLeft();
            }

            if (Keyboard::isKeyPressed(Keyboard::D))
            {
                plane.moveRight();
                boss.moveRight();
            }
            else
            {
                plane.stopRight();
                boss.stopRight();
            }
            // Fire a bullet
            if (Keyboard::isKeyPressed(Keyboard::W)) {

                if (gameTimeTotal.asMilliseconds()
                    - lastPressed.asMilliseconds()
                    > 1000 / fireRate)
                {
                    // bullets[currentBullet].shoot(
                    //                              plane.getCenter().x + 20, plane.getCenter().y,
                    //                              mouseWorldPosition.x, mouseWorldPosition.y - resolution.y);
                    //
                    // currentBullet++;
                    // lastPressed = gameTimeTotal;
                    bullets.shoot(
                                                 plane.getCenter().x + 20, plane.getCenter().y,
                                                 mouseWorldPosition.x, mouseWorldPosition.y - resolution.y);


                    lastPressed = gameTimeTotal;
                }

            }// End fire a bullet
          }

          // beam of Boss
          if(state == State::PLAYING)
          {
            if (gameTimeTotalBoss.asMilliseconds()
                - lastPressedBoss.asMilliseconds()
                > 900 / fireRate)
                {
                    beam.shoot(
                    boss.getCenter().x + 10, boss.getCenter().y,
                    mouseWorldPosition.x, mouseWorldPosition.y - resolution.y);
                    lastPressedBoss = gameTimeTotalBoss;
                }// End fire a bullet
        }// End WASD while playing

        // beam of small enemy
        if(state == State::PLAYING)
        {

          if (gameTimeTotalEnemy.asMilliseconds()
              - lastPressedEnemy.asMilliseconds()
              > 1000 / fireRate)
            {
              for(int i = 0; i < NumEnemy; ++i)
              {
                  enemybeamList[i].shoot(
                  enemyList[i].getCenter().x, enemyList[i].getCenter().y,
                  mouseWorldPosition.x, mouseWorldPosition.y - resolution.y);
                  lastPressedEnemy = gameTimeTotalEnemy;
              }
            }

            // End fire a bullet
      }// End WASD while playing

        // Handle the levelling up state
        if (state == State::LEVELING_UP)
        {
            // Handle the player levelling up
            if (Keyboard::isKeyPressed(Keyboard::R))
            {
                state = State::PLAYING;
            }

            if (event.key.code == Keyboard::Num2)
            {
                state = State::PLAYING;
            }

            if (event.key.code == Keyboard::Num3)
            {
                state = State::PLAYING;
            }

            if (event.key.code == Keyboard::Num4)
            {
                state = State::PLAYING;
            }

            if (event.key.code == Keyboard::Num5)
            {
                state = State::PLAYING;
            }

            if (event.key.code == Keyboard::Num6)
            {
                state = State::PLAYING;
            }

            if (state == State::PLAYING)
            {
                // Prepare the level
                // We will modify the next two lines later
                space.width = resolution.x-30;
                space.height = resolution.y-90;
                space.left = 0;
                space.top = 0;

                // We will modify this line of code later
                int limitSize = 50;

                // Spawn the player in the middle of the arena
                plane.spawn(space, resolution, limitSize);

                boss.spawn(space, resolution, limitSize);

                for(int distance = 0; distance < NumEnemy; distance++)
                {

                  enemyList[distance].spawn(space, resolution, distance, NumEnemy);

                }

                //enemy.spawn(space, resolution, limitSize);


                // Reset the clock so there isn't a frame jump
                clock.restart();
            }
        }// End levelling up

        /*
         ****************
         UPDATE THE FRAME
         ****************
         */
        if (state == State::PLAYING)
        {
            // Update the delta time
            Time dt = clock.restart();
            // Update the total game time
            gameTimeTotal += dt;
            gameTimeTotalBoss += dt;
            gameTimeTotalEnemy += dt;
            // Make a decimal fraction of 1 from the delta time
            float dtAsSeconds = dt.asSeconds();
            float dtAsSecondsBoss = dt.asSeconds();
            float dtAsSecondsEnemy = dt.asSeconds();

            // Where is the mouse pointer
            mouseScreenPosition = Mouse::getPosition(window);

            // Convert mouse position to world coordinates of mainView
            mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);

            // Update the player
            plane.update(dtAsSeconds, Mouse::getPosition());

            boss.update(dtAsSecondsBoss, Mouse::getPosition(), space);

            // Make a note of the players new position
            Vector2f planePosition(plane.getCenter());

            Vector2f bossPosition(boss.getCenter());

            std::vector<Vector2f> enemyPositionList;

            for(int distance = 0; distance < NumEnemy; distance++)
            {

              enemyPositionList.push_back(enemyList[distance].getCenter());

            }

            //Vector2f enemyPosition(enemy.getCenter());

            // Make the view centre around the player
            //mainView.setCenter(player.getCenter());

          // plane beam
            // for(int i = 0; i < 100; ++i)
            // {
              if(bullets.isInFlight())
              {
                bullets.update(dtAsSeconds);
              }
            //}
            // Boss beam
            if(beam.isInFlightBoss())
            {
              beam.update(dtAsSecondsBoss);
            }
            //enemy beam
            for(int i = 0; i < NumEnemy; ++i)
            {
              if(enemybeamList[i].isInFlightEnemy())
              {

                enemybeamList[i].update(dtAsSecondsEnemy);
              }

            }

            // Collision Detection of Boss
            // for(int i = 0;i < 100; i++)
            // {
              for(int j=0; j < NumEnemy; j++)
              {
                if(bullets.isInFlight() && boss.isAliveBoss())
                {
                if(bullets.getPosition().intersects(boss.getPosition()))
                {
                  //Stop the bullets
                  bullets.stop();

                  // Register the hit and see if it was a kill
                  if(boss.hit(beamOfPlane))
                  {
                    // not just a hit but a kill too
                    NumBoss--;
                  }
                }
                }
              }
            //}

            for(int j=0; j < NumEnemy; j++)
            {
              if(bullets.isInFlight() && enemyList[j].isAliveEnemy())
              {
              if(bullets.getPosition().intersects(enemyList[j].getPosition()))
              {
                //Stop the bullets
                bullets.stop();

                // Register the hit and see if it was a kill
                if(enemyList[j].hit(beamOfPlane))
                {
                  // not just a hit but a kill too
                  NumEnemy--;
                }
              }
              }
            }// End Enemy Collision

          // whather plane got Bossbeam
          if(plane.getPosition().intersects(beam.getPosition()) &&
              beam.isInFlightBoss())
              {
                if(plane.hit(gameTimeTotal,BossBeamPower))
                {

                }
                if(plane.getHealth() <= 0)
                {
                  // plane.resetPlayerStats();
                  // boss.resetPlayerStats();
                  // for(int i = 0; i < defNumEnemy; i++)
                  // {
                  //   enemyList[i].resetPlayerStats();
                  // }
                  state = State::GAME_OVER;

                }
              }

            // whather plane got enemybeam
            for(int i = 0; i < NumEnemy; i++)
            {
            if(plane.getPosition().intersects(enemybeamList[i].getPosition()) &&
                enemybeamList[i].isInFlightEnemy())
                {
                  if(plane.hit(gameTimeTotal,EnemyBeamPower))
                  {

                  }
                  if(plane.getHealth() <= 0)
                  {
                    plane.resetPlayerStats();
                    state = State::GAME_OVER;
                  }
                }
              }

        }// End updating the scene

        healthBar.setSize(Vector2f(plane.getHealth()*3, 70));

        /*
         **************
         Draw the scene
         **************
         */

        if (state == State::PLAYING)
        {
            window.clear();
            window.draw(BackgroundSp);
            window.setView(mainView);

            // for(int i =  0; i < 100; i++)
            // {
              if(bullets.isInFlight())
              {
                window.draw(bullets.getSprite());
              }
            //}


            for(int i = 0; i < NumEnemy; ++i)
            {
              if(enemybeamList[i].isInFlightEnemy() && enemyList[i].isAliveEnemy())
              {
                window.draw(enemybeamList[i].getSprite());
              }
            }




            if(beam.isInFlightBoss() && NumBoss == 1)
            {
              window.draw(beam.getSprite());
            }
            // Draw the player
            window.draw(plane.getSprite());

            for(int distance = 0; distance < NumEnemy; distance++)
            {
              if(enemyList[distance].isAliveEnemy())
                window.draw(enemyList[distance].getSprite());
            }

            if(NumBoss == 1)
            {
            window.draw(boss.getSprite());
            }

            window.draw(healthBar);
        }

        if (state == State::LEVELING_UP)
        {
        }

        if (state == State::PAUSED)
        {
          window.draw(pausedText);
        }

        if (state == State::GAME_OVER)
        {
          window.draw(spriteGameOver);
          window.draw(gameOverText);
          window.draw(gameOverText2);

        }

        window.display();

    }// End game loop


    return 0;
}
