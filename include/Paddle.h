#ifndef PADDLE_H
#define PADDLE_H
#include <SFML/Graphics.hpp>

using namespace sf;

class Paddle
{
    public:
        Paddle();
        Paddle(float width, float height, float paddleSpeed, float windowCenterX, float windowCenterY);
        RectangleShape getShape();
        void update();
        float leftOfPaddle();
        float rightOfPaddle();
        float topOfPaddle();

    protected:

    private:
        RectangleShape paddleShape;
        float speed;
        float windowHeight;
        float windowWidth;
        bool isMostLeft();
        bool isMostRight();

};

#endif // PADDLE_H
