#include "Scene.h"
#include <iostream>

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in, Camera *cam)
{
	// Store pointer for input class
	input = in;
	camera = cam;
		
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	// Other OpenGL / render setting should be applied here.
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialise scene variables
	skyTexture = SOIL_load_OGL_texture(
		"gfx/skybox.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	wallTexture = SOIL_load_OGL_texture(
		"gfx/wallpaper.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	floorTexture = SOIL_load_OGL_texture(
		"gfx/Dark_Mahogany.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	rugTexture = SOIL_load_OGL_texture(
		"gfx/rug.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	pillarTexture = SOIL_load_OGL_texture(
		"gfx/pillar.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	deskTexture = SOIL_load_OGL_texture(
		"gfx/placemat.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	lightOnTexture = SOIL_load_OGL_texture(
		"gfx/lightOn.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	lightOffTexture = SOIL_load_OGL_texture(
		"gfx/lightOff.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	camera->update();

	for (int i = 0; i < 4; i++) {
		walls[i] = new Plane(25, 10);
	}

	roof = new Plane(25, 30);
	floor = new Plane(25, 30);
	rug = new Plane(5, 8);
	platformFloor = new Plane(20, 5);
	platformWall = new Plane(20, 1);
	deskTop = new Plane(10, 10);

	pillar = new Cylinder(5, 20, 0.15);

	skybox = new Skybox();

	shelf.load("models/SHELF OBJ.obj", "models/SHELF_TEXTURE.bmp");
	books.load("models/BOOKS OBJ.obj", "models/BOOKS_TEXTURE.bmp");
	desk.load("models/DESK.obj", "models/DeskTex.jpg");
	chair.load("models/CHAIR.obj", "models/ChairTex.png");
	deskChair.load("models/DESK CHAIR.obj", "models/DeskChairTex.jpg");
	fence.load("models/FENCE.obj", "gfx/pillar.jpg");
	lamp.load("models/LAMP.obj", "models/LampTex.jpg");
}

void Scene::handleInput(float dt)
{
	// Handle user input

	//Camera Rotation
	//Keyboard Rotation
	/*if (input->isKeyDown('j')) {
		yaw -= speed * dt;
		camera->rotate(yaw, 2);
	}
	else if (input->isKeyDown('l')) {
		yaw += speed * dt;
		camera->rotate(yaw, 2);
	}

	if (input->isKeyDown('i')) {
		pitch -= speed * dt;
		camera->rotate(pitch, 1);
	}
	else if (input->isKeyDown('k')) {
		pitch += speed * dt;
		camera->rotate(pitch, 1);
	}*/

	//Mouse Rotation
	float centreX = width / 2;
	float centreY = height / 2;

	if (((input->getMouseX() - centreX) > 0) || ((input->getMouseX() - centreX) < 0)) {
		yaw += (input->getMouseX() - centreX) * 0.1;
		camera->rotate(yaw, 2);
	}

	if (((input->getMouseY() - centreY) > 0) || ((input->getMouseY() - centreY) < 0)) {
		pitch -= (input->getMouseY() - centreY) * 0.1;
		camera->rotate(pitch, 1);
	}

	glutWarpPointer(width / 2, height / 2);

	//Camera Movement
	//Move forward/backward
	if (input->isKeyDown('w')) {
		camera->move(dt, 1);
	}
	else if (input->isKeyDown('s')) {
		camera->move(dt, 2);
	}

	//Move up/down
	if (input->isKeyDown(' ')) {
		camera->move(dt, 3);
	}
	else if (input->isKeyDown('z')) {
		camera->move(dt, 4);
	}

	//Move right/left
	if (input->isKeyDown('d')) {
		camera->move(dt, 5);
	}
	else if (input->isKeyDown('a')) {
		camera->move(dt, 6);
	}

	//Control the lamp
	if (input->isKeyDown('l') && lampSwitch) {
		lampSwitch = false;
		input->SetKeyUp('l');
	}
	else if (input->isKeyDown('l') && !lampSwitch) {
		lampSwitch = true;
		input->SetKeyUp('l');
	}

	//Control the roof lights
	if (input->isKeyDown('1')) {
		if (lightOne) {
			lightOne = false;
		}
		else {
			lightOne = true;
		}

		input->SetKeyUp('1');
	}

	if (input->isKeyDown('2')) {
		if (lightTwo) {
			lightTwo = false;
		}
		else {
			lightTwo = true;
		}

		input->SetKeyUp('2');
	}

	//Control camera state
	if (input->isLeftMouseButtonPressed()) {
		input->setLeftMouseButton(false);
		camera->nextState();
	}

	//Control chair movement
	if (input->isKeyDown('c') && chairMove < 2) {
		movingOut = true;
		input->SetKeyUp('c');
	}
	else if (input->isKeyDown('c') && chairMove >= 2) {
		movingIn = true;
		input->SetKeyUp('c');
	}

	if (movingOut) {
		if (chairMove < 2) {
			chairMove += 0.01;

			if (camera->getState() == 0) {
				camera->setPosition(camera->getPosition().x + 0.01, camera->getPosition().y, camera->getPosition().z);
			}
		}
		else if (chairMove >= 2) {
			movingOut = false;
		}
	}

	if (movingIn) {
		if (chairMove > 0) {
			chairMove -= 0.01;

			if (camera->getState() == 0) {
				camera->setPosition(camera->getPosition().x - 0.01, camera->getPosition().y, camera->getPosition().z);
			}
		}
		else if (chairMove <= 0) {
			movingIn = false;
		}
	}

	if (input->isKeyDown('r')) {
		if (wireToggle) {
			wireToggle = false;
		}
		else {
			wireToggle = true;
		}

		input->SetKeyUp('r');
	}
}

void Scene::update(float dt)
{
	// Calculate FPS for output
	calculateFPS();
}

void Scene::render() {
	//Re-enable lighting after disabling it at the end of render
	glEnable(GL_LIGHTING);

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z, camera->getLookAt().x, camera->getLookAt().y, camera->getLookAt().z, camera->getUp().x, camera->getUp().y, camera->getUp().z);

	//Light values
	GLfloat Light_Ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat Light_Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat Ambient_Position[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat Light_Position1[] = { 13.2f, 9.8f, 13.2f, 1.0f };
	GLfloat Light_Position2[] = { -8.2f, 9.8f, -13.2f, 1.0f };
	GLfloat Lamp_Position[] = { 8.1f, 2.8f, -4.2f, 1.0f };
	GLfloat spot_Direction[] = { 0.0f, -1.0f, 0.0f };

	//Ambient light
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, Ambient_Position);

	//Roof light #1
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, Light_Position1);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.2);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.4);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);

	//Roof light #2
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, Light_Position2);

	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.2);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.4);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0);

	//Desk lamp
	glLightfv(GL_LIGHT3, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT3, GL_POSITION, Lamp_Position);

	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 30.0f);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_Direction);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 10.0);

	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 1.0);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.5);

	//Enable the light
	glEnable(GL_LIGHT0);

	//Enable/Disable the lights depending on if their 
	//corresponding key has been pressed
	if (lightOne) {
		glEnable(GL_LIGHT1);
	}
	else {
		glDisable(GL_LIGHT1);
	}
	
	if (lightTwo) {
		glEnable(GL_LIGHT2);
	}
	else {
		glDisable(GL_LIGHT2);
	}

	if (lampSwitch) {
		glEnable(GL_LIGHT3);
	}
	else {
		glDisable(GL_LIGHT3);
	}

	// Render geometry/scene here -------------------------------------

	if (wireToggle) {
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
	}

	//Set type of texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//Set texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	//Draw the scene --------------------------------------------
	
	//Generate shadow matrices
	GLfloat floorVerts[] = { -12.5, 0, -15,
							 -12.5, 0, 15,
							  12.5, 0, 15,
							  12.5, 0, -15 };

	Shadow::generateShadowMatrix(floorShadowMatrixOne, Light_Position1, floorVerts);
	Shadow::generateShadowMatrix(floorShadowMatrixTwo, Light_Position2, floorVerts);

	//Draw the skybox first
	glBindTexture(GL_TEXTURE_2D, skyTexture);
	glPushMatrix();
		drawSkybox(camera);
	glPopMatrix();

	//Create the walls, floor and roof
	drawRoom();

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glDisable(GL_DEPTH_TEST);

	glPushMatrix();
		glTranslatef(-10, 0, 15);
		glRotatef(-90, 1, 0, 0);
		floor->render2();
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	//Render the shadow
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glColor3f(0, 0, 0);

	//Only draw shadows caused by light 1 if light 1 is on
	if (lightOne) {
		//Draw shadows for all objects that cast shadows on the floor from light 1
		glPushMatrix();
			glMultMatrixf((GLfloat *)floorShadowMatrixOne);

			glPushMatrix();
				glTranslatef(2.4, 0, -8);
				glScalef(3, 3, 3);
				chair.render();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(2.6, 0, 0.05);
				glRotatef(180, 0, 1, 0);
				glScalef(3, 3, 3);
				chair.render();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(8, 0, -3.9);

				glPushMatrix();
					glRotatef(90, 0, 1, 0);
					glRotatef(-90, 1, 0, 0);
					glScalef(0.025, 0.025, 0.025);
					desk.render();
				glPopMatrix();

				glPushMatrix();
					glTranslatef(2 + chairMove, 0, 0);
					glRotatef(-90, 0, 1, 0);
					glRotatef(-90, 1, 0, 0);
					glScalef(0.025, 0.025, 0.025);
					deskChair.render();
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(15.075, 0, 10);

				glPushMatrix();
					glTranslatef(0, 5, 0);
					glRotatef(-180, 0, 1, 0);
					glRotatef(-90, 1, 0, 0);
					platformFloor->render2();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	}

	//Only draw shadows caused by light 2 if light 2 is on
	if (lightTwo) {
		//Draw shadows for all objects that cast shadows on the floor from light 2
		glPushMatrix();
			glMultMatrixf((GLfloat *)floorShadowMatrixTwo);

			glPushMatrix();
				glTranslatef(2.4, 0, -8);
				glScalef(3, 3, 3);
				chair.render();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(2.6, 0, 0.05);
				glRotatef(180, 0, 1, 0);
				glScalef(3, 3, 3);
				chair.render();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(8, 0, -3.9);

				glPushMatrix();
					glRotatef(90, 0, 1, 0);
					glRotatef(-90, 1, 0, 0);
					glScalef(0.025, 0.025, 0.025);
					desk.render();
				glPopMatrix();

				glPushMatrix();
					glTranslatef(2 + chairMove, 0, 0);
					glRotatef(-90, 0, 1, 0);
					glRotatef(-90, 1, 0, 0);
					glScalef(0.025, 0.025, 0.025);
					deskChair.render();
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(15.075, 0, 10);

				glPushMatrix();
					glTranslatef(0, 5, 0);
					glRotatef(-180, 0, 1, 0);
					glRotatef(-90, 1, 0, 0);
					platformFloor->render2();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	}

	glColor3f(1.0, 1.0, 1.0);
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	glDisable(GL_STENCIL_TEST);
	//End of stencil buffer use and shadow drawing

	//Start drawing objects

	//Create the bookshelves on the raised platform
	glPushMatrix();
		glTranslatef(12.5, 4.5, 15);
		glRotatef(-180, 0, 1, 0);
		glScalef(0.05, 0.03, 0.03);
		shelf.render();
		books.render();

		glPushMatrix();
			glTranslatef((5/0.05), 0, 0);
			shelf.render();
			books.render();
		glPopMatrix();

		glPushMatrix();
			glTranslatef((10 / 0.05), 0, 0);
			shelf.render();
			books.render();
		glPopMatrix();

		glPushMatrix();
			glTranslatef((15 / 0.05), 0, 0);
			shelf.render();
			books.render();
		glPopMatrix();
	glPopMatrix();

	//Desk and Chair (free rug included!)
	glPushMatrix();
		glPushMatrix();
			//The disable/enable of GL_LIGHT3 (lamp light) is to prevent the lamp
			//from lighting the rug underneath the desk. 
			//There is probably a better way to do this.
			glDisable(GL_LIGHT3);
			glBindTexture(GL_TEXTURE_2D, rugTexture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTranslatef(4, 0.001, 0);
			glRotatef(-90, 1, 0, 0);
			rug->render2();

			//Only re-enable the lamp if the lamp should be on (i.e. lampSwitch == false)
			if (lampSwitch) {
				glEnable(GL_LIGHT3);
			}
		glPopMatrix();

		//Position and draw the desk area. Including desk, desk chair, lamp, and desk top (needed to make
		//lamp light desk correctly as desk normals are weird. Probably only has a normal in each
		//corner for the top of the desk).
		glPushMatrix();
			glTranslatef(8, 0, -3.9);
			
			glPushMatrix();
				glRotatef(90, 0, 1, 0);
				glRotatef(-90, 1, 0, 0);
				glScalef(0.025, 0.025, 0.025);
				desk.render();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.1, 1.9, -1.5);

				glPushMatrix();
					glRotatef(-90, 0, 1, 0);
					glRotatef(-90, 1, 0, 0);
					glScalef(0.02, 0.02, 0.02);
					lamp.render();
				glPopMatrix();

				glPushMatrix();
					glBindTexture(GL_TEXTURE_2D, deskTexture);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

					glTranslatef(-1.1, 0.03, 0.5);
					glRotatef(-90, 0, 1, 0);
					glRotatef(-90, 1, 0, 0);
					glScalef(0.2, 0.2, 1);
					deskTop->render2();
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(2 + chairMove, 0, 0);
				glRotatef(-90, 0, 1, 0);
				glRotatef(-90, 1, 0, 0);
				glScalef(0.025, 0.025, 0.025);
				deskChair.render();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	//Creating the seating area
	glPushMatrix();
		glTranslatef(2.4, 0, -8);
		glScalef(3, 3, 3);
		chair.render();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2.6, 0, 0.05);
		glRotatef(180, 0, 1, 0);
		glScalef(3, 3, 3);
		chair.render();
	glPopMatrix();

	//Creating the raised area with railing and pillars 
	glBindTexture(GL_TEXTURE_2D, pillarTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	drawPlatform();

	//Draw roof light 1
	glPushMatrix();
		glTranslatef(13.2, 9.999, 13.2);
		glRotatef(90, 1, 0, 0);
		glScalef(0.3, 0.3, 1);
		drawLight(lightOne);
	glPopMatrix();

	//Draw roof light 2
	glPushMatrix();
		glTranslatef(-8.2, 9.999, -13.2);
		glRotatef(90, 1, 0, 0);
		glScalef(0.3, 0.3, 1);
		drawLight(lightTwo);
	glPopMatrix();

	//Disable lighting as it interferes with text on the screen
	//re-enable at the start of the render function
	glDisable(GL_LIGHTING);
	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

	
}

