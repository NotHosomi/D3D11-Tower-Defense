#pragma once
#include "ConstantBuffer.h"
#include <DirectXMath.h>
#include <memory>

class Drawable;

class TransformBuffer : public Bindable
{
public:
	TransformBuffer(Renderer& renderer, const Drawable& parent, UINT slot = 0);
	void bind(Renderer& renderer) noexcept override;
private:
	struct Transforms
	{
		DirectX::XMMATRIX modelViewProj;
		DirectX::XMMATRIX model;
	};

	static std::unique_ptr<VertexConstantBuffer<Transforms>> vertex_constant_buffer;
	const Drawable& parent;
};