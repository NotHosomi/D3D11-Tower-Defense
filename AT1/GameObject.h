#pragma once

#include <vector>
#include "Vector3.h"
#include "SkinnedCube.h"
#include "GameData.h"

class GameObject
{
public:
	//GameObject(Vector3 pos, Vector3 rot, Vector3 scale);
	GameObject(Renderer& renderer, Vector3 pos, Vector3 rot, Vector3 scale, std::string texture);
	virtual void update(GameData& _GD) = 0;
	void draw(Renderer* renderer);
protected:
	// statics
	//static void destroy(GameObject* go);
	//static std::vector<GameObject*> destroy_list;
	//static std::vector<GameObject*>& fetchDestroyList() { return destroy_list; };

	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	// TODO: replace with
	//std::vector<SkinnedCube> model;
	SkinnedCube model;
};

