#include "Egg.h"

void Egg::Draw(GLfloat _egg_point[][3]) {
	//계란판을 기준으로.

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			_egg_point[i][j] = _egg_point[i][j];
		}

	}

	glColor3f(colors[0], colors[1], colors[2]);

	glVertexPointer(3, GL_FLOAT, 0, _egg_point); // 실제 정점좌표를 저장한 MyVertex제시

	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, MyVertexList);


	for (GLint i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	}
}

void Egg::DrawObject(GLfloat _egg_point[][3]) {
	glFrontFace(GL_CCW); //표면을 무엇으로 할 것인가, CCW는 반시계방향으로 표면을 표현하겠다는 것임
	glEnable(GL_CULL_FACE); // 보여지는 부분중에서 안보이는 부분을 제거하는 함수. 즉, 우리에게 안보이는 뒤에 면에 대해서는 안 그려도 되므로 뒷 부분은 안그림.

	//glEnableClientState(GL_COLOR_ARRAY); //컬러도 리스트로 관리하려면 이것 사용하면 됨
	glEnableClientState(GL_VERTEX_ARRAY);//정점배열기능 활성화를 위함

	//판 그리기
	glNormal3f(0, 1, 0.0);
	Egg* egg = new Egg();
	egg->Draw(_egg_point);

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	//선 나누기
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(3.0);
	//세로
	glVertex3f(6, -4, -5);
	glVertex3f(6, -4, -9);
	glVertex3f(7, -4, -5);
	glVertex3f(7, -4, -9);
	glVertex3f(8, -4, -5);
	glVertex3f(8, -4, -9);
	glVertex3f(9, -4, -9);
	glVertex3f(9, -4, -5);
	glEnd();
	//가로
	glBegin(GL_LINES);
	glVertex3f(6, -4, -5);
	glVertex3f(9, -4, -5);
	glVertex3f(6, -4, -6);
	glVertex3f(9, -4, -6);
	glVertex3f(6, -4, -7);
	glVertex3f(9, -4, -7);
	glVertex3f(6, -4, -8);
	glVertex3f(9, -4, -8);
	glVertex3f(6, -4, -9);
	glVertex3f(9, -4, -9);
	glEnd();
	//높이
	glBegin(GL_LINES);
	glVertex3f(6, -4.5, -5);
	glVertex3f(6, -4.0, -5);
	glVertex3f(9, -4.5, -5);
	glVertex3f(9, -4.0, -5);
	glVertex3f(6, -4.5, -9);
	glVertex3f(6, -4.0, -9);
	glVertex3f(9, -4.5, -9);
	glVertex3f(9, -4.0, -9);
	glEnd();

	//밑면

	glBegin(GL_LINES);
	glVertex3f(6, -4.5, -5);
	glVertex3f(9, -4.5, -5);
	glVertex3f(6, -4.5, -5);
	glVertex3f(6, -4.5, -9);
	glVertex3f(9, -4.5, -5);
	glVertex3f(9, -4.5, -9);
	glVertex3f(6, -4.5, -9);
	glVertex3f(9, -4.5, -9);
	glEnd();

	//계란
	glColor3f(1.0, 0.7216, 0.4392);
	glNormal3f(0, 1, 0.0);
	glPushMatrix();
	glTranslatef(8.5, -4.2, -7.5);
	glutSolidSphere(0.4, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.5, -4.2, -6.5);
	glutSolidSphere(0.4, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7.5, -4.2, -8.5);
	glutSolidSphere(0.4, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.5, -4.2, -7.5);
	glutSolidSphere(0.4, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.5, -4.2, -6.5);
	glutSolidSphere(0.4, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.5, -4.2, -5.5);
	glutSolidSphere(0.4, 20, 10);
	glPopMatrix();

}