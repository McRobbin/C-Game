#pragma comment(lib,"glaux.lib")

#include<iostream>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>
#include<GL\GLAUX.H>

#include <math.h>
#include <map>
#include <vector>

#include "Frame.h"
#include "Door.h"
#include "Wall.h"
#include "Camera.h"
#include "Card.h"
#include "CardReader.h"
#include "Cabinet.h"
#include "Key.h"
#include "Ruler.h"
#include "Table.h"
#include "Egg.h"
#include "Carpet.h"
#include "Dumpling.h"

using namespace std;

void PickingObject(GLint x, GLint y);
void SelectProcess(GLuint name);

//이미지 매핑 텍스쳐 저장.
GLuint	texture[27];

GLboolean lock_open = false;

//선택 버퍼.
GLuint selectBuff[64];
GLint hits;

//게임의 모드 admin mode
GLint mode;

//반응성 없는 일반 오브젝트 벡터.
vector<Object*> norm_obj;

//반응성 있는 스페셜 오브젝트 맵.
map<GLuint, SpecialObject*> special_obj;

//카메라 객체.
Camera* camera = new Camera();

//시간.
GLint timer = 0;

//키패드 온

//조명
GLfloat LightPostion[] = { camera->eye_z, camera->eye_y, camera->eye_x,1.0 };
GLfloat LightDirection[] = { camera->eye_x + camera->center_x, camera->eye_y + camera->center_y, camera->eye_z + camera->center_z };

//그리는 순서.
GLubyte Object::MyVertexList[24] = { 0,3,2,1, 2,3,7,6, 0,4,7,3, 1,2,6,5, 4,5,6,7, 0,1,5,4 };

//디폴트 Object Color
GLfloat Object::MyColors[8][3] = {

	{0.2,0.2,0.2},{1.0,0.0,0.0},{1.0,1.0,0.0},{0.0,1.0,0.0},
	{0.0,0.0,1.0},{1.0,0.0,1.0},{1.0,1.0,1.0},{0.0,1.0,1.0}
};

//물체 정점 및 색상 초기화.
GLfloat wall_color[3] = {0.5, 0.5, 0.5};
GLfloat wall_point[8][3] = { {-10,-10,-10},{-10,10,-10},{10,10,-10},{10,-10,-10}, //뒤
							  {-10,-10,-11},{-10,10,-11},{10,10,-11},{10,-10,-11} };


GLfloat frame_color[3] = {1.0,1.0,1.0};
GLfloat frame_point[8][3] = { {-3.0,3.0,-9.5},{-3.0,8.0,-9.5},{3.0,8.0,-9.5},{3.0,3.0,-9.5},
							  {-3.0,3.0,-9.9},{-3.0,8.0,-9.9},{3.0,8.0,-9.9},{3.0,3.0,-9.9} };


GLfloat cabinet_color[3] = {0.5,0.5,0.7};
GLfloat cabinet_point[8][3] = {{-10,-10,3},{-10,2,3},{-8,2,3},{-8,-10,3},
	{-10,-10,-3},{-10,2,-3},{-8,2,-3},{-8,-10,-3}};

GLfloat door_color[3] = {0.5,0.5,0.7};
GLfloat door_point[8][3] = {{-3,-10,10},{-3,2,10},{3,2,10},{3,-10,10},
	{-3,-10,9.5},{-3,2,9.5},{3,2,9.5},{3,-10,9.5}};

GLfloat card_color[3] = {0.0,0.0,1.0};
GLfloat card_point[8][3] = {{-8.5,2,-2},{-8.5,2.1,-2},{-8.1,2.1,-2},{-8.1,2,-2},
	{-8.5,2,-3},{-8.5,2.1,-3},{-8.1,2.1,-3},{-8.1,2,-3}};

GLfloat key_color[3] = {0.0,0.0,1.0};
GLfloat key_point[8][3] = { //키 몸통
	{-9.01,-1.01,0.0},{-9.01,-0.99,0.0},{-8.99,-0.99,0.0},{-8.99,-1.01,0.0},
	{-9.01,-1.01,-0.5},{-9.01,-0.99,-0.5},{-8.99,-0.99,-0.5},{-8.99,-1.01,-0.5}};

