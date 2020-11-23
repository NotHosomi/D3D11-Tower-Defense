#include "Vector3.h"

#include <cmath>

Vector3::Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

Vector3::Vector3(const Vector3& rhs)
{
    this->x = rhs.x;
    this->y = rhs.y;
}

/**
 *   @brief   Normalises vector.
 *   @details Turns the vector into a unit vector (magnitude of 1).
 *   @return  void
 */
void Vector3::normalise()
{
    float lcl_magnitude = magnitude();

    // return is 0 magnitude
    if (!lcl_magnitude)
    {
        return;
    }

    x /= lcl_magnitude;
    y /= lcl_magnitude;
}

float Vector3::magnitude()
{
    return sqrtf((x * x) + (y * y));
}

float Vector3::dot(const Vector3& a, const Vector3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Vector3::cross(const Vector3& a, const Vector3& b)
{
    Vector3 p;
    p.x = a.y * b.z - a.z * b.y;
    p.y = a.z * b.x - a.x * b.z;
    p.z = a.x * b.y - a.y * b.x;
    return p;
}

Vector3 Vector3::operator*(float scalar)
{
    Vector3 vec(*this);
    vec.x *= scalar;
    vec.y *= scalar;
    vec.z *= scalar;
    return vec;
}

Vector3 Vector3::operator+(const Vector3& operand)
{
    Vector3 vec(*this);
    vec.x += operand.x;
    vec.y += operand.y;
    vec.z += operand.z;
    return vec;
}

Vector3 Vector3::operator-(const Vector3& operand)
{
    Vector3 vec(*this);
    vec.x -= operand.x;
    vec.y -= operand.y;
    vec.z -= operand.z;
    return vec;
}

bool Vector3::operator==(const Vector3& operand)
{
    return (x == operand.x && y == operand.y && z == operand.z);
}
