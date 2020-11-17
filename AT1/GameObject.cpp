#include "GameObject.h"

GameObject::GameObject(Renderer& renderer, Vector3 pos, Vector3 rot, Vector3 scale, std::string texture) :
	model(renderer, Vector3(), Vector3(), Vector3(1, 1, 1), texture),
	position(pos), rotation(rot), scale(scale)
{
}

void GameObject::draw(Renderer* renderer)
{
	model.draw(*renderer);
}

//void GameObject::destroy(GameObject* go)
//{
//	destroy_list.emplace_back(go);
//}
