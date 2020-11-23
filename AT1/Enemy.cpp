#include "Enemy.h"
#include <random>

Enemy::Enemy(Renderer& renderer, PathCorner* first_stop_target, Vector3 spawn_pos, EnemyType e_type)
{
	model = new SkinnedCube(renderer, "Hi");

	float dims = 0.5f;
	float height_mult = 1;
	switch (e_type)
	{
	default:
	case EnemyType::LING:
		dims = 0.25;
		speed = 2;
		max_health = 25;
		break;
	case EnemyType::RUNT: dims = 0.4;
		speed = 1.1;
		max_health = 60;
		break;
	//case EnemyType::FLOATER: dims = 0.4;
	//	speed = 0.5;
	//	max_health = 25;
	//	break;
	case EnemyType::GRUNT: dims = 0.6;
		speed = 1;
		max_health = 100;
		break;
	case EnemyType::STRIDER: dims = 0.4;
		height_mult = 1.3;
		speed = 2;
		max_health = 135;
		break;
	case EnemyType::BRUNT: dims = 0.9;
		height_mult = 0.7;
		speed = 0.35;
		max_health = 1000;
		break;
	}
	model->setScale(Vector3(dims, dims, dims * height_mult));

	offset = Vector3(dims * rand() / (float)RAND_MAX - dims * 0.5f, dims * rand() / (float)RAND_MAX - dims * 0.5f, 0);
	setPos(spawn_pos + offset);

	destination = first_stop_target;
	current_health = max_health;
}

void Enemy::update(GameData* _GD)
{
	move(_GD->dt);
}

void Enemy::damage(float amount)
{
	// To do, fetch SE_DMG_AMP stacks
	// stacks *= 0.005
	// amount *= 1 + stacks
	current_health -= static_cast<int>(amount);


	if (current_health <= 0)
	{
		GameObject::destroy(this);
	}
}

int Enemy::getMaxHp() const
{
	return max_health;
}

void Enemy::move(float dt)
{
	Vector3 dist = (destination->getPos() + offset) - getPos();
	Vector3 dir = dist;
	dir.normalise();
	dir = dir * (speed * dt);

	if (dir.magnitude() >= dist.magnitude())
	{
		dir = dist;
		destination = destination->getNextStopTarget();

		if (destination == nullptr)
		{
			GameObject::destroy(this);
		}
	}
	setPos(getPos() + dir);
}
