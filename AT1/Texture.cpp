#include "Texture.h"
#include "Surface.h"

Texture::Texture(Renderer& renderer, const Surface& s)
{
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width = s.GetWidth();
	desc.Height = s.GetHeight();
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = s.GetBufferPtr();
	sd.SysMemPitch = s.GetWidth() * sizeof(Surface::Color);

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
	GetDevice(renderer)->CreateTexture2D(&desc, &sd, &texture);

	CD3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = desc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;
	GetDevice(renderer)->CreateShaderResourceView(texture.Get(), &srvDesc, &texture_view);
}

void Texture::bind(Renderer& renderer) noexcept
{
	GetContext(renderer)->PSSetShaderResources(0, 1, texture_view.GetAddressOf());
}
