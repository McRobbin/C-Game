#include "Camera.h"



void Camera::CameraSit() {
	this->status = CAM_STAT_SIT;
	this->eye_y = -7.5;
}


void Camera::CameraStand() {
	this->status = CAM_STAT_STAND;
	this->eye_y = 0.0;
}

void Camera::CameraBound() {

	/*****벽 못 뚫게*******/
	if (this->eye_x >= 9.5)
		this->eye_x = 9.5;
	if (this->eye_x <= -9.5)
		this->eye_x = -9.5;
	if (this->eye_y >= 9.5)
		this->eye_y = 9.5;
	if (this->eye_y <= -9.5)
		this->eye_y = -9.5;
	if (this->eye_z >= 9.5)
		this->eye_z = 9.5;
	if (this->eye_z <= -9.5)
		this->eye_z = -9.5;

	GLfloat temp_x = this->eye_x;
	GLfloat temp_y = this->eye_y;
	GLfloat temp_z = this->eye_z;

	/*****테이블 못 뚫게 ****/

	if (this->eye_x >= 5.0 && this->eye_z <= -3.0) {
		if (this->eye_x - 5.0 >= -(this->eye_z) - 3.0) {
			this->eye_z = -3.0;
		}
		else this->eye_x = 5.0;
	}


	/**********캐비넷 못 뚫게***********/
	if (this->eye_x <= -7.8 && (this->eye_z <= 3.2 && this->eye_z >= -3.2)) {
		if (this->eye_z > 0) {
			if (-(this->eye_x) - 7.8 >= 3.2 - this->eye_z) {
				this->eye_z = 3.2;
			}
			else this->eye_x = -7.8;
		}
		else {
			if (-(this->eye_x) - 7.8 >= 3.2 + this->eye_z) {
				this->eye_z = -3.2;
			}
			else this->eye_x = -7.8;
		}

	}

	/*******리더기 못 뚫게********/
	if (this->eye_z < -8.8 && (this->eye_x<-2.8 && this->eye_x>-5.2)) {
		if (-2.8 - this->eye_x < this->eye_x + 5.2) {
			if (-(this->eye_z) - 8.8 > -2.8 - this->eye_x)
				this->eye_x = -2.8;
			else this->eye_z = -8.8;
		}
		else {
			if (-(this->eye_z) - 8.8 > this->eye_x + 5.2)
				this->eye_x = -5.2;
			else  this->eye_z = -8.8;
		}
	}
}

void Camera::Moving() {
	GLfloat camera_speed = 0.15;
	// cameraFront 와 axis 외적 및 정규화
	GLfloat cross_x = (this->center_y*this->axis_z) - (this->center_z*this->axis_y);
	GLfloat cross_y = (this->center_x*this->axis_z) - (this->center_z*this->axis_x);
	GLfloat cross_z = (this->center_x*this->axis_y) - (this->center_y*this->axis_x);
	GLfloat normalized_cross = sqrt(pow(cross_x, 2) + pow(cross_y, 2) + pow(cross_z, 2));

	switch (this->move_state) {
	case 1:
		eye_x -= (cross_x / normalized_cross) * camera_speed;
		eye_z -= (cross_z / normalized_cross) * camera_speed;

		eye_x -= camera_speed * center_x;
		if (eye_z >= 9.5)
			eye_z = 9.5;
		else
			eye_z -= camera_speed * center_z;
		break;

	case 2:

		eye_x -= camera_speed * center_x;
		if (eye_z >= 9.5)
			eye_z = 9.5;
		else
			eye_z -= camera_speed * center_z;

		break;
	case 3:
		eye_x -= camera_speed * center_x;
		if (eye_z >= 9.5)
			eye_z = 9.5;
		else
			eye_z -= camera_speed * center_z;
		eye_x += (cross_x / normalized_cross) * camera_speed;
		eye_z += (cross_z / normalized_cross) * camera_speed;
		
		break;

	case 4:
		eye_x -= (cross_x / normalized_cross) * camera_speed;
		eye_z -= (cross_z / normalized_cross) * camera_speed;

		break;
	case 5:

		break;
	case 6:
		eye_x += (cross_x / normalized_cross) * camera_speed;
		eye_z += (cross_z / normalized_cross) * camera_speed;
		break;
	case 7:
		eye_x += camera_speed * center_x;

		if (eye_z <= -9.5)
			eye_z = -9.5;
		else
			eye_z += camera_speed * center_z;
		eye_x -= (cross_x / normalized_cross) * camera_speed;
		eye_z -= (cross_z / normalized_cross) * camera_speed;
		break;
	case 8:
		eye_x += camera_speed * center_x;

		if (eye_z <= -9.5)
			eye_z = -9.5;
		else
			eye_z += camera_speed * center_z;
		break;
	case 9:
		eye_x += camera_speed * center_x;

		if (eye_z <= -9.5)
			eye_z = -9.5;
		else
			eye_z += camera_speed * center_z;
		eye_x += (cross_x / normalized_cross) * camera_speed;
		eye_z += (cross_z / normalized_cross) * camera_speed;

		break;
	default:

		break;
	}
	return;
}