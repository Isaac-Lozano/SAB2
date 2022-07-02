#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>


class Vector3f
{
public:
    float x;
    float y;
    float z;

    Vector3f();
    Vector3f(float x, float y, float z);
    Vector3f(Vector3f* other);

    float getX();
    float getY();
    float getZ();

    void set(float x, float y, float z);

    void set(Vector3f* other);

    float length();

    float lengthSquared();

    void setLength(float newLength);

    void normalize();

    void neg();

    float dot(Vector3f* other);

    void scale(float scale);

    Vector3f scaleCopy(float scale);

    Vector3f cross(Vector3f* other);

    Vector3f operator + (const Vector3f &other);

    Vector3f operator - (const Vector3f &other);

    Vector3f operator * (const Vector3f &other);

    Vector3f operator / (const Vector3f &other);

    bool operator == (const Vector3f &other);
};

const Vector3f X_AXIS(1, 0, 0);
const Vector3f Y_AXIS(0, 1, 0);
const Vector3f Z_AXIS(0, 0, 1);

const Vector3f X_AXIS_N(-1,  0,  0);
const Vector3f Y_AXIS_N( 0, -1,  0);
const Vector3f Z_AXIS_N( 0,  0, -1);

class Vector2f
{
public:
    float x;
    float y;

    Vector2f();
    Vector2f(float x, float y);
    Vector2f(Vector2f* other);

    float getX();
    float getY();

    void set(float x, float y);

    void set(Vector2f* other);

    float length();

    float lengthSquared();

    Vector2f normalized();

    void neg();

    float dot(Vector2f* other);

    Vector2f scaleCopy(float scale);

    Vector2f operator + (const Vector2f &other);

    Vector2f operator - (const Vector2f &other);

    Vector2f operator * (const Vector2f &other);

    Vector2f operator / (const Vector2f &other);

    Vector2f operator * (const float &scale);
};

class Vector4f
{
public:
    float x;
    float y;
    float z;
    float w;

    Vector4f();
    Vector4f(float x, float y, float z, float w);
    Vector4f(Vector4f* other);

    float getX();
    float getY();
    float getZ();
    float getW();

    void set(float x, float y, float z, float w);

    void set(Vector4f* other);

    float length();

    float lengthSquared();

    void normalize();

    void neg();

    float dot(Vector4f* other);

    void scale(float scale);

    Vector4f operator + (const Vector4f &other);

    Vector4f operator - (const Vector4f &other);

    Vector4f operator * (const Vector4f &other);

    Vector4f operator / (const Vector4f &other);
};
#endif
