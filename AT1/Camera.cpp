#include "Camera.h"
#include <algorithm>

DirectX::XMMATRIX Camera::getMatrix() const noexcept
{
	namespace dx = DirectX;
	const auto pos = dx::XMVectorSet(x, y, z, 0.0f);

	return dx::XMMatrixTranslationFromVector(pos);
}

void Camera::moveCam(float dx, float dy, float dz)
{
	x += dx * SPEED;
	x = std::clamp(x, MIN_X, MAX_X);
	y += dy * SPEED;
	y = std::clamp(y, MIN_Y, MAX_Y);
	z += dz * SPEED;
	z = std::clamp(z, MIN_Z, MAX_Z);
}
