#pragma once
#include "TestObject.h"

class Cylinder : public Primitive<Cylinder>
{
public:
	Cylinder(Renderer& renderer);
};