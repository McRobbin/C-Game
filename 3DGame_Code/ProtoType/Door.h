#pragma once
#include<iostream>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>

#include "Object.h"
#include "SpecialObject.h"

class Door : public SpecialObject {
protected:

public:
	Door(GLuint index) : SpecialObject(index) {};

	void Draw(GLfloat vertecies[][3]);
	void DrawHandle(GLfloat size);
	void DrawObject(GLfloat vertecies[][3]);
	void DoorBelow();
};