// Calculates FPS
void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 1.f, 1.f, mouseText);
	displayText(-1.f, 0.90f, 0.f, 0.f, 1.f, fps);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}

void Scene::drawSkybox(Camera* cam) {
	glTranslatef(cam->getPosition().x, cam->getPosition().y, cam->getPosition().z);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
		skybox->render2();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

void Scene::drawRoom() {
	//Bind the texture for the walls
	glBindTexture(GL_TEXTURE_2D, wallTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Creating the walls for the room
	glPushMatrix();
		glTranslatef(-10, 0, -15);
		walls[0]->render2();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(15, 0, -15);
		glRotatef(-90, 0, 1, 0);
		glScalef(1.2, 1, 1);
		walls[1]->render2();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(15, 0, 15);
		glRotatef(-180, 0, 1, 0);
		walls[2]->render2();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-10, 0, 15);
		glRotatef(90, 0, 1, 0);
		glScalef(1.2, 1, 1);
		walls[3]->render2();
	glPopMatrix();

	//Creating the roof
	glPushMatrix();
		glTranslatef(-10, 10, -15);
		glRotatef(90, 1, 0, 0);
		roof->render2();
	glPopMatrix();

	//Creating the floor
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, floorTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTranslatef(-10, 0, 15);
		glRotatef(-90, 1, 0, 0);
		floor->render2();
	glPopMatrix();
}

void Scene::drawPillar() {
	//Each pillar is made of 4 cylinders
	pillar->render2();

	glPushMatrix();
		glTranslatef(-0.1, 0, 0);
		pillar->render2();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.05, 0, 0.1);
		pillar->render2();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.05, 0, -0.1);
		pillar->render2();
	glPopMatrix();
}

