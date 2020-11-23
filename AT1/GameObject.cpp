#include "GameObject.h"


std::vector<GameObject*> GameObject::destroy_list = std::vector<GameObject*>();
std::vector<GameObject*> GameObject::create_list = std::vector<GameObject*>();

GameObject::~GameObject()
{
	delete model;
	model = nullptr;
}

void GameObject::draw(Renderer* renderer)
{
	if (model != nullptr)
	{
		model->draw(*renderer);
	}
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
	rotation = rot;
	model->setRot(rot);
}
Vector3 GameObject::getRot()
{
	return rotation;
}
void GameObject::setScale(Vector3 scale)
{
	this->scale = scale;
	model->setScale(scale);
}
Vector3 GameObject::getScale()
{
	return scale;
}

void GameObject::destroy(GameObject* go)
{
	if (!std::count(destroy_list.begin(), destroy_list.end(), go))
	{
		destroy_list.emplace_back(go);
	}
}

void GameObject::create(GameObject* go)
{
	if (!std::count(destroy_list.begin(), destroy_list.end(), go))
	{
		create_list.emplace_back(go);
	}
}
