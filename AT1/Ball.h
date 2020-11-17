#pragma once
#include "Primitive.h"
#include <random>

class Ball : public Primitive<Ball>
{
public:
	Ball(Renderer& gfx, std::mt19937& rng,
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist,
		std::uniform_int_distribution<int>& longdist,
		std::uniform_int_distribution<int>& latdist);
	void update(float dt) noexcept override;
	DirectX::XMMATRIX getXMTransform() const noexcept override;
private:
	float r;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float x;
	float y;
	float z;
	float droll;
	float dpitch;
	float dyaw;
	float dx;
	float dy;
	float dz;
};