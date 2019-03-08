#include "Paddle.h"

using namespace sf;

Paddle::Paddle()
{

}

Paddle::Paddle(float width, float height, float paddleSpeed, float windowCenterX, float windowCenterY)
{
    paddleShape = RectangleShape(Vector2f(width, height));
    paddleShape.setFillColor(Color::White);
    paddleShape.setPosition(windowCenterX, (2*windowCenterY)-(2*height));
    paddleShape.setOrigin(width/2, height/2);
    speed = paddleSpeed;
    windowWidth = windowCenterX*2;
    windowHeight = windowCenterY*2;
}

RectangleShape Paddle::getShape()
{
    return paddleShape;
}

void Paddle::update()
{
    if (Keyboard::isKeyPressed(Keyboard::Left) && !isMostLeft()){
        paddleShape.move(-speed, 0);
    } else if (Keyboard::isKeyPressed(Keyboard::Right) && !isMostRight())
    {
        paddleShape.move(speed, 0);
    }
}

bool Paddle::isMostLeft()
{
    return (paddleShape.getPosition().x) - (paddleShape.getSize().x/2) < 0;
}

bool Paddle::isMostRight()
{
    return (paddleShape.getPosition().x) + (paddleShape.getSize().x/2) > windowWidth;
}

float Paddle::leftOfPaddle()
{
    return (paddleShape.getPosition().x) - (paddleShape.getSize().x/2);
}

float Paddle::rightOfPaddle()
{
    return (paddleShape.getPosition().x) + (paddleShape.getSize().x/2);
}

float Paddle::topOfPaddle()
{
    return (paddleShape.getPosition().y) - (paddleShape.getSize().y/2);
}
