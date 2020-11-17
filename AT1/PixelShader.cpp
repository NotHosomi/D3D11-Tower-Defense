#include "PixelShader.h"
#include <d3dcompiler.h>

PixelShader::PixelShader(Renderer& renderer, const std::wstring& path)
{
	Microsoft::WRL::ComPtr<ID3DBlob> blob;
	D3DReadFileToBlob(path.c_str(), &blob);
	GetDevice(renderer)->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pixel_shader);
}

void PixelShader::bind(Renderer& renderer) noexcept
{
	GetContext(renderer)->PSSetShader(pixel_shader.Get(), nullptr, 0u);
}