void Scene::drawPlatform() {
	glPushMatrix();
		glTranslatef(15.075, 0, 10);

		//Creating the raised platform
		glPushMatrix();
			glTranslatef(0, 5, 0);
			glRotatef(-180, 0, 1, 0);
			glRotatef(-90, 1, 0, 0);
			platformFloor->render2();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-20, 4, 0);
			glRotatef(90, 1, 0, 0);
			platformFloor->render2();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-20, 5, 0);
			glRotatef(-180, 1, 0, 0);
			platformWall->render2();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-20, 5, 5);
			glRotatef(90, 0, 1, 0);
			glRotatef(-180, 1, 0, 0);
			glScalef(0.25, 1, 1);
			platformWall->render2();
		glPopMatrix();

		//Creating the pillars and fences for the raised platform
		glPushMatrix();
			glTranslatef(0, 5, 0);
			glScalef(0.08, 0.04, 0.08);
			fence.render();
		glPopMatrix();

		drawPillar();

		glPushMatrix();
			glTranslatef(-2.5, 5, 0);
			glScalef(0.08, 0.04, 0.08);
			fence.render();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-5, 0, 0);

			drawPillar();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-5, 5, 0);
			glScalef(0.08, 0.04, 0.08);
			fence.render();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-7.5, 5, 0);
			glScalef(0.08, 0.04, 0.08);
			fence.render();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-10, 0, 0);

			drawPillar();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-10, 5, 0);
			glScalef(0.08, 0.04, 0.08);
			fence.render();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-12.5, 5, 0);
			glScalef(0.08, 0.04, 0.08);
			fence.render();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-15, 0, 0);

			drawPillar();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-15, 5, 0);
			glScalef(0.08, 0.04, 0.08);
			fence.render();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-17.5, 5, 0);
			glScalef(0.08, 0.04, 0.08);
			fence.render();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-20, 0, 0);

			drawPillar();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-20, 5, 0);
			glScalef(0.08, 0.04, 0.08);
			fence.render();
		glPopMatrix();

		glRotatef(90, 0, 1, 0);

		glPushMatrix();
			glTranslatef(-2.5, 5, -20);
			glScalef(0.08, 0.04, 0.08);
			fence.render();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-5, 0, -20);

			drawPillar();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-5, 5, -20);
			glScalef(0.08, 0.04, 0.08);
			fence.render();
		glPopMatrix();
	glPopMatrix();
}

void Scene::drawLight(bool lightOn) {
	glEnable(GL_BLEND);

	if (lightOn) {
		glBindTexture(GL_TEXTURE_2D, lightOnTexture);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, lightOffTexture);
	}

	glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		glTexCoord2f(0, 0);
		glVertex3f(-1, 1, 0);
		
		glNormal3f(0, 0, 1);
		glTexCoord2f(0, 1);
		glVertex3f(-1, -1, 0);

		glNormal3f(0, 0, 1);
		glTexCoord2f(1, 1);
		glVertex3f(1, -1, 0);

		glNormal3f(0, 0, 1);
		glTexCoord2f(1, 0);
		glVertex3f(1, 1, 0);
	glEnd();

	glDisable(GL_BLEND);
}