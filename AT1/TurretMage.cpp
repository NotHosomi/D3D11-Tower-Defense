#include "TurretMage.h"
#include "Pyramid.h"
#include "Projectile.h"

TurretMage::TurretMage(Renderer& renderer, Vector3 pos) :
	Turret(renderer, pos)
{
	model = new Pyramid(renderer, Vector3(255, 0, 0), Vector3(255, 255, 0));
	pos.z += 0.5;
	setPos(pos);
	model->setScale(Vector3(0.5, 0.5, 1));

	damage = 10;
	attack_time = 3;
	range = 5.5;
}

void TurretMage::attack(GameData* _GD)
{
	GameObject* projectile = new Projectile(*_GD->renderer, getPos() + Vector3(0, 0, 1), target->getPos(), level);
	GameObject::create(projectile);
	pickTarget(_GD);
}

void TurretMage::pickTarget(GameData* _GD)
{
	// for each enemy
		// count enemies in explosion radius
	// target = enemy in range with highest neighbour count
	int most_neightbours = 0;

	for (GameObject* go : *_GD->game_objects)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(go);
		if (enemy == nullptr)
		{
			continue;
		}

		Vector3 diff = enemy->getPos() - getPos();
		if (diff.magnitude() < range)
		{
			// count how many enemies are within the explosion radius of this enemy
			// FIXME: THIS IS TERRIBLE
			int n = 0;
			for (GameObject* neighbour : *_GD->game_objects)
			{
				if (dynamic_cast<Enemy*>(neighbour) == nullptr)
				{
					continue;
				}
				Vector3 second_diff = neighbour->getPos() - enemy->getPos();
				if (second_diff.magnitude() < Explosion::EXPLOSION_RADIUS)
				{
					++n;
				}
			}

			// update the target if this is a larger crowd
			if (n > most_neightbours)
			{
				most_neightbours = n;
				target = enemy;
			}
		}
	}

	if (most_neightbours == 0)
	{
		// no target
		target = nullptr;
		return;
	}
	updateRot();
}