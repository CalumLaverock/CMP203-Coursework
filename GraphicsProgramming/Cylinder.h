#pragma once
#include "Shape.h"
#include "Disc.h"

class Cylinder : public Shape
{
public:
	Cylinder(int, int, float);
	~Cylinder();

	void render2();

private:
	Disc* disc;
	int segments;
};

