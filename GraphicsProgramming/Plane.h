#pragma once
#include "Shape.h"
#include "Vector3.h"

class Plane : public Shape
{
public:
	Plane(int, int);
	~Plane();

	void render2();
};

