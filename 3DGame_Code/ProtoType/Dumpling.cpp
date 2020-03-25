#include "Dumpling.h"

extern GLuint texture[17];

void Dumpling::Draw(GLfloat _dump_point[][3]) {
	GLfloat dump_point[8][3];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			dump_point[i][j] = _dump_point[i][j];
		}

	}

	glColor3f(MyColors[0][0], MyColors[0][1], MyColors[0][2]);


	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, dump_point); // 실제 정점좌표를 저장한 MyVertex제시

	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, MyVertexList);


	for (GLint i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	}
}

void Dumpling::DrawObject(GLfloat _dump_point[][3]) {
	if (this->status == 1) {

		glBindTexture(GL_TEXTURE_2D, texture[15]);
		//dumbling
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-2, -9.7, 9);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(2, -9.7, 9);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(2, -9.7, 7);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-2, -9.7, 7);
		glEnd();


		//전면
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1.0);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-2, -10, 9);
		glVertex3f(2, -10, 9);
		glVertex3f(2, -9.7, 9);
		glVertex3f(-2, -9.7, 9);
		glEnd();

		//후면
		glBegin(GL_QUADS);
		glNormal3f(0, 0, -1.0);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-2, -10, 7);
		glVertex3f(2, -10, 7);
		glVertex3f(2, -9.7, 7);
		glVertex3f(-2, -9.7, 7);
		glEnd();

		//왼쪽면
		glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0.0);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-2, -10, 7);
		glVertex3f(-2, -10, 9);
		glVertex3f(-2, -9.7, 9);
		glVertex3f(-2, -9.7, 7);
		glEnd();

		//오른쪽면
		glBegin(GL_QUADS);
		glNormal3f(1, 0, 0.0);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(2, -10, 7);
		glVertex3f(2, -10, 9);
		glVertex3f(2, -9.7, 9);
		glVertex3f(2, -9.7, 7);
		glEnd();

	}
}
