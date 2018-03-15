//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************

#ifdef __MACH__ // Incluimos las librerías necesarias para que funcione en OSX
	#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos.h"


using namespace std;

// tamaño de los ejes
//const int AXIS_SIZE=5000;
//Variables globales para controlar teclas
unsigned char tecla='1'; /* objeto visualizado por defecto */
int tipo = 0;
char modo ;
// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//Objetos piramide y cubo
_piramide piramide(1,1.6);
_cubo cubo(1);
//Objeto cubodesplazado
_cubo cubodesplazado(1,1,1,1);

//Objetos tronco y tetraedro
_tetraedro tetraedro(2);
_tronco_piramide tronco_piramide(1.5, 0.5, 1.5);
//**************************************************************************
//
//***************************************************************************

void clear_window(){

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{/*
GLfloat Vertices[8][3]= {{5,0,0},{4,4,0},{0,5,0},{-4,4,0},{-5,0,0},{-4,-4,0},{0,-5,0},{4,-4,0}};
int i;

glColor3f(0,1,0);
glPointSize(4);

glBegin(GL_POINTS);
for (i=0;i<8;i++){
	glVertex3fv((GLfloat *) &Vertices[i]);
	}
glEnd();

*/
switch (tipo) {

	case 1://Puntos
		if(modo=='c')
			cubo.draw_puntos(1.0,0,0,12);
		else if(modo == 't')
			cubodesplazado.draw_puntos(1.0,0,0,12);
		else if(modo == 'e')
			tronco_piramide.draw_puntos(1.0,0,0,12);
		else if(modo == 'p')
			piramide.draw_puntos(1.0,0,0,12);
		break;
	case 2://Alambre
		if(modo=='c')
			cubo.draw_aristas(1.0,0,0,1.0);
			else if(modo == 't')
				cubodesplazado.draw_aristas(1.0,0,0,1.0);
			else if(modo == 'e')
				tronco_piramide.draw_aristas(1.0,0,0,1.0);
			else if(modo == 'p')
			piramide.draw_aristas(1.0,0,0,1.0);
		break;
	case 3://Solido
	if(modo=='c')
		cubo.draw_solido(1.0,0,0);
		else if(modo == 't')
			cubodesplazado.draw_solido(1.0,0,0);
		else if(modo == 'e')
			tronco_piramide.draw_solido(1.0,0,0);
		else if(modo == 'p')
			piramide.draw_solido(1.0,0,0);
		break;
	case 4://Ajedrez
	if(modo=='c')
		cubo.draw_solido_ajedrez(1.0,0,0,0,1.0,0);
		else if(modo == 't')
			cubodesplazado.draw_solido_ajedrez(1.0,0,0,0,1.0,0);
		else if(modo == 'e')
			tronco_piramide.draw_solido_ajedrez(1.0,0,0,0,1.0,0);
		else if(modo == 'p')
			piramide.draw_solido_ajedrez(1.0,0,0,0,1.0,0);//Para cambiar color r1,g1,b1,r2,g2,b2
		break;
	case 5://Colores Aleatorios de las caras
		if(modo=='c')
			cubo.draw_solido_colores();
			else if(modo == 't')
				cubodesplazado.draw_solido_colores();
			else if(modo == 'e')
				tronco_piramide.draw_solido_colores();
			else if(modo == 'p')
				piramide.draw_solido_colores();
			break;
			case 6://Puntos circulates
				if(modo=='c')
					cubo.draw_puntos_circulares(1.0,0,0,12);
					else if(modo == 't')
						cubodesplazado.draw_puntos_circulares(1.0,0,0,12);
					else if(modo == 'e')
						tronco_piramide.draw_puntos_circulares(1.0,0,0,12);
					else if(modo == 'p')
						piramide.draw_puntos_circulares(1.0,0,0,12);
					break;



}


}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();//Intercambia buffer mas rapidos para la visualizacion
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{
	/*switch (toupper(Tecla1))
	{
		case 'Q':
			exit(0);
			break;

		case 'P':
			tipo=0; //puntos
			break;

		case 'E':
			tipo=1; //Alambre
			break;

		case 'S':
			tipo=2; //Sólido
			break;
		case 'A':
			tipo=3; //Ajedrez
			break;

		case '1':	//Cubo
			modo='c';
			break;

		case '2':	//Piramide
			modo='p';
			break;
		case '3':	//Cubo desplazado
				modo='t';
				break;

		case '4':	//Tronco
			modo='e';
			break;

	}*/


	if (toupper(Tecla1)=='Q') exit(0);
	else if (Tecla1 == '1' || Tecla1 == '2' || Tecla1 == '3' || Tecla1 == '4' || Tecla1 == '5' || Tecla1 == '6')
		tipo = (int)Tecla1 - 48;
	else if (toupper(Tecla1)=='C')
		modo = 'c';
	else if (toupper(Tecla1)=='P')
		modo = 'p';
	else if (toupper(Tecla1)=='T')
		modo = 't';
	else if (toupper(Tecla1)=='E')
		modo = 'e';

	glutPostRedisplay();


}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){//Usados para la camara
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=5;
Window_height=5;
Front_plane=10;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=2*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
//
change_projection();
//
glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(UI_window_width,UI_window_height);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("Práctica 1");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}