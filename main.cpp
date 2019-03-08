#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"

using namespace std;
using namespace sf;

void checkCollisionBallPaddle(Ball* ball, Paddle paddle)
{
    float ballBottomY = ball->getShape().getPosition().y;
    float ballLeftX = ball->getShape().getPosition().x - (ball->getShape().getScale().x/2);
    float ballRightX = ball->getShape().getPosition().x + (ball->getShape().getScale().x/2);

    if (ballLeftX >= paddle.leftOfPaddle()
        && ballRightX <= paddle.leftOfPaddle()+0.21*paddle.getShape().getSize().x
        && ballBottomY >= paddle.topOfPaddle())
    {
        ball->bouncePaddleLeft();
    } else if(ballLeftX >= paddle.leftOfPaddle()+0.20*paddle.getShape().getSize().x
              && ballRightX <= paddle.leftOfPaddle()+0.41*paddle.getShape().getSize().x
              && ballBottomY >= paddle.topOfPaddle())
    {
        ball->bouncePaddleMiddleLeft();
    } else if(ballLeftX >= paddle.leftOfPaddle()+0.40*paddle.getShape().getSize().x
              && ballRightX <= paddle.leftOfPaddle()+0.61*paddle.getShape().getSize().x
              && ballBottomY >= paddle.topOfPaddle())
    {
        ball->bouncePaddleMiddle();
    } else if(ballLeftX >= paddle.leftOfPaddle()+0.60*paddle.getShape().getSize().x
              && ballRightX <= paddle.leftOfPaddle()+0.81*paddle.getShape().getSize().x
              && ballBottomY >= paddle.topOfPaddle())
    {
        ball->bouncePaddleMiddleRight();
    } else if(ballLeftX >= paddle.leftOfPaddle()+0.80*paddle.getShape().getSize().x
              && ballRightX <= paddle.rightOfPaddle()
              && ballBottomY >= paddle.topOfPaddle())
    {
        ball->bouncePaddleRight();
    }

}

bool isIntesecting(Ball* ball, Block* block)
{
    float ballBottomY = ball->getShape().getPosition().y + (ball->getShape().getScale().y/2);
    float ballTopY = ball->getShape().getPosition().y - (ball->getShape().getScale().y/2);
    float ballLeftX = ball->getShape().getPosition().x - (ball->getShape().getScale().x/2);
    float ballRightX = ball->getShape().getPosition().x + (ball->getShape().getScale().x/2);


    return ((ballTopY <= block -> getBlockBottomY()
       && ball->getShape().getPosition().x >= block->getBlockLeftX()
       && ball->getShape().getPosition().x <= block->getBlockRightX()
       && ballTopY >= block->getBlockTopY())
        || (ballBottomY >= block->getBlockTopY()
       && ball->getShape().getPosition().x >= block->getBlockLeftX()
       && ball->getShape().getPosition().x <= block->getBlockRightX()
       && ballBottomY <= block->getBlockBottomY())
        || (ballLeftX <= block->getBlockRightX()
      && ball->getShape().getPosition().y <= block->getBlockBottomY()
      && ball->getShape().getPosition().y >= block->getBlockTopY()
      && ballLeftX >= block->getBlockLeftX())
        || (ballRightX >= block->getBlockLeftX()
     && ball->getShape().getPosition().y <= block->getBlockBottomY()
     && ball->getShape().getPosition().y >= block->getBlockTopY()
     && ballRightX <= block->getBlockRightX()));
}

void checkCollisionBallBlock(Ball* ball, Block* block)
{
    if (isIntesecting(ball, block))
    {
        float ballBottomY = ball->getShape().getPosition().y + (ball->getShape().getScale().y/2);
        float ballTopY = ball->getShape().getPosition().y - (ball->getShape().getScale().y/2);
        float ballLeftX = ball->getShape().getPosition().x - (ball->getShape().getScale().x/2);
        float ballRightX = ball->getShape().getPosition().x + (ball->getShape().getScale().x/2);

        float intersectLeft(block->getBlockLeftX()-ballRightX);
        float intersectTop(block->getBlockTopY()-ballBottomY);
        float intersectRight(block->getBlockRightX()-ballLeftX);
        float intersectBottom(block->getBlockBottomY()-ballTopY);

        bool fromLeft(abs(intersectLeft) < abs(intersectRight));
        bool fromBottom(abs(intersectBottom) < abs(intersectTop));

        float intersectionX(fromLeft ? abs(intersectLeft) : abs(intersectRight));
        float intersectionY(fromBottom ? abs(intersectBottom) : abs(intersectTop));

        if(intersectionX < intersectionY)
        {
            fromLeft ? ball->bounceFromRight() : ball->bounceFromLeft();
            block->destroy();
        } else
        {
            fromBottom ? ball->bounceFromTop() : ball->bounceFromBottom();
            block->destroy();
        }

    }
}

int main()
{
    int windowLength = 800, windowHeight = 600;
    RenderWindow window(VideoMode(windowLength, windowHeight), "Arkanoid");
    Ball ball(8, 5, windowLength/2, windowHeight/2);
    CircleShape lifes[3];
    Block blocks[8][4];
    Paddle paddle(100, 20, 5.0, windowLength/2, windowHeight/2);
    window.setFramerateLimit(60);
    int blockNumber = 8*4;
    for(int i=0; i<8; i++)
        for(int j=0; j<4; j++)
            blocks[i][j] = Block(100, 25, i, j);
    for(int i=0; i<3; i++)
    {
        lifes[i] = CircleShape(5);
        lifes[i].setOrigin(Vector2f(2.5, 2.5));
        lifes[i].setPosition(Vector2f(750 + 15*i, 575));
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
        }

        window.clear();
        if(ball.getLifes() >= 0){
            if(blockNumber > 0)
            {
            paddle.update();
            ball.update();
            blockNumber = 0;

            checkCollisionBallPaddle(&ball, paddle);
            for(int i=0; i<8; i++)
                for(int j=0; j<4; j++)
                    if(!blocks[i][j].isDestroyed()){
                        checkCollisionBallBlock(&ball, &blocks[i][j]);
                        window.draw(blocks[i][j].getShape());
                        blockNumber++;
                    }
            ball.checkDeath();
            for(int i=0; i<ball.getLifes(); i++)
                window.draw(lifes[i]);


            window.draw(paddle.getShape());
            window.draw(ball.getShape());


            } else
            {
                Font font;
                font.loadFromFile("assets/fonts/ARCADECLASSIC.TTF");
                Text youLost("YOU\nWON!", font);
                sf::FloatRect textRect = youLost.getLocalBounds();
                youLost.setCharacterSize(60);
                youLost.setOrigin(textRect.left + textRect.width/2, textRect.top + textRect.height/2);
                youLost.setPosition(Vector2f(windowLength/2.0f,windowHeight/2.0f));

                window.draw(youLost);
            }



        } else
        {
            Font font;
            font.loadFromFile("assets/fonts/ARCADECLASSIC.TTF");
            Text youLost("YOU\nLOST!", font);
            sf::FloatRect textRect = youLost.getLocalBounds();
            youLost.setCharacterSize(60);
            youLost.setOrigin(textRect.left + textRect.width/2, textRect.top + textRect.height/2);
            youLost.setPosition(Vector2f(windowLength/2.0f,windowHeight/2.0f));

            window.draw(youLost);
        }

        window.display();

    }
    return 0;
}
