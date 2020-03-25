#include "Card.h"

extern GLuint texture[17];

void Card::Draw(GLfloat _card_point[][3]) {
	GLfloat card_point[8][3];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			card_point[i][j] = _card_point[i][j];
		}

	}
	glColor3f(MyColors[0][0], MyColors[0][1], MyColors[0][2]);


	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, card_point); // 실제 정점좌표를 저장한 MyVertex제시

	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, MyVertexList);


	for (GLint i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	}
}

void Card::DrawObject(GLfloat _card_point[][3]) {
	if (this->status == 0) {
		//Card* card = new Card(this->index);

		glBindTexture(GL_TEXTURE_2D, texture[7]);
		//정면
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-8.1, 2.1, -2);    // 1
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-8.1, 2.1, -3);    // 2
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-8.5, 2.1, -3);    //3
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-8.5, 2.1, -2);    //4
		glEnd();
	}

}
