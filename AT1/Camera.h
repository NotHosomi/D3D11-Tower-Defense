#pragma once
#include "Renderer.h"

class Camera
{
public:
	DirectX::XMMATRIX getMatrix() const noexcept;
	void moveCam(float dx, float dy, float dz);
private:
	const float MIN_X = -19;
	const float MAX_X = 0;
	const float MIN_Y = -14;
	const float MAX_Y = 0;
	const float MIN_Z = 5;
	const float MAX_Z = 10;
	const float SPEED = 1;

	float x = ((MAX_X - MIN_X) / 2.0f) + MIN_X;
	float y = ((MAX_Y - MIN_Y) / 2.0f) + MIN_Y;
	float z = MAX_Z;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;
};