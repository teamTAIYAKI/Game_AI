/*
 * Cpp_game_0001.cpp
 * Yusuke_Kato
 * 2016.5.21
 * 2016.5.24
 */
 
/*
 * OpenGL
 */
 
/*
 * player,enemy,両方自動
 * 
 * ・逃げるにはどうするか
 */
 
#include <GL/glut>
#include <iostream>
#include <windows>
#include <time>
using namespace std;

static GLint px = -40,py = -40;//player位置
static GLint nx = 40, ny = 40;//enemy位置

static GLint flag = 0;

/* 点を作る。要素は（x座標、y座標、大きさ） */
void Point(int x,int y,float size){
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

void player_motion(void)
{	
	int dy,dx;
	int w_dy, w_dx;
	int copy_py, copy_px;
	
	if(flag == 0 || flag == 1){
		copy_py = py;
		copy_px - px;
		/* playerとenemyの距離 */
		if(py > ny) dy = py - ny;
		else if(py < ny) dy = ny - py;
		if(px > nx) dx = px - nx;
		else if(px < nx) dx = nx - px;
		/* playerと壁の距離 */
		if(py >= 0) w_dy = 40 - py;
		else if(py < 0) w_dy = py + 40;
		if(px >= 0) w_dx = 40 - px;
		else if(px < 0) w_dx - px + 40;
		/* 動き */
		if((dy >= 8 && dy <= 16) && (dx >= 8 && dx <= 16)){
			if(py > ny){
				if(py < 40) py += 8;
			} else if(py < ny){
				if(py > -40) py -= 8;
			}
			if(px > nx){
				if(px < 40) px += 8;
			} else if(px < nx){
				if(px > -40) px -= 8;
			}
			if(copy_py == py && copy_px == px){
				if(w_dy == 0){
					if(py > 0) py -= 8;
					else if(py < 0) py += 8;
				}
				if(w_dx == 0){
					if(px > 0) px -= 8;
					else if(px < 0) px += 8;
				}
			}
		}
		else {
			if(py > 0) py -= 8;
			else if(py < 0) py += 8;
			if(py > 0) px -= 8;
			else if(px < 0) px += 8;
		}
		Sleep(1000);
		if(flag == 0) flag = 1;
		else if(flag == 1) flag = 2;
	}//if_flag
}

/* enemyの動き */
void enemy_motion(void)
{
	if(flag == 2){
		if(ny > py) ny -= 8;
		else if(ny < py) ny += 8;
		if(nx > px) nx -= 8;
		else if(nx < px) nx += 8;
		if(ny == py && nx == px){
			cout << "\n\n ......END...... \n\n";
			exit(0);
		}
		Sleep(1000);//なくてもいい
		flag = 0;//ターンの切り替えのため
	}//if_flag
}

void display(void)
{
	int i, j;
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	/* field作成 : -40～40に間隔8ずつ */
	for(j = -40; j <= 40; j += 8){
		glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex2d(j,40);//横
		glVertex2d(j,-40);
		glVertex2d(40,j);//縦
		glVertex2d(-40,j);
		glVertex2d(j,40);//斜：右上から左下：左上
		glVertex2d(-40,-j);
		glVertex2d(40,j);//斜：右上から左下：右下
		glVertex2d(-j,-40);
		glVertex2d(40,j);//斜：左上から右下：右上
		glVertex2d(j,40);
		glVertex2d(-40,j);//斜：左上から右下：左下
		glVertex2d(j,-40);
		glEnd();
	}//for_j
	for(j = -40; j <= 40; j += 8){
		for(i = -40; i <= 40; i += 8){
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			Point(j,i,20);
		}//for_i
	}//for_j
	/* player描写 */
	glColor4f(0.2f, 0.6f, 0.3f, 0.2f);
	Point(px,py,15);//player
	/* enemy描写 */
	glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
	Point(nx,ny,15);//enemy
	
	glFlush();
	
	player_motion();
	enemy_motion();
	
	glutPostRedisplay();
}//display

/* よくわからない */
void resize(int w, int h)
{
	glViewport( 0, 0, w, h );
 	glMatrixMode(GL_PROJECTION);
 	glLoadIdentity();
 	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
 	glMatrixMode(GL_MODELVIEW);
 	glLoadIdentity();
}//resize

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
	init();
	glutMainLoop();
	return 0;
}//main