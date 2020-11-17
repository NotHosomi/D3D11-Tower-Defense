#include "Sampler.h"

Sampler::Sampler(Renderer& gfx)
{

	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	GetDevice(gfx)->CreateSamplerState(&samplerDesc, &sampler);
}

void Sampler::bind(Renderer& renderer) noexcept
{
	GetContext(renderer)->PSSetSamplers(0, 1, sampler.GetAddressOf());
}