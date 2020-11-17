#pragma once
#include "Bindable.h"

template<typename C>
class ConstantBuffer : public Bindable
{
public:
	void Update(Renderer& renderer, const C& consts)
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetContext(renderer)->Map(
			constant_buffer.Get(), 0,
			D3D11_MAP_WRITE_DISCARD, 0, &msr);
		memcpy(msr.pData, &consts, sizeof(consts));
		GetContext(renderer)->Unmap(constant_buffer.Get(), 0);
	};

	ConstantBuffer(Renderer& renderer, const C& consts, UINT slot = 0u) :
		slot(slot)
	{
		D3D11_BUFFER_DESC desc = {};
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.ByteWidth = sizeof(consts);
		desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = &consts;

		GetDevice(renderer)->CreateBuffer(&desc, &sd, &constant_buffer);
	};

	ConstantBuffer(Renderer& renderer, UINT slot = 0u) :
		slot(slot)
	{
		D3D11_BUFFER_DESC desc;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0u;
		desc.ByteWidth = sizeof(C);
		desc.StructureByteStride = 0u;
		GetDevice(renderer)->CreateBuffer(&desc, nullptr, &constant_buffer);
	};

protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> constant_buffer;
	UINT slot;
};


template<typename C>
class VertexConstantBuffer : public ConstantBuffer<C>
{
public:
	using ConstantBuffer<C>::ConstantBuffer;
	using ConstantBuffer<C>::slot;
	void bind(Renderer& renderer) noexcept override
	{
		Bindable::GetContext(renderer)->VSSetConstantBuffers(slot, 1u, constant_buffer.GetAddressOf());
	};
private:
	using ConstantBuffer<C>::constant_buffer;
};

template<typename C>
class PixelConstantBuffer : public ConstantBuffer<C>
{
public:
	using ConstantBuffer<C>::ConstantBuffer;
	using ConstantBuffer<C>::slot;
	void bind(Renderer& renderer) noexcept override
	{
		Bindable::GetContext(renderer)->PSSetConstantBuffers(slot, 1u, constant_buffer.GetAddressOf());
	};
private:
	using ConstantBuffer<C>::constant_buffer;
};

