#include "Ruler.h"

extern GLuint texture[17];

void Ruler::Draw(GLfloat _ruler_point[][3]) {
	GLfloat ruler_point[8][3];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			ruler_point[i][j] = _ruler_point[i][j];
		}

	}

	glColor3f(MyColors[0][0], MyColors[0][1], MyColors[0][2]);


	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, ruler_point); // 실제 정점좌표를 저장한 MyVertex제시

	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, MyVertexList);


	for (GLint i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	}
}

void Ruler::DrawObject(GLfloat _ruler_point[][3]) {
	Ruler* ruler = new Ruler(this->index);

	if (this->status == 0) {

		glBindTexture(GL_TEXTURE_2D, texture[8]);
		//정면
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, -1, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(7.0, -5.1, -8);    //1 
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(7.0, -5.1, -4);    //2
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(6.5, -5.1, -4);    //3
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(6.5, -5.1, -8);    // 4
		glEnd();
	}
}
