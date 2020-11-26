#include "Picker.h"
#include "Tile.h"
#include "Grid.h"
#include "Keyboard.h"
#include "TurretGun.h"
#include "TurretLaser.h"

#include "SkinnedCube.h"
#include "Maths.h"

Picker::Picker(Renderer& renderer)
{
	// Lazy use of Tile object for instatiating a plane
	// Creating a new primitive class just for the picker to use would use more memory than this
	// as the Tile class one has one member var and it's just a pointer, whereas a new class would
	// need new functions
	model = new SkinnedCube(renderer, "Blank");
	// x & y scale are half of the square root of 2
	model->setScale(Vector3(0.7071, 0.7071, 0.1));
	model->setRot(Vector3(PI / 4, 0, 0));

	Vector3 pos;
	pos.x = Grid::GRID_WIDTH / 2;
	pos.y = Grid::GRID_WIDTH / 2;
	pos.z = 0.01;
	setPos(pos);
}

void Picker::update(GameData* _GD)
{
	Vector3 wish_dir;
	if (_GD->keys->getKeyDown('D'))
	{
		wish_dir.x++;
	}
	if (_GD->keys->getKeyDown('A'))
	{
		wish_dir.x--;
	}
	if (_GD->keys->getKeyDown('W'))
	{
		wish_dir.y++;
	}
	if (_GD->keys->getKeyDown('S'))
	{
		wish_dir.y--;
	}
	// Discrete movement, no deltatime mult
	// TODO: Bounds check
	setPos(getPos() + wish_dir);

	// Try to place
	if (_GD->keys->getKeyDown('Q'))
	{
		Tile* target = _GD->world->getTile(getPos());
		if (target->fetchOccupier() == nullptr)
		{
			auto new_turret = new TurretGun(*_GD->renderer, getPos());
			GameObject::create(new_turret);
			target->setOccupier(new_turret);
		}
	}
	else if (_GD->keys->getKeyDown('E'))
	{
		Tile* target = _GD->world->getTile(getPos());
		if (target->fetchOccupier() == nullptr)
		{
			auto new_turret = new TurretLaser(*_GD->renderer, getPos());
			GameObject::create(new_turret);
			target->setOccupier(new_turret);
		}
	}
	//else if (_GD->keys->getKeyDown('R'))
	//{
	//	Tile* target = _GD->world->getTile(getPos());
	//	if (target->fetchOccupier() == nullptr)
	//	{
	//		auto new_turret = new TurretMage(*_GD->renderer, getPos());
	//		GameObject::create(new_turret);
	//		target->setOccupier(new_turret);
	//	}
	//}

	if (_GD->keys->getKeyDown('F'))
	{
		Turret* target = _GD->world->getTile(getPos())->fetchOccupier();
		if (target != nullptr)
		{
			// TODO:
			//target->upgrade()
		}
	}

	// FIXME: turret destruction causes crash in GO Destroy loop, at delete statement
	if (_GD->keys->getKeyDown(VK_SHIFT))
	{
		Tile* target = _GD->world->getTile(getPos());
		if (target->fetchOccupier() != nullptr)
		{
			GameObject::destroy(target->fetchOccupier());
			target->setOccupier(nullptr);
		}
	}
}


