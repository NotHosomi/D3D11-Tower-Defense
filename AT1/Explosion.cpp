#include "Explosion.h"
#include "Ball.h"
#include "Enemy.h"

Explosion::Explosion(Renderer& renderer, Vector3 pos, int level)
{
	model = new Ball(renderer, 5, 5);
	setPos(pos);
	model->setScale(Vector3(2, 2, 2) * EXPLOSION_RADIUS);

	dmg = EXPLOSION_BASE_DAMAGE + LVL_DMG_BONUS * level;
}

void Explosion::update(GameData* _GD)
{
	// damage enemies
	for (GameObject* go : *_GD->game_objects)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(go);
		if (enemy == nullptr)
		{
			continue;
		}
		Vector3 diff = enemy->getPos() - getPos();
		if (diff.magnitude() < EXPLOSION_RADIUS)
		{
			enemy->damage(dmg);
		}
	}

	GameObject::destroy(this);
}
