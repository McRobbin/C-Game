#pragma once
#include "SpecialObject.h"
class Key :
	public SpecialObject
{
public:
	Key(GLuint index) : SpecialObject(index) {};

	void Draw(GLfloat vertecies[][3]);
	void DrawHandle(GLfloat size);
	void DrawObject(GLfloat vertecies[][3]);
};