GLfloat table_color[3] = {0.0,0.0,1.0};
GLfloat table_point[8][3] = { //책상 판자
	{5,-5,-3},{5,-4.5,-3},{10,-4.5,-3},{10,-5,-3},
	{5,-5,-10},{5,-4.5,-10},{10,-4.5,-10},{10,-5,-10}};

GLfloat ruler_color[3] = {0.0,0.0,1.0};
GLfloat ruler_point[8][3] = { //책상 판자
	{6.5,-5.1,-4},{6.5,-5.0,-4},{7.0,-5.0,-4},{7.0,-5.1,-4},
	{6.5,-5.1,-6},{6.5,-5.0,-6},{7.0,-5.0,-6},{7.0,-5.1,-6}};

GLfloat card_reader_color[3] = {0.0,0.0,1.0};
GLfloat card_reader_point[8][3] = { //카드 리더기 윗 부분
	{-5.0,0.03,-9},{-4.5,0.55,-9},{-3.5,0.55,-9},{-3,0.03,-9},
	{-5.0,0.03,-10},{-4.5,0.55,-10},{-3.5,0.55,-10},{-3,0.03,-10}};

GLfloat egg_color[3] = {0.5,0.5,0.5};
GLfloat egg_point[8][3] = { //카드 리더기 윗 부분
	{6,-4.5,-5},{6,-4.0,-5},{9,-4.0,-5},{9,-4.5,-5},
	{6,-4.5,-9},{6,-4.0,-9},{9,-4.0,-9},{9,-4.5,-9}};

GLfloat carpet_table_color[3] = { 1.0,0.0,0.0 };
GLfloat carpet_table_point[8][3] = {
	{-4,-9.9,4},{-4,-9.8,4},{4,-9.8,4},{4,-9.9,4},
	{-4,-9.9,-4},{-4,-9.8,-4},{4,-9.8,-4},{4,-9.9,-4}};

GLfloat dump_color[3] = { 1.0, 1.0, 1.0 };
GLfloat dump_point[8][3] = { {-2, -10, 9}, {-2, -9.7, 9}, {2, -9.7, 9}, {2, -10, 9},
{-2, -10, 7}, {-2, -9.7, 7}, {2, -9.7, 7}, {2, -10, 7} };


//텍스쳐 매핑 용 함수.
AUX_RGBImageRec *LoadBMP(const char *Filename)                    // 비트맵 이미지를 읽어옴
{
	FILE *File = NULL;
	if (!Filename)                                // 파일이름이 전달되었는지 확인
	{
		return NULL;                            // 그렇지 않다면 NULL을 반환
	}
	File = fopen(Filename, "r");
	if (File)                                // 파일이 존재하는가?
	{
		fclose(File);                            // 핸들을 닫음
		return auxDIBImageLoad(Filename);                // 비트맵을 읽어들이고 포인터를 반환
	}
	return NULL;                                // 로딩이 실패하면 NULL을 반환
}

