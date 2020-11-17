#pragma once
#include "TestObject.h"

class Cube : public TestObject<Cube>
{
public:
	Cube(Renderer& renderer, std::mt19937& rng,
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist,
		std::uniform_real_distribution<float>& bdist,
		DirectX::XMFLOAT3 material);
	DirectX::XMMATRIX getXMTransform() const noexcept override;
private:

	DirectX::XMFLOAT3X3 transform;
};