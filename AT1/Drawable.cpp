#include "Drawable.h"
#include "IndexBuffer.h"
#include "Bindable.h"
#include <cassert>
#include <typeinfo>

DirectX::XMMATRIX Drawable::getXMTransform() const noexcept
{
	return //local_transform *
		DirectX::XMMatrixScaling(x_scale, y_scale, z_scale) *
		DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(x, y, z);
}

void Drawable::draw(Renderer& renderer) const noexcept
{
	for (auto& it : binds)
	{
		it->bind(renderer);
	}
	for (auto& it : getStaticBinds())
	{
		it->bind(renderer);
	}
	renderer.drawIndexed(index_buffer->count());
}

void Drawable::addBind(std::unique_ptr<Bindable> bind) noexcept
{
	assert("*Must* use AddIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));
	binds.push_back(std::move(bind));
}

void Drawable::addIndexBuffer(std::unique_ptr<class IndexBuffer> buffer) noexcept
{
	assert("Attempting to add index buffer a second time" && index_buffer == nullptr);
	index_buffer = buffer.get();
	binds.push_back(std::move(buffer));
}

void Drawable::setPos(Vector3 new_pos)
{
	x = new_pos.x;
	y = new_pos.y;
	z = new_pos.z;
}

void Drawable::setRos(Vector3 new_rot)
{
	roll = new_rot.x;
	pitch = new_rot.y;
	yaw = new_rot.z;
}

void Drawable::setScale(Vector3 new_scale)
{
	x_scale = new_scale.x;
	y_scale = new_scale.y;
	z_scale = new_scale.z;
}