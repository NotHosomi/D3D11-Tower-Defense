#include "GameObject.h"
#include "Ball.h"

GameObject::~GameObject()
{
	delete model;
	model = nullptr;
}

void GameObject::draw(Renderer* renderer)
{
	model->draw(*renderer);
}

// internal transform controls
void GameObject::setPos(Vector3 pos)
{
	position = pos;
	model->setPos(pos);
}
Vector3 GameObject::getPos()
{
	return position;
}
void GameObject::setRot(Vector3 rot)
{
	position = rot;
	model->setRos(rot);
}
Vector3 GameObject::getRot()
{
	return rotation;
}
void GameObject::setScale(Vector3 scale)
{
	position = scale;
	model->setScale(scale);
}
Vector3 GameObject::getScale()
{
	return scale;
}

//void GameObject::destroy(GameObject* go)
//{
//	destroy_list.emplace_back(go);
//}