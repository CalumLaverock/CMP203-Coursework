#include "Plane.h"

Plane::Plane(int xSeg, int ySeg)
{
	Vector3 vertex = { 0.0, 0.0, 0.0 };
	Vector3 normal = { 0.0, 0.0, 1.0 };
	Vector3 texture = { 0.0, 0.0, 0.0 };

	for (int y = 0; y < ySeg; y++) {
		for (int x = 0; x < xSeg; x++) {
			//Lower left vertex of each unit quad
			vertex.x = x;
			vertex.y = y;

			texture.x = x;
			texture.y = y + 1;

			addVertex(vertex);
			addNormal(normal);
			addTexCoord(texture);

			//Lower right vertex of each unit quad
			vertex.x = x + 1;
			vertex.y = y;

			texture.x = x + 1;
			texture.y = y + 1;

			addVertex(vertex);
			addNormal(normal);
			addTexCoord(texture);

			//Upper right vertex of each unit quad
			vertex.x = x + 1;
			vertex.y = y + 1;

			texture.x = x + 1;
			texture.y = y;

			addVertex(vertex);
			addNormal(normal);
			addTexCoord(texture);

			//Upper left vertex of each unit quad
			vertex.x = x;
			vertex.y = y + 1;

			texture.x = x;
			texture.y = y;

			addVertex(vertex);
			addNormal(normal);
			addTexCoord(texture);
		}
	}
}

Plane::~Plane()
{
}

void Plane::render2() 
{
	//Enable the necessary arrays for generating the shape
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//Setup the relevant pointers needed i.e. one to point to the vertex array,
	//one for the normal array and one for the texture coord array
	glVertexPointer(3, GL_FLOAT, 0, verts.data());
	glNormalPointer(GL_FLOAT, 0, norms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords.data());

	//glDrawArrays() will access the full arrays for vertices, normals and tex coords
	//with one function call. glBegin() and glEnd() is not needed here.
	//An index array is not needed meaning that the order in the arrays is very important.
	glDrawArrays(GL_QUADS, 0, verts.size() / 3);

	//Disable the arrays after using them
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
