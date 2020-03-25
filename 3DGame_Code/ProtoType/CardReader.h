#pragma once
#include "SpecialObject.h"
class CardReader :
	public SpecialObject
{
public:
	CardReader(GLuint index) : SpecialObject(index) {};

	void Draw(GLfloat vertecies[][3]);
	void DrawObject(GLfloat vertecies[][3]);
};

