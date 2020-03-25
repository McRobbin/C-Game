#pragma once
#include "Object.h"
class Egg :
	public Object
{
public:
	Egg() : Object() {};

	void Draw(GLfloat vertecies[][3]);
	void DrawObject(GLfloat vertecies[][3]);
};

