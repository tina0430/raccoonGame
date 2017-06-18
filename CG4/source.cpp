/*
세종대학교 디지털콘텐츠 14011217학번 이지희
컴퓨터그래픽스 과제 4
*/

#include <stdlib.h>
#include <glut.h>

GLfloat W = 800, H = 600;
GLfloat X[10] = {-1.0, -0.3, 0.9, -0.2, -0.6, -0.3, -0.1, -0.7, 0.6, 0.0};				//0 : 너구리 1-9 : 당근
GLfloat Y[3] = {-0.78, -0.18, 0.42};													//1층, 2층 3층
GLfloat Z[10] = {0.0};																	//0 : 너구리 1-9 : 당근
GLfloat LX = 0, LY = 0, LZ = 0;															//너구리 위치변화
GLfloat tx[6] = {0.0};		 															//당근 자동차 이동 1,2 : x축 3,4 : y축 방향 5,6 : z축 방향

GLfloat l[2] = {0.09, 0.09};															//너구리 귀 쫑긋쫑긋

GLfloat theta_l[2] = {0.0};																//너구리 회전
GLfloat theta_c[3] = {0.0};																//당근 자동차 바퀴 회전
GLfloat theta_s = 0.0;																	//별 회전
GLfloat theta_z = 45;																	//perspective 각도

GLfloat cx = 0.0, cy = -0.2, cz = 3.5;													//카메라 위치 설정

GLint temp1= 1 , temp2 = 1, temp3 = 1;													//temp1 : 재시작, temp2 : 충돌효과, temp3 : 시점

GLboolean l_click = false , r_click = false;											//클릭이 되었는 지 안되었는 지 체크
GLint px, py;																			//마우스의 이전 위치 기록

//육면체 좌표
GLfloat vertices[][3] = {{-0.10, -0.10, -0.10},											//0			
{0.10, -0.10, -0.10},											//1			
{0.10, 0.10, -0.10}, 											//2			
{-0.10, 0.10, -0.10},											//3			
{-0.10, -0.10, 0.10},											//4			
{0.10, -0.10, 0.10},											//5			
{0.10, 0.10, 0.10},											//6			
{-0.10, 0.10, 0.10}};											//7				

//사각뿔 좌표 (누워있당)
GLfloat vertices2[][3] = {{-0.10, 0.0, 0.0},											//0			
{0.10, -0.10, -0.10},											//1			
{0.10, 0.10, -0.10},											//2			
{0.10, -0.10, 0.10},											//3			
{0.10, 0.10, 0.10}};											//4			


GLfloat colors[][3] = {{0.0, 0.0, 0.0},													//0 : 검정 
{1.0, 0.0, 0.0},													//1 : 빨강 
{1.0, 1.0, 0.0},													//2 : 노랑 
{0.0, 1.0, 0.0},													//3 : 초록 
{0.0, 0.0, 1.0},													//4 : 파랑 
{1.0, 0.0, 1.0},													//5 : 마젠타 
{1.0, 1.0, 1.0},													//6 : 흰 
{0.0, 1.0, 1.0}};												//7 : 시안

//육면체
GLubyte cubeIndices[] = {0, 3, 2, 1,													//face 0
	2, 3, 7, 6,													//face 1 
	0, 4, 7, 3, 													//face 2
	1, 2, 6, 5, 													//face 3
	4, 5, 6, 7, 													//face 4
	0, 1, 5, 4};													//face 5

//사각뿔
GLubyte cubeIndices2[] = {0, 2, 1,														//face 0
	0, 4, 2, 														//face 1 
	0, 3, 4,  													//face 2
	0, 1, 3,  													//face 3
	1, 2, 4, 3};													//face 4

void drawFloor (GLint floor)
{	  
	for ( int i = 0 ; i < 8 ; i++ )
	{
		colors[i][0] = 0.8;
		colors[i][1] = 0.81;
		colors[i][2] = 0.59;
	}
	glColorPointer(3, GL_FLOAT, 0, colors);	
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glLoadIdentity();
	glScalef(12.8, 0.2, 5.0);

	switch(floor)
	{
	case 1 :																			//1층일 경우
		glTranslatef(0.0, -4.5, 0.0);
		break;

	case 2 :																			//2층일 경우
		glTranslatef(0.0, -1.5, 0.0);
		break;

	case 3 :																			//3층일 경우
		glTranslatef(0.0, 1.5, 0.0);
		break;
	}

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
}

