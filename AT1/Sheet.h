#pragma once
#include "Primitive.h"
#include <random>
#include <string>

class Sheet : public Primitive<Sheet>
{
public:
	Sheet(Renderer& renderer, std::string texture, float width, float height);
	void update(float dt) noexcept override;
	DirectX::XMMATRIX getXMTransform() const noexcept override;
private:
	const float width;
	const float height;
};