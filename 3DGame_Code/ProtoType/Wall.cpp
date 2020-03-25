#include<iostream>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>

extern GLuint texture[17];

#include "Wall.h"

void Wall::Draw(GLfloat _wall_point[][3]) {
	GLfloat wall_point[8][3];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			wall_point[i][j] = _wall_point[i][j];
		}

	}

	glColor3f(colors[0], colors[1], colors[2]);


	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, wall_point); // 실제 정점좌표를 저장한 MyVertex제시

	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, MyVertexList);


	for (GLint i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	}

}

void Wall::DrawObject(GLfloat _wall_point[][3]) {

	GLfloat wall_point[8][3];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			wall_point[i][j] = _wall_point[i][j];
		}

	}

	GLfloat wall_point2[8][3] = { {-10,-10,10},{-10,10,10},{10,10,10},{10,-10,10}, //앞
							  {-10,-10,11},{-10,10,11},{10,10,11},{10,-10,11} };

	GLfloat wall_point3[8][3] = { {-11,-10,10},{-11,10,10},{-10,10,10},{-10,-10,10}, //좌
								  {-11,-10,-10},{-10,10,-10},{10,10,-10},{10,-10,-10} };

	GLfloat wall_point4[8][3] = { {10,-10,10},{10,10,10},{11,10,10},{11,-10,10}, //우
								  {10,-10,-10},{10,10,-10},{11,10,-10},{11,-10,-10} };

	GLfloat wall_point5[8][3] = { {-10,10,10},{-10,11,10},{10,11,10},{10,10,10}, //위
								  {-10,10,-10},{-10,11,-10},{10,11,-10},{10,10,-10} };

	GLfloat wall_point6[8][3] = { {-10,-11,10},{-10,-10,10},{10,-10,10},{10,-11,10}, //아래
								  {-10,-11,-10},{-10,-10,-10},{10,-10,-10},{10,-11,-10} };



	glPushMatrix();


	glFrontFace(GL_CCW); //표면을 무엇으로 할 것인가, CCW는 반시계방향으로 표면을 표현하겠다는 것임
//glEnable(GL_CULL_FACE); // 보여지는 부분중에서 안보이는 부분을 제거하는 함수. 즉, 우리에게 안보이는 뒤에 면에 대해서는 안 그려도 되므로 뒷 부분은 안그림.
//glEnableClientState(GL_COLOR_ARRAY); //컬러도 리스트로 관리하려면 이것 사용하면 됨
	glEnableClientState(GL_VERTEX_ARRAY);//정점배열기능 활성화를 위함

	Wall* wall = new Wall();

	wall->Draw(wall_point);
	wall->Draw(wall_point2);
	wall->Draw(wall_point3);
	wall->Draw(wall_point4);
	wall->Draw(wall_point5);
	wall->Draw(wall_point6);

	glDisableClientState(GL_VERTEX_ARRAY);
	glFrontFace(GL_CW);



	/*******텍스쳐 매핑********/

	{
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		//정면

		glColor3f(0.94, 0.94, 0.94);
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10.0, -10.0, -10.0);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10.0, -10.0, -10.0);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10.0, 10.0, -10.0);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10.0, 10.0, -10.0);    // 텍스처와 쿼드의 왼쪽위
		glEnd();

		//뒷면
		glRotatef(180, 0, 1, 0);
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10.0, -10.0, -10.0);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10.0, -10.0, -10.0);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10.0, 10.0, -10.0);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10.0, 10.0, -10.0);    // 텍스처와 쿼드의 왼쪽위
		glEnd();

		//왼쪽
		glRotatef(90, 0, 1, 0);
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10.0, -10.0, -10.0);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10.0, -10.0, -10.0);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10.0, 10.0, -10.0);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10.0, 10.0, -10.0);    // 텍스처와 쿼드의 왼쪽위
		glEnd();

		//오른쪽
		glRotatef(180, 0, 1, 0);
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10.0, -10.0, -10.0);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10.0, -10.0, -10.0);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10.0, 10.0, -10.0);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10.0, 10.0, -10.0);    // 텍스처와 쿼드의 왼쪽위
		glEnd();
	}
	{
		//위
		glRotatef(90, 1, 0, 0);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10.0, -10.0, -10.0);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10.0, -10.0, -10.0);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10.0, 10.0, -10.0);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10.0, 10.0, -10.0);    // 텍스처와 쿼드의 왼쪽위
		glEnd();

		//마루
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glColor3f(1.0, 0.72, 0.43);

		glRotatef(180, 1, 0, 0);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10.0, -10.0, -10.0);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10.0, -10.0, -10.0);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10.0, 10.0, -10.0);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10.0, 10.0, -10.0);    // 텍스처와 쿼드의 왼쪽위
		glEnd();

		glPopMatrix();
		//glRotatef(-90, 0, 1, 0);

	}

}