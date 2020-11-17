#pragma once
#include "Bindable.h"
#include <vector>

class IndexBuffer : public Bindable
{
public:
	IndexBuffer(Renderer& renderer, const std::vector<unsigned short> &indices);
	void bind(Renderer& renderer) noexcept override;
	UINT count() const noexcept;
protected:
	UINT n;
	Microsoft::WRL::ComPtr<ID3D11Buffer> index_buffer;
};