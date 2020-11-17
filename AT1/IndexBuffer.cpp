#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Renderer& renderer, const std::vector<unsigned short>& indices)
	:
	n((UINT)indices.size())
{

	D3D11_BUFFER_DESC desc = {};
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.CPUAccessFlags = 0u;
	desc.MiscFlags = 0u;
	desc.ByteWidth = UINT(n * sizeof(unsigned short));
	desc.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = indices.data();
	GetDevice(renderer)->CreateBuffer(&desc, &sd, &index_buffer);
}

void IndexBuffer::bind(Renderer& renderer) noexcept
{
	GetContext(renderer)->IASetIndexBuffer(index_buffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
}

UINT IndexBuffer::count() const noexcept
{
	return n;
}