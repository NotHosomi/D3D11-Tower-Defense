#include "InputLayout.h"

InputLayout::InputLayout(Renderer& gfx,
	const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout,
	ID3DBlob* pVertexShaderBytecode)
{
	GetDevice(gfx)->CreateInputLayout(
		layout.data(), (UINT)layout.size(),
		pVertexShaderBytecode->GetBufferPointer(),
		pVertexShaderBytecode->GetBufferSize(),
		&input_layout);
}

void InputLayout::bind(Renderer& gfx) noexcept
{
	GetContext(gfx)->IASetInputLayout(input_layout.Get());
}
