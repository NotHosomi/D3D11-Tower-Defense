#pragma once
#include "Primitive.h"
#include "Vector3.h"
#include <string>

class SkinnedCube : public Primitive<SkinnedCube>
{
public:
	SkinnedCube(Renderer& renderer, Vector3 pos, Vector3 rot, Vector3 scale, std::string texture);
	DirectX::XMMATRIX getXMTransform() const noexcept;
	void update(float dt) noexcept override {};

	void setPos(Vector3 new_pos);
	void setRos(Vector3 new_rot);
	void setScale(Vector3 new_scale);
private:
	const DirectX::XMMATRIX local_transform;
	// parent transform
	float x = 0;
	float y = 0;
	float z = 0;
	float roll = 0;
	float pitch = 0;
	float yaw = 0;
	float x_scale = 0;
	float y_scale = 0;
	float z_scale = 0;
};