//텍스쳐 로드 함수.
int LoadGLTextures()                                // 비트맵을 로드하고 텍스처로 변환
{
	int Status = FALSE;
	AUX_RGBImageRec *TextureImage[27];
	memset(TextureImage, 0, sizeof(void *) * 27);
	// 비트맵을 로딩하고 에러를 검사한다. 비트맵이 발견되지 않았다면 종료한다.

	if (TextureImage[0] = LoadBMP("../res/wall.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정

		glGenTextures(1, &texture[0]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[0])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[0]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[0]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[0]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[1] = LoadBMP("../res/flower.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[1]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[1]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[1]->sizeX, TextureImage[1]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[1]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[1])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[1]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[1]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[1]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[2] = LoadBMP("../res/floor.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[2]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[2]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[2]->sizeX, TextureImage[2]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[2]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[2])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[2]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[2]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[2]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[3] = LoadBMP("../res/table.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[3]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[3]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[3]->sizeX, TextureImage[3]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[3]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[3])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[3]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[3]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[3]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[4] = LoadBMP("../res/door.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[4]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[4]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[4]->sizeX, TextureImage[4]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[4]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[4])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[4]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[4]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[4]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[5] = LoadBMP("../res/lock.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[5]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[5]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[5]->sizeX, TextureImage[5]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[5]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[5])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[5]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[5]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[5]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[6] = LoadBMP("../res/reader.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[6]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[6]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[6]->sizeX, TextureImage[6]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[6]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[6])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[6]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[6]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[6]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[7] = LoadBMP("../res/card.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[7]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[7]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[7]->sizeX, TextureImage[7]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[7]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[7])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[7]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[7]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[7]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[8] = LoadBMP("../res/ruler.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[8]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[8]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[8]->sizeX, TextureImage[8]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[8]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[8])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[8]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[8]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[8]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[9] = LoadBMP("../res/frame.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[9]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[9]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[9]->sizeX, TextureImage[9]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[9]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[9])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[9]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[9]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[9]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[10] = LoadBMP("../res/door_below.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[10]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[10]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[10]->sizeX, TextureImage[10]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[10]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[10])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[10]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[10]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[10]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[11] = LoadBMP("../res/carpet.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[11]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[11]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[11]->sizeX, TextureImage[11]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[11]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[11])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[11]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[11]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[11]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[12] = LoadBMP("../res/book.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[12]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[12]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[12]->sizeX, TextureImage[12]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[12]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[12])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[12]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[12]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[12]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[13] = LoadBMP("../res/open_book.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[13]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[13]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[13]->sizeX, TextureImage[13]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[13]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[13])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[13]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[13]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[13]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[14] = LoadBMP("../res/memo.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[14]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[14]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[14]->sizeX, TextureImage[14]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[14]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[14])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[14]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[14]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[14]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[15] = LoadBMP("../res/dumbling.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[15]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[15]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[15]->sizeX, TextureImage[15]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[15]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[15])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[15]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[15]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[15]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[16] = LoadBMP("../res/door_below_2.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[16]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[16]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[16]->sizeX, TextureImage[16]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[16]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[16])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[16]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[16]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[16]);                        // 이미지 구조체를 해제
	}
	if (TextureImage[17] = LoadBMP("../res/KeyPad0.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[17]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[17]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[17]->sizeX, TextureImage[17]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[17]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[17])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[17]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[17]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[17]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[18] = LoadBMP("../res/KeyPad1.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[18]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[18]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[18]->sizeX, TextureImage[18]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[18]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[18])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[18]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[18]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[18]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[19] = LoadBMP("../res/KeyPad2.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[19]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[19]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[19]->sizeX, TextureImage[19]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[19]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[19])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[19]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[19]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[19]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[20] = LoadBMP("../res/KeyPad3.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[20]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[20]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[20]->sizeX, TextureImage[20]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[20]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[20])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[20]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[20]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[20]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[21] = LoadBMP("../res/KeyPad4.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[21]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[21]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[21]->sizeX, TextureImage[21]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[21]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[21])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[21]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[21]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[21]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[22] = LoadBMP("../res/KeyPad5.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[22]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[22]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[22]->sizeX, TextureImage[22]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[22]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[22])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[22]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[22]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[22]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[23] = LoadBMP("../res/KeyPad6.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[23]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[23]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[23]->sizeX, TextureImage[23]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[23]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[23])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[23]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[23]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[23]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[24] = LoadBMP("../res/KeyPad7.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[24]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[24]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[24]->sizeX, TextureImage[24]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[24]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[24])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[24]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[24]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[24]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[25] = LoadBMP("../res/KeyPad8.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[25]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[25]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[25]->sizeX, TextureImage[25]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[25]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[25])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[25]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[25]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[25]);                        // 이미지 구조체를 해제
	}

	if (TextureImage[26] = LoadBMP("../res/KeyPad9.bmp"))
	{
		Status = TRUE;                            // Status를 TRUE로 설정
		printf("yes");
		glGenTextures(1, &texture[26]);                    // 텍스처를 만듬

			// 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
		glBindTexture(GL_TEXTURE_2D, texture[26]);

		// 텍스처를 만든다
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[26]->sizeX, TextureImage[26]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[26]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[26])                            // 텍스처가 존재하는지 확인
	{
		if (TextureImage[26]->data)                    // 텍스처 이미지가 존재하는지 확인
		{
			free(TextureImage[26]->data);                // 텍스처 이미지 메모리를 해제
		}

		free(TextureImage[26]);                        // 이미지 구조체를 해제
	}

	/********키패드 그리기 끝********/

	return Status;                                       // Status를 반환
}

void ObjectInit() {
	Object* normal;
	SpecialObject *special;

	normal = new Wall();
	normal->setColors(wall_color);
	norm_obj.push_back(normal);

	//100
	special = new Frame(100);
	special->setColors(frame_color);
	special_obj[special->getIndex()] = special;

	//101
	special = new Cabinet(101);
	special->setColors(cabinet_color);
	special_obj[special->getIndex()] = special;


	//102
	special = new Door(102);
	special->setColors(door_color);
	special_obj[special->getIndex()] = special;


	//103
	special = new Card(103);
	special->setColors(card_color);
	special_obj[special->getIndex()] = special;


	//104
	special = new Key(104);
	special->setColors(key_color);
	special_obj[special->getIndex()] = special;

	normal = new Table();
	normal->setColors(table_color);
	norm_obj.push_back(normal);

	//105
	special = new Ruler(105);
	special->setColors(ruler_color);
	special_obj[special->getIndex()] = special;

	//106
	special = new CardReader(106);
	special->setColors(card_reader_color);
	special_obj[special->getIndex()] = special;

	normal = new Egg();
	normal->setColors(egg_color);
	norm_obj.push_back(normal);

	//107
	special = new Carpet(107);
	special->setColors(carpet_table_color);
	special_obj[107] = special;

	//108
	special = new Dumpling(108);
	special->setColors(dump_color);
	special_obj[108] = special;
}

void InitLight() {

	//GLfloat LightPostion[] = { eye_x,eye_y,eye_z,1.0 };
	//GLfloat LightDirection[] = { eye_x + center_x, eye_y + center_y, eye_z + center_z };
	GLfloat SpotAngle[] = { 25.0 };

	GLfloat light0_ambient[] = { 0.0, 0.0, 0.0 ,0.0 };
	GLfloat light0_diffuse[] = { 0.5,0.5,0.5,1.0 };
	GLfloat light0_specular[] = { 0.0,0.0,0.0,0.0 };

	GLfloat material_ambient[] = { 0.5,0.5,0.5,1.0 };
	GLfloat material_diffuse[] = { 0.8,0.8,0.8,1.0 };
	GLfloat material_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat material_shininess[] = { 30.0 };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);


	glLightfv(GL_LIGHT0, GL_POSITION, LightPostion);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, LightDirection);
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, SpotAngle);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.16);
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.08);

}

