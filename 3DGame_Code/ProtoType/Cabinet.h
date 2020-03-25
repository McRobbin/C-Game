#pragma once
#include<iostream>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>

#include "Object.h"
#include "SpecialObject.h"
#include <vector>

using namespace std;

class Cabinet : public SpecialObject {
protected:


public:
	int key_x = 0, key_y = 0;

	int answer_index = 0;
	int t = 0;

	int cabinet_answer[16] = { 4,6,2, 0,3,0, 1,1,2, 2,2,1, 1,3,2,3 };
	vector<int> cabinet_submit;
	
	Cabinet(GLuint index) : SpecialObject(index) {};

	void Draw(GLfloat vertecies[][3]);
	void DrawObject(GLfloat vertecies[][3]);
	void DrawingKeyPad();
	bool ValidAnswer();
};