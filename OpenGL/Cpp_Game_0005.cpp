/*
 * Cpp_game_0005.cpp
 * Yusuke_Kato
 * 2016.5.21
 * 2016.5.27
 */
 
/*
 * OpenGL
 */
 
/*
 * ��Q��������
 * ���ꂪgameAI�ƌ����邩�ǂ����͂Ƃ�����
 * �v������肤�܂������Ă���C������
 *
 * player:�ǂ�������i�蓮�j
 * enemy:������i�����j
 * 
 * �ł��Ă͂���
 */
 
/*
 * ����L�[�i�W�j
 * w:��
 * s:��
 * d:�E
 * a:��
 * e:�E��
 * q:����
 * x:�E��
 * z:����
 */
 
#include <GL/glut>
#include <iostream>
#include <windows>
#include <time>
using namespace std;

#define Y_MAX 40
#define Y_MIN -40
#define X_MAX 40
#define X_MIN -40
#define STEP 8//�ړ��̊Ԋu�A�}�X��
#define ENEMY_NONE 24//����Ƃ��̋�������Ă�����G�͋C�ɂ��Ȃ�
/* �e���|�[�g�|�C���g */
#define TERE_Y_1 16
#define TERE_X_1 24
#define TERE_Y_2 -40
#define TERE_X_2 -16

static GLint px = X_MIN,py = Y_MIN;//player�ʒu
static GLint nx = X_MAX,ny = Y_MAX;//enemy�ʒu

static GLint flag = 0;//�����Ƒ��肪���݂ɓ�������

