#pragma once
#include<iostream>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>

#include <string>

using namespace std;

class Object {

protected:

	GLfloat colors[3];

public:
	static GLubyte MyVertexList[24];
	static GLfloat MyColors[8][3];

	Object() {};

	void setColors(GLfloat ver[3]);

	virtual void Draw(GLfloat vertecies[][3]) = 0;
	virtual void DrawObject(GLfloat vertecies[][3]) = 0;
};