#pragma once
#include "GameObject.h"
#include "Explosion.h"

class Projectile : public GameObject
{
public:
	Projectile(Renderer& renderer, Vector3 start, Vector3 target, int level);
	void update(GameData* _GD) override;

	static constexpr float SPEED = 4;
private:
	Vector3 target;
	int lvl;
};

