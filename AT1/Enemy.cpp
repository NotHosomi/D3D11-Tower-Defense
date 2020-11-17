#include "Enemy.h"
#include <random>

Enemy::Enemy(Renderer& renderer, PathCorner* first_stop_target) :
	GameObject(renderer, Vector3(), Vector3(), Vector3(0.5, 0.5, 0.5), "hi")
	//offset((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 0)
{
	destination = first_stop_target;
	current_health = max_health;
}

void Enemy::update(float dt)
{
	move(dt);
}

void Enemy::damage(float amount)
{
	// To do, fetch SE_DMG_AMP stacks
	// stacks *= 0.005
	// amount *= 1 + stacks
	current_health -= static_cast<int>(amount);


	if (current_health <= 0)
	{
		// kill self
		//GameObject::destroy(this);
	}
}

void Enemy::move(float dt)
{
	Vector3 dist = (destination->getPos() + offset) - position;
	Vector3 dir = dist;
	dir.normalise();
	dir * speed * dt;

	if (dir.magnitude() >= dist.magnitude())
	{
		dir = dist;
		destination = destination->getNextStopTarget();

		if (destination == nullptr)
		{
			// Damage objective
			// Kill self
		}
	}
}
