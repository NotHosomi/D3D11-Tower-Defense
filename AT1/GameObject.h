#pragma once

#include <vector>
#include "Vector3.h"
#include "SkinnedCube.h"
#include "GameData.h"

class GameObject
{
public:
	//constructor
	GameObject() = default;
	~GameObject();
	GameObject(const GameObject&) = delete;
	GameObject& operator= (const GameObject&) = delete;

	virtual void update(GameData& _GD) = 0;
	void draw(Renderer* renderer);

	void setPos(Vector3 pos);
	Vector3 getPos();
	void setRot(Vector3 pos);
	Vector3 getRot();
	void setScale(Vector3 pos);
	Vector3 getScale();
protected:
	// statics
	//static void destroy(GameObject* go);
	//static std::vector<GameObject*> destroy_list;
	//static std::vector<GameObject*>& fetchDestroyList() { return destroy_list; };


	Drawable* model;
	// TODO: replace with
	//std::vector<SkinnedCube> model;
private:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
};

