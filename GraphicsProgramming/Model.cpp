// Below ifdef required to remove warnings for unsafe version of fopen and fscanf.
// Secure version won't work cross-platform, forcing this small hack.
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "model.h"

bool Model::load(char* modelFilename, char* textureFilename)
{
	bool result;

	// Load in the model data,
	result = loadModel(modelFilename);
	if (!result)
	{
		MessageBox(NULL, L"Model failed to load", L"Error", MB_OK);
		return false;
	}

	// Load the texture for this model.
	loadTexture(textureFilename);

	return true;
}

void Model::render()
{
	glBindTexture(GL_TEXTURE_2D, texture);

	//Enable the necessary arrays for generating the shape
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//Setup the relevant pointers needed i.e. one to point to the vertex array,
	//one for the normal array and one for the texture coord array
	glVertexPointer(3, GL_FLOAT, 0, &vertex[0]);
	glNormalPointer(GL_FLOAT, 0, &normals[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &texCoords[0]);

	//glDrawArrays() will access the full arrays for vertices, normals and tex coords
	//with one function call. glBegin() and glEnd() is not needed here.
	//An index array is not needed meaning that the order in the arrays is very important.
	glDrawArrays(GL_TRIANGLES, 0, vertex.size() / 3);

	//Disable the arrays after using them
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


// Modified from a mulit-threaded version by Mark Ropper.
bool Model::loadModel(char* filename)
{
	vector<Vector3> verts;
	vector<Vector3> norms;
	vector<Vector3> texCs;
	vector<unsigned int> faces;
	
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		return false;
	}
	while (true)
	{
		char lineHeader[128];

		// Read first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break; // exit loop
		}
		else // Parse
		{
			if (strcmp(lineHeader, "v") == 0) // Vertex
			{
				Vector3 vertices;
				fscanf(file, "%f %f %f\n", &vertices.x, &vertices.y, &vertices.z);
				verts.push_back(vertices);
			}
			else if (strcmp(lineHeader, "vt") == 0) // Tex Coord
			{
				Vector3 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				texCs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) // Normal
			{
				Vector3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				norms.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) // Face
			{
				unsigned int face[9];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &face[0], &face[1], &face[2],
																			&face[3], &face[4], &face[5],
																			&face[6], &face[7], &face[8]);
				if (matches != 9)
				{
					// Parser error, or not triangle faces
					return false;
				}
				
				for (int i = 0; i < 9; i++)
				{
					faces.push_back(face[i]);
				}


			}
		}
	}

	// "Unroll" the loaded obj information into a list of triangles.
	for (int f = 0; f < faces.size(); f += 3) {
		//add the vertex data read from the file into a vector of floats
		vertex.push_back(verts[faces[f] - 1].x);
		vertex.push_back(verts[faces[f] - 1].y);
		vertex.push_back(verts[faces[f] - 1].z);

		//add the tex coord data read from the file into a vector of floats
		texCoords.push_back(texCs[faces[f + 1] - 1].x);
		texCoords.push_back(texCs[faces[f + 1] - 1].y);

		//add the normal data read from the file into a vector of floats
		normals.push_back(norms[faces[f + 2] - 1].x);
		normals.push_back(norms[faces[f + 2] - 1].y);
		normals.push_back(norms[faces[f + 2] - 1].z);
	}
	
	
	// Once data has been sorted clear read data (which has been copied and are not longer needed).
	verts.clear();
	norms.clear();
	texCs.clear();
	faces.clear();

	return true;
}

void Model::loadTexture(char* filename)
{
	texture = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y // Depending on texture file type some need inverted others don't.
	);

	//check for an error during the load process
	if (texture == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

}



