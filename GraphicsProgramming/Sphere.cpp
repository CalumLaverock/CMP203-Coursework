#include "Sphere.h"

Sphere::Sphere(int xSeg, int ySeg, float rad)
{
	xSegments = xSeg;
	ySegments = ySeg;
	radius = rad;

	float theta;
	float delta;

	float xTexInc = 1 / (float)xSegments;
	float yTexInc = 1 / (float)ySegments;
	float u = 0;
	float v = 0;

	Vector3 vertex = { 0.0, 0.0, 0.0 };
	Vector3 normal = { 0.0, 0.0, 0.0 };
	Vector3 texture = { 0.0, 0.0, 0.0 };

	for (int lats = 0; lats < ySegments; lats++) {
		for (int longs = 0; longs < xSegments; longs++) {
			//Calculate and add vertex 1 (lats, longs)
			delta = (3.1415926 * lats) / ySegments;
			theta = (2 * 3.1415926 * longs) / xSegments;

			vertex.x = radius * cosf(theta) * sinf(delta);
			vertex.y = radius * cosf(delta);
			vertex.z = radius * sinf(theta) * sinf(delta);

			texture.x = u;
			texture.y = v;

			normal.x = vertex.x / radius;
			normal.y = vertex.y / radius;
			normal.z = vertex.z / radius;

			addVertex(vertex);
			addTexCoord(texture);
			addNormal(normal);

			//Calculate and add vertex 2 (lats, longs + 1)
			delta = (3.1415926 * lats) / ySegments;
			theta = (2 * 3.1415926 * (longs + 1)) / xSegments;

			vertex.x = radius * cosf(theta) * sinf(delta);
			vertex.y = radius * cosf(delta);
			vertex.z = radius * sinf(theta) * sinf(delta);

			texture.x = u + xTexInc;
			texture.y = v;

			normal.x = vertex.x / radius;
			normal.y = vertex.y / radius;
			normal.z = vertex.z / radius;

			addVertex(vertex);
			addTexCoord(texture);
			addNormal(normal);

			//Calculate and add vertex 3 (lats + 1, longs + 1)
			delta = (3.1415926 * (lats + 1)) / ySegments;
			theta = (2 * 3.1415926 * (longs + 1)) / xSegments;

			vertex.x = radius * cosf(theta) * sinf(delta);
			vertex.y = radius * cosf(delta);
			vertex.z = radius * sinf(theta) * sinf(delta);

			texture.x = u + xTexInc;
			texture.y = v + yTexInc;

			normal.x = vertex.x / radius;
			normal.y = vertex.y / radius;
			normal.z = vertex.z / radius;

			addVertex(vertex);
			addTexCoord(texture);
			addNormal(normal);

			//Calculate and add vertex 4 (lats + 1, longs)
			delta = (3.1415926 * (lats + 1)) / ySegments;
			theta = (2 * 3.1415926 * longs) / xSegments;

			vertex.x = radius * cosf(theta) * sinf(delta);
			vertex.y = radius * cosf(delta);
			vertex.z = radius * sinf(theta) * sinf(delta);

			texture.x = u;
			texture.y = v + yTexInc;

			normal.x = vertex.x / radius;
			normal.y = vertex.y / radius;
			normal.z = vertex.z / radius;

			addVertex(vertex);
			addTexCoord(texture);
			addNormal(normal);

			u += xTexInc;
		}

		u = 0;
		v += yTexInc;
	}
}

Sphere::~Sphere()
{
}

void Sphere::render2()
{
	//Enable the necessary arrays for generating the shape
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//Setup the relevant pointers needed i.e. one to point to the vertex array,
	//one for the normal array and one for the texture coord array
	glVertexPointer(3, GL_FLOAT, 0, &verts[0]);
	glNormalPointer(GL_FLOAT, 0, &norms[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &texCoords[0]);

	//glDrawArrays() will access the full arrays for vertices, normals and tex coords
	//with one function call. glBegin() and glEnd() is not needed here.
	//An index array is not needed meaning that the order in the arrays is very important.
	glDrawArrays(GL_QUADS, 0, verts.size() / 3);

	//Disable the arrays after using them
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