void MyMouse(GLint button, GLint state, GLint x, GLint y) {
	//Object Picking 및 함수 실행.

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		PickingObject(x, y);

		if (hits  < 3) {
			cout << "////////" << endl;
			for (int i = 0; i < hits; i++) {
				int index = i * 4 + 3;
				GLuint name = selectBuff[index];
				cout << name << endl;

				for (map<GLuint, SpecialObject*>::iterator iter = special_obj.begin(); iter != special_obj.end(); iter++) {
					if (iter->first == name) {
						SelectProcess((GLuint)name);
						
					}
				}
			}
			cout << camera->eye_x << " // " << camera->eye_y << "//" << camera->eye_z << endl;
			cout << "////////" << endl;

			hits = 0;
		}
	}
	
	glutPostRedisplay();
}

void MySpecialKey(int key, int x, int y) {
	if (camera->status == CAM_STAT_FIX) {
		Cabinet* cab = dynamic_cast<Cabinet*>(special_obj[101]);
		switch (key) {
		case GLUT_KEY_LEFT:
			cab->key_x--;
			if (cab->key_x < 0)
				cab->key_x = 4;
			break;
		case GLUT_KEY_RIGHT:
			cab->key_x++;
			if (cab->key_x > 4)
				cab->key_x = 0;
			break;
		case GLUT_KEY_UP:
			cab->key_y++;
			if (cab->key_y >= 2)
				cab->key_y = 0;
			break;
		case GLUT_KEY_DOWN:
			cab->key_y--;
			if (cab->key_y < 0)
				cab->key_y = 1;
			break;


		case GLUT_KEY_F1:
			if (special_obj[101]->getStatus() == 1) {
				special_obj[101]->setStatus(0);
				camera->CameraStand();
				Cabinet* cab = dynamic_cast<Cabinet*>(special_obj[101]);
				cab->cabinet_submit.clear();
			}
			cout << "ESC" << endl;
			break;

		}
	}



	glutPostRedisplay();



}

