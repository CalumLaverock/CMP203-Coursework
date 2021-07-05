#include "shape.h"

Shape::Shape() 
{
}

void Shape::render1()
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

	//Dereference the pointers just created using glArrayElement, the argument
	//will access the appropriate information from the arrays.
	//One glArrayElement() is the equivalent of glVertex3f(), glNormal3f() and glTexCoord2f()
	//for one vertex.
	glBegin(GL_QUADS);
		glArrayElement(0);
		glArrayElement(1);
		glArrayElement(2);
		glArrayElement(3);

		glArrayElement(4);
		glArrayElement(5);
		glArrayElement(6);
		glArrayElement(7);

		glArrayElement(8);
		glArrayElement(9);
		glArrayElement(10);
		glArrayElement(11);

		glArrayElement(12);
		glArrayElement(13);
		glArrayElement(14);
		glArrayElement(15);

		glArrayElement(16);
		glArrayElement(17);
		glArrayElement(18);
		glArrayElement(19);

		glArrayElement(20);
		glArrayElement(21);
		glArrayElement(22);
		glArrayElement(23);
	glEnd();

	//Disable the arrays after using them
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::render2()
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
	glDrawArrays(GL_QUADS, 0, 24);

	//Disable the arrays after using them
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::render3()
{
	//Enable the necessary arrays for generating the shape
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_INDEX_ARRAY);

	//Setup the relevant pointers needed i.e. one to point to the vertex array,
	//one for the normal array and one for the texture coord array
	glVertexPointer(3, GL_FLOAT, 0, verts.data());
	glNormalPointer(GL_FLOAT, 0, norms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords.data());
	glIndexPointer(GL_UNSIGNED_BYTE, 0, indices.data());

	//glDrawElements() will access the full arrays with one function call however
	//it does require an index array.
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices.data());

	//Disable the arrays after using them
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_INDEX_ARRAY);
}

void Shape::addVertex(Vector3 vert) {
	verts.push_back(vert.getX());
	verts.push_back(vert.getY());
	verts.push_back(vert.getZ());
}

void Shape::addNormal(Vector3 norm) {
	norms.push_back(norm.getX());
	norms.push_back(norm.getY());
	norms.push_back(norm.getZ());
}

void Shape::addTexCoord(Vector3 texCo) {
	texCoords.push_back(texCo.getX());
	texCoords.push_back(texCo.getY());
}

void Shape::addIndex(GLubyte index) {
	indices.push_back(index);
}


