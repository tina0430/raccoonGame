/*
�������б� ������������ 14011217�й� ������
��ǻ�ͱ׷��Ƚ� ���� 4
*/

#include <stdlib.h>
#include <glut.h>

GLfloat W = 800, H = 600;
GLfloat X[10] = {-1.0, -0.3, 0.9, -0.2, -0.6, -0.3, -0.1, -0.7, 0.6, 0.0};				//0 : �ʱ��� 1-9 : ���
GLfloat Y[3] = {-0.78, -0.18, 0.42};													//1��, 2�� 3��
GLfloat Z[10] = {0.0};																	//0 : �ʱ��� 1-9 : ���
GLfloat LX = 0, LY = 0, LZ = 0;															//�ʱ��� ��ġ��ȭ
GLfloat tx[6] = {0.0};		 															//��� �ڵ��� �̵� 1,2 : x�� 3,4 : y�� ���� 5,6 : z�� ����

GLfloat l[2] = {0.09, 0.09};															//�ʱ��� �� �б��б�

GLfloat theta_l[2] = {0.0};																//�ʱ��� ȸ��
GLfloat theta_c[3] = {0.0};																//��� �ڵ��� ���� ȸ��
GLfloat theta_s = 0.0;																	//�� ȸ��
GLfloat theta_z = 45;																	//perspective ����

GLfloat cx = 0.0, cy = -0.2, cz = 3.5;													//ī�޶� ��ġ ����

GLint temp1= 1 , temp2 = 1, temp3 = 1;													//temp1 : �����, temp2 : �浹ȿ��, temp3 : ����

GLboolean l_click = false , r_click = false;											//Ŭ���� �Ǿ��� �� �ȵǾ��� �� üũ
GLint px, py;																			//���콺�� ���� ��ġ ���

//����ü ��ǥ
GLfloat vertices[][3] = {{-0.10, -0.10, -0.10},											//0			
{0.10, -0.10, -0.10},											//1			
{0.10, 0.10, -0.10}, 											//2			
{-0.10, 0.10, -0.10},											//3			
{-0.10, -0.10, 0.10},											//4			
{0.10, -0.10, 0.10},											//5			
{0.10, 0.10, 0.10},											//6			
{-0.10, 0.10, 0.10}};											//7				

//�簢�� ��ǥ (�����ִ�)
GLfloat vertices2[][3] = {{-0.10, 0.0, 0.0},											//0			
{0.10, -0.10, -0.10},											//1			
{0.10, 0.10, -0.10},											//2			
{0.10, -0.10, 0.10},											//3			
{0.10, 0.10, 0.10}};											//4			


GLfloat colors[][3] = {{0.0, 0.0, 0.0},													//0 : ���� 
{1.0, 0.0, 0.0},													//1 : ���� 
{1.0, 1.0, 0.0},													//2 : ��� 
{0.0, 1.0, 0.0},													//3 : �ʷ� 
{0.0, 0.0, 1.0},													//4 : �Ķ� 
{1.0, 0.0, 1.0},													//5 : ����Ÿ 
{1.0, 1.0, 1.0},													//6 : �� 
{0.0, 1.0, 1.0}};												//7 : �þ�

//����ü
GLubyte cubeIndices[] = {0, 3, 2, 1,													//face 0
	2, 3, 7, 6,													//face 1 
	0, 4, 7, 3, 													//face 2
	1, 2, 6, 5, 													//face 3
	4, 5, 6, 7, 													//face 4
	0, 1, 5, 4};													//face 5

