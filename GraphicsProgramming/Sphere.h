#pragma once
#include "Shape.h"

class Sphere : public Shape
{
public:
	Sphere(int, int, float);
	~Sphere();

	void render2();

private:
	int xSegments, ySegments;
	float radius;
};