void drawLacoon (GLfloat x, GLfloat y, GLfloat z)
{	
	glColor3f(1.0, 0.2, 0.2);

	glLoadIdentity();		
	glTranslatef(x+LX, y+LY, z+LZ);
	glutSolidSphere(0.065, 10, 10);														//몸
	glPushMatrix();																		//전역 좌표계 저장

	glTranslatef(0.0, 0.09, 0.0);												
	glRotatef(theta_l[0], 0, 0, 1);
	glutSolidSphere(0.05, 10, 10);														//얼굴
	glPushMatrix();																		//얼굴 기준 좌표계 저장

	for ( int i = 0 ; i < 8 ; i++ )
	{
		colors[i][0] = 1.0;
		colors[i][1] = 0.2;
		colors[i][2] = 0.2;
	}
	glColorPointer(3, GL_FLOAT, 0, colors);	
	glVertexPointer(3, GL_FLOAT, 0, vertices2);

	glTranslatef(0.0, 0.04, 0.0);
	glPushMatrix();																		//귀 기준 좌표계 저장

	glScalef(2*l[0], l[0], l[0]);
	glTranslatef(-0.1, 0.0, 0.0);														//왼쪽 귀
	glRotatef(-65, 0, 0, 1);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices2);
	glRotatef(65, 0, 0, 1);

	glTranslatef(0.2, 0.0, 0.0);														//오른쪽 귀
	glRotatef(-115, 0, 0, 1);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices2);
	glPopMatrix();																		//귀 탈출
	glPopMatrix();																		//귀 기준 좌표계 탈출
	glPopMatrix();																		//얼굴 기준 좌표계 탈출


	glTranslatef(0.0, -0.06, 0.0);
	glRotatef(90, 0, 0, 1);
	glPushMatrix();																		//다리 기준 좌표계 저장

	glScalef(0.32, 0.32, 0.24);
	glTranslatef(0.0, -0.11, 0.0);
	glRotatef(15, 0, 0, 1);
	glDrawElements(GL_QUADS, 16, GL_UNSIGNED_BYTE, cubeIndices2);
	glRotatef(-15, 0, 0, 1);

	glTranslatef(0.0, 0.22, 0.0);
	glRotatef(-15, 0, 0, 1);
	glDrawElements(GL_QUADS, 16, GL_UNSIGNED_BYTE, cubeIndices2);
	glPopMatrix();																		//다리 기준 좌표계 탈출
}

void drawCarrot (GLfloat x, GLfloat y, GLfloat z, GLint d)
{	
	for ( int i = 0 ; i < 8 ; i++ )
	{
		colors[i][0] = 0.968;
		colors[i][1] = 0.515;
		colors[i][2] = 0.054;
	}
	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, vertices2);

	glLoadIdentity();									
	glTranslatef(x, y, z);
	glPushMatrix();																		//전역 좌표계 저장

	if (d == 0) glTranslatef(tx[d*2], 0, 0);											//d -> 0 : x축 1 : y축 2 : z축
	if (d == 1) glTranslatef(0, tx[d*2], 0);
	if (d == 2) glTranslatef(0, 0, tx[d*2]);
	glPushMatrix();																		//전체적인 이동 저장

	glRotatef(90.0, 0.0, 0.0, 1.0);
	glScalef(0.7, 0.7, 0.7);
	glDrawElements(GL_QUADS, 16, GL_UNSIGNED_BYTE, cubeIndices2);						//당근 몸

	for ( int i = 0 ; i < 8 ; i++ )
	{
		colors[i][0] = 0.148;
		colors[i][1] = 0.73;
		colors[i][2] = 0.304;
	}
	glColorPointer(3, GL_FLOAT, 0, colors);	
	glVertexPointer(3, GL_FLOAT, 0, vertices2);

	glTranslatef(0.11, 0.0, 0.0);														//잎
	glScalef(0.55, 0.45, 0.45);
	glDrawElements(GL_QUADS, 16, GL_UNSIGNED_BYTE, cubeIndices2);
	glPopMatrix();																		//잎 탈출

	glColor3f(0.55, 0.37, 0.05);
	glTranslatef(0.0, -0.049, 0.0);
	if ( d == 0 )																		//바퀴 -- x축 이동
	{
		glRotatef(theta_c[0], 0, 0, 1);
		glTranslatef(0.0, 0.0, 0.06);
		glutWireTorus(0.015, 0.035, 10, 10);
		glTranslatef(0.0, 0.0, -0.12);
		glutWireTorus(0.015, 0.035, 10, 10);
	}

	else if ( d == 1 )																	//바퀴 -- y축 이동
	{
		glTranslatef(0.0, 0.0, -0.06);
		glutWireTorus(0.015, 0.035, 10, 10);
		glTranslatef(0.0, 0.0, 0.12);
		glutWireTorus(0.015, 0.035, 10, 10);
	}

	else if ( d == 2 )																	//바퀴 -- z축 이동
	{
		glRotatef(90, 0, 1, 0);
		glRotatef(theta_c[2], 0, 0, 1);
		glTranslatef(0.0, 0.0, -0.06);
		glutWireTorus(0.015, 0.035, 10, 10);
		glTranslatef(0.0, 0.0, 0.12);
		glutWireTorus(0.015, 0.035, 10, 10);
	}
	glPopMatrix();																		//바퀴 탈출
}

