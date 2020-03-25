#pragma once
#include "SpecialObject.h"
class Ruler :
	public SpecialObject
{
public:
	Ruler(GLuint index) : SpecialObject(index) {};

	void Draw(GLfloat vertecies[][3]);
	void DrawObject(GLfloat vertecies[][3]);
};

