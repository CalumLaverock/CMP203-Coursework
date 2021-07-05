#include "Camera.h"

Camera::Camera()
{
	State temp;

	temp = { 10, 3, -3.9, false };
	states.push_back(temp);

	temp = { 2.4, 2.5, -8, false };
	states.push_back(temp);

	temp = { 2.6, 2.5, 0.05, false };
	states.push_back(temp);

	temp = { -4, 7, 11, false };
	states.push_back(temp);

	//default to free roam camera
	temp = { 0, 5, 0, true };
	states.push_back(temp);

	statePosition();
}

Camera::~Camera()
{
}

void Camera::update() {
	float cosR, cosP, cosY; //temp values for sin/cos from
	float sinR, sinP, sinY;

	// Roll, Pitch and Yaw are variables stored by the camera
	// handle rotation
	// Only want to calculate these values once, when rotation changes, not every frame.
	cosY = cosf(yaw*3.1415 / 180);
	cosP = cosf(pitch*3.1415 / 180);
	cosR = cosf(roll*3.1415 / 180);
	sinY = sinf(yaw*3.1415 / 180);
	sinP = sinf(pitch*3.1415 / 180);
	sinR = sinf(roll*3.1415 / 180);

	//This using the parametric equation of a sphere
	// Calculate the three vectors to put into glu Lookat
	// Look direction, position and the up vector

	// This function could also calculate the right vector
	forward.x = sinY * cosP;
	forward.y = sinP;
	forward.z = cosP * -cosY;

	// Look At Point
	// To calculate add Forward Vector to Camera position.

	// Up Vector
	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;

	// Side Vector (right)
	// this is a cross product between the forward and up vector.
	// If you don’t need to calculate this, don’t do it. 
	right = forward.cross(up);
}

void Camera::rotate(float rotation, int axis) {
	//depending on which key is pressed or how the mouse is moved, 
	//the camera will rotate around a different axis
	switch (axis) {
	case 1 :
		setRotation(rotation, yaw, roll); break;
	case 2 :
		setRotation(pitch, rotation, roll); break;
	case 3 :
		setRotation(pitch, yaw, rotation); break;
	}

	//update the camera after each time it rotates
	update();
}

void Camera::move(float dt, int direction) {
	//depending on which key was pressed, the camera will move in a different direction
	if (states[4].current) {
		switch (direction) {
		case 1:
			position.add(forward, dt); break;
		case 2:
			position.subtract(forward, dt); break;
		case 3:
			setPosition(position.x, position.y += dt, position.z); break;
		case 4:
			setPosition(position.x, position.y -= dt, position.z); break;
		case 5:
			position.add(right, dt); break;
		case 6:
			position.subtract(right, dt); break;
		}

		//you can't leave the room on free roam
		if (position.x >= 14) {
			position.x = 14;
		}
		else if (position.x <= -9) {
			position.x = -9;
		}

		if (position.y >= 9) {
			position.y = 9;
		}
		else if (position.y <= 1) {
			position.y = 1;
		}

		if (position.z >= 14) {
			position.z = 14;
		}
		else if (position.z <= -14) {
			position.z = -14;
		}
	}
}

void Camera::statePosition() {
	position.x = states[currentState].x;
	position.y = states[currentState].y;
	position.z = states[currentState].z;

	update();
}

void Camera::setPosition(float x, float y, float z) {
	position = { x, y, z };
}

void Camera::setRotation(float p, float y, float r) {
	pitch = p;
	yaw = y;
	roll = r;
}

void Camera::setDefaults() {
	position.x = 0;
	position.y = 5;
	position.z = 0;

	yaw = 0;
	pitch = 0;
	roll = 0;
}

void Camera::setState(int s) {
	states[currentState].current = false;

	currentState = s;
	states[s].current = true;
}

int Camera::getState() {
	return currentState;
}

void Camera::nextState() {
	states[currentState].current = false;

	currentState++;

	if (currentState > 4) {
		currentState = 0;
	}

	states[currentState].current = true;

	statePosition();
}

Vector3 Camera::getPosition() {
	return position;
}

Vector3 Camera::getLookAt() {
	return forward + position;
}

Vector3 Camera::getUp() {
	return up;
}