#include <Windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

GLfloat pts[4][3], ptsc[7][3], qts[4][3], u, p[3], range = 8.0;
// pts -> 4 points for hermite or interpolating curve, ptsc -> 7 points for 6th grade bezier, qts -> 4 points for 2nd out of 2 bezier curves.
int i, j, win, oldI, move = 0, q = 0, firstTime = 1, draw = 1;
GLdouble posX, posY, posZ;

int includes(double x, double y){
	
	if(draw!=3){
		for(i=0;i<4;i++){
			if((float)x>=pts[i][0]-0.1&&(float)x<=pts[i][0]+0.1&&(float)y>=pts[i][1]-0.1&&(float)y<=pts[i][1]+0.1){
				oldI = i;
				q = 0;
				return 1;
			}
		}
		if(draw==4){
			for(i=1;i<4;i++){
				if((float)x>=qts[i][0]-0.1&&(float)x<=qts[i][0]+0.1&&(float)y>=qts[i][1]-0.1&&(float)y<=qts[i][1]+0.1){
					q = 1;
					oldI = i;
					return 1;
				}
			}
		}
	}
	else{
		for(i=0;i<7;i++){
			if((float)x>=ptsc[i][0]-0.1&&(float)x<=ptsc[i][0]+0.1&&(float)y>=ptsc[i][1]-0.1&&(float)y<=ptsc[i][1]+0.1){
				oldI = i;
				return 1;
			}
		}
	}
	return 0;
	
}

void GetOGLPos(int x, int y){

    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
 
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);
 
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels(x, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
 
    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	
}

void myinit(void){

	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-range,range,-range,range,-5.0,5.0);
	glMatrixMode(GL_MODELVIEW);

}

void part_a(){

	float b[4];
	if(firstTime==1){
		srand(time(NULL));
		for(i=0;i<4;i++){
			pts[i][2] = 0.0;
			for(j=0;j<2;j++)
				pts[i][j] = 10.0*((float)rand()/(float)RAND_MAX)-5.0;
		}
		firstTime = 0;
	}
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_STRIP);
		for(i=0;i<100;i++){
			u = (float)i/99;
			b[0] = 2*u*u*u-3*u*u+1;
			b[1] = -2*u*u*u*u+3*u*u;
			b[2] = u*u*u-2*u*u+u;
			b[3] = u*u*u-u*u;
			for(j=0;j<3;j++)
				p[j] = b[0]*pts[0][j]+b[1]*pts[1][j]+b[2]*pts[2][j]+b[3]*pts[3][j];
			glVertex3fv(p);
		}
	glEnd();
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINE_STRIP);
		glVertex3fv(&pts[0][0]);
		glVertex3fv(&pts[2][0]);
	glEnd();
	glBegin(GL_LINE_STRIP);
		glVertex3fv(&pts[1][0]);
		glVertex3fv(&pts[3][0]);
	glEnd();
	glColor3f(0.0,0.0,0.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
		for(i=0;i<4;i++)
			glVertex3fv(&pts[i][0]);
	glEnd();

}

void part_b(){

	float b[4];
	if(firstTime==1){
		srand(time(NULL));
		for(i=0;i<4;i++){
			pts[i][2] = 0.0;
			for(j=0;j<2;j++)
				pts[i][j] = 10.0*((float)rand()/(float)RAND_MAX)-5.0;
		}
		firstTime = 0;
	}
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_STRIP);
		for(i=0;i<100;i++){
			u = (float)i/99;
			b[0] = -4.5*u*u*u+9*u*u-5.5*u+1;
			b[1] = 13.5*u*u*u-22.5*u*u+9*u;
			b[2] = -13.5*u*u*u+18*u*u-4.5*u;
			b[3] = 4.5*u*u*u-4.5*u*u+u;
			for(j=0;j<3;j++)
				p[j] = b[0]*pts[0][j]+b[1]*pts[1][j]+b[2]*pts[2][j]+b[3]*pts[3][j];
			glVertex3fv(p);
		}
	glEnd();
	glColor3f(0.0,0.0,0.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
		for(i=0;i<4;i++)
			glVertex3fv(&pts[i][0]);
	glEnd();

}

void part_c(){
 
	float b[7];
	if(firstTime==1){
		srand(time(NULL));
		for(i=0;i<7;i++){
			ptsc[i][2] = 0.0;
			for(j=0;j<2;j++)
				ptsc[i][j] = 10.0*((float)rand()/(float)RAND_MAX)-5.0;
		}
		firstTime = 0;
	}
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_STRIP);
		for(i=0;i<100;i++){
			u = (float)i/99;
			b[0] = pow(1-u,6);
			b[1] = 6*u*pow(1-u,5);
			b[2] = 15*u*u*pow(1-u,4);
			b[3] = 20*u*u*u*pow(1-u,3);
			b[4] = 15*pow(u,4)*(1-u)*(1-u);
			b[5] = 6*pow(u,5)*(1-u);
			b[6] = pow(u,6);
			for(j=0;j<3;j++)
				p[j] = b[0]*ptsc[0][j]+b[1]*ptsc[1][j]+b[2]*ptsc[2][j]+b[3]*ptsc[3][j]+b[4]*ptsc[4][j]+b[5]*ptsc[5][j]+b[6]*ptsc[6][j];
			glVertex3fv(p);
		}
	glEnd();
	glColor3f(0.0,0.0,0.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
		for(i=0;i<7;i++)
			glVertex3fv(&ptsc[i][0]);
	glEnd();

}

