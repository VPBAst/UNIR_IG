/* 
 * File:   solution.c
 * Actividad: IGReloj - trabajo grupal
 * Authores: SILVA PEREZ, OLIVER
 * 			 LOSPITAO RUIZ, RUTH
 *           PATALLO BERMUDEZ, VICTOR 
* 
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

//DEFINICION DE CONSTANTES

const GLfloat v_x = 100.0f;
const GLfloat v_y = 100.0f;

const GLfloat CLOCK_RADIUS= 80.0;
const GLfloat PI=3.141592653589793;

// DIMENSIONES MANECILLAS
const GLint sy = 75;
const GLint my = 60;
const GLint hy = 50;

// SEGUNDOS, MINUTOS, HORAS
int hour;
int minute;
int second;

//ANGULOS MANECILLA
double secondAngle = 0 , minuteAngle = 0 , hourAngle = 0;

//PINTAR CIRCULO
void PaintCircle( float radius)
{
    float theta=0.0f;
    float px=0.0f;
    float py=0.0f;
     
  
    //PINTAR CIRCULO   
           
    glBegin(GL_POLYGON);
   
     for (int i=0;i<360;i++)
    {
        theta= i*PI/180;
        px= radius * cos(theta);
        py= radius * sin (theta);
        
        glVertex2f(px,py);
    }
    glEnd();

   
}

/*AÑADIR MARCAS AL RELOJO **************************************************************************************/
void addMarks()
{
    double x,y;
    int count=0;
    glPointSize(10.0);

    
    for(double i=0 ; i<=2*PI ; i+=PI/30.0) {
		if(i==PI/2.0) {
			x = CLOCK_RADIUS;
		}
		else if(i==3*PI/2.0) {
			x = -CLOCK_RADIUS;
		}
		else {
			x = CLOCK_RADIUS *sin(i);
		}
		y =  CLOCK_RADIUS *cos(i);
		if(count%5==0) {
			glPointSize(7.0);
			glBegin(GL_POINTS);
                            glVertex2f(x , y);
                         glEnd();
			
		}
		else {
			glPointSize(3.0);
                        glBegin(GL_POINTS);
                          glVertex2f(x , y);
                         glEnd();
		}
		count++;
	}
}/******************************************************************************************************/


// PINTAR RELOJ*****************************************************************************************/
void PaintClock()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f); 
    PaintCircle(CLOCK_RADIUS+10);

    
    glColor3f(1.0f, 1.0f, 1.0f); 
    PaintCircle(CLOCK_RADIUS+5);
     
   //Se añadan marcas horarias
    glColor3f(1.0,0.0,0.0);
    addMarks();
 
    
    //SEGUNDERO. calculamos angulo segundos y pintamos segundero
    secondAngle = second * 6;
    
  //rotar coseno en sentido agujas reloj
    glRotatef(-secondAngle, 0.0f, 0.0f, 1.0f);

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); 
    glVertex2i(0,0);
    glVertex2i(0,sy);
    glEnd();
    
    glLoadIdentity(); 

   //MANECILLAS MINUTOS
    minuteAngle = minute * 6;
    glRotatef(-minuteAngle, 0.0f, 0.0f, 1.0f);
    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2i(0,0);
    glVertex2i(0,my);
    glEnd();
    
    glLoadIdentity(); 

    hourAngle = (hour + hour/60.0) * 30;
    glRotatef(-hourAngle, 0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2i(0,0);
    glVertex2i(0,hy);
    glEnd();
    
    glLoadIdentity(); 
    glFlush();
}

void redimensiona(GLsizei largo, GLsizei alto)
{
    
    glViewport(0, 0, largo, alto);    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if (largo <= alto)
       gluOrtho2D(-v_x, v_x, -v_y * alto / largo, v_y * alto / largo);
    else
     gluOrtho2D(-v_x * largo / alto, v_x * largo / alto, -v_y, v_y);
       
   
}

void advance(int n)
{
 
     time_t hora = time(0);
     struct tm *datahora = localtime(&hora);
     
     hour = datahora->tm_hour;
     minute = datahora->tm_min;
     second = datahora->tm_sec;
     
     glutPostRedisplay(); 
     glutTimerFunc(1000, advance, 0);     
}


void init_gl(int argc, char *argv[]) {

       	glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(400,400);
	glutInitWindowSize(500,600);
     	glutCreateWindow("Reloj Actividad Grupal 2021/2022");
        //Matriz de molelo y vista
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluOrtho2D(-100,100,-100,100);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

int main(int argc, char** argv) {

    
    //inicialiciones de glut		
	init_gl (argc, argv);
	glutDisplayFunc(PaintClock);
	glutReshapeFunc(redimensiona);
	glutTimerFunc(1000, advance, 0);
	glutMainLoop();
	return 0;
}
