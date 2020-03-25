#include "Key.h"

void Key::Draw(GLfloat _key_point[][3]) {
	GLfloat key_point[8][3];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			key_point[i][j] = _key_point[i][j];
		}

	}

	glColor3f(MyColors[0][0], MyColors[0][1], MyColors[0][2]);


	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, key_point); // 실제 정점좌표를 저장한 MyVertex제시

	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, MyVertexList);


	for (GLint i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	}
}

void Key::DrawObject(GLfloat _key_point[][3]) {
	if (this->status == 0) {

		GLfloat _key_point2[8][3] = { //키 끝
		{-9.03,-1.01,-0.35},{-9.03,-0.99,-0.35},{-9.01,-0.99,-0.35},{-9.01,-1.01,-0.35},
		{-9.03,-1.01,-0.40},{-9.03,-0.99,-0.40},{-9.01,-0.99,-0.40},{-9.01,-1.01,-0.40}};
		GLfloat _key_point3[8][3] = { //키 중간
		{-9.04,-1.01,-0.45},{-9.04,-0.99,-0.45},{-9.01,-0.99,-0.45},{-9.01,-1.01,-0.45},
		{-9.04,-1.01,-0.5},{-9.04,-0.99,-0.5},{-9.01,-0.99,-0.5},{-9.01,-1.01,-0.5}};

		Key* key = new Key(this->index);
		glFrontFace(GL_CCW); //표면을 무엇으로 할 것인가, CCW는 반시계방향으로 표면을 표현하겠다는 것임
		glEnable(GL_CULL_FACE); // 보여지는 부분중에서 안보이는 부분을 제거하는 함수. 즉, 우리에게 안보이는 뒤에 면에 대해서는 안 그려도 되므로 뒷 부분은 안그림.
		glEnableClientState(GL_COLOR_ARRAY); //컬러도 리스트로 관리하려면 이것 사용하면 됨
		glEnableClientState(GL_VERTEX_ARRAY);//정점배열기능 활성화를 위함

		glNormal3f(1, 0, 0.0);
		key->Draw(_key_point); //키
		key->Draw(_key_point2);
		key->Draw(_key_point3);


		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisable(GL_CULL_FACE);
		glFrontFace(GL_CW);


		//손잡이
		key->DrawHandle(0.05);

	}
}

void Key::DrawHandle(GLfloat size) {
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(-9, -1, 0);
	glutWireSphere(size, 20, 5);
	glTranslatef(9, 1, 0);
}
