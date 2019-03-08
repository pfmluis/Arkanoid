#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>

using namespace sf;
class Ball
{
    public:
        Ball();
        Ball(int radius, float speed, float windowCenterX, float windowCenterY);
        int getBallRadius();
        CircleShape getShape();
        void update();
        void bouncePaddleLeft();
        void bouncePaddleMiddleLeft();
        void bouncePaddleMiddle();
        void bouncePaddleMiddleRight();
        void bouncePaddleRight();
        void bounceFromTop();
        void bounceFromLeft();
        void bounceFromBottom();
        void bounceFromRight();
        int getLifes();
        void checkDeath();

    protected:

    private:
        float speed;
        int lifes;
        CircleShape ballShape;
        Vector2f direction;
        bool hitBottom();
        bool hitTop();
        bool hitLeft();
        bool hitRight();
        float windowHeight;
        float windowWidth;
        void die();
        void restart();
};

#endif // BALL_H
