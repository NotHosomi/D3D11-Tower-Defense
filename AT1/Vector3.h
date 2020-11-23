#pragma once

class Vector3
{
public:
	// construction
	Vector3() = default;
	Vector3(float x_, float y_, float z_);
	Vector3(const Vector3& rhs);
	~Vector3() = default;

	// operations
	Vector3 operator*(float scalar);
	Vector3& operator=(const Vector3& rhs) = default;
	Vector3 operator+(const Vector3& operand);
	Vector3 operator-(const Vector3& operand);
	bool operator==(const Vector3& operand);
	void normalise();
	float magnitude();
	
	float dot(const Vector3& a, const Vector3& b);
	Vector3 cross(const Vector3& a, const Vector3& b);

	// data
	float x = 0;
	float y = 0;
	float z = 0;
};