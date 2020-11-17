#pragma once
#include "Renderer.h"
#include <DirectXMath.h>
#include <Memory>
#include <vector>

class Bindable;

class Drawable
{
	template<class T>
	friend class DrawableBase;
public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	virtual ~Drawable() = default;

	virtual DirectX::XMMATRIX getXMTransform() const noexcept = 0;
	void draw(Renderer& renderer) const noexcept;
	virtual void update(float dt) noexcept = 0;
	void addBind(std::unique_ptr<Bindable> bind) noexcept;
	void addIndexBuffer(std::unique_ptr<class IndexBuffer> ibuf) noexcept;

	const class IndexBuffer* index_buffer = nullptr;
private:
	virtual const std::vector<std::unique_ptr<Bindable>>& getStaticBinds() const noexcept = 0; // Disable pure when meshes are added

	std::vector<std::unique_ptr<Bindable>> binds;
};

