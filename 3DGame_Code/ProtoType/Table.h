#pragma once
#include "Object.h"
class Table :
	public Object
{
public:
	Table() : Object() {};

	void Draw(GLfloat vertecies[][3]);
	void DrawObject(GLfloat vertecies[][3]);
};

