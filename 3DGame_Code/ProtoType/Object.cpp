#include<iostream>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>

#include "Object.h"

using namespace std;

void Object::setColors(GLfloat ver[3]) {
	colors[0] = ver[0];
	colors[1] = ver[1];
	colors[2] = ver[2];
}
