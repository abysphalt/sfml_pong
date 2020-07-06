#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
//#include <switch.h>
#include <dirent.h>

const int WIDTH = 1920/2;
const int HEIGTH = 1080/2;



extern int main()
{
    //  Setup NXLink and romfs
    //  socketInitializeDefault();
    //  nxlinkStdio();
    //  Result rc = romfsInit();


    sf::VideoMode vm(WIDTH, HEIGTH);
    sf::RenderWindow window(vm,"Pong");

    int score = 0;
    int lives = 3;

    Bat bat1(WIDTH/2, HEIGTH -20);
    Bat bat2(WIDTH/2, 20);
    Ball ball1(HEIGTH/2,0);

    sf::Text hud;
    sf::Font font;
    font.loadFromFile("fonts/sans.ttf");
    hud.setFont(font);
    hud.setCharacterSize(20);
    hud.setFillColor(sf::Color::White);
    hud.setPosition(20,20);

    sf::Clock clock;

    while (window.isOpen())
    {
        /*
        Handle input
        */
Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                //Quit the game when the window is closed
                window.close();
        }
        // Handle the player quitting
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Handle the pressing and releasing of the arrow keys
        if (Keyboard::isKeyPressed(Keyboard::Left) || sf::Joystick::isButtonPressed(0,1))
        {
            bat1.moveLeft();
        }
        else
        {
            bat1.stopLeft();
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            bat1.moveRight();
        }
        else
        {
            bat1.stopRight();
        }

        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            bat1.moveUp();
        }
        else
        {
            bat1.stopUp();
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            bat1.moveDown();
        }
        else
        {
            bat1.stopDown();
        }


        /*
        Update functions
        */

        sf::Time dt = clock.restart();
        bat1.update(dt);
        ball1.update(dt);
        std::stringstream ss;
        ss << "Score: " << score << " Lives: " << lives;
        hud.setString(ss.str());

        //Collision detection for each edge of the screen
        //Down
        if (ball1.getPosition().top > window.getSize().y - 30)

        {
            ball1.reboundBottom();
        }
        //UP
        if (ball1.getPosition().top < 0)
        {
            ball1.reboundTop();
        }

        //Left
        if (ball1.getPosition().left < 0)
        {
            ball1.reboundLeft();
        }

        //Right
        if (ball1.getPosition().left + ball1.getPosition().width > window.getSize().x )
        {
            ball1.reboundRight();
        }

        //Collision between bat and ball
        if(ball1.getPosition().intersects(bat1.getPosition()) || ball1.getPosition().intersects(bat2.getPosition()) )
        {
            ball1.reboundBat();
        }
        /*
        Draw functions
        */

        window.clear();
        window.draw(hud);
        window.draw(bat1.getShape());
        window.draw(bat2.getShape());
        window.draw(ball1.getShape());
        window.display();


    }

    return 0;
}
