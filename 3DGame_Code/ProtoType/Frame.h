#pragma once
#include<iostream>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>

#include "Object.h"
#include "SpecialObject.h"


class Frame : public SpecialObject {
protected:
	
public:
	Frame(GLuint index) : SpecialObject(index) {};

	void Draw(GLfloat vertecies[][3]);
	void DrawObject(GLfloat vertecies[][3]);
	void DrawFlower();
};