//�簢��
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
	case 1 :																			//1���� ���
		glTranslatef(0.0, -4.5, 0.0);
		break;

	case 2 :																			//2���� ���
		glTranslatef(0.0, -1.5, 0.0);
		break;

	case 3 :																			//3���� ���
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
	glutSolidSphere(0.065, 10, 10);														//��
	glPushMatrix();																		//���� ��ǥ�� ����

	glTranslatef(0.0, 0.09, 0.0);												
	glRotatef(theta_l[0], 0, 0, 1);
	glutSolidSphere(0.05, 10, 10);														//��
	glPushMatrix();																		//�� ���� ��ǥ�� ����

	for ( int i = 0 ; i < 8 ; i++ )
	{
		colors[i][0] = 1.0;
		colors[i][1] = 0.2;
		colors[i][2] = 0.2;
	}
	glColorPointer(3, GL_FLOAT, 0, colors);	
	glVertexPointer(3, GL_FLOAT, 0, vertices2);

	glTranslatef(0.0, 0.04, 0.0);
	glPushMatrix();																		//�� ���� ��ǥ�� ����

	glScalef(2*l[0], l[0], l[0]);
	glTranslatef(-0.1, 0.0, 0.0);														//���� ��
	glRotatef(-65, 0, 0, 1);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices2);
	glRotatef(65, 0, 0, 1);

	glTranslatef(0.2, 0.0, 0.0);														//������ ��
	glRotatef(-115, 0, 0, 1);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices2);
	glPopMatrix();																		//�� Ż��
	glPopMatrix();																		//�� ���� ��ǥ�� Ż��
	glPopMatrix();																		//�� ���� ��ǥ�� Ż��


	glTranslatef(0.0, -0.06, 0.0);
	glRotatef(90, 0, 0, 1);
	glPushMatrix();																		//�ٸ� ���� ��ǥ�� ����

	glScalef(0.32, 0.32, 0.24);
	glTranslatef(0.0, -0.11, 0.0);
	glRotatef(15, 0, 0, 1);
	glDrawElements(GL_QUADS, 16, GL_UNSIGNED_BYTE, cubeIndices2);
	glRotatef(-15, 0, 0, 1);

	glTranslatef(0.0, 0.22, 0.0);
	glRotatef(-15, 0, 0, 1);
	glDrawElements(GL_QUADS, 16, GL_UNSIGNED_BYTE, cubeIndices2);
	glPopMatrix();																		//�ٸ� ���� ��ǥ�� Ż��
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
	glPushMatrix();																		//���� ��ǥ�� ����

	if (d == 0) glTranslatef(tx[d*2], 0, 0);											//d -> 0 : x�� 1 : y�� 2 : z��
	if (d == 1) glTranslatef(0, tx[d*2], 0);
	if (d == 2) glTranslatef(0, 0, tx[d*2]);
	glPushMatrix();																		//��ü���� �̵� ����

	glRotatef(90.0, 0.0, 0.0, 1.0);
	glScalef(0.7, 0.7, 0.7);
	glDrawElements(GL_QUADS, 16, GL_UNSIGNED_BYTE, cubeIndices2);						//��� ��

	for ( int i = 0 ; i < 8 ; i++ )
	{
		colors[i][0] = 0.148;
		colors[i][1] = 0.73;
		colors[i][2] = 0.304;
	}
	glColorPointer(3, GL_FLOAT, 0, colors);	
	glVertexPointer(3, GL_FLOAT, 0, vertices2);

	glTranslatef(0.11, 0.0, 0.0);														//��
	glScalef(0.55, 0.45, 0.45);
	glDrawElements(GL_QUADS, 16, GL_UNSIGNED_BYTE, cubeIndices2);
	glPopMatrix();																		//�� Ż��

	glColor3f(0.55, 0.37, 0.05);
	glTranslatef(0.0, -0.049, 0.0);
	if ( d == 0 )																		//���� -- x�� �̵�
	{
		glRotatef(theta_c[0], 0, 0, 1);
		glTranslatef(0.0, 0.0, 0.06);
		glutWireTorus(0.015, 0.035, 10, 10);
		glTranslatef(0.0, 0.0, -0.12);
		glutWireTorus(0.015, 0.035, 10, 10);
	}

	else if ( d == 1 )																	//���� -- y�� �̵�
	{
		glTranslatef(0.0, 0.0, -0.06);
		glutWireTorus(0.015, 0.035, 10, 10);
		glTranslatef(0.0, 0.0, 0.12);
		glutWireTorus(0.015, 0.035, 10, 10);
	}

	else if ( d == 2 )																	//���� -- z�� �̵�
	{
		glRotatef(90, 0, 1, 0);
		glRotatef(theta_c[2], 0, 0, 1);
		glTranslatef(0.0, 0.0, -0.06);
		glutWireTorus(0.015, 0.035, 10, 10);
		glTranslatef(0.0, 0.0, 0.12);
		glutWireTorus(0.015, 0.035, 10, 10);
	}
	glPopMatrix();																		//���� Ż��
}

void drawLabbor (GLfloat x, GLfloat y, GLfloat z)
{ 
	for ( int i = 0 ; i < 8 ; i++ )														//������
	{
		colors[i][0] = 0.125;
		colors[i][1] = 0.94;
		colors[i][2] = 0.707;
	}
	glColorPointer(3, GL_FLOAT, 0, colors);												//��� ������ ������ ĥ�Ҳ�~
	glVertexPointer(3, GL_FLOAT, 0, vertices);											//������ �����س��� ����ü ���ؽ��� �׸���

	glLoadIdentity();																	//��ٸ� ���� �ٸ�
	glTranslatef(x, y+0.18, z);															
	glScalef(0.15, 2.8, 0.1);															
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);						

	glLoadIdentity();																	//��ٸ� ������ �ٸ�						
	glTranslatef(x+0.16, y+0.18, z);
	glScalef(0.15, 2.8, 0.1);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);

	for ( int i = -3 ; i < 4 ; i ++ )													//��ٸ� ����
	{
		glLoadIdentity();													
		glTranslatef(x+0.08, y+i*0.075+0.165, z);
		glScalef(0.7, 0.13, 0.1);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
	}
}

