#include "Cylinder.h"

Cylinder::Cylinder(int seg, int noOfVerts, float radius)
{
	segments = seg;
	float interval = (2 * 3.1415926) / noOfVerts;
	float angle = 0;

	float xTexInc = 1 / (float)noOfVerts;
	float yTexInc = 1 / (float)segments;
	float u = 0;
	float v = 1;

	Vector3 vertex = { 0.0, 0.0, 0.0 };
	Vector3 normal = { 0.0, 0.0, 0.0 };
	Vector3 texture = { 0.0, 0.0, 0.0 };

	disc = new Disc(noOfVerts, radius);

	for (int i = 0; i < segments; i++) {
		for (int longs = 0; longs < noOfVerts; longs++) {
			angle += interval;

			//Calculate and add vertex 1
			vertex.x = radius * cosf(angle);
			vertex.y = i;
			vertex.z = radius * sinf(angle);
			
			texture.x = u;
			texture.y = v;

			normal.x = vertex.x / radius;
			normal.y = vertex.y / radius;
			normal.z = vertex.z / radius;

			addVertex(vertex);
			addTexCoord(texture);
			addNormal(normal);

			//Calculate and add vertex 2
			vertex.x = radius * cosf(angle);
			vertex.y = i + 1;
			vertex.z = radius * sinf(angle);
			
			texture.x = u;
			texture.y = v - yTexInc;

			normal.x = vertex.x / radius;
			normal.y = vertex.y / radius;
			normal.z = vertex.z / radius;

			addVertex(vertex);
			addTexCoord(texture);
			addNormal(normal);

			//Calculate and add vertex 3
			vertex.x = radius * cosf(angle + interval);
			vertex.y = i + 1;
			vertex.z = radius * sinf(angle + interval);
			
			texture.x = u + xTexInc;
			texture.y = v - yTexInc;

			normal.x = vertex.x / radius;
			normal.y = vertex.y / radius;
			normal.z = vertex.z / radius;

			addVertex(vertex);
			addTexCoord(texture);
			addNormal(normal);

			//Calculate and add vertex 4
			vertex.x = radius * cosf(angle + interval);
			vertex.y = i;
			vertex.z = radius * sinf(angle + interval);
			
			texture.x = u + xTexInc;
			texture.y = v;

			normal.x = vertex.x / radius;
			normal.y = vertex.y / radius;
			normal.z = vertex.z / radius;

			addVertex(vertex);
			addTexCoord(texture);
			addNormal(normal);

			u += xTexInc;
		}
		u = 0;
		v -= yTexInc;
	}
}

Cylinder::~Cylinder()
{
}

void Cylinder::render2() {
	glPushMatrix();
		glRotatef(90, 1, 0, 0);
		disc->render2();
	glPopMatrix();

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

	glPushMatrix();
		glTranslatef(0, segments, 0);
		glRotatef(-90, 1, 0, 0);
		disc->render2();
	glPopMatrix();
}