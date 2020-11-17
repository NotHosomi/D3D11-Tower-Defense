#include "VertexBuffer.h"

void VertexBuffer::bind(Renderer& renderer) noexcept
{
	const UINT offset = 0u;
	GetContext(renderer)->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
}