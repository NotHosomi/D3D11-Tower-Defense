#pragma once
#include "PathCorner.h"
#include "GameObject.h"


class Enemy : public GameObject
{
public:
	enum class EnemyType
	{
		LING,
		RUNT,
		FLOATER,
		GRUNT,
		STRIDER,
		BRUNT
	};

	Enemy(Renderer& renderer, PathCorner* first_stop_target, Vector3 spawn_pos, EnemyType e_type);
	void update(GameData* _GD) override;//override
	void damage(float amount);


	int getMaxHp() const;
private:
	void move(float dt);

	// const, but setting logic is too complex for constructor assignment
	Vector3 offset;

	PathCorner* destination; // Don't need a destructor, we don't own this

	float speed = 3;
	int max_health = 100;
	int current_health;
	// TODO: Enum status effects
	// std::vector<int> se_stacks;
};