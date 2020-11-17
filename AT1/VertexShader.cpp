#include "VertexShader.h"
#include <d3dcompiler.h>

VertexShader::VertexShader(Renderer& renderer, const std::wstring& path)
{

	D3DReadFileToBlob(path.c_str(), &blob);
	GetDevice(renderer)->CreateVertexShader(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		&pVertexShader
	);
}

void VertexShader::bind(Renderer& renderer) noexcept
{
	GetContext(renderer)->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}

ID3DBlob* VertexShader::GetBytecode() const noexcept
{
	return blob.Get();
}
