// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
#include "Camera.h"
#include "Disc.h"
#include "Sphere.h"
#include "Model.h"
#include "Plane.h"
#include "Cube.h"
#include "Skybox.h"
#include "Cylinder.h"
#include "Shadow.h" 


class Scene{

public:
	Scene(Input *in, Camera *cam);
	// Main render function
	void render();
	// Handle input function that receives delta time from parent.
	void handleInput(float dt);
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);

protected:
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	void calculateFPS();

	// draw primitive functions
	void drawSkybox(Camera* cam);
	void drawRoom();
	void drawPillar();
	void drawPlatform();
	void drawLight(bool);

	// For access to user input.
	Input* input;
		
	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];

	// For wireframe shapes
	bool wireToggle = false;

	// For rotations
	float rotation = 0;
	float speed = 10;

	// For lights
	bool rotateLight = false;
	bool lampSwitch = false;
	bool lightOne = true, lightTwo = true;

	// For shadows
	float floorShadowMatrixOne[16];
	float floorShadowMatrixTwo[16];

	// For movement
	float chairMove = 0;
	bool movingOut;
	bool movingIn;

	// Textures
	GLuint wallTexture;
	GLuint floorTexture;
	GLuint skyTexture;
	GLuint rugTexture;
	GLuint pillarTexture;
	GLuint deskTexture;
	GLuint lightOnTexture;
	GLuint lightOffTexture;

	// Camera
	Camera* camera;

	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;

	// Shapes
	Skybox *skybox;
	Plane *walls[4];
	Plane *roof;
	Plane *floor;
	Plane *rug;
	Plane *platformFloor;
	Plane *platformWall;
	Plane *deskTop;
	Cylinder *pillar;

	Model shelf;
	Model books;
	Model chair;
	Model desk;
	Model deskChair;
	Model fence;
	Model lamp;
};

#endif