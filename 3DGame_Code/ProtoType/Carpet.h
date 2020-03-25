#pragma once
#include "SpecialObject.h"
class Carpet :
	public SpecialObject
{
public:
	Carpet(GLuint index) : SpecialObject(index) {};

	void Draw(GLfloat vertecies[][3]);
	void DrawObject(GLfloat vertecies[][3]);
};

