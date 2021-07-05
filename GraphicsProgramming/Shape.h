#ifndef _SHAPE_H
#define _SHAPE_H

#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <vector>
#include "Vector3.h"

class Shape
{
public:
	Shape();

	void addVertex(Vector3);
	void addNormal(Vector3);
	void addTexCoord(Vector3);
	void addIndex(GLubyte);

	void render1();
	void render2();
	void render3();

protected:
	std::vector<float> verts, norms, texCoords;
	std::vector<GLubyte> indices;

	int vertices;
};
#endif 