void drawLabbor (GLfloat x, GLfloat y, GLfloat z)
{ 
	for ( int i = 0 ; i < 8 ; i++ )														//색지정
	{
		colors[i][0] = 0.125;
		colors[i][1] = 0.94;
		colors[i][2] = 0.707;
	}
	glColorPointer(3, GL_FLOAT, 0, colors);												//방금 지정한 색으로 칠할꾸~
	glVertexPointer(3, GL_FLOAT, 0, vertices);											//위에서 저장해놓은 육면체 벌텍스로 그릴껴

	glLoadIdentity();																	//사다리 왼쪽 다리
	glTranslatef(x, y+0.18, z);															
	glScalef(0.15, 2.8, 0.1);															
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);						

	glLoadIdentity();																	//사다리 오른쪽 다리						
	glTranslatef(x+0.16, y+0.18, z);
	glScalef(0.15, 2.8, 0.1);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);

	for ( int i = -3 ; i < 4 ; i ++ )													//사다리 발판
	{
		glLoadIdentity();													
		glTranslatef(x+0.08, y+i*0.075+0.165, z);
		glScalef(0.7, 0.13, 0.1);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
	}
}

void drawStar (GLfloat x, GLfloat y, GLfloat z)
{ 
	for ( int i = 0 ; i < 8 ; i++ )														//색지정
	{
		colors[i][0] = 0.996;
		colors[i][1] = 0.945;
		colors[i][2] = 0.0;
	}

	glColorPointer(3, GL_FLOAT, 0, colors);	
	glVertexPointer(3, GL_FLOAT, 0, vertices2);

	glLoadIdentity();																	
	glTranslatef(x, y, z-0.1);
	glPushMatrix();

	glRotatef(90.0, 0.0, 0.0, 1.0);
	glScalef(0.7, 0.7, 0.7);
	glRotatef(theta_s, 1.0, 0.0, 0.0);
	glDrawElements(GL_QUADS, 16, GL_UNSIGNED_BYTE, cubeIndices2);
	glPopMatrix();

	glTranslatef(0.0, 0.05, 0.0);
	glRotatef(-90.0, 0.0, 0.0, 1.0);
	glScalef(0.7, 0.7, 0.7);
	glRotatef(-theta_s, 1.0, 0.0, 0.0);
	glDrawElements(GL_QUADS, 16, GL_UNSIGNED_BYTE, cubeIndices2);
	glPopMatrix();

}

void floor1 (void)																			//1층 그리는 함수
{
	drawFloor(1);																			//1층 바닥
	drawLabbor (0.52, Y[0], -0.4);															//사다리

	drawCarrot ( X[1], Y[0], Z[1], 0);														//악당1 - x축으로 움직임
	drawCarrot ( X[2], Y[0]+0.35, Z[2], 1);													//악당2 - y축으로 움직임
	drawCarrot ( X[3], Y[0], Z[3], 2);														//악당3 - z축으로 움직임
}

void floor2 (void)																			//1층 그리는 함수
{
	drawFloor(2);																			//1층 바닥
	drawLabbor (-0.58, Y[1], 0.4);															//사다리	

	drawCarrot ( X[4], Y[1], Z[4], 0);														//악당1 - x축으로 움직임	
	drawCarrot ( X[5], Y[1]+0.35, Z[5], 1);													//악당2 - y축으로 움직임		
	drawCarrot ( X[6], Y[1], Z[6], 2);														//악	당3 - z축으로 움직임
}

void floor3 (void)																			//1층 그리는 함수
{
	drawFloor(3);																			//1층 바닥				

	drawCarrot ( X[7], Y[2], Z[7], 0);														//악당1 - x축으로 움직임			
	drawCarrot ( X[8], Y[2]+0.35, Z[8], 1);													//악당2 - y축으로 움직임	
	drawCarrot ( X[9], Y[2], Z[9], 2);														//악당3 - z축으로 움직임

	drawStar (1.1, Y[2], 0.0);
}																						

void Display(void)																		//display 답신
{
	if ( temp3 == 1 )
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();																	//변환 적용 후
		gluPerspective(theta_z, 1, 0.01, 1000);
		gluLookAt(cx, cy, cz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}

	else if ( temp3 == 2 )
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-W/H, W/H, -1.0, 1.0, -1.0, 1.0); 
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);									//프레임 버퍼와 z 버퍼를 클리어
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();																	//변환 적용 후

	if ( temp1 == 1 )
		floor1();

	if ( temp1 == 2 )
	{
		floor1();
		floor2();
	}

	if ( temp1 == 3 )
	{
		floor1();
		floor2();	
		floor3();
	}

	drawLacoon ( X[0], Y[0], Z[0] );

	glutSwapBuffers();																	//버퍼를 교환한다.
}

