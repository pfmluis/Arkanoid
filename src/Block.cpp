#include "Block.h"

Block::Block()
{
}

Block::Block(float width, float height, int horizontalIndex, int verticalIndex)
{
    rectangleShape = RectangleShape(Vector2f(width, height));
    rectangleShape.setPosition((horizontalIndex*2)+(horizontalIndex*width), height + (verticalIndex*2)+(verticalIndex*height));
}

RectangleShape Block::getShape()
{
    return rectangleShape;
}

void Block::destroy()
{
    destroyed = true;
}

bool Block::isDestroyed()
{
    return destroyed;
}

float Block::getBlockBottomY()
{
    return rectangleShape.getPosition().y + rectangleShape.getSize().y;
}

float Block::getBlockTopY()
{
    return rectangleShape.getPosition().y;
}

float Block::getBlockRightX()
{
    return rectangleShape.getPosition().x + rectangleShape.getSize().x;
}

float Block::getBlockLeftX()
{
    return rectangleShape.getPosition().x;
}