void MyDisplay() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120, camera->width / camera->height, 0.1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLightfv(GL_LIGHT0, GL_POSITION, LightPostion); //반드시 이 위치에 와야 시점에 따라 움직임
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, LightDirection);

	if (camera->status != CAM_STAT_FIX) {
		if (mode == 0) //운영자모드
			gluLookAt(camera->eye_x, camera->eye_y, camera->eye_z,
				camera->eye_x + camera->center_x, camera->eye_y + camera->center_y, camera->eye_z + camera->center_z,
				camera->axis_x, camera->axis_y, camera->axis_z);
		else //사용자 모드
			gluLookAt(camera->eye_x, 0, camera->eye_z, camera->eye_x + camera->center_x, 0 + camera->center_y, camera->eye_z + camera->center_z,
				camera->axis_x, camera->axis_y, camera->axis_z);
	}
	else
		gluLookAt(-6, 0, 0, -10, 0, 0, 0, 1, 0);

	norm_obj[0]->DrawObject(wall_point);
	glEnable(GL_DEPTH_TEST);

	norm_obj[1]->DrawObject(table_point);
	norm_obj[2]->DrawObject(egg_point);

	special_obj[100]->DrawObject(frame_point);
	special_obj[101]->DrawObject(cabinet_point);
	special_obj[102]->DrawObject(door_point);
	special_obj[103]->DrawObject(card_point);
	special_obj[104]->DrawObject(key_point);
	special_obj[105]->DrawObject(ruler_point);
	special_obj[106]->DrawObject(card_reader_point);
	special_obj[107]->DrawObject(carpet_table_point);
	special_obj[108]->DrawObject(dump_point);
	//DrawingKeyPad();
	
	glDisable(GL_DEPTH_TEST);

	glFlush();

	glutSwapBuffers();

}

void PickingObject(GLint x, GLint y) {
	GLint viewport[4];

	glSelectBuffer(64, selectBuff);
	glGetIntegerv(GL_VIEWPORT, viewport);

	glRenderMode(GL_SELECT);

	glInitNames();
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluPickMatrix(x, viewport[3] - y, 2, 2, viewport);
	gluPerspective(120, (GLdouble)camera->width / (GLdouble)camera->height, 0.1, 1000);
	glPushName(0);
	
	glLoadName(100);
	special_obj[100]->DrawObject(frame_point);
	if (camera->status != CAM_STAT_FIX) {
		glLoadName(101);
		special_obj[101]->DrawObject(cabinet_point);
	}
	glLoadName(102);
	special_obj[102]->DrawObject(door_point);
	glLoadName(103);
	special_obj[103]->DrawObject(card_point);
	glLoadName(104);
	special_obj[104]->DrawObject(key_point);
	glLoadName(105);
	special_obj[105]->DrawObject(ruler_point);
	glLoadName(106);
	special_obj[106]->DrawObject(card_reader_point);
	glLoadName(107);
	special_obj[107]->DrawObject(carpet_table_point);
	glLoadName(108);
	special_obj[108]->DrawObject(dump_point);


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glFlush();
	hits = glRenderMode(GL_RENDER);
	//현재의 행렬 저장,

}

