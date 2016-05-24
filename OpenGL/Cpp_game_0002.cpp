/*
 * Cpp_game_001.cpp
 * Yusuke_Kato
 * 2016.5.21
 * 2016.5.24
 */
 
/*
 * OpenGLを用いたそれ
 * ・やり方間違っている可能性が高い
 *   displayの中でやるのか
 *   simuとか作ってそっちで動かすのか
 *   よくわからない
 * 
 * ・障害物の設置
 *   どうやってよけるか、敵、自分
 * 
 * ・（一応解決した）flag_2を作って解決はした
 *    あんまりきれいとは言えないので、
 *    もっと良い方法を考える
 *    playerが2回行動する
 * 
 * ・（解決した）flagを用いてターンを作った
 *	 ターン制にするにはどうすればいいか
 * 	 自分が動いて、相手が動いて、というような順番を作る方法を考える
 */
 
#include <GL/glut>
#include <iostream>
#include <windows>//Sleepを使いたかった
#include <time>
using namespace std;

static GLint px = -40,py = -40;//player位置
static GLint nx = 40, ny = 40;//enemy位置

static GLint flag = 0;//flagターンを作るため
static GLint flag_2 = 0;//playerが2回行動するため

#define PI 3.14159265//円周率

/* 点を作る。要素は（x座標、y座標、大きさ） */
void Point(int x,int y,float size){
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

/* enemyの動き */
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
		//Sleep(1000);//なくてもいい
		flag = 0;//ターンの切り替えのため
		flag_2 = 0;
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
	/* 障害物 */
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
	/* player描写 */
	glColor4f(0.2f, 0.6f, 0.3f, 0.2f);
	Point(px,py,15);//player
	/* enemy描写 */
	glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
	Point(nx,ny,15);//enemy
	
	glFlush();
	
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

/* これから使うかも */
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