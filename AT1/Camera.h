#pragma once
#include "Renderer.h"

class Camera
{
public:
	DirectX::XMMATRIX getMatrix() const noexcept;
	void moveCam(float dx, float dy, float dz);
private:
	const float MIN_X = -7;
	const float MAX_X = 7;
	const float MIN_Y = -5;
	const float MAX_Y = 5;
	const float MIN_Z = 10;
	const float MAX_Z = 20;
	const float SPEED = 2;
	//const float Y_SPEED = 2;
	//const float Z_SPEED = 2;

	float x = 0.0f;
	float y = 0.0f;
	float z = 20.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;
};