void SelectProcess(GLuint name) {
	switch (name) {
	case 100://프레임.
		if(special_obj[105]->getStatus() > 0)
			special_obj[100]->setStatus(special_obj[100]->getStatus() + 1);
		return;
	case 101://캐비넷.
		if (camera->eye_x > -7.8 && camera->eye_x < -5.0 && camera->eye_z > -2.1 && camera->eye_z < 2.1) {
			if (special_obj[107]->getStatus() > 1 && special_obj[100]->getStatus() > 0) {
				if (special_obj[101]->getStatus() == 0) {
					special_obj[101]->setStatus(special_obj[101]->getStatus() + 1);
				}
				if (special_obj[101]->getStatus() == 1) {
					camera->status = CAM_STAT_FIX;
				}
			}
		}
		return;
	case 102://문
		
		if(special_obj[104]->getStatus() > 0)
			special_obj[102]->setStatus(special_obj[102]->getStatus() + 1);
		if (special_obj[102]->getStatus() > 1) {
			exit(0);
		}
		return;
	case 103://카드.
		special_obj[103]->setStatus(special_obj[103]->getStatus() + 1);
		return;
	case 104://키.
		if(special_obj[101]->getStatus() > 0)
			special_obj[104]->setStatus(special_obj[104]->getStatus() + 1);
		return;
	case 105://자.
		if (camera->status == CAM_STAT_SIT) {
			special_obj[105]->setStatus(special_obj[105]->getStatus() + 1);
		}
		return;
	case 106://카드리더.
		if(special_obj[108]->getStatus() == 0 && special_obj[103]->getStatus() > 0)
			special_obj[108]->setStatus(special_obj[108]->getStatus() + 1);
		return;
	case 107://카펫.
		if (camera->status == CAM_STAT_SIT) {
			special_obj[107]->setStatus(special_obj[107]->getStatus() + 1);
		}
		return;
	case 108://만두.
		special_obj[108]->setStatus(special_obj[108]->getStatus() + 1);
		return;
	default:
		return;
	}
}

void MyReshape(int w, int h) {
	camera->width = w;
	camera->height = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120, (GLdouble)w / (GLdouble)h, 0.1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();

}

void MyPassiveMouse(GLint x, GLint y) {
	if(camera->status != CAM_STAT_FIX){
	//마지막 프레임과 현재 프레임 사이의 차이 계산
		GLfloat xoffset = x - camera->width / 2.0; //x
		GLfloat yoffset = camera->height / 2.0 - y; //y

		SetCursorPos(camera->width / 2.0, camera->height / 2.0);

		//마우스 감도 조절
		GLfloat sensitivity = 0.03;
		xoffset *= sensitivity;
		yoffset *= sensitivity;



		camera->yaw += xoffset;
		camera->pitch += yoffset;

		if (camera->pitch > 89.0)
			camera->pitch = 89.0;
		if (camera->pitch < -89.0)
			camera->pitch = -89.0;

		GLfloat pi = PI;

		GLfloat front_x = cos(camera->pitch*pi / 180.0) * cos(camera->yaw*pi / 180.0);
		GLfloat front_y = sin(camera->pitch*pi / 180.0);
		GLfloat front_z = cos(camera->pitch*pi / 180.0) * sin(camera->yaw*pi / 180.0);


	

		//front 벡터 정규화
		GLfloat normalized_front = sqrt(pow(front_x, 2) + pow(front_y, 2) + pow(front_z, 2));

		camera->center_x = front_x / normalized_front;
		camera->center_y = front_y / normalized_front;
		camera->center_z = front_z / normalized_front;
	}
	glutPostRedisplay();

}