void Idle(void)
{
	GLfloat ch1 = tx[0] - tx[1];
	GLfloat ch2 = tx[2] - tx[3];
	GLfloat ch3 = tx[4] - tx[5];
	GLfloat ch4 = theta_l[0] - theta_l[1];
	GLfloat ch5 = l[0] - l[1];

	tx[1] = tx[0];
	tx[3] = tx[2];
	tx[5] = tx[4];
	theta_l[1] = theta_l[0];
	l[1] = l[0];

	//x축 움직임
	if ( ch1 <= 0 )																		//오->왼
	{
		if ( tx[0] > -0.72 )
			tx[0] -= 0.0006;
		else
			tx[0] += 0.0006;

		theta_c[0] += 0.09;																//반시계 방향
		if ( theta_c[0] > 360.0 )
			theta_c[0] = 0;
	}

	else																				//왼->오
	{
		if ( tx[0] < 0.18 )
			tx[0] += 0.0006;
		else
			tx[0] -= 0.0006;

		theta_c[0] -= 0.09;																//시계 방향
		if ( theta_c[0] < -360.0 )
			theta_c[0] = 0;
	}


	//y축 움직임
	if ( ch2 <= 0 )				
	{
		if ( tx[2] > -0.36 )
			tx[2] -= 0.0006;
		else
			tx[2] += 0.0006;
	}

	else
	{
		if ( tx[2] < 0.0 )
			tx[2] += 0.0006;
		else
			tx[2] -= 0.0006;
	}

	//z축 움직임
	if ( ch3 >= 0 )				
	{
		if ( tx[4] < 0.54 )
			tx[4] += 0.0006;
		else
			tx[4] -= 0.0006;

		theta_c[2] += 0.09;
		if ( theta_c[2] > 360.0 )
			theta_c[2] = 0;
	}

	else
	{
		if ( tx[4] > -0.18 )
			tx[4] -= 0.0006;
		else
			tx[4] += 0.0006;

		theta_c[2] -= 0.09;
		if ( theta_c[2] < -360.0 )
			theta_c[2] = 0;
	}

	if ( ch4 >= 0 )
	{
		if ( theta_l[0] < 20 )
			theta_l[0] += 0.04;
		else
			theta_l[0] -= 0.04;
	}

	else
	{
		if ( theta_l[0] > -20 )
			theta_l[0] -= 0.04;
		else
			theta_l[0] += 0.04;
	}

	if ( ch5 >= 0 )
	{
		if ( l[0] <= 0.152 )
			l[0] += 0.00004;
		else
			l[0] -= 0.00004;
	}

	else
	{
		if ( l[0] > 0.132 )
			l[0] -= 0.00004;
		else
			l[0] += 0.00004;
	}

	theta_s += 0.03;																	//별 회전
	if ( theta_s > 360.0 )
		theta_s = 0;



	//충돌효과
	GLfloat a[9], b[9], c[9];

	a[0] = X[0]+LX - (X[1]+tx[0]);
	a[1] = X[0]+LX - X[2];
	a[2] = X[0]+LX - X[3];
	a[3] = X[0]+LX - (X[4]+tx[0]);
	a[4] = X[0]+LX - X[5];
	a[5] = X[0]+LX - X[6];
	a[6] = X[0]+LX - (X[7]+tx[0]);
	a[7] = X[0]+LX - X[8];
	a[8] = X[0]+LX - X[9];

	b[0] = Y[0]+LY - Y[0];
	b[1] = Y[0]+LY - (Y[0]+tx[2]+0.35);
	b[2] = Y[0]+LY - Y[0];
	b[3] = Y[0]+LY - Y[1];
	b[4] = Y[0]+LY - (Y[1]+tx[2]+0.35);
	b[5] = Y[0]+LY - Y[1];
	b[6] = Y[0]+LY - Y[2];
	b[7] = Y[0]+LY - (Y[2]+tx[2]+0.35);
	b[8] = Y[0]+LY - Y[2];

	c[0] = Z[0]+LZ - Z[1];
	c[1] = Z[0]+LZ - Z[2];
	c[2] = Z[0]+LZ - (Z[3]+tx[4]);
	c[3] = Z[0]+LZ - Z[4];
	c[4] = Z[0]+LZ - Z[5];
	c[5] = Z[0]+LZ - (Z[6]+tx[4]);
	c[6] = Z[0]+LZ - Z[7];
	c[7] = Z[0]+LZ - Z[8];
	c[8] = Z[0]+LZ - (Z[9]+tx[4]);

	for ( int j = 0 ; j < 9 ; j++ )
		if ( a[j]*a[j] + b[j]*b[j] + c[j]*c[j] < 0.005)
			temp2 = 0;

	if ( temp2 == 1 )
		glutPostRedisplay();
}

void Mouse(int btn, int state, int x, int y)									//mouse 답신
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		l_click = true;

	else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		r_click = true;
	else
	{
		l_click = false;
		r_click = false;
	}
}

void MouseMotion (GLint x, GLint y)
{	
	if ( l_click )
	{
		if ( py > y )
		{
			if (theta_z != 0)
				theta_z++;
		}
		else
			if ( theta_z != 180 )
				theta_z--;
	}

	if ( r_click )
		;

	py = y;

	glutPostRedisplay();
}

void Init(void)
{
	glViewport(0, 0, W, H);

	if ( temp3 == 1 )
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(theta_z,1,0.01,1000);
		gluLookAt(cx, cy, cz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}

	else if ( temp3 == 2 )
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-W/H, W/H, -1.0, 1.0, -1.0, 1.0); 
	}
}

