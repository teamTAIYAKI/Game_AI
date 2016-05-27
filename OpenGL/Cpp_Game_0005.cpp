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
 * 障害物をつくる
 * これがgameAIと言えるかどうかはともかく
 * 思ったよりうまくいっている気がする
 *
 * player:追いかける（手動）
 * enemy:逃げる（自動）
 * 
 * できてはいる
 */
 
/*
 * 操作キー（８つ）
 * w:上
 * s:下
 * d:右
 * a:左
 * e:右上
 * q:左上
 * x:右下
 * z:左下
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
#define STEP 8//移動の間隔、マス目
#define ENEMY_NONE 24//相手とこの距離離れていたら敵は気にしない
/* テレポートポイント */
#define TERE_Y_1 16
#define TERE_X_1 24
#define TERE_Y_2 -40
#define TERE_X_2 -16

static GLint px = X_MIN,py = Y_MIN;//player位置
static GLint nx = X_MAX,ny = Y_MAX;//enemy位置

static GLint flag = 0;//自分と相手が交互に動くため

/* 点を作る。要素は（x座標、y座標、大きさ） */
void Point(int x,int y,float size){
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

/* 相手の動き（自動） */
void enemy_motion(void)
{	
	int dy,dx;//自分と相手の距離の差(正と負を考える)(絶対値fabs)
	int w_dy_p,w_dy_m,w_dx_p,w_dx_m;//壁からの距離
	int copy_py, copy_px;//移動する前の座標を保存しておく
	int random;//乱数生成
	
	if(flag == 0){
		copy_py = py;//結果そこから動かなかったということを判断するため
		copy_px = px;
		/* playerとenemyの距離 */
		dy = py - ny;//位置によって正負が変わる
		dx = px - nx;//絶対値とったりしても使う
		/* playerと壁の距離 */
		//w:wall,p:plus,m:minus
		w_dy_p = Y_MAX - py;//上からの距離p:plus,m:minus
		w_dy_m = py - Y_MIN;//下から
		w_dx_p = X_MAX - px;//右から
		w_dx_m = px - X_MIN;//左から
		/********** 動き **********/
		/**************************/
		/* 相手が近くにはいないとき、まず中心へ向かう */
		if(fabs(dy) >= ENEMY_NONE && fabs(dx) >= ENEMY_NONE){
			if(py >= 0) py -= STEP;
			else if(py < 0) py += STEP;
			if(px >= 0) px -= STEP;
			else if(px < 0) px += STEP;
			/* 入れないところに行ったら戻す */
			if((py==8&&px==0)||(py==0&&(px>=-8&&py<=8))||(py==-8&&px==0)){
				py = copy_py;
				px = copy_px;
			}
		}
		/* 相手が近いときは広いほうへ逃げる */
		else if(fabs(dy) < ENEMY_NONE || fabs(dx) < ENEMY_NONE ){
			if(py == ny){//条件１
				if(w_dy_p >= w_dy_m)py += STEP;
				else if(w_dy_p < w_dy_m)py -= STEP;
			}else if(px == nx){//条件２
				if(w_dx_p >= w_dx_m) px += STEP;
				else if(w_dx_p < w_dx_m) px -= STEP;
			}else if(py > ny && px > nx){//条件３
				if(w_dy_m >= w_dx_m){
					py -= STEP;
					px += STEP;
				}
				else if(w_dy_m < w_dx_m){
					py += STEP;
					px -= STEP;
				}
			}else if(py > ny && px < nx){//条件４
				if(w_dy_m >= w_dx_p){
					py -= STEP;
					px -= STEP;
				}
				else if(w_dy_m < w_dx_p){
					py += STEP;
					px += STEP;
				}
			}else if(py < ny && px > nx){//条件５
				if(w_dy_p >= w_dx_m){
					py += STEP;
					px += STEP;
				}
				else if(w_dy_p < w_dx_m){
					py -= STEP;
					px -= STEP;
				}
			}else if(py < ny && px < nx){//条件６
				if(w_dy_p >= w_dx_p){
					py += STEP;
					px -= STEP;
				}
				else if(w_dy_p < w_dx_p){
					py -= STEP;
					px += STEP;
				}
			}
			/* 入れないところに行ったら戻す */
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
	
	/* field作成 : -40～40に間隔8ずつ */
	for(j = -40; j <= 40; j += STEP){
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
	glBegin(GL_POLYGON);
	glVertex2d(15,7);//横
	glVertex2d(15,-7);
	glVertex2d(-15,-7);
	glVertex2d(-15,7);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2d(7,15);//縦
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
	/* テレポートポイント */
	glColor4f(1.0f,0.0f,0.0f,0.0f);
	Point(TERE_X_1,TERE_Y_1,20);
	Point(TERE_X_2,TERE_Y_2,20);
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
			/* テレポート */
			if(ny == TERE_Y_1 && nx == TERE_X_1){
				ny = TERE_Y_2;
				nx = TERE_X_2;
			}
			/* 入れないところに行ったら戻す */
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