void MyKeyboard(unsigned char key, int X, int Y) {
	
	
	if (camera->status == CAM_STAT_FIX) {
		Cabinet* cab = dynamic_cast<Cabinet*>(special_obj[101]);
		switch (key) {
		case 13:
			if (cab->key_y == 0) {
				cab->cabinet_submit.push_back(cab->key_x);


			}
			else {
				cab->cabinet_submit.push_back(cab->key_x + 5);

			}

			if (cab->cabinet_submit.size() == 16) {
				bool isAns = cab->ValidAnswer();
				camera->CameraStand();
				if (isAns) {
					special_obj[101]->setStatus(special_obj[101]->getStatus() + 1);
				}
				else {
					special_obj[101]->setStatus(special_obj[101]->getStatus() - 1);
				}
			}

			break;
		}

	}
	else{
		switch (key) {


		case 'w':
			switch (camera->move_state) {
			case 4: camera->move_state = 7; break;
			case 6: camera->move_state = 9; break;
			default: camera->move_state = 8; break;
			}

			break;

		case 's':
			switch (camera->move_state) {
			case 4: camera->move_state = 1; break;
			case 6: camera->move_state = 3; break;
			default: camera->move_state = 2; break;
			}

			break;

		case 'a':
			switch (camera->move_state) {
			case 8: camera->move_state = 7; break;
			case 2: camera->move_state = 1; break;
			default: camera->move_state = 4; break;
			}

			break;
		case 'd':
			switch (camera->move_state) {
			case 8: camera->move_state = 9; break;
			case 2: camera->move_state = 3; break;
			default: camera->move_state = 6; break;
			}

			break;

		case 'm':
			if (mode == 0)
				mode = 1;
			else mode = 0;
			break;

		case 27:
			exit(0);


			//앉기 키 c
		case 'c':
			if (camera->status == CAM_STAT_STAND) {
				camera->CameraSit();
			}

			else if(camera->status == CAM_STAT_SIT){
				camera->CameraStand();
			}
			break;

			//점프키 스페이스.
		case ' ':
			if (camera->y_vel == 0)
				camera->y_vel = 0.8;
			break;
		}
	}

	glutPostRedisplay();
}

void MyKeyUp(unsigned char key, int x, int y) {

	switch (key) {


	case 'w':
		switch (camera->move_state) {
		case 7: camera->move_state = 4; break;
		case 9: camera->move_state = 6; break;
		default: camera->move_state = 0; break;
		}

		break;

	case 's':
		switch (camera->move_state) {
		case 1: camera->move_state = 4; break;
		case 3: camera->move_state = 6; break;
		default: camera->move_state = 0; break;
		}

		break;

	case 'a':
		switch (camera->move_state) {
		case 7: camera->move_state = 8; break;
		case 1: camera->move_state = 2; break;
		default: camera->move_state = 0; break;
		}

		break;

	case 'd':
		switch (camera->move_state) {
		case 9: camera->move_state = 8; break;
		case 3: camera->move_state = 2; break;
		default: camera->move_state = 0; break;
		}

		break;

	}
	glutPostRedisplay();
}

void MyTimer(int val) {
	timer += 30;
	
	//점프 구현.
	if (camera->y_vel != 0) {
		camera->eye_y += camera->y_vel;
		camera->y_vel -= 0.05;

		if (camera->eye_y < 0) {
			camera->eye_y = 0;
			camera->y_vel = 0;
		}
	}

	GLint sec = timer / 1000;
	GLint min = sec / 60;
	//게임 오버 지점.
	if (min > 9) {
		exit(0);
	}

	camera->Moving();
	camera->CameraBound();

	glutPostRedisplay();
	glutTimerFunc(30, MyTimer, 1);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(camera->width, camera->height);

	glutCreateWindow("Escape Room");

	if (!LoadGLTextures())                            // 텍스처 로딩 루틴으로 점프함( 새코드 )
	{
		return FALSE;                            // 텍스처가 로딩되지 않았다면 FALSE를 반환 ( 새코드 )
	}

	ObjectInit();

	glClearDepth(10.0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	InitLight();

	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glutFullScreen();
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);

	SetCursorPos(glutGet(camera->width) / 2.0, glutGet(camera->height) / 2.0);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutKeyboardUpFunc(MyKeyUp);
	glutMouseFunc(MyMouse);
	glutTimerFunc(60, MyTimer, 1);
	glutPassiveMotionFunc(MyPassiveMouse);
	glutSpecialFunc(MySpecialKey);

	glutMainLoop();

	return 0;

}