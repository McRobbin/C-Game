#include<iostream>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>

#include "Door.h"

extern GLuint texture[17];

void Door::Draw(GLfloat _door_point[][3]) {
	GLfloat door_point[8][3];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			door_point[i][j] = _door_point[i][j];
		}

	}
	glColor3f(MyColors[0][0], MyColors[0][1], MyColors[0][2]);


	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, door_point); // 실제 정점좌표를 저장한 MyVertex제시

	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, MyVertexList);


	for (GLint i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	}
}

void Door::DrawHandle(GLfloat size) {
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(-2.5, -4, 10);
	glutSolidSphere(size, 20, 5);
	glTranslatef(2.5, 4, -10);
}

void Door::DrawObject(GLfloat _door_point[][3]) {
	//door_open = true;
	
	if (status == 1) {
		glDisable(GL_LIGHTING);
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		//정면
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); //1

		glVertex3f(3.5, -10, 10);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(0.0f, 0.0f); //2
		glVertex3f(3.5, -10, 4);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(0.0f, 1.0f); //3
		glVertex3f(3.5, 2, 4);    // 텍스처와 쿼드의 오른쪽위

		glTexCoord2f(1.0f, 1.0f); //4
		glVertex3f(3.5, 2, 10);    // 텍스처와 쿼드의 왼쪽위
		glEnd();

		//후면
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);  //1

		glVertex3f(3, -10, 10);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(0.0f, 0.0f); //2
		glVertex3f(3, -10, 4);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(0.0f, 1.0f); //3
		glVertex3f(3, 2, 4);    // 텍스처와 쿼드의 오른쪽위

		glTexCoord2f(1.0f, 1.0f); //4
		glVertex3f(3, 2, 10);    // 텍스처와 쿼드의 왼쪽위
		glEnd();

		//옆면
		glColor3f(159.0 / 255.0, 84.0 / 255.0, 45.0 / 255.0);
		glBegin(GL_QUADS);
		glVertex3f(3, -10, 4);
		glVertex3f(3.5, -10, 4);
		glVertex3f(3.5, 2, 4);
		glVertex3f(3, 2, 4);
		glEnd();
		//윗면
		glBegin(GL_QUADS);
		glVertex3f(3.5, 2, 10);
		glVertex3f(3.5, 2, 4);
		glVertex3f(3, 2, 4);
		glVertex3f(3, 2, 10);
		glEnd();

		//문위치에 바깥 세상
		glBindTexture(GL_TEXTURE_2D, texture[16]);
		//정면
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-3, -10, 10);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(3, -10, 10);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(3, 2, 10);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-3, 2, 10);    // 텍스처와 쿼드의 왼쪽위
		glEnd();

	}
	else {
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		//정면
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, -1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-3, -10, 9.49);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(3, -10, 9.49);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(3, 2, 9.49);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-3, 2, 9.49);    // 텍스처와 쿼드의 왼쪽위
		glNormal3f(0, 0, 1.0);
		glEnd();


		glFrontFace(GL_CCW); //표면을 무엇으로 할 것인가, CCW는 반시계방향으로 표면을 표현하겠다는 것임
		//glEnable(GL_CULL_FACE); // 보여지는 부분중에서 안보이는 부분을 제거하는 함수. 즉, 우리에게 안보이는 뒤에 면에 대해서는 안 그려도 되므로 뒷 부분은 안그림.
		glEnableClientState(GL_COLOR_ARRAY); //컬러도 리스트로 관리하려면 이것 사용하면 됨
		glEnableClientState(GL_VERTEX_ARRAY);//정점배열기능 활성화를 위함

		this->Draw(_door_point);
		this->DoorBelow();
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		//glDisable(GL_CULL_FACE);
		glFrontFace(GL_CW);


		//손잡이
		//door_1->Drawing(0.3);
	}

}

void Door::DoorBelow() {
	if (status == 0) {
		glBindTexture(GL_TEXTURE_2D, texture[10]);
		//정면
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, -1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1, -9, 9.489);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1, -9, 9.489);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1, -7, 9.489);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1, -7, 9.489);    // 텍스처와 쿼드의 왼쪽위
		glEnd();
	}
}
