#pragma once
#include "Renderer.h"
#include <DirectXMath.h>
#include <Memory>
#include <vector>
#include "Vector3.h"

class Bindable;

class Drawable
{
	template<class T>
	friend class DrawableBase;
public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	// move constructor for emplacing
	Drawable(Drawable&& other) noexcept;
	virtual ~Drawable() = default;

	virtual DirectX::XMMATRIX getXMTransform() const noexcept;
	void draw(Renderer& renderer) const noexcept;
	virtual void update(float dt) noexcept {};
	void addBind(std::unique_ptr<Bindable> bind) noexcept;
	void addIndexBuffer(std::unique_ptr<class IndexBuffer> ibuf) noexcept;

	const class IndexBuffer* index_buffer = nullptr;

	// parent GameObject interface
	void setPos(Vector3 new_pos);
	void setRot(Vector3 new_rot);
	void setScale(Vector3 new_scale);
private:
	virtual const std::vector<std::unique_ptr<Bindable>>& getStaticBinds() const noexcept = 0; // Disable pure when meshes are added

	std::vector<std::unique_ptr<Bindable>> binds;

	const DirectX::XMMATRIX local_transform = DirectX::XMMatrixScaling(1, 1, 1);
	// parent transform
	// TODO: Convert to XMVECTORs
	float x = 0;
	float y = 0;
	float z = 0;
	float roll = 0;
	float pitch = 0;
	float yaw = 0;
	float x_scale = 1;
	float y_scale = 1;
	float z_scale = 1;
};