void part_d(){

	float b[4];
	if(firstTime==1){
		srand(time(NULL));
		for(i=0;i<4;i++){
			pts[i][2] = 0.0;
			qts[i][2] = 0.0;
			for(j=0;j<2;j++){
				pts[i][j] = 10.0*((float)rand()/(float)RAND_MAX)-5.0;
				if(i>1)
					qts[i][j] = 10.0*((float)rand()/(float)RAND_MAX)-5.0;
			}
		}
		firstTime = 0;
	}
	if(q==0){
		for(i=0;i<3;i++){
			qts[0][i] = pts[3][i];
			qts[1][i] = 2*pts[3][i]-pts[2][i];
		}
	}
	else{
		for(i=0;i<3;i++){
			pts[3][i] = qts[0][i];
			pts[2][i] = 2*qts[0][i]-qts[1][i];
		}
	}
	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_STRIP);
		glColor3f(1.0,0.0,0.0);
		for(i=0;i<100;i++){
			u = (float)i/99;
			b[0] = -u*u*u+3*u*u-3*u+1;
			b[1] = 3*u*u*u-6*u*u+3*u;
			b[2] = -3*u*u*u+3*u*u;
			b[3] = u*u*u;
			for(j=0;j<3;j++)
				p[j] = b[0]*pts[0][j]+b[1]*pts[1][j]+b[2]*pts[2][j]+b[3]*pts[3][j];
			glVertex3fv(p);
		}
		glColor3f(0.0,0.0,1.0);
		for(i=0;i<100;i++){
			u = (float)i/99;
			b[0] = -u*u*u+3*u*u-3*u+1;
			b[1] = 3*u*u*u-6*u*u+3*u;
			b[2] = -3*u*u*u+3*u*u;
			b[3] = u*u*u;
			for(j=0;j<3;j++)
				p[j] = b[0]*qts[0][j]+b[1]*qts[1][j]+b[2]*qts[2][j]+b[3]*qts[3][j];
			glVertex3fv(p);
		}
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glColor3f(0.0,0.0,0.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
		for(i=0;i<4;i++){
			glVertex3fv(&pts[i][0]);
			glVertex3fv(&qts[i][0]);
		}
	glEnd();

}

void display(void){

	if(draw==1)
		part_a();
	else if(draw==2)
		part_b();
	else if(draw==3)
		part_c();
	else
		part_d();
	glFlush();
	glutSwapBuffers();
		
}

void mouse(int button, int state, int x, int y){

	int d;
	GetOGLPos(x,y);
	d = includes(posX,posY);
	if(d==1){
		if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
			move = 1;
	}
	else
		move = 0;

}

void motion(int x, int y){
	
	if(move==1){
		if(draw==1||draw==2){
			GetOGLPos(x,y);
			pts[oldI][0] = (float)posX;
			pts[oldI][1] = (float)posY;
		}
		else if(draw==3){
			GetOGLPos(x,y);
			ptsc[oldI][0] = (float)posX;
			ptsc[oldI][1] = (float)posY;
		}
		else{
			GetOGLPos(x,y);
			if(q==1){
				qts[oldI][0] = (float)posX;
				qts[oldI][1] = (float)posY;
			}
			else{
				pts[oldI][0] = (float)posX;
				pts[oldI][1] = (float)posY;
			}
		}
		glutPostRedisplay();
	}
	
}

void chooseFromMenu(int option){

	if(option==1){
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-range,range,-range,range,-5.0,5.0);
		glMatrixMode(GL_MODELVIEW);
		draw = 1;
		firstTime = 1;
		glutPostRedisplay();
	}
	else if(option==2){
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-range,range,-range,range,-5.0,5.0);
		glMatrixMode(GL_MODELVIEW);
		draw = 2;
		firstTime = 1;
		glutPostRedisplay();
	}
	else if(option==3){
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-range,range,-range,range,-5.0,5.0);
		glMatrixMode(GL_MODELVIEW);
		draw = 3;
		firstTime = 1;
		glutPostRedisplay();
	}
	else if(option==4){
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-range,range,-range,range,-5.0,5.0);
		glMatrixMode(GL_MODELVIEW);
		draw = 4;
		firstTime = 1;
		q = 0;
		glutPostRedisplay();
	}
	else{
		glutDestroyWindow(win);
		exit(0);
	}
		
}

void buildMenu(){

	int menu;
	menu = glutCreateMenu(chooseFromMenu);
	glutAddMenuEntry("Hermite cubic curve",1);
	glutAddMenuEntry("Interpolating curve",2);
	glutAddMenuEntry("6th grade Bezier curve",3);
	glutAddMenuEntry("Two cubic Bezier curves",4);
	glutAddMenuEntry("Quit",5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void main(int argc, char **argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(650, 650);
	glutInitWindowPosition(0,0);
	win = glutCreateWindow("Curves");
	myinit();
	glutDisplayFunc(display);
	buildMenu();
	glutMotionFunc(motion);
	glutMouseFunc(mouse);
	glutMainLoop();
	
}