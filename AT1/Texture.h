#pragma once
#include "Bindable.h"

class Texture : public Bindable
{
public:
	Texture(Renderer& renderer, const class Surface& s);
	void bind(Renderer& renderer) noexcept override;
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture_view;
};

