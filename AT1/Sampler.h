#pragma once
#include "Bindable.h"

class Sampler : public Bindable
{
public:
	Sampler(Renderer& renderer);
	void bind(Renderer& renderer) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler;
};