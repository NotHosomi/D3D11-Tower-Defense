#pragma once
#include "GameObject.h"
#include "Cylinder.h"
#include "Enemy.h"

class Turret : public GameObject
{
public:
	void update(GameData* _GD) override;
	void draw(Renderer* renderer) override;
protected:
	Turret(Renderer& renderer, Vector3 pos);

	virtual void attack(GameData* _GD) = 0;
	virtual void pickTarget(GameData* _GD) = 0;
	bool validateTarget(GameData* _GD);
	void updateRot();

	Enemy* target = nullptr;

	float damage = 0;
	float attack_time = 0;
	float range = 0;

	float shoot_timer = 0;
	int level = 0;
private:
	Cylinder turret_base;
};

