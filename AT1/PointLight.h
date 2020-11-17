#pragma once
#include "Renderer.h"
#include "ConstantBuffer.h"

class PointLight
{
public:
	PointLight(Renderer& renderer);
	void Bind(Renderer& renderer, DirectX::FXMMATRIX view) const noexcept;
	void setPos(float x, float y, float z);
private:
	struct PointLightCBuf
	{
		alignas(16) DirectX::XMFLOAT3 pos;
		alignas(16) DirectX::XMFLOAT3 ambient;
		alignas(16) DirectX::XMFLOAT3 diffuseColor;
		float diffuseIntensity;
		float attConst;
		float attLin;
		float attQuad;
	};

	PointLightCBuf constbuf_data;
	mutable PixelConstantBuffer<PointLightCBuf> constbuf;
};