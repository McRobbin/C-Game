#include<iostream>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>

#include "Frame.h"

extern GLuint texture[17];

void Frame::Draw(GLfloat _frame_point[][3]) {
	GLfloat frame_point[8][3];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			frame_point[i][j] = _frame_point[i][j];
		}

	}

	glColor3f(MyColors[0][0], MyColors[0][1], MyColors[0][2]);


	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, frame_point); // 실제 정점좌표를 저장한 MyVertex제시

	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, MyVertexList);


	for (GLint i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	}
}

void Frame::DrawObject(GLfloat _frame_point[][3]) {
	glFrontFace(GL_CCW); //표면을 무엇으로 할 것인가, CCW는 반시계방향으로 표면을 표현하겠다는 것임
	glEnable(GL_CULL_FACE); // 보여지는 부분중에서 안보이는 부분을 제거하는 함수. 즉, 우리에게 안보이는 뒤에 면에 대해서는 안 그려도 되므로 뒷 부분은 안그림.
	//glEnableClientState(GL_COLOR_ARRAY); //컬러도 리스트로 관리하려면 이것 사용하면 됨
	glEnableClientState(GL_VERTEX_ARRAY);//정점배열기능 활성화를 위함

	this->Draw(_frame_point);
	this->DrawFlower();

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisable(GL_CULL_FACE);
	glFrontFace(GL_CW);

}

void Frame::DrawFlower() {
	
	if (this->status != 0) {
		glBindTexture(GL_TEXTURE_2D, texture[9]);
		//flower
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-3.0, 3.0, -9.4999);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(3.0, 3.0, -9.4999);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(3.0, 8.0, -9.4999);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-3.0, 8.0, -9.4999);    // 텍스처와 쿼드의 왼쪽위
		glEnd();
	}
	else{
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		//flower
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-3.0, 3.0, -9.4999);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(3.0, 3.0, -9.4999);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(3.0, 8.0, -9.4999);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-3.0, 8.0, -9.4999);    // 텍스처와 쿼드의 왼쪽위
		glEnd();
	}
}
