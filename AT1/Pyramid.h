#pragma once
#include "Primitive.h"

class Pyramid : public Primitive<Pyramid>
{
public:
	Pyramid(Renderer& renderer, Vector3 peak_colour, Vector3 base_colour);
};