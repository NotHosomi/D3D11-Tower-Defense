#include "Trace.h"
#include "UnlitCube.h"
#include "Maths.h"

Trace::Trace(Renderer& renderer, Vector3 start, Vector3 end, Vector3 colour)
{
	DirectX::XMFLOAT3 col = { colour.x, colour.y, colour.z };
	model = new UnlitCube(renderer, col);

	Vector3 dist = end - start;
	model->setScale(Vector3(0.05f, dist.magnitude(), 0.05f));

	setPos(start + dist * 0.5);

	Vector3 rot;
	dist.normalise();
	rot.z = atan2(sqrt(dist.y * dist.y + dist.x * dist.x), dist.z);
	rot.x = atan2(dist.y, dist.x);
	rot.x += PI / 2;
	setRot(rot);
}

void Trace::update(GameData* _GD)
{
	GameObject::destroy(this);
}