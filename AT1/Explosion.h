#pragma once
#include "GameObject.h"

class Explosion :
    public GameObject
{
public:
	Explosion(Renderer& renderer, Vector3 pos, int level);
	void update(GameData* _GD) override;

	static constexpr float EXPLOSION_RADIUS = 1;
private:
	static constexpr float LVL_DMG_BONUS = 10;
	static constexpr float EXPLOSION_BASE_DAMAGE = 40;
	float dmg;

	static constexpr float LIFETIME = 0.1f;
	float age = 0;
};

