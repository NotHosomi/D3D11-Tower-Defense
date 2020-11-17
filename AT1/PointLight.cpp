#include "PointLight.h"

PointLight::PointLight(Renderer& gfx) :
	constbuf(gfx)
{
	constbuf_data = {
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
	auto dataCopy = constbuf_data;
	const auto pos = DirectX::XMLoadFloat3(&constbuf_data.pos);
	DirectX::XMStoreFloat3(&dataCopy.pos, DirectX::XMVector3Transform(pos, view));
	constbuf.Update(gfx, dataCopy);
	constbuf.bind(gfx);
}

void PointLight::setPos(float x, float y, float z)
{
	constbuf_data.pos = DirectX::XMFLOAT3(x, y, z);
}
