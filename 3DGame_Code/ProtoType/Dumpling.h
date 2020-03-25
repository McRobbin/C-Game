#pragma once
#include "SpecialObject.h"
class Dumpling :
	public SpecialObject
{
public:
	Dumpling(GLuint index) : SpecialObject(index) {};
	void Draw(GLfloat vertecies[][3]);
	void DrawObject(GLfloat vertecies[][3]);
};

