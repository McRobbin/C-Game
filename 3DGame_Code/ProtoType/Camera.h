#pragma once
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>
#include <math.h>

#define PI 3.14159265

#define CAM_STAT_STAND 0
#define CAM_STAT_SIT 1
#define CAM_STAT_FIX 2


class Camera
{
public:
	//for user
	GLint status = CAM_STAT_STAND;
	GLfloat y_vel = 0;
	//0이 정지부터 숫자 키패드 방향으로 진행.
	GLint move_state = 0;

	//for Camera
	GLfloat zoom = 1.0;
	GLfloat center_x = 0;
	GLfloat center_y = 0;
	GLfloat center_z = -1.0;
	GLfloat axis_x = 0;
	GLfloat axis_y = 1;
	GLfloat axis_z = 0;
	GLfloat eye_x = 0, eye_y = 0, eye_z = 0;
	GLfloat pitch = 0.0;
	GLfloat yaw = 0.0;

	//for Window
	GLboolean fullScreen = true;

	GLint width = 500;
	GLint height = 500;



	Camera() {};

	void CameraSit();
	void CameraStand();
	void CameraBound();
	void Moving();
};

