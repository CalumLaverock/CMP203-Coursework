#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
#include "Vector3.h"
#include <vector>

class Camera
{
public:
	Camera();
	~Camera();

	void update();
	void rotate(float rotation, int axis);
	void move(float dt, int direction);
	void statePosition();

	Vector3 getPosition();
	Vector3 getLookAt();
	Vector3 getUp();

	void setPosition(float x, float y, float z);
	void setDefaults();
	void setState(int);
	int getState();
	void nextState();

private:
	Vector3 position = { 0,5,0 };
	Vector3 forward = { 0,0,0 };
	Vector3 up = { 0,0,0 };
	Vector3 right = { 0,0,0 };

	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;

	struct State 
	{   
		double x, y, z;
		bool current;
	};

	int currentState = 4;
	std::vector<State> states;

	void setRotation(float pitch, float yaw, float roll);
};

