#pragma once
#include "SpecialObject.h"

class Card :
	public SpecialObject
{
public:
	Card(GLuint index) : SpecialObject(index) {};

	void Draw(GLfloat vertecies[][3]);
	void DrawObject(GLfloat vertecies[][3]);
};

