#include "PointLight.h"

PointLight::PointLight(Renderer& gfx) :
	cbuf(gfx)
{
	cbData = {
			{ 0.0f,0.0f,0.0f },
			{ 0.05f,0.05f,0.05f },
			{ 1.0f,1.0f,1.0f },
			1.0f,
			1.0f,
			0.045f,
			0.0075f,
	};
}

void PointLight::Bind(Renderer& gfx, DirectX::FXMMATRIX view) const noexcept
{
	auto dataCopy = cbData;
	const auto pos = DirectX::XMLoadFloat3(&cbData.pos);
	DirectX::XMStoreFloat3(&dataCopy.pos, DirectX::XMVector3Transform(pos, view));
	cbuf.Update(gfx, dataCopy);
	cbuf.bind(gfx);
}
