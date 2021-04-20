#pragma once
#include "GameObject.h"

// We need access to Drawable's functions to make manipulatable verts
// We ALSO need to be able to add the core to the GO stack for ease of updating and rendering
class Core : public Drawable, public GameObject
{
public:
	using Drawable::draw(Renderer& renderer);
	void update(GameData* _GD) override;
};

