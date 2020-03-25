#pragma once
#include "Object.h"

class SpecialObject :
	public Object
{
protected:
	int status = 0;
	GLuint index;
public:

	SpecialObject(GLuint index) { this->index = index; this->status = 0;};
	
	GLuint getIndex() { return index; };
	int getStatus() { return status; };
	void setStatus(int stat) { this->status = stat; };

	virtual void Draw(GLfloat vertecies[][3]) = 0;
	virtual void DrawObject(GLfloat vertecies[][3]) = 0;
};
