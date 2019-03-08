#include "Ball.h"

Ball::Ball()
{

}

Ball::Ball(int radius, float ballSpeed, float windowCenterX, float windowCenterY)
{
    speed = ballSpeed;
    direction = Vector2f(-speed, -speed);
    ballShape = CircleShape(radius);
    ballShape.setFillColor(Color::White);
    ballShape.setPosition(windowCenterX, windowCenterY);
    ballShape.setOrigin(radius, radius);
    windowWidth = windowCenterX*2;
    windowHeight = windowCenterY*2;
    lifes = 3;
}

int Ball::getLifes()
{
    return lifes;
}

int Ball::getBallRadius()
{
    return ballShape.getScale().x;
}

CircleShape Ball::getShape()
{
    return ballShape;
}

void Ball::update()
{
    ballShape.move(direction);

    if (hitTop())
    {
        direction.y = speed;
    } else if (hitBottom())
    {
        direction.y = -speed;
    } else if (hitLeft())
    {
        direction.x = speed;
    } else if (hitRight())
    {
        direction.x = -speed;
    }
}

bool Ball::hitTop()
{
    return ballShape.getPosition().y - getBallRadius() < 0;
}

bool Ball::hitBottom()
{
    return ballShape.getPosition().y + getBallRadius() > windowHeight;
}

bool Ball::hitLeft()
{
    return ballShape.getPosition().x - getBallRadius() < 0;
}

bool Ball::hitRight()
{
    return ballShape.getPosition().x + getBallRadius() > windowWidth;
}

void Ball::bouncePaddleLeft()
{
    direction.y = -speed;
    direction.x = -speed;
}

void Ball::bouncePaddleMiddleLeft()
{
    direction.y = -speed;
    direction.x = -speed/2;
}

void Ball::bouncePaddleMiddle()
{
    direction.y = -speed;
    direction.x = 0;
}

void Ball::bouncePaddleMiddleRight()
{
    direction.y = -speed;
    direction.x = speed/2;
}

void Ball::bouncePaddleRight()
{
    direction.y = -speed;
    direction.x = speed;
}

void Ball::bounceFromBottom()
{
    direction.y = -speed;
}

void Ball::bounceFromLeft()
{
    direction.x = speed;
}

void Ball::bounceFromRight()
{
    direction.x = -speed;
}

void Ball::bounceFromTop()
{
    direction.y = speed;
}

void Ball::die()
{
    Clock clock;
    lifes--;
    ballShape.setPosition(windowWidth/2, windowHeight/2);
    direction.x = direction.y = 0;

    while(clock.getElapsedTime().asSeconds() <= 2)
    {

    }

    bounceFromBottom();


}

void Ball::checkDeath()
{
    if(getShape().getPosition().y + getBallRadius() > windowHeight)
    {
        die();
    }
}

