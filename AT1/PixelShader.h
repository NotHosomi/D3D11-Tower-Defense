#pragma once
#include "Bindable.h"
#include <string>

class PixelShader : public Bindable
{
public:
	PixelShader(Renderer& renderer, const std::wstring& path);
	void bind(Renderer& renderer) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixel_shader;
};