void drawStar (GLfloat x, GLfloat y, GLfloat z)
{ 
	for ( int i = 0 ; i < 8 ; i++ )														//������
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

void floor1 (void)																			//1�� �׸��� �Լ�
{
	drawFloor(1);																			//1�� �ٴ�
	drawLabbor (0.52, Y[0], -0.4);															//��ٸ�

	drawCarrot ( X[1], Y[0], Z[1], 0);														//�Ǵ�1 - x������ ������
	drawCarrot ( X[2], Y[0]+0.35, Z[2], 1);													//�Ǵ�2 - y������ ������
	drawCarrot ( X[3], Y[0], Z[3], 2);														//�Ǵ�3 - z������ ������
}

void floor2 (void)																			//1�� �׸��� �Լ�
{
	drawFloor(2);																			//1�� �ٴ�
	drawLabbor (-0.58, Y[1], 0.4);															//��ٸ�	

	drawCarrot ( X[4], Y[1], Z[4], 0);														//�Ǵ�1 - x������ ������	
	drawCarrot ( X[5], Y[1]+0.35, Z[5], 1);													//�Ǵ�2 - y������ ������		
	drawCarrot ( X[6], Y[1], Z[6], 2);														//��	��3 - z������ ������
}

void floor3 (void)																			//1�� �׸��� �Լ�
{
	drawFloor(3);																			//1�� �ٴ�				

	drawCarrot ( X[7], Y[2], Z[7], 0);														//�Ǵ�1 - x������ ������			
	drawCarrot ( X[8], Y[2]+0.35, Z[8], 1);													//�Ǵ�2 - y������ ������	
	drawCarrot ( X[9], Y[2], Z[9], 2);														//�Ǵ�3 - z������ ������

	drawStar (1.1, Y[2], 0.0);
}																						

void Display(void)																		//display ���
{
	if ( temp3 == 1 )
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();																	//��ȯ ���� ��
		gluPerspective(theta_z, 1, 0.01, 1000);
		gluLookAt(cx, cy, cz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}

	else if ( temp3 == 2 )
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-W/H, W/H, -1.0, 1.0, -1.0, 1.0); 
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);									//������ ���ۿ� z ���۸� Ŭ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();																	//��ȯ ���� ��

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

	glutSwapBuffers();																	//���۸� ��ȯ�Ѵ�.
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

	//x�� ������
	if ( ch1 <= 0 )																		//��->��
	{
		if ( tx[0] > -0.72 )
			tx[0] -= 0.0006;
		else
			tx[0] += 0.0006;

		theta_c[0] += 0.09;																//�ݽð� ����
		if ( theta_c[0] > 360.0 )
			theta_c[0] = 0;
	}

	else																				//��->��
	{
		if ( tx[0] < 0.18 )
			tx[0] += 0.0006;
		else
			tx[0] -= 0.0006;

		theta_c[0] -= 0.09;																//�ð� ����
		if ( theta_c[0] < -360.0 )
			theta_c[0] = 0;
	}


	//y�� ������
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

	//z�� ������
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

	theta_s += 0.03;																	//�� ȸ��
	if ( theta_s > 360.0 )
		theta_s = 0;



	//�浹ȿ��
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

void Mouse(int btn, int state, int x, int y)									//mouse ���
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

	if ( 0.56 >  X[0]+LX && X[0]+LX > 0.54 && -0.77 > Y[0]+LY && Y[0]+LY > -0.79 )		//��ٸ� �ֺ����� ���� ��ٸ��� ����?
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
	case 'w' :	if ( labbor1 )														//��ٸ��� �������� y��ǥ ����
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
	case 'l' : cx += 0.05;		break;												//x��-��������
	case 'J' :
	case 'j' : cx -= 0.05;		break;												//x��-����������
	case 'I' :
	case 'i' : cy += 0.05;		break;												//y��-����
	case 'K' :
	case 'k' : cy -= 0.05;		break;												//y��-�Ʒ���
	case 'U' :
	case 'u' : cz += 0.05;		break;												//z��-�ָ�
	case 'O' :
	case 'o' : cz -= 0.05;		break;												//z��-������

		//Init();
	case 'Q' :
	case 'q' : exit(0); break;														//���� ����
	}

	if ( temp2 == 1 )																	//���ΰ��� �Ǵ��� �浹�ϸ� temp2�� 0�� �Ǿ ȭ�� ����
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

void selectFloorMenu (int id)															//�� ���� �޴�
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

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);							//���� ���ۿ� z ���� ���
	glutInitWindowSize(W, H);															//������â ũ�� ����
	glutInitWindowPosition(300,100);													//������â ��Ÿ���� �� ��ǥ
	glutCreateWindow("LacoonGame");														//������â �̸� ����

	Init();

	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutIdleFunc(Idle);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);

	glEnable(GL_DEPTH_TEST);															//���� ����
	glEnableClientState(GL_COLOR_ARRAY);												
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	SubMenu = glutCreateMenu(selectFloorMenu);											//������ �޴�
	glutAddMenuEntry("first", 1);
	glutAddMenuEntry("secind", 2);
	glutAddMenuEntry("third", 3);

	glutCreateMenu(Menu);																//��ü �޴�
	glutAddSubMenu("Set floor", SubMenu);												//������ �޴� �ҷ���
	glutAddMenuEntry("Restart", 2);
	glutAddMenuEntry("Change", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);													//��Ŭ���� �޴� ����

	glutMainLoop();
}