/* �_�����B�v�f�́ix���W�Ay���W�A�傫���j */
void Point(int x,int y,float size){
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

/* ����̓����i�����j */
void enemy_motion(void)
{	
	int dy,dx;//�����Ƒ���̋����̍�(���ƕ����l����)(��Βlfabs)
	int w_dy_p,w_dy_m,w_dx_p,w_dx_m;//�ǂ���̋���
	int copy_py, copy_px;//�ړ�����O�̍��W��ۑ����Ă���
	int random;//��������
	
	if(flag == 0){
		copy_py = py;//���ʂ������瓮���Ȃ������Ƃ������Ƃ𔻒f���邽��
		copy_px = px;
		/* player��enemy�̋��� */
		dy = py - ny;//�ʒu�ɂ���Đ������ς��
		dx = px - nx;//��Βl�Ƃ����肵�Ă��g��
		/* player�ƕǂ̋��� */
		//w:wall,p:plus,m:minus
		w_dy_p = Y_MAX - py;//�ォ��̋���p:plus,m:minus
		w_dy_m = py - Y_MIN;//������
		w_dx_p = X_MAX - px;//�E����
		w_dx_m = px - X_MIN;//������
		/********** ���� **********/
		/**************************/
		/* ���肪�߂��ɂ͂��Ȃ��Ƃ��A�܂����S�֌����� */
		if(fabs(dy) >= ENEMY_NONE && fabs(dx) >= ENEMY_NONE){
			if(py >= 0) py -= STEP;
			else if(py < 0) py += STEP;
			if(px >= 0) px -= STEP;
			else if(px < 0) px += STEP;
			/* ����Ȃ��Ƃ���ɍs������߂� */
			if((py==8&&px==0)||(py==0&&(px>=-8&&py<=8))||(py==-8&&px==0)){
				py = copy_py;
				px = copy_px;
			}
		}
		/* ���肪�߂��Ƃ��͍L���ق��֓����� */
		else if(fabs(dy) < ENEMY_NONE || fabs(dx) < ENEMY_NONE ){
			if(py == ny){//�����P
				if(w_dy_p >= w_dy_m)py += STEP;
				else if(w_dy_p < w_dy_m)py -= STEP;
			}else if(px == nx){//�����Q
				if(w_dx_p >= w_dx_m) px += STEP;
				else if(w_dx_p < w_dx_m) px -= STEP;
			}else if(py > ny && px > nx){//�����R
				if(w_dy_m >= w_dx_m){
					py -= STEP;
					px += STEP;
				}
				else if(w_dy_m < w_dx_m){
					py += STEP;
					px -= STEP;
				}
			}else if(py > ny && px < nx){//�����S
				if(w_dy_m >= w_dx_p){
					py -= STEP;
					px -= STEP;
				}
				else if(w_dy_m < w_dx_p){
					py += STEP;
					px += STEP;
				}
			}else if(py < ny && px > nx){//�����T
				if(w_dy_p >= w_dx_m){
					py += STEP;
					px += STEP;
				}
				else if(w_dy_p < w_dx_m){
					py -= STEP;
					px -= STEP;
				}
			}else if(py < ny && px < nx){//�����U
				if(w_dy_p >= w_dx_p){
					py += STEP;
					px -= STEP;
				}
				else if(w_dy_p < w_dx_p){
					py -= STEP;
					px += STEP;
				}
			}
			/* ����Ȃ��Ƃ���ɍs������߂� */
			if((py==8&&px==0)||(py==0&&(px>=-8&&px<=8))||(py==-8&&px==0)){
				py = copy_py;
				px = copy_px;
			}
		}
		/**************************/
		/**************************/
		if(py == ny && px == nx){
			cout << "\n END \n";
			exit(0);
		}
		Sleep(1000);
		if(flag == 0) flag = 1;
	}//if_flag
}

void display(void)
{
	int i, j;
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	/* field�쐬 : -40�`40�ɊԊu8���� */
	for(j = -40; j <= 40; j += STEP){
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
	glBegin(GL_POLYGON);
	glVertex2d(15,7);//��
	glVertex2d(15,-7);
	glVertex2d(-15,-7);
	glVertex2d(-15,7);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2d(7,15);//�c
	glVertex2d(-7,15);
	glVertex2d(-7,-15);
	glVertex2d(7,-15);
	glEnd();
	glColor4f(0.0f,0.0f,0.0f,0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2d(0,16);
	glVertex2d(16,0);
	glVertex2d(0,-16);
	glVertex2d(-16,0);
	glEnd();
	for(j = -40; j <= 40; j += STEP){
		for(i = -40; i <= 40; i += STEP){
			if(!((j==-8&&i==0)||(j==0&&(i>=-8&&i<=8))||(j==8&&i==0))){
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				Point(j,i,20);
			}
		}//for_i
	}//for_j
	/* �e���|�[�g�|�C���g */
	glColor4f(1.0f,0.0f,0.0f,0.0f);
	Point(TERE_X_1,TERE_Y_1,20);
	Point(TERE_X_2,TERE_Y_2,20);
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

void keyboard(unsigned char key ,int x, int y)
{
	int copy_ny,copy_nx;
	
	if(flag == 1){
		copy_ny = ny;
		copy_nx = nx;
			if( key == 'w'){
				if(ny < 40){
					ny += STEP;
				}//if_py
			}//if_key
			else if( key == 's'){
				if(ny > -40){
					ny -= STEP;
				}//if_py
			}//if_key
			else if( key == 'd'){
				if(nx < 40){
					nx += STEP;
				}//if_px
			}//if_key
			else if( key == 'a'){
				if(nx > -40){
					nx -= STEP;
				}//if_px
			}//if_key
			else if( key == 'e'){
				if(ny < 40 && nx < 40){
					ny += STEP;
					nx += STEP;
				}//if_px
			}//if_key
			else if( key == 'q'){
				if(ny < 40 && nx > -40){
					ny += STEP;
					nx -= STEP;
				}//if_px
			}//if_key
			else if( key == 'x'){
				if(ny > -40 && nx < 40){
					ny -= STEP;
					nx += STEP;
				}//if_px
			}//if_key
			else if( key == 'z'){
				if(ny > -40 && nx > -40){
					ny -= STEP;
					nx -= STEP;
				}//if_px
			}//if_key
			/* �e���|�[�g */
			if(ny == TERE_Y_1 && nx == TERE_X_1){
				ny = TERE_Y_2;
				nx = TERE_X_2;
			}
			/* ����Ȃ��Ƃ���ɍs������߂� */
			if((ny==8&&nx==0)||(ny==0&&(nx>=-8&&nx<=8))||(ny==-8&&nx==0)){
				ny = copy_ny;
				nx = copy_nx;
			}
			if(py == ny && px == nx){
				cout << "\n END \n";
				exit(0);
			}
		flag = 0;
	}//if_flag==2
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
	glutKeyboardFunc(keyboard);
	init();
	glutMainLoop();
	return 0;
}//main