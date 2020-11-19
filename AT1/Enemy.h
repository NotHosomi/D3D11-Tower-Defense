#pragma once
#include "PathCorner.h"
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy(Renderer& renderer, PathCorner* first_stop_target, Vector3 spawn_pos);
	void update(GameData* _GD) override;//override
	void damage(float amount);

private:
	void move(float dt);

	const Vector3 offset;

	PathCorner* destination; // Don't need a destructor, we don't own this

	float SPEED = 3;
	int max_health = 100;
	int current_health;
	// TODO: Enum status effects
	// std::vector<int> se_stacks;
};