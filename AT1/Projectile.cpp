#include "Projectile.h"
#include "Ball.h"
#include "Explosion.h"

Projectile::Projectile(Renderer& renderer, Vector3 start, Vector3 target, int level)
{
	model = new Ball(renderer, 4, 4);
	setPos(start);
	model->setScale(Vector3(0.4f, 0.4f, 0.4f));

	this->target = target;
	lvl = level;
}

void Projectile::update(GameData* _GD)
{
	Vector3 dist = target - getPos();
	Vector3 dir = dist;
	dir.normalise();
	dir = dir * (SPEED * _GD->dt);

	if (dir.magnitude() >= dist.magnitude())
	{
		dir = dist;
		GameObject::destroy(this);
		setPos(target);
		GameObject::create(new Explosion(*_GD->renderer, getPos(), lvl));
		return;
	}
	setPos(getPos() + dir);
}
