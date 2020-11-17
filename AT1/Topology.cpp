#include "Topology.h"

Topology::Topology(D3D11_PRIMITIVE_TOPOLOGY type) :
	type(type)
{}

void Topology::bind(Renderer& renderer) noexcept
{
	GetContext(renderer)->IASetPrimitiveTopology(type);
}