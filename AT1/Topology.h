#pragma once
#include "Bindable.h"

class Topology : public Bindable
{
public:
	Topology(D3D11_PRIMITIVE_TOPOLOGY type);
	void bind(Renderer& renderer) noexcept override;
protected:
	D3D11_PRIMITIVE_TOPOLOGY type;
};