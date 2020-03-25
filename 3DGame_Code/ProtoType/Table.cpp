#include "Table.h"

extern GLuint texture[17];

void Table::Draw(GLfloat _table_point[][3]) {
	GLfloat table_point[8][3];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			table_point[i][j] = _table_point[i][j];
		}

	}

	glColor3f(MyColors[0][0], MyColors[0][1], MyColors[0][2]);


	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, table_point); // 실제 정점좌표를 저장한 MyVertex제시

	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, MyVertexList);


	for (GLint i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	}
}

void Table::DrawObject(GLfloat _table_point[][3]) {
	//테이블은 상판을 기준으로.
	GLfloat table_point[8][3];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			table_point[i][j] = _table_point[i][j];
		}

	}

	GLfloat _table_point2[8][3] = { //책상 다리1
	{5,-10,-3},{5,-5,-3},{5.5,-5,-3},{5.5,-10,-3},
	{5,-10,-3.5},{5,-5,-3.5},{5.5,-5,-3.5},{5.5,-10,-3.5}
	};

	GLfloat _table_point3[8][3] = { //책상 다리2
	{5,-10,-9.5},{5,-5,-9.5},{5.5,-5,-9.5},{5.5,-10,-9.5},
	{5,-10,-10},{5,-5,-10},{5.5,-5,-10},{5.5,-10,-10}
	};

	GLfloat _table_point4[8][3] = { //책상 다리3
	{9.5,-10,-9.5},{9.5,-5,-9.5},{10,-5,-9.5},{10,-10,-9.5},
	{9.5,-10,-10},{9.5,-5,-10},{10,-5,-10},{10,-10,-10}
	};

	GLfloat _table_point5[8][3] = { //책상 다리4
	{9.5,-10,-3},{9.5,-5,-3},{10,-5,-3},{10,-10,-3},
	{9.5,-10,-3.5},{9.5,-5,-3.5},{10,-5,-3.5},{10,-10,-3.5}
	};



	glBindTexture(GL_TEXTURE_2D, texture[3]);
	//상판
	{
		//상판
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(5, -4.5, -3);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10, -4.5, -3);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10, -4.5, -10);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(5, -4.5, -10);    // 텍스처와 쿼드의 왼쪽위
		glEnd();
		//하판
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, -1, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(5, -5, -10);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10, -5, -10);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10, -5, -3);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(5, -5, -3);    // 텍스처와 쿼드의 왼쪽위
		glEnd();
	}
	{
		//좌판
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(5, -5, -10);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(5, -5, -3);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(5, -4.5, -3);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(5, -4.5, -10);    // 텍스처와 쿼드의 왼쪽위
		glEnd();

		//전면판
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(5, -5, -3);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10, -5, -3);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10, -4.5, -3);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(5, -4.5, -3);    // 텍스처와 쿼드의 왼쪽위
		glEnd();
	}

	//왼쪽 앞 다리
	{	//정면
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(5, -10, -3);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(5.5, -10, -3);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(5.5, -5, -3);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(5, -5, -3);    // 텍스처와 쿼드의 왼쪽위
		glEnd();

		//뒷면
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, -1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(5, -10, -3.5);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(5.5, -10, -3.5);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(5.5, -5, -3.5);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(5, -5, -3.5);    // 텍스처와 쿼드의 왼쪽위
		glEnd();

		//왼쪽면
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(5, -10, -3.5);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(5, -10, -3);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(5, -5, -3);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(5, -5, -3.5);    // 텍스처와 쿼드의 왼쪽위
		glEnd();

		//오른쪽 면
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(1, 0, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(5.5, -10, -3);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(5.5, -10, -3.5);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(5.5, -5, -3.5);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(5.5, -5, -3);    // 텍스처와 쿼드의 왼쪽위
		glEnd();

	}
	//왼쪽 뒷 다리
	{	//정면
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(5, -10, -9.5);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(5.5, -10, -9.5);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(5.5, -5, -9.5);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(5, -5, -9.5);    // 텍스처와 쿼드의 왼쪽위
		glEnd();

		//뒷면
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, -1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(5, -10, -10);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(5.5, -10, -10);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(5.5, -5, -10);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(5, -5, -10);    // 텍스처와 쿼드의 왼쪽위
		glEnd();

		//왼쪽면
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(5, -10, -10);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(5, -10, -9.5);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(5, -5, -9.5);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(5, -5, -10);    // 텍스처와 쿼드의 왼쪽위
		glEnd();

		//오른쪽 면
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(1, 0, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(5.5, -10, -9.5);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(5.5, -10, -10);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(5.5, -5, -10);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(5.5, -5, -9.5);    // 텍스처와 쿼드의 왼쪽위
		glEnd();

	}
	//오른쪽 뒷다리
	{	//정면
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(9.5, -10, -9.5);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10, -10, -9.5);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10, -5, -9.5);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(9.5, -5, -9.5);    // 텍스처와 쿼드의 왼쪽위
		glEnd();


		//왼쪽면
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(9.5, -10, -10);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(9.5, -10, -9.5);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(9.5, -5, -9.5);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(9.5, -5, -10);    // 텍스처와 쿼드의 왼쪽위
		glEnd();


	}
	//오른쪽 앞 다리
	{	//정면
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(9.5, -10, -3);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10, -10, -3);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10, -5, -3);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(9.5, -5, -3);    // 텍스처와 쿼드의 왼쪽위
		glEnd();

		//뒷면
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, -1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(9.5, -10, -3.5);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10, -10, -3.5);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10, -5, -3.5);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(9.5, -5, -3.5);    // 텍스처와 쿼드의 왼쪽위
		glEnd();

		//왼쪽면
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(9.5, -10, -3.5);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(9.5, -10, -3);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(9.5, -5, -3);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(9.5, -5, -3.5);    // 텍스처와 쿼드의 왼쪽위
		glEnd();
	}
}