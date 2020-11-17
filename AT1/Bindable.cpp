#include "Bindable.h"

ID3D11DeviceContext* Bindable::GetContext(Renderer& renderer) noexcept
{
	return renderer.context.Get();
}

ID3D11Device* Bindable::GetDevice(Renderer& renderer) noexcept
{
	return renderer.device.Get();
}