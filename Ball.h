#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
private:
    Vector2f m_Position;
    RectangleShape m_Shape;

    float m_Speed = 1300.0f;
    float m_DirectionX = .2f;
    float m_DirectionY = .2f;

public:
    Ball(float startX,float startY);

    FloatRect getPosition();

    RectangleShape getShape();

    float getXVelocity();

    void reboundBat();
    void reboundBatOrSides();
    void reboundBatOrTop();

    void reboundTop();
    void reboundBottom();

    void reboundSides();
    void reboundLeft();
    void reboundRight();


    void resetSpeed();

    void update(Time dt);



};