void Keyboard (unsigned char Key, int x, int y)
{
	GLboolean labbor1 = 0.61 >  X[0]+LX && X[0]+LX > 0.53 && -0.2 > Y[0]+LY && -0.3 > Z[0]+LZ && Z[0]+LZ > -0.4;
	GLboolean labbor2 = -0.44 >  X[0]+LX && X[0]+LX > -0.52 && 0.39 > Y[0]+LY && 0.4 > Z[0]+LZ && Z[0]+LZ > 0.3;

	if ( 0.56 >  X[0]+LX && X[0]+LX > 0.54 && -0.77 > Y[0]+LY && Y[0]+LY > -0.79 )		//사다리 주변으로 가면 사다리에 장착?
		LY += 0.02;

	if ( -0.44 >  X[0]+LX && X[0]+LX > -0.46 && -0.19 > Y[0]+LY && Y[0]+LY > -0.21 )
		LY += 0.02;

	switch( Key )
	{
	case 'a' : 
	case 'A' :	LX -= 0.05;	break;											
	case 'D' :
	case 'd' :	LX += 0.05;	break;		

	case 'W' :
	case 'w' :	if ( labbor1 )														//사다리에 있을때만 y좌표 변함
				{
					LY += 0.05;	break;		
				}
				else if ( labbor2 )
				{
					LY += 0.05;	break;		
				}
				else			break;
	case 'S' :
	case 's' :	if ( 0.61 >  X[0]+LX && X[0]+LX > 0.53 &&  Y[0]+LY > -0.81 )
				{
					LY -= 0.04;	break;	
				}
				else if ( -0.44 >  X[0]+LX && X[0]+LX > -0.52 &&  Y[0]+LY > -0.22 )
				{
					LY -= 0.04;	break;
				}
				else			break;

	case 'z' : 
	case 'Z' : LZ -= 0.05;		break;
	case 'x' : 
	case 'X' : LZ += 0.05;		break;

	case 'L' :
	case 'l' : cx += 0.05;		break;												//x축-왼쪽으로
	case 'J' :
	case 'j' : cx -= 0.05;		break;												//x축-오른쪽으로
	case 'I' :
	case 'i' : cy += 0.05;		break;												//y축-위로
	case 'K' :
	case 'k' : cy -= 0.05;		break;												//y축-아래로
	case 'U' :
	case 'u' : cz += 0.05;		break;												//z축-멀리
	case 'O' :
	case 'o' : cz -= 0.05;		break;												//z축-가까이

		//Init();
	case 'Q' :
	case 'q' : exit(0); break;														//게임 종료
	}

	if ( temp2 == 1 )																	//주인공과 악당이 충돌하면 temp2가 0이 되어서 화면 정지
		glutPostRedisplay();
}

void Menu (int id)
{
	if ( id == 2 )
	{
		LX = LY = LZ = 0;
		tx[0] = tx[1] = tx[2] = tx[3] = tx[4] = tx[5] = 0;

		temp1 = 1;
		temp2 = 1;

		cx = 0.0;
		cy = -0.2;
		cz = 3.5;

		theta_l[0] = theta_l[1] = 0.0;		
		theta_s = 0.0;		
		theta_z = 45;
		for ( int i = 0 ; i < 3 ; i ++ )
			theta_c[i] = 0.0;	
	}

	if ( id == 3 )
	{
		if ( temp3 == 1 )
			temp3 = 2;
		else if ( temp3 == 2 )
		{
			cx = 0.0, cy = -0.2, cz = 3.5;	
			temp3 = 1;
		}
	}
}

void selectFloorMenu (int id)															//층 선택 메뉴
{
	switch (id)
	{
	case 1 : 
		temp1 = 1;	break;
	case 2 : 
		temp1 = 2;	break;
	case 3 :
		temp1 = 3;	break;
	}

	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	GLint SubMenu;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);							//이중 버퍼와 z 버퍼 사용
	glutInitWindowSize(W, H);															//윈도우창 크기 설정
	glutInitWindowPosition(300,100);													//윈도우창 나타나는 곳 좌표
	glutCreateWindow("LacoonGame");														//윈도우창 이름 설정

	Init();

	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutIdleFunc(Idle);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);

	glEnable(GL_DEPTH_TEST);															//은면 제거
	glEnableClientState(GL_COLOR_ARRAY);												
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	SubMenu = glutCreateMenu(selectFloorMenu);											//층선택 메뉴
	glutAddMenuEntry("first", 1);
	glutAddMenuEntry("secind", 2);
	glutAddMenuEntry("third", 3);

	glutCreateMenu(Menu);																//전체 메뉴
	glutAddSubMenu("Set floor", SubMenu);												//층선택 메뉴 불러옴
	glutAddMenuEntry("Restart", 2);
	glutAddMenuEntry("Change", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);													//우클릭시 메뉴 나옴

	glutMainLoop();
}