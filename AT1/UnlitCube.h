#pragma once
#include "TestObject.h"

class UnlitCube : public Primitive<UnlitCube>
{
public:
	UnlitCube(Renderer& renderer, DirectX::XMFLOAT3 material);
private:
};