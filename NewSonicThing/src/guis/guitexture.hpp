#ifndef GUITEXTURE_H
#define GUITEXTURE_H

#include <glad/glad.h>
#include "../toolbox/vector.hpp"

class GuiTexture
{
private:
    GLuint textureId;
    Vector2f position;
    Vector2f sizeRaw;
    Vector2f sizeScaled;
    float scale;
    float rotation;
    bool visible;

public:
    GuiTexture();

    //position is (0,0) = top left of screen, (1,1) is bottom right
    //Note that the image is drawn with its CENTER at position
    GuiTexture(GLuint textureId, Vector2f* position, Vector2f* size, float rotation);

    //position is (0,0) = top left of screen, (1,1) is bottom right
    //Note that the image is drawn with its CENTER at position
    GuiTexture(GLuint textureId, float posX, float posY, float sizeX, float sizeY, float rotation);

    GLuint getTexture();

    void setTexture(GLuint newTextureId);

    //WARNING: ONLY use this to read the position, do NOT use this to write to the position, use setX and setY
    Vector2f* getPosition();

    Vector2f* getSizeRaw();

    Vector2f* getSizeScaled();

    //If you REALLY want control over the size that the image will actually be rendered, set that here.
    //Note that changes here will be overwritten if you call setScale() after.
    void setSizeScaled(float scaleX, float scaleY);

    float getRotation();

    void setRotation(float newRotation);

    //position is (0,0) = top left of screen, (1,1) is bottom right
    //Note that the image is drawn with its CENTER at position
    void setX(float newX);

    //position is (0,0) = top left of screen, (1,1) is bottom right
    //Note that the image is drawn with its CENTER at position
    void setY(float newY);

    bool getVisible();

    void setVisible(bool newVisible);

    float getScale();

    void setScale(float newScale);

};

#endif