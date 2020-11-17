#include "Marker.h"
#include "Ball.h"
#include "SkinnedCube.h"

Marker::Marker(Renderer& renderer, Vector3 pos)
{
	model = new Ball(renderer, 5, 10);
	model->setPos(pos);
}