/*
 * Cpp_game_001.cpp
 * Yusuke_Kato
 * 2016.5.21
 * 2016.5.24
 */
 
/*
 * OpenGL��p��������
 * �E�����Ԉ���Ă���\��������
 *   display�̒��ł��̂�
 *   simu�Ƃ�����Ă������œ������̂�
 *   �悭�킩��Ȃ�
 * 
 * �E��Q���̐ݒu
 *   �ǂ�����Ă悯�邩�A�G�A����
 * 
 * �E�i�ꉞ���������jflag_2������ĉ����͂���
 *    ����܂肫�ꂢ�Ƃ͌����Ȃ��̂ŁA
 *    �����Ɨǂ����@���l����
 *    player��2��s������
 * 
 * �E�i���������jflag��p���ă^�[���������
 *	 �^�[�����ɂ���ɂ͂ǂ�����΂�����
 * 	 �����������āA���肪�����āA�Ƃ����悤�ȏ��Ԃ������@���l����
 */
 
#include <GL/glut>
#include <iostream>
#include <windows>//Sleep���g����������
#include <time>
using namespace std;

static GLint px = -40,py = -40;//player�ʒu
static GLint nx = 40, ny = 40;//enemy�ʒu

static GLint flag = 0;//flag�^�[������邽��
static GLint flag_2 = 0;//player��2��s�����邽��

#define PI 3.14159265//�~����

/* �_�����B�v�f�́ix���W�Ay���W�A�傫���j */
void Point(int x,int y,float size){
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

/* enemy�̓��� */
void enemy_motion(void)
{
	int ny_copy, nx_copy;
	int ran;
	
	if(flag == 2){
		ny_copy = ny;
		nx_copy = nx;
		if(ny > py){
			ny -= 8;
			if(ny ==  0 && nx == 0){
				ny += 8;
			}
		}
		else if(ny < py){
			ny += 8;
			if(ny == 0 && nx == 0){
				ny -= 8;
			}
		}
		if(nx > px){
			nx -= 8;
			if(ny == 0 && nx == 0){
				nx += 8;
			}
		}
		else if(nx < px){
			nx += 8;
			if(ny == 0 && nx == 0){
				nx -= 8;
			}
		}
		if(ny == ny_copy && nx == nx_copy){
			srand((unsigned int)time(NULL));
			ran = rand()%2+1;
			if(ny > py){
				if(ran == 1){
					nx += 8;
					ny -= 8;
				} else if(ran == 2){
					nx -= 8;
					ny -= 8;
				}
			} else if(ny < py){
				if(ran == 1){
					nx += 8;
					ny += 8;
				} else if(ran == 2){
					nx -= 8;
					ny += 8;
				}
			}
			if(nx > px){
				if(ran == 1){
					ny += 8;
					nx -= 8;
				} else if(ran == 2){
					ny -= 8;
					nx -= 8;
				}
			} else if(nx < px){
				if(ran == 1){
					ny += 8;
					nx += 8;
				} else if(ran == 2){
					ny -= 8;
					nx += 8;
				}
			}
		}
		if(ny == py && nx == px){
			cout << "\n\n ......END...... \n\n";
			exit(0);
		}
		//Sleep(1000);//�Ȃ��Ă�����
		flag = 0;//�^�[���̐؂�ւ��̂���
		flag_2 = 0;
	}//if_flag
}

void display(void)
{
	int i, j;
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	/* field�쐬 : -40�`40�ɊԊu8���� */
	for(j = -40; j <= 40; j += 8){
		glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex2d(j,40);//��
		glVertex2d(j,-40);
		glVertex2d(40,j);//�c
		glVertex2d(-40,j);
		glVertex2d(j,40);//�΁F�E�ォ�獶���F����
		glVertex2d(-40,-j);
		glVertex2d(40,j);//�΁F�E�ォ�獶���F�E��
		glVertex2d(-j,-40);
		glVertex2d(40,j);//�΁F���ォ��E���F�E��
		glVertex2d(j,40);
		glVertex2d(-40,j);//�΁F���ォ��E���F����
		glVertex2d(j,-40);
		glEnd();
	}//for_j
	/* ��Q�� */
	glColor4f(1.0f, 0.5f, 0.5f, 1.0f);
	Point(0,0,20);
	glBegin(GL_POLYGON);
	glVertex2d(7,7);
	glVertex2d(7,-7);
	glVertex2d(-7,-7);
	glVertex2d(-7,7);
	glEnd();
	glColor4f(0.0f,0.0f,0.0f,0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2d(8,0);
	glVertex2d(0,-8);
	glVertex2d(-8,0);
	glVertex2d(0,8);
	glEnd();
	for(j = -40; j <= 40; j += 8){
		for(i = -40; i <= 40; i += 8){
			if(!(j == 0 && i == 0)){
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				Point(j,i,20);
			}
		}//for_i
	}//for_j
	/* player�`�� */
	glColor4f(0.2f, 0.6f, 0.3f, 0.2f);
	Point(px,py,15);//player
	/* enemy�`�� */
	glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
	Point(nx,ny,15);//enemy
	
	glFlush();
	
	enemy_motion();
	
	glutPostRedisplay();
}//display

/* �悭�킩��Ȃ� */
void resize(int w, int h)
{
	glViewport( 0, 0, w, h );
 	glMatrixMode(GL_PROJECTION);
 	glLoadIdentity();
 	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
 	glMatrixMode(GL_MODELVIEW);
 	glLoadIdentity();
}//resize

/* ���ꂩ��g������ */
void mouse(int button, int state, int x, int y)
{
	switch (button) {
		case GLUT_LEFT_BUTTON:
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		default:
			break;
	}
}//mouse

void keyboard(unsigned char key ,int x, int y)
{
	if ( key == '\x1b') exit(0);
	if ( key == 'w'){
		if(py < 40){
			if(flag == 1) flag_2 = 1;
			py += 8;
			if(py == 0 && px == 0){
				py -= 8;
			}
			flag = 1;
			if(flag_2 == 1) flag = 2;
		}//if_py
	}//if_key
	if ( key == 's'){
		if(py > -40){
			if(flag == 1) flag_2 = 1;
			py -= 8;
			if(py == 0 && px == 0){
				py += 8;
			}
			flag = 1;
			if(flag_2 == 1) flag = 2;
		}//if_py
	}//if_key
	if ( key == 'd'){
		if(px < 40){
			if(flag == 1) flag_2 = 1;
			px += 8;
			if(py == 0 && px == 0){
				px -= 8;
			}
			flag = 1;
			if(flag_2 == 1) flag = 2;
		}//if_px
	}//if_key
	if ( key == 'a'){
		if(px > -40){
			if(flag == 1) flag_2 = 1;
			px -= 8;
			if(py == 0 && px == 0){
				px += 8;
			}
			flag = 1;
			if(flag_2 == 1) flag = 2;
		}//if_px
	}//if_key
}//keyboard

void init(void)
{
	glClearColor(1.0, 0.5, 0.5, 1.0);
}//init

int main(int argc, char *argv[])
{
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 640);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	init();
	glutMainLoop();
	return 0;
}//main