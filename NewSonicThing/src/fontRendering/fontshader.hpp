#ifndef FONTSHADER_H
#define FONTSHADER_H

class Matrix4f;
class Camera;
class Light;
class Vector3f;

#include <glad/glad.h>


class FontShader
{
private:
    GLuint programId;
    GLuint vertexShaderId;
    GLuint fragmentShaderId;

    int location_color;
    int location_translation;
    int location_scale;

public:
    FontShader(const char*, const char*);

    void start();

    void stop();

    void cleanUp();

    void loadColor(Vector3f* color);

    void loadTranslation(Vector2f* translation);

    void loadScale(float scale);

protected:
    void bindAttributes();

    void bindAttribute(int, const char*);

    void getAllUniformLocations();

    int getUniformLocation(const char*);

    void loadFloat(int, float);

    void loadVector(int, Vector3f*);

    void load2DVector(int location, Vector2f* vect);

    void loadBoolean(int, float);

    void loadMatrix(int, Matrix4f*);

    GLuint loadShader(const char*, int);
};

#endif
