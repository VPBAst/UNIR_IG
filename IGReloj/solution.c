/* 
 * File:   solution.c
 * Date: November, 2021
 * Actividad: IGReloj - trabajo grupal
 * Authores: SILVA PEREZ, OLIVER
 * 			 LOSPITAO RUIZ, RUTH
 *           PATALLO BERMUDEZ, VICTOR 
 *           GARCÍA GARIJO, ALBERTO
 *           BELDA DIEPPA, RUYMAN   
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

/**
* Funcion que pinta un circulo dado un radio
*/
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

/**
* Funcion que añade al dibujo del reloj los puntos que representan marcas horarias
*/
void addMarks()
{
    double x,y;
    int count=0;
    glPointSize(10.0); 

    // Genera los puntos: //
    // La función glVertex se usa entre las llamadas a glBegin() y glEnd()
	// para especificar vértices de punto, línea / y polígono //
	
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
			// Puntos que indican las horas //
			glPointSize(7.0);
			glBegin(GL_POINTS);
            glVertex2f(x , y);
            glEnd();
		}
		else {
			// Puntos que indican los minutos //
			glPointSize(3.0);
            glBegin(GL_POINTS);
        	glVertex2f(x , y);
            glEnd();
		}
		count++;
	}
}


/**
* Funcion que pinta el reloj 
*
* Para pintar las manecillas se usa la funcion glRotatef (GLfloat angulo, GLfloat x, GLfloat y, GLfloat z);
* El ángulo de rotacion es siempre un ángulo en sentido en contra de las agujas del reloj y medido en grados.  
* Si por ejemplo quisieramos rotar 90 grados la recta del segundero sobre el eje Z el codigo sería el siguiente:
* glRotatef(-90, 0.0f, 0.0f, 1.0f);
*
*/ 
void PaintClock()
{
	// Pintamos el primer circulo de color rojo //
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f); 
    PaintCircle(CLOCK_RADIUS+10);
    
    // Pintamos un segundo circulo de menor radio y color blanco 
	// que representa la esfera central del reloj//
    glColor3f(1.0f, 1.0f, 1.0f); 
    PaintCircle(CLOCK_RADIUS+5);
     
    //Añadimos las marcas horarias y de minutos en color rojo //
    glColor3f(1.0f, 0.0f, 0.0f);
    addMarks();
 
    // MANECILLA SEGUNDERO //
       
    secondAngle = second * 6;// Calculamos el angulo de rotacion en funcion de los segundos //
    glRotatef(-secondAngle, 0.0f, 0.0f, 1.0f); // Indicamos la rotacion //
    glBegin(GL_LINES); // Indicamos que vamos a pintar una linea //
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2i(0,0); // Coordenadas origen de la linea //
    glVertex2i(0,sy); // Coordenadas destino (sy: es el tamaño de la linea) //
    glEnd();
    glLoadIdentity(); 

    // MANECILLA MINUTO // 
   
    minuteAngle = minute * 6; // Calculamos el angulo de rotacion en funcion de los segundos //
    glRotatef(-minuteAngle, 0.0f, 0.0f, 1.0f); // Indicamos la rotacion //
    glLineWidth(5);
    glBegin(GL_LINES); // Indicamos que vamos a pintar una linea //
    glColor3f(0.0f, 1.0f, 0.0f); 
    glVertex2i(0,0); // origen de la linea de minutos //
    glVertex2i(0,my); // Coordenadas destino (my: tamaño de la recta de minutos) //
    glEnd();
    glLoadIdentity(); 
	
	// MANECILLA HORA //
	
    hourAngle = (hour + hour/60.0) * 30; // Calculamos el angulo de rotacion en funcion de la hora //
    glRotatef(-hourAngle, 0.0f, 0.0f, 1.0f);// Indicamos la rotacion //
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2i(0,0); // origen de la recta de minutos //
    glVertex2i(0,hy); // my: tamaño de la recta de horas //
    glEnd();
    glLoadIdentity(); 
    
    glFlush();
}

/**
* Funcion de redimension llamada desde glutReshapeFunc 
*/ 
void redimensiona(GLsizei largo, GLsizei alto)
{
    
    glViewport(0, 0, largo, alto);    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Reconfiguracion de las coordenadas del mundo en funcion de largo y ancho de la ventana //
    if (largo <= alto)
       gluOrtho2D(-v_x, v_x, -v_y * alto / largo, v_y * alto / largo);
    else
     gluOrtho2D(-v_x * largo / alto, v_x * largo / alto, -v_y, v_y);
       
   
}

/** 
* Funcion que consulta la hora del sistema y fuerza el repintado del reloj
* para actualizar la posicion de las manecillas
*/
void advance(int n)
{
 	 // Consultamos la hora del sistema //
     time_t hora = time(0);
     struct tm *datahora = localtime(&hora);
     
     // Actualizamos los valores de las variables globales que contienen hora, minuto y segundo //
     hour = datahora->tm_hour;
     minute = datahora->tm_min;
     second = datahora->tm_sec;
     
     // Forzamos a que se ejecute la funcion asignada a glutDisplayFunc() 
	 // en nuestro caso displayClock //
     glutPostRedisplay(); 
     
     // Temporizador que espera 1 segundo y realiza la llamada de nuevo //
     glutTimerFunc(1000, advance, 0);     
}

/*
* Inicializacion de OPenGL y Glut 
*/
void init_gl(int argc, char *argv[]) {
		
		// Inicializamos Glut //
       	glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
        
        // Posicion, tamaño, titulo de la ventana //
		glutInitWindowPosition(400,400);
		glutInitWindowSize(500,600);
     	glutCreateWindow("Reloj Actividad Grupal 2021/2022");
     	
        //Matriz de molelo y vista//
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        //Proyeccion ortogonal en 2D, establece coordenadas del mundo que mostraremos en ventana //
        gluOrtho2D(-100,100,-100,100);
        // Color de fondo de la ventana (en blanco) //
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

/**
* Funcion principal ejecutada al inicio del programa
*/
int main(int argc, char** argv) {

    
    //Llamada a la inicialicion de OpenGL y Glut	//
	init_gl (argc, argv);
	
	// Llamada a la funcion que dibuja el reloj //
	glutDisplayFunc(PaintClock);
	
	// Llamada a la funcion a ejecutar cuando se redeimensiona la ventana //
	glutReshapeFunc(redimensiona);
	
	// Funcion temporizador, que llama a la funcion que repinta las manecillas del reloj cada segundo//
	glutTimerFunc(1000, advance, 0);
	
	// Funcion bucle para mantener la ventana ventana abierta y que no se nos cierre al terminar la ejecucion //
	glutMainLoop();
	
	return 0;
}

