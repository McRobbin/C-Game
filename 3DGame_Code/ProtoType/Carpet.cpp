#include "Carpet.h"

extern GLuint texture[17];

void Carpet::Draw(GLfloat _carpet_point[][3]) {
	GLfloat carpet_point[8][3];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			carpet_point[i][j] = _carpet_point[i][j];
		}

	}

	glColor3f(colors[0], colors[1], colors[2]);


	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, carpet_point); // 실제 정점좌표를 저장한 MyVertex제시

	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, MyVertexList);


	for (GLint i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	}
}

void Carpet::DrawObject(GLfloat carpet_point[][3]) {
	this->Draw(carpet_point);
	if (status == 0) {
		glBindTexture(GL_TEXTURE_2D, texture[11]);
		//carpet
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-4, -9.799, 4);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(4, -9.799, 4);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(4, -9.799, -4);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-4, -9.799, -4);    // 텍스처와 쿼드의 왼쪽위
		glEnd();


		glFrontFace(GL_CCW); //표면을 무엇으로 할 것인가, CCW는 반시계방향으로 표면을 표현하겠다는 것임
		glEnable(GL_CULL_FACE); // 보여지는 부분중에서 안보이는 부분을 제거하는 함수. 즉, 우리에게 안보이는 뒤에 면에 대해서는 안 그려도 되므로 뒷 부분은 안그림.

		//glEnableClientState(GL_COLOR_ARRAY); //컬러도 리스트로 관리하려면 이것 사용하면 됨
		glEnableClientState(GL_VERTEX_ARRAY);//정점배열기능 활성화를 위함

		//판 그리기

		glDisableClientState(GL_VERTEX_ARRAY);
		//glDisableClientState(GL_COLOR_ARRAY);
		glDisable(GL_CULL_FACE);
		glFrontFace(GL_CW);

	}
	else if(this->status == 1){
		glBindTexture(GL_TEXTURE_2D, texture[11]);
		//carpet
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glNormal3f(0, 1, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-4, -9.7999, 4);    // 텍스처와 쿼드의 왼쪽아래

		glTexCoord2f(0.5f, 0.0f);
		glVertex3f(0, -9.7999, 4);    // 텍스처와 쿼드의 왼쪽아래

		glTexCoord2f(1.0f, 0.5f);
		glVertex3f(4, -9.7999, 0);    // 텍스처와 쿼드의 오른쪽아래

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(4, -9.7999, -4);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-4, -9.7999, -4);    // 텍스처와 쿼드의 왼쪽위
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[12]);
		//book
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glNormal3f(0, 1, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(2.5, -9.7, 4);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(4, -9.7, 4);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(4, -9.7, 2);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(2.5, -9.7, 2);
		glEnd();

		//왼쪽면
		glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0.0);
		glVertex3f(2.5, -10, 2);
		glVertex3f(2.5, -10, 4);
		glVertex3f(2.5, -9.7, 4);
		glVertex3f(2.5, -9.7, 2);
		glEnd();

		//오른쪽면
		glBegin(GL_QUADS);
		glNormal3f(1, 0, 0.0);
		glVertex3f(4, -10, 2);
		glVertex3f(4, -10, 4);
		glVertex3f(4, -9.7, 4);
		glVertex3f(4, -9.7, 2);
		glEnd();

		//정면
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1.0);
		glVertex3f(2.5, -10, 2);
		glVertex3f(4, -10, 2);
		glVertex3f(4, -9.7, 2);
		glVertex3f(2.5, -9.7, 2);
		glEnd();

		//후면
		glBegin(GL_QUADS);
		glNormal3f(0, 0, -1.0);
		glVertex3f(4, -10, 4);
		glVertex3f(2.5, -10, 4);
		glVertex3f(2.5, -9.7, 4);
		glVertex3f(4, -9.7, 4);
		glEnd();

	}

	else {

		glBindTexture(GL_TEXTURE_2D, texture[11]);
		//carpet
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glNormal3f(0, 1, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-4, -9.7999, 4);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(0.5f, 0.0f);
		glVertex3f(0, -9.7999, 4);    // 텍스처와 쿼드의 왼쪽아래
		glTexCoord2f(1.0f, 0.5f);
		glVertex3f(4, -9.7999, 0);    // 텍스처와 쿼드의 오른쪽아래
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(4, -9.7999, -4);    // 텍스처와 쿼드의 오른쪽위
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-4, -9.7999, -4);    // 텍스처와 쿼드의 왼쪽위
		glEnd();
			
		glBindTexture(GL_TEXTURE_2D, texture[13]);
		//open_book
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5, -9.7, 4);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(4, -9.7, 4);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(4, -9.7, 2);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5, -9.7, 2);
		glEnd();
			
		glBindTexture(GL_TEXTURE_2D, texture[14]);
		//memo
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.7, -9.699, 3.5);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(3.0, -9.699, 3.5);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(3.0, -9.699, 2.5);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.7, -9.699, 2.5);
		glEnd();

		//왼쪽면
		glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0.0);
		glVertex3f(0.5, -10, 2);
		glVertex3f(0.5, -10, 4);
		glVertex3f(0.5, -9.7, 4);
		glVertex3f(0.5, -9.7, 2);
		glEnd();

		//오른쪽면
		glBegin(GL_QUADS);
		glNormal3f(1, 0, 0.0);
		glVertex3f(4, -10, 2);
		glVertex3f(4, -10, 4);
		glVertex3f(4, -9.7, 4);
		glVertex3f(4, -9.7, 2);
		glEnd();
			
		//후면
		glBegin(GL_QUADS);
		glNormal3f(0, 0, -1.0);
		glVertex3f(0.5, -10, 2);
		glVertex3f(4, -10, 2);
		glVertex3f(4, -9.7, 2);
		glVertex3f(0.5, -9.7, 2);
		glEnd();
	
		//정면
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1.0);
		glVertex3f(4, -10, 4);
		glVertex3f(0.5, -10, 4);
		glVertex3f(0.5, -9.7, 4);
		glVertex3f(4, -9.7, 4);
		glEnd();
	}
}
