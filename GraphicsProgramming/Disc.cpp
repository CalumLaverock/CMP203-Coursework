#include "Disc.h"

Disc::Disc(int noOfVerts, float radius)
{
	vertices = noOfVerts;
	float interval = (2 * 3.1415926) / noOfVerts;
	float angle = 0;
	Vector3 vertex = { 0.0, 0.0, 0.0 };
	Vector3 normal = { 0.0, 0.0, 0.0 };
	Vector3 texture = { 0.0, 0.0, 0.0 };

	for (int i = 0; i < noOfVerts; i++) {
		//Add the centre vertex to the 3 arrays
		addVertex({ 0.0, 0.0, 0.0 });
		addNormal({ 0.0, 0.0, 1.0 });
		addTexCoord({ 0.5, 0.5, 0.0 });

		//Calculate the first vertex of the triangle
		vertex.x = radius * cosf(angle);
		vertex.y = radius * sinf(angle);

		//Calculate the texture coordinates of the first vertex
		texture.x = (cosf(angle) / radius * 2) + 0.5;
		texture.y = (sinf(angle) / radius * 2) + 0.5;

		//Add the first vertex of the triangle to the arrays
		addVertex(vertex);
		addNormal({ 0.0, 0.0, 1.0 });
		addTexCoord(texture);

		//Increase the angle
		angle += interval;

		//Calculate the next vertex of the triangle
		vertex.x = radius * cosf(angle);
		vertex.y = radius * sinf(angle);

		//Calculate the texture coordinates of the next vertex
		texture.x = (cosf(angle) / radius * 2) + 0.5;
		texture.y = (sinf(angle) / radius * 2) + 0.5;

		//Add the next vertex to the arrays
		addVertex(vertex);
		addNormal({ 0.0, 0.0, 1.0 });
		addTexCoord(texture);
	}
}

Disc::~Disc()
{
}

void Disc::render2()
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
	glDrawArrays(GL_TRIANGLES, 0, verts.size() / 3);

	//Disable the arrays after using them
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}