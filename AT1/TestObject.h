#pragma once
#include "Primitive.h"
#include "Bindable.h"
#include <random>

template<class T>
class TestObject : public Primitive<T>
{
public:
	TestObject(Renderer& renderer, std::mt19937& rng,
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist)
		:
		r(rdist(rng)),
		droll(ddist(rng)),
		dpitch(ddist(rng)),
		dyaw(ddist(rng)),
		dy(odist(rng)),
		dx(odist(rng)),
		dz(odist(rng)),
		z(adist(rng)),
		x(adist(rng)),
		y(adist(rng))
	{}
	void update(float dt) noexcept
	{
		roll += droll * dt;
		pitch += dpitch * dt;
		yaw += dyaw * dt;
		x += dx * dt;
		y += dy * dt;
		z += dz * dt;
	}
	DirectX::XMMATRIX getXMTransform() const noexcept
	{
		return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
			DirectX::XMMatrixTranslation(r, 0.0f, 0.0f) *
			DirectX::XMMatrixRotationRollPitchYaw(x, y, z);
	}
private:
	// positional
	float r;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float x;
	float y;
	float z;
	// speed (delta/s)
	float droll;
	float dpitch;
	float dyaw;
	float dx;
	float dy;
	float dz;
};
