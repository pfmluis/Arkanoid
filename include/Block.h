#ifndef BLOCK_H
#define BLOCK_H
#include <SFML/Graphics.hpp>

using namespace sf;

class Block
{
    public:
        Block();
        Block(float width, float height, int horizontalIndex, int verticalIndex);
        RectangleShape getShape();
        bool isDestroyed();
        void destroy();
        float getBlockBottomY();
        float getBlockTopY();
        float getBlockLeftX();
        float getBlockRightX();

    protected:

    private:
        RectangleShape rectangleShape;
        bool destroyed = false;
};

#endif // BLOCK_H
