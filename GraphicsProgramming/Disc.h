#pragma once
#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <vector>
#include "Vector3.h"
#include "Shape.h"

class Disc : public Shape
{
public:
	Disc(int, float);
	~Disc();

	void render2();
};

