#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string>
#include <ctime>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#define PI 3.1415927

//posicion del objeto en wall-e
float posOX;
float posOZ;

//variable par cambiar la velocidad de wall-e
double velocidad=0.1;

int pegar=0;

//Definimos variables
int rotate_y=0;
int rotate_x=0;
int rotate_z=0;
//se necesitan para validar el cielo
int posX, posZ;
int posX1, posZ1;

GLuint texture[10];
GLUquadricObj* cylinder; 
GLUquadricObj *disk;  
GLUquadricObj *sphere;	
GLuint tex[0];
//variables para sonidos
Mix_Chunk *Pared = NULL;
Mix_Chunk *Basura = NULL;
Mix_Chunk *Llanta = NULL;
Mix_Chunk *Recoge = NULL;

void pauseAnimation(void);
void pauseAnimation2(void);
void startAnimation2(void);
unsigned int textureID;

int instruccion=0;
int instru=0,instru1=0;
int botV=0;
// variables que representan direccion de la camara
float lx=0.0f,lz=-1.0f;
// XZ posicion de la camara
float x=0.0f,z=5.0f;

float rx=0.0f, rz=1.5f;

int up =0;
int dw=0;
int lf =0;
int rg =0;

GLfloat movermano=0.0f; //varible para el movimiento de las manos
int frameNumber;  
int frameNumber2; 
float escala=0.0;
int estado=0;
float r_esfera=2.7;
char text[32];

int ESD=0;
int toca, tocaB, tocaL, tocaR;

int camaX = 0;
GLfloat X = 0.0f;
GLfloat Y = 0.0f;
int camaZ = 4;
GLfloat Z = 0.0f;

void musica(void){

}


// para ocultar los objetos
int oculto=0;
float oculto1[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float oculto2[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float oculto3[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float idBa[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};	
float idB[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float idBa2[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};	


extern "C" {
    #include "texturas/texture.c"
}

extern "C" {
    #include "texturas/cielo.c"
}
extern "C" {
    #include "texturas/reciclar.c"
}
extern "C" {
    #include "texturas/sueloA.c"
}
extern "C" {
    #include "texturas/cieloAzul.c"
}

extern "C" {
    #include "texturas/cesped.c"
}
extern "C" {
    #include "texturas/ventanam2.c"
}
extern "C" {
    #include "texturas/acera11.c"
}
extern "C" {
    #include "texturas/calle1.c"
}
extern "C" {
    #include "texturas/cajas.c"
}
extern "C" {
    #include "texturas/botella.c"
}
extern "C" {
    #include "texturas/coca.c"
}
extern "C" {
    #include "texturas/papel.c"
}
extern "C" {
    #include "texturas/vidrio.c"
}
void define_textura(struct textura_calle textuN)
{
	glGenTextures(1,&textureID);   				// Genera la textura 1 con la variable texture
	glBindTexture(GL_TEXTURE_2D,textureID);		// Asocia la variable texture como GL_TEXTURE_2D
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  // Asigna Gl_MODULATE A GL_TEXTURE_ENV_MODE
	gluBuild2DMipmaps( GL_TEXTURE_2D, textuN.bytes_per_pixel,textuN.width,textuN.height,GL_RGB,GL_UNSIGNED_BYTE,textuN.pixel_data );
		// Define las propiedasdes de la textura 2D asociando la textura exportada gimp_image a la GL_TEXTURE_2D
};

void define_textura(struct textura_acera textuN)
{
	glGenTextures(1,&textureID);   				// Genera la textura 1 con la variable texture
	glBindTexture(GL_TEXTURE_2D,textureID);		// Asocia la variable texture como GL_TEXTURE_2D
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  // Asigna Gl_MODULATE A GL_TEXTURE_ENV_MODE
	gluBuild2DMipmaps( GL_TEXTURE_2D, textuN.bytes_per_pixel,textuN.width,textuN.height,GL_RGB,GL_UNSIGNED_BYTE,textuN.pixel_data );
		// Define las propiedasdes de la textura 2D asociando la textura exportada gimp_image a la GL_TEXTURE_2D
};

void define_textura(struct textura_edificio textuN)
{
	glGenTextures(1,&textureID);   				// Genera la textura 1 con la variable texture
	glBindTexture(GL_TEXTURE_2D,textureID);		// Asocia la variable texture como GL_TEXTURE_2D
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  // Asigna Gl_MODULATE A GL_TEXTURE_ENV_MODE
	gluBuild2DMipmaps( GL_TEXTURE_2D, textuN.bytes_per_pixel,textuN.width,textuN.height,GL_RGB,GL_UNSIGNED_BYTE,textuN.pixel_data );
		// Define las propiedasdes de la textura 2D asociando la textura exportada gimp_image a la GL_TEXTURE_2D
};

void define_textura(struct textura_suelo textuN)
{
	glGenTextures(1,&textureID);   				// Genera la textura 1 con la variable texture
	glBindTexture(GL_TEXTURE_2D,textureID);		// Asocia la variable texture como GL_TEXTURE_2D
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  // Asigna Gl_MODULATE A GL_TEXTURE_ENV_MODE
	gluBuild2DMipmaps( GL_TEXTURE_2D, textuN.bytes_per_pixel,textuN.width,textuN.height,GL_RGB,GL_UNSIGNED_BYTE,textuN.pixel_data );
		// Define las propiedasdes de la textura 2D asociando la textura exportada gimp_image a la GL_TEXTURE_2D
};

void define_textura(struct textura_cielo textuN)
{
	glGenTextures(1,&textureID);   				// Genera la textura 1 con la variable texture
	glBindTexture(GL_TEXTURE_2D,textureID);		// Asocia la variable texture como GL_TEXTURE_2D
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  // Asigna Gl_MODULATE A GL_TEXTURE_ENV_MODE
	gluBuild2DMipmaps( GL_TEXTURE_2D, textuN.bytes_per_pixel,textuN.width,textuN.height,GL_RGB,GL_UNSIGNED_BYTE,textuN.pixel_data );
		// Define las propiedasdes de la textura 2D asociando la textura exportada gimp_image a la GL_TEXTURE_2D
};

void define_textura(struct textura_reciclar textuN)
{
	glGenTextures(1,&textureID);   				// Genera la textura 1 con la variable texture
	glBindTexture(GL_TEXTURE_2D,textureID);		// Asocia la variable texture como GL_TEXTURE_2D
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  // Asigna Gl_MODULATE A GL_TEXTURE_ENV_MODE
	gluBuild2DMipmaps( GL_TEXTURE_2D, textuN.bytes_per_pixel,textuN.width,textuN.height,GL_RGB,GL_UNSIGNED_BYTE,textuN.pixel_data );
		// Define las propiedasdes de la textura 2D asociando la textura exportada gimp_image a la GL_TEXTURE_2D
};
void define_textura(struct textura_cieloA  textuN)
{
	glGenTextures(1,&textureID);   				// Genera la textura 1 con la variable texture
	glBindTexture(GL_TEXTURE_2D,textureID);		// Asocia la variable texture como GL_TEXTURE_2D
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  // Asigna Gl_MODULATE A GL_TEXTURE_ENV_MODE
	gluBuild2DMipmaps( GL_TEXTURE_2D, textuN.bytes_per_pixel,textuN.width,textuN.height,GL_RGB,GL_UNSIGNED_BYTE,textuN.pixel_data );
		// Define las propiedasdes de la textura 2D asociando la textura exportada gimp_image a la GL_TEXTURE_2D
};

void define_textura(struct textura_sueloA  textuN)
{
	glGenTextures(1,&textureID);   				// Genera la textura 1 con la variable texture
	glBindTexture(GL_TEXTURE_2D,textureID);		// Asocia la variable texture como GL_TEXTURE_2D
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  // Asigna Gl_MODULATE A GL_TEXTURE_ENV_MODE
	gluBuild2DMipmaps( GL_TEXTURE_2D, textuN.bytes_per_pixel,textuN.width,textuN.height,GL_RGB,GL_UNSIGNED_BYTE,textuN.pixel_data );
		// Define las propiedasdes de la textura 2D asociando la textura exportada gimp_image a la GL_TEXTURE_2D
};

void define_textura(struct textura_cesped  textuN)
{
	glGenTextures(1,&textureID);   				// Genera la textura 1 con la variable texture
	glBindTexture(GL_TEXTURE_2D,textureID);		// Asocia la variable texture como GL_TEXTURE_2D
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  // Asigna Gl_MODULATE A GL_TEXTURE_ENV_MODE
	gluBuild2DMipmaps( GL_TEXTURE_2D, textuN.bytes_per_pixel,textuN.width,textuN.height,GL_RGB,GL_UNSIGNED_BYTE,textuN.pixel_data );
		// Define las propiedasdes de la textura 2D asociando la textura exportada gimp_image a la GL_TEXTURE_2D
};
//caja
void define_textura(struct textura_cajas  textuN)
{
	glGenTextures(1,&textureID);   				// Genera la textura 1 con la variable texture
	glBindTexture(GL_TEXTURE_2D,textureID);		// Asocia la variable texture como GL_TEXTURE_2D
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  // Asigna Gl_MODULATE A GL_TEXTURE_ENV_MODE
	gluBuild2DMipmaps( GL_TEXTURE_2D, textuN.bytes_per_pixel,textuN.width,textuN.height,GL_RGB,GL_UNSIGNED_BYTE,textuN.pixel_data );
		// Define las propiedasdes de la textura 2D asociando la textura exportada gimp_image a la GL_TEXTURE_2D
};

void define_textura(struct textura_botellas  textuN)
{
	glGenTextures(1,&textureID);   				// Genera la textura 1 con la variable texture
	glBindTexture(GL_TEXTURE_2D,textureID);		// Asocia la variable texture como GL_TEXTURE_2D
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  // Asigna Gl_MODULATE A GL_TEXTURE_ENV_MODE
	gluBuild2DMipmaps( GL_TEXTURE_2D, textuN.bytes_per_pixel,textuN.width,textuN.height,GL_RGB,GL_UNSIGNED_BYTE,textuN.pixel_data );
		// Define las propiedasdes de la textura 2D asociando la textura exportada gimp_image a la GL_TEXTURE_2D
};
void define_textura(struct textura_papels  textuN)
{
	glGenTextures(1,&textureID);   				// Genera la textura 1 con la variable texture
	glBindTexture(GL_TEXTURE_2D,textureID);		// Asocia la variable texture como GL_TEXTURE_2D
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  // Asigna Gl_MODULATE A GL_TEXTURE_ENV_MODE
	gluBuild2DMipmaps( GL_TEXTURE_2D, textuN.bytes_per_pixel,textuN.width,textuN.height,GL_RGB,GL_UNSIGNED_BYTE,textuN.pixel_data );
		// Define las propiedasdes de la textura 2D asociando la textura exportada gimp_image a la GL_TEXTURE_2D
};
void define_textura(struct textura_vidrios  textuN)
{
	glGenTextures(1,&textureID);   				// Genera la textura 1 con la variable texture
	glBindTexture(GL_TEXTURE_2D,textureID);		// Asocia la variable texture como GL_TEXTURE_2D
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  // Asigna Gl_MODULATE A GL_TEXTURE_ENV_MODE
	gluBuild2DMipmaps( GL_TEXTURE_2D, textuN.bytes_per_pixel,textuN.width,textuN.height,GL_RGB,GL_UNSIGNED_BYTE,textuN.pixel_data );
		// Define las propiedasdes de la textura 2D asociando la textura exportada gimp_image a la GL_TEXTURE_2D
};
void define_textura(struct textura_cocas  textuN)
{
	glGenTextures(1,&textureID);   				// Genera la textura 1 con la variable texture
	glBindTexture(GL_TEXTURE_2D,textureID);		// Asocia la variable texture como GL_TEXTURE_2D
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  // Asigna Gl_MODULATE A GL_TEXTURE_ENV_MODE
	gluBuild2DMipmaps( GL_TEXTURE_2D, textuN.bytes_per_pixel,textuN.width,textuN.height,GL_RGB,GL_UNSIGNED_BYTE,textuN.pixel_data );
		// Define las propiedasdes de la textura 2D asociando la textura exportada gimp_image a la GL_TEXTURE_2D
};
int pos2;
int intento[16];
void info(void){
glPushMatrix();
    char text41[70];
    sprintf(text41, "Presione letra i, luego tecla izquierda para ver informacion");
    glRasterPos3f( X-10,20+instru,Z);
    for(int i = 0; text41[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text41[i]);
    glPopMatrix();
}
 void info1(void){
glPushMatrix();
    char text42[70];
    sprintf(text42, "Presione letra i , luego tecla izquierda para ver informacion");
    glRasterPos3f( X-2,1.5+idBa2[pos2],Z);
    for(int i = 0; text42[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text42[i]);
    glPopMatrix();
}

// angulo de rotación
float angulo = 0.0f;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_spot_dir[] = { 0.0f, 0.0f, 0.0f};
const GLfloat light_attenuation[] = {1.0f};
GLfloat light_position[] =       { 0.0f, 10.0f, 0.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };
 

int ok=0;

//funcion para poder recoger la basura

int contar[16];
int pos;

 int pos1=0;
 
void recoger_basura(double xi, double xf,  double Zn, double Xn,double zi,double zf, int id){
	if(Xn>xf and Xn<xi and Zn>zf and Zn<zi ){
        tocaR=1;
        oculto2[id]={1};
        contar[id]={1};
        pos =id;
        
        pauseAnimation();
        frameNumber=0;
        }}
       
int toca2;       
//Coalicion para los arboles
void colicion3(double xi, double xf,  double Zn, double Xn,double zi,double zf, int id){
    if(Xn>xf and Xn<xi and Zn>zf and Zn<zi ){
        oculto3[id]={1};
        pos2 =id;
        if(oculto1[id]<1.1){

			 toca2=1;
			pauseAnimation();
			startAnimation2();
			oculto1[id]={escala};
			
		}else{
			pauseAnimation();
			pauseAnimation2();
			frameNumber2=0;
			escala=0.0;
			r_esfera=2.7;

		}
}}
        
//Coalicion Para edificios
void colicion2(double xi, double xf,  double Zn, double Xn,double zi,double zf){
	if(Xn>xf and Xn<xi and Zn>zf and Zn<zi ){
		  pauseAnimation();
		  toca=1;}
}
int count=0;


//Coalicion Para los basureros
void colicion_basurero(double xi, double xf,  double Zn, double Xn,double zi,double zf,int ID){
	if(Xn>xf and Xn<xi and Zn>zf and Zn<zi ){
		pegar=1;
		tocaB=1;
       if(ID==1){   
			idBa[pos]={1};
		}else if(ID==2){
				idBa[pos]={2};
		}else if(ID==3){
				idBa[pos]={3};
		}
			
        pauseAnimation();}
}
//Coalicion Para edificios primera linea
void colicion(double xi, double xf,  double Zn, double Xn,double Zi){
	if(Xn>xf and Xn<xi and (((abs(Zi))-abs(Zn))<=0.1) ){
		  pauseAnimation();
          toca=1;}}

//funcion para generar el cilindro
void draw_cylinder(GLfloat radius,
                   GLfloat height,
                   GLubyte R,
                   GLubyte G,
                   GLubyte B)
{
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the tube */
    
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            glVertex3f(x, y , 0.0);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
        glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */
    glColor3ub(R,G,B);
    glBegin(GL_POLYGON);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
    glEnd();
}

//funcion para generar las llantas de wall-e
void llanta(GLfloat radius,
                   GLfloat height,
                   GLubyte R,
                   GLubyte G,
                   GLubyte B)
{
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the tube */
    
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            glVertex3f(x, y , 0.0);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
        glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */
   glColor3ub(R,G,B);
    glBegin(GL_LINES);
    angle = 0.0;
        for(double l=0;l<2*PI;l+=(2*PI/24 )) {
            x = radius * cos(l);
            y = radius * sin(l);
            glVertex3f(x, y , height);
           
            glVertex3f(0, 0.0, height);
        }  
    glEnd();  
}

//funcion para generar una caja de cereal
 void contenedor(){
	tex[1] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
   (
       "texturas/ceral.png",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
       SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
   );
   
	
	glPushMatrix();
	glColor3f(0.871, 0.722, 0.529);
	glBegin(GL_QUADS);
		glVertex3f(1, 0.0f, -1);
		glVertex3f(1, 0.0f, 1);
		glVertex3f(1, 5.0f, 1);
		glVertex3f(1, 5.0f, -1);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0.871, 0.722, 0.529);
	glBegin(GL_QUADS);
		glVertex3f(-1, 0.0f, -1);
		glVertex3f(-1, 0.0f, 1);
		glVertex3f(-1, 5.0f, 1);
		glVertex3f(-1, 5.0f, -1);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.871, 0.722, 0.529);
	glBegin(GL_QUADS);
		glVertex3f(-1, 0.0f, -1);
		glVertex3f(1, 0.0f, -1);
		glVertex3f(1, 5.0f, -1);
		glVertex3f(-1, 5.0f, -1);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.871, 0.722, 0.529);
	glBegin(GL_QUADS);
		glVertex3f(-1, 5.0f, -1);
		glVertex3f(1, 5.0f, -1);
		glVertex3f(1, 5.0f, 1);
		glVertex3f(-1, 5.0f, 1);
	glEnd();
	glPopMatrix();
	
	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex[1]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(-1, 0.0f, 1);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(1, 0.0f, 1);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(1, 5.0f, 1);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(-1, 5.0f, 1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

//para generar los tallos del arbol
void orificio(){
    glColor3f(0.000, 0.000, 0.000);
    glPushMatrix();
    glTranslatef(0,0.05,0);
	glRotatef(-90, 1.0, 0.0, 0.0);
    disk = gluNewQuadric();
	gluDisk(disk, 0.0, 0.2, 200, 200);
    glPopMatrix();
}
//dibuja el arbol 1
void arbol1(){
	//TALLO
    glPushMatrix();
    glColor3f(0.627, 0.322, 0.176);
	glRotatef(-90, 1.0, 0.0, 0.0);
	draw_cylinder(0.1, 0.8, 211, 211, 211);
    glPopMatrix();	

    glPushMatrix();
    glColor3f(0.133, 0.545, 0.133);
    glTranslatef(0,1.0,0);
	glutSolidSphere(0.4,20,20);
    glPopMatrix();	
}
//dbuja el arbol 2
void arbol2(){
    glPushMatrix();
    glColor3f(0.627, 0.322, 0.176);
	glRotatef(-90, 1.0, 0.0, 0.0);
	draw_cylinder(0.1, 0.6, 211, 211, 211);
    glPopMatrix();	

    glPushMatrix();
    glColor3f(0.133, 0.545, 0.133);
	glTranslatef(0,0.6,0);
    glRotated(-90.0, 1.0, 0.0, 0.0);
    glutSolidCone(0.5,0.6,40,40);
    glPopMatrix();
}
//dibuja el arbol 3
void arbol3(){
    glPushMatrix();
    glColor3f(0.627, 0.322, 0.176);
	glRotatef(-90, 1.0, 0.0, 0.0);
	draw_cylinder(0.1, 0.6, 211, 211, 211);
    glPopMatrix();	

    glPushMatrix();
    glColor3f(0.133, 0.545, 0.133);
	glTranslatef(0,0.6,0);
    glRotated(-90.0, 1.0, 0.0, 0.0);
    glutSolidCone(0.4,0.5,40,40);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.133, 0.545, 0.133);
	glTranslatef(0,0.9,0);
    glRotated(-90.0, 1.0, 0.0, 0.0);
    glutSolidCone(0.3,0.3,40,40);
    glPopMatrix();
  
    glPushMatrix();
    glColor3f(0.133, 0.545, 0.133);
	glTranslatef(0,1.1,0);
    glRotated(-90.0, 1.0, 0.0, 0.0);
    glutSolidCone(0.2,0.3,40,40);
    glPopMatrix();
}

//Con esta funcion se dibujan los edificios
void conte(int tex2){
	glPushMatrix();
	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	define_textura(textura_ace);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-1.85, 0.01f, -1.85);
		glTexCoord2f(50.0f, 0.0f);glVertex3f(1.85, 0.01f, -1.85);
		glTexCoord2f(50.0f, 50.0f);glVertex3f(1.85, 0.01f, 1.85);
		glTexCoord2f(0.0f, 50.0f);glVertex3f(-1.85, 0.01f, 1.85);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	define_textura(textura_fll);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
		glTexCoord2f(10.0f, 20.0f);glVertex3f(-1, 0.0f, 1);
		glTexCoord2f(0.0f, 20.0f);glVertex3f(1, 0.0f, 1);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(1, 5.0f, 1);
		glTexCoord2f(10.0f, 0.0f);glVertex3f(-1, 5.0f, 1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(1, 0.0f, -1);
		glTexCoord2f(0.0f, 20.0f);glVertex3f(1, 0.0f, 1);
		glTexCoord2f(10.0f, 20.0f);glVertex3f(1, 5.0f, 1);
		glTexCoord2f(10.0f, 0.0f);glVertex3f(1, 5.0f, -1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	glPushMatrix();
	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-1, 0.0f, -1);
		glTexCoord2f(10.0f, 0.0f);glVertex3f(-1, 0.0f, 1);
		glTexCoord2f(10.0f, 20.0f);glVertex3f(-1, 5.0f, 1);
		glTexCoord2f(0.0f, 20.0f);glVertex3f(-1, 5.0f, -1);
	glEnd();
	glDisable(GL_TEXTURE_2D);	
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-1, 0.0f, -1);
		glTexCoord2f(10.0f, 0.0f);glVertex3f(1, 0.0f, -1);
		glTexCoord2f(10.0f, 20.0f);glVertex3f(1, 5.0f, -1);
		glTexCoord2f(0.0f, 20.0f);glVertex3f(-1, 5.0f, -1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0.871, 0.722, 0.529);
	glBegin(GL_QUADS);
		glVertex3f(-1, 5.0f, -1);
		glVertex3f(1, 5.0f, -1);
		glVertex3f(1, 5.0f, 1);
		glVertex3f(-1, 5.0f, 1);
	glEnd();
	glPopMatrix();
		
}
void botellaV(){
	  glColor3f(0.000, 0.749, 1.000);
    glPushMatrix();
    
    glTranslatef(5,0,0);
	glRotatef(-90, 1.0, 0.0, 0.0);

	cylinder = gluNewQuadric();
	gluQuadricDrawStyle( cylinder, GLU_FILL );
	gluCylinder( cylinder, 0.650, 0.650, 7.0, 211, 211);
    glPopMatrix();
    glColor3f(0.561, 0.737, 0.561);
    glPushMatrix();
    
    glTranslatef(5,0,0);
	glRotatef(-90, 1.0, 0.0, 0.0);

	cylinder = gluNewQuadric();
	gluQuadricDrawStyle( cylinder, GLU_FILL );
	gluCylinder( cylinder, 0.750, 0.750, 7.0, 211, 211);
    glPopMatrix();
    
    glPushMatrix();
    cylinder = gluNewQuadric();
	gluQuadricDrawStyle( cylinder, GLU_FILL );
    glTranslatef(5,7,0);
	glRotatef(-180,0.0, 1.0, 1.0);
	gluCylinder( cylinder, 0.650, 0.20, 3.50, 211, 211);
    glPopMatrix();
    //segunda capa
    glColor3f(0.561, 0.737, 0.561);
    glPushMatrix();
    cylinder = gluNewQuadric();
	gluQuadricDrawStyle( cylinder, GLU_FILL );
    glTranslatef(5,7,0);
	glRotatef(-180,0.0, 1.0, 1.0);
	gluCylinder( cylinder, 0.750, 0.30, 3.50, 211, 211);
    glPopMatrix();

}
// se dibuna las manos de wall-e
void manos(){
	
	
	//braso
	glPushMatrix();
    glColor3f(0.502, 0.502, 0.502);
    glScalef(0.2,1,6);
    glutSolidCube(0.5);
    glPopMatrix();
    
    //union brazo-cancho
    glPushMatrix();
    glColor3f(0.502, 0.502, 0.502);
    glTranslatef(0.0,0,1.5);
    glScalef(1,4,1);
    glutSolidCube(0.2);
    glPopMatrix();
    
    //gancho superior
    glPushMatrix();
    glColor3f(0.502, 0.502, 0.502);
    glTranslatef(0.0,0.3,2);
    glScalef(1,1,4);
    glutSolidCube(0.2);
    glPopMatrix();
    
    //gancho inferior
    glPushMatrix();
    glColor3f(0.502, 0.502, 0.502);
    glTranslatef(0.0,-0.3,2);
    glScalef(1,1,4);
    glutSolidCube(0.2);
    glPopMatrix();     
}
//se dibuja el robot
void Wall(){
   //cuello
    //abajo
    glPushMatrix();
    glColor3f(0.502, 0.502, 0.502);
    glTranslatef(0,3.5,0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    draw_cylinder(0.5, 0.4, 216, 211, 211);
    glPopMatrix(); 
    
    //delgado inclinado
    glPushMatrix();
    glColor3f(0.502, 0.502, 0.502);
    glTranslatef(0,3.8,0);
    glRotatef(-60, 1.0, 0.0, 0.0);
    draw_cylinder(0.2, 0.6, 216, 211, 211);
    glPopMatrix(); 
    
    //delgado inclinado
    glPushMatrix();
    glColor3f(0.502, 0.502, 0.502);
    glTranslatef(0,4.8,0);
    glRotatef(-315, 1.0, 0.0, 0.0);
    draw_cylinder(0.2, 0.7, 216, 211, 211);
    glPopMatrix(); 
    
    
    //delgado arriba
    glPushMatrix();
    glColor3f(0.502, 0.502, 0.502);
    glTranslatef(0,4.7,0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    draw_cylinder(0.3, 0.3, 216, 211, 211);
    glPopMatrix(); 
    
    //delgado mas arriba
    glPushMatrix();
    glColor3f(0.502, 0.502, 0.502);
    glTranslatef(0,5.0,0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    draw_cylinder(0.2, 0.2, 216, 211, 211);
    glPopMatrix(); 
    
    //union de los ojos
    glPushMatrix();
    glColor3f(0.502, 0.502, 0.502);
    glTranslatef(0.0,5.3,0.0);
    glScalef(1,0.5,0.5);
    glutSolidCube(0.5);
    glPopMatrix();
    
    
    
    ///////////////ojos
    
    //der
    glPushMatrix();
    glColor3f(1.000, 0.643, 0.000);
    glTranslatef(0.5,5.3,-0.5);
    cylinder= gluNewQuadric();
	gluCylinder(cylinder,0.2,0.4,1.5,211,211);
    glPopMatrix();
    
    //parte trasera
    glPushMatrix();
    glColor3f(1.000, 0.643, 0.000);
    glTranslatef(0.5,5.3,-0.5);
    disk= gluNewQuadric();
	gluDisk(disk,0.0,0.2,200,200);	
    glPopMatrix();
    
    //gegro
    glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(0.5,5.3,1);
	glutSolidSphere(0.39,20,20);
	glPopMatrix();
	//blanco
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(0.5,5.3,1.3);
	glutSolidSphere(0.2,20,20);
	glPopMatrix();
    
    //izq
    //amarillo
    glPushMatrix();
    glColor3f(1.000, 0.643, 0.000);
    glTranslatef(-0.5,5.3,-0.5);
    cylinder= gluNewQuadric();
	gluCylinder(cylinder,0.2,0.4,1.5,211,211);
    glPopMatrix();
    
    //parte trasera
    glPushMatrix();
    glColor3f(1.000, 0.643, 0.000);
    glTranslatef(-0.5,5.3,-0.5);
    disk= gluNewQuadric();
	gluDisk(disk,0.0,0.2,200,200);	
    glPopMatrix();
    //negro
    glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(-0.5,5.3,1);
	glutSolidSphere(0.39,20,20);
	glPopMatrix();
	//blanco
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(-0.5,5.3,1.3);
	glutSolidSphere(0.2,20,20);
	glPopMatrix();
    
    /////////////////sosten de llantas////////////
    //sosten der frente
    glPushMatrix();
    glColor3f(0.184, 0.310, 0.310);
    glTranslatef(2,1.0,1.5);
    glRotatef(90, 0.0, 1.0, 0.0);
    draw_cylinder(0.25, 0.5, 216, 211, 211);
    glPopMatrix(); 
    
    //sosten izq frente
    glPushMatrix();
    glColor3f(0.184, 0.310, 0.310);
    glTranslatef(-2,1.0,1.5);
    glRotatef(-90, 0.0, 1.0, 0.0);
    draw_cylinder(0.25, 0.5, 216, 211, 211);
    glPopMatrix(); 
    
    
    //sosten der atras
    glPushMatrix();
    glColor3f(0.184, 0.310, 0.310);
    glTranslatef(2,1.5,-1.5);
    glRotatef(90, 0.0, 1.0, 0.0);
    draw_cylinder(0.25, 1, 216, 211, 211);
    glPopMatrix(); 
    
    //sosten izq atras
    glPushMatrix();
    glColor3f(0.184, 0.310, 0.310);
    glTranslatef(-2,1.5,-1.5);
    glRotatef(-90, 0.0, 1.0, 0.0);
    draw_cylinder(0.25, 1, 216, 211, 211);
    glPopMatrix(); 
    
    /////////////////////////////////llantas/////////////
    
    //llantas izq atras
    glPushMatrix();
    glColor3f(0.184, 0.310, 0.310);
    glTranslatef(-2.25,1.5,-1.5);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glRotatef( rotate_z, 0.0, 0.0, 1.0 );
    llanta(1.5, 0.75, 216, 211, 211);
    glPopMatrix(); 
    
    //llantas der atras
    glPushMatrix();
    glColor3f(0.184, 0.310, 0.310);
    glTranslatef(2.25,1.5,-1.5);
    glRotatef(90, 0.0, 1.0, 0.0);
    glRotatef( rotate_z, 0.0, 0.0, 1.0 );
    llanta(1.5, 0.75, 216, 211, 211);
    glPopMatrix(); 
    
    
    //llantas izq frente
    glPushMatrix();
    glColor3f(0.184, 0.310, 0.310);
    glTranslatef(-2.25,1.0,1.5);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glRotatef( rotate_z, 0.0, 0.0, 1.0 );
    llanta(1.0, 0.25, 216, 211, 211);
    glPopMatrix(); 
    
    //llantas der frente
    glPushMatrix();
    glColor3f(0.184, 0.310, 0.310);
    glTranslatef(2.25,1.0,1.5);
    glRotatef(90, 0.0, 1.0, 0.0);
    glRotatef( rotate_z, 0.0, 0.0, 1.0 );
    llanta(1.0, 0.25, 216, 211, 211);
    glPopMatrix(); 
    
    
    ////////////////////manos/////////////
    
    glPushMatrix();
		glTranslatef(0,0,movermano);
		//sosten der
		glPushMatrix();
			glTranslatef(2,3.2,0);
			glRotatef(90, 0.0, 1.0, 0.0);
			draw_cylinder(0.05, 0.25, 216, 211, 211);
		glPopMatrix(); 
		//mano
		glPushMatrix();
			glTranslatef(2.25,3.2,1.4);
			manos();
		glPopMatrix();
    glPopMatrix();
    
    //sosten izq
    glPushMatrix();
    if(ESD==1){
		//manguera
		glPushMatrix();
		glColor3f(0.184, 0.310, 0.310);
		glTranslatef(0,3.6,-3);
		glRotatef(-90, 1.0, 0.0, 0.0);
		draw_cylinder(0.1, 0.5, 216, 211, 211);
		glPopMatrix();
		
		glPushMatrix();
		glColor3f(0.184, 0.310, 0.310);
		glTranslatef(0,3.95,-3);
		draw_cylinder(0.1, 1.15, 216, 211, 211);
		glPopMatrix();
		
		//bomba
		glPushMatrix();
		glColor3f(0.184, 0.310, 0.310);
		glTranslatef(0,1,-3);
		glRotatef(-90, 1.0, 0.0, 0.0);
		draw_cylinder(1, 2.3, 216, 211, 211);
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(0,1,-3);
		glRotatef(-90, 1.0, 0.0, 0.0);
		draw_cylinder(0.1, 0.2, 216, 211, 211);
		glPopMatrix();
		
		
		
		
		}
    glPopMatrix();
    //tetera
    glPushMatrix();
    glTranslatef(0,0,-movermano+1);
    if(ESD==1){
		
		
		
		
		
		glPushMatrix();
		//glColor3f(0.184, 0.310, 0.310);
		glColor3f(0.502, 0.502, 0.502);
		glTranslatef(-2.3,3.1,3.0);
		draw_cylinder(0.3, 1, 216, 211, 211);
		glPopMatrix();
		
		glPushMatrix();
		glColor3f(0.184, 0.310, 0.310);
		glTranslatef(-2.3,3.1,3.9);
		glRotatef(30, 1.0, 0.0, 0.0);
		draw_cylinder(0.3, 0.6, 216, 211, 211);
		
		glPushMatrix();
		glTranslatef(0,0,0.6);
		cylinder = gluNewQuadric();
		gluQuadricDrawStyle( cylinder, GLU_FILL );
		gluCylinder( cylinder, 0.30, 0.80, 1.2, 211, 211);
		glPopMatrix();
		glPushMatrix();
		
		
		glTranslatef(0,0,1.8);
		
		double i, cx,cy;
    
		glBegin(GL_POLYGON);
		glColor3f(0.174, 0.300, 0.300);
		for (i=0;i<=(2*M_PI); i+=0.01)
		{
			cx=0.8*cos(i) +0;
			cy=0.8*sin(i) +0;
			glVertex2f(cx,cy); 
			
		}
		 glEnd();
		 glPopMatrix();
		glPopMatrix();
		
		
		
		
		//gotas de agua
		glPushMatrix();
		glColor3f(0.000, 0.0, 6.5500);
		glTranslatef(-2.2,r_esfera,5.5);
		glutSolidSphere(0.09,100,100);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0.000, 0.0, 6.5500);
		glTranslatef(-2.2,r_esfera,5.4);
		glutSolidSphere(0.09,100,100);
		glPopMatrix();
		
		glPushMatrix();
		glColor3f(0.000, 0.0, 6.5500);
		glTranslatef(-2.0,r_esfera,5.6);
		glutSolidSphere(0.09,100,100);
		glPopMatrix();
		
		glPushMatrix();
		glColor3f(0.000, 0.0, 6.5500);
		glTranslatef(-2.0,r_esfera,5.4);
		glutSolidSphere(0.09,100,100);
		glPopMatrix();
		
		glPushMatrix();
		glColor3f(0.000, 0.0, 6.5500);
		glTranslatef(-2.4,r_esfera,5.6);
		glutSolidSphere(0.09,100,100);
		glPopMatrix();
		
	}
    //glTranslatef(0,0,-movermano+1);
    glPushMatrix();
    glTranslatef(-2,3.2,0);
    glRotatef(-90, 0.0, 1.0, 0.0);
    draw_cylinder(0.05, 0.25, 216, 211, 211);
    glPopMatrix(); 
    //mano
    glPushMatrix();
    glTranslatef(-2.25,3.2,1.4);
    manos();
    glPopMatrix();
    
    glPopMatrix();
    ///////////////////////////////cuerpo///////////////////////
    glPushMatrix();
    glTranslatef(0.0,2.0,0.0);
    glScalef(1,0.75,1);
    glColor3f(1.000, 0.643, 0.000);
    glutSolidCube(4);
    glPopMatrix();
    
    glPushMatrix();
    if(ESD==0){
		
		glBegin(GL_POLYGON);
		glColor3f(0.502, 0.502, 0.502);        
        glVertex3f(1.5,1.4,2.0); 
        glVertex3f(1.5,1.4,3.5);
        glVertex3f(-1.5,1.4,3.5);
        glVertex3f(-1.5,1.4,2.0);
		glEnd();
		glBegin(GL_POLYGON);
		glColor3f(0.502, 0.502, 0.502);        
        glVertex3f(1.5,1.4,2.0);
        glVertex3f(1.5,1.4,3.5);
        glVertex3f(1.5,3.4,2.0);
        
		glEnd();
		
		glBegin(GL_POLYGON);
		glColor3f(0.502, 0.502, 0.502);        
        glVertex3f(-1.5,1.4,2.0);
        glVertex3f(-1.5,1.4,3.5);
        glVertex3f(-1.5,3.4,2.0);
        
		glEnd();
      
		
		
		}
		glPopMatrix();
    
   
    
    glPushMatrix();
    glTranslatef(1.6,3.6,0.0);
    glScalef(2,0.5,10);
    glColor3f(0.502, 0.502, 0.502);
    glutSolidCube(0.4);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1.6,3.6,0.0);
    glScalef(2,0.5,10);
    glColor3f(0.502, 0.502, 0.502);
    glutSolidCube(0.4);
    glPopMatrix();
}
//se dibuja un cilindro
void barril(){
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	draw_cylinder(0.3, 0.8, 211, 211, 211);
    glPopMatrix();
}
//se dibuja un basureo 
void basurero(){
	glPushMatrix();
	glColor3f(1,0,0);
	glTranslatef(1,0,0);
	barril();
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0.255, 0.412, 0.882);
	glTranslatef(0,0,0);
	barril();
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0.196, 0.804, 0.196);
	glTranslatef(-0.5,0,0);
	barril();
	glPopMatrix();
	
	}
// se dibuja una lata
void Lata (float r,float al){
    glPushMatrix();
    glColor3f( 	0.000, 0.000, 0.804);
    
    glTranslatef(0,0,0);
	glRotatef(-90, 1.0, 0.0, 0.0);

	cylinder = gluNewQuadric();
	gluCylinder( cylinder, 1.5, 1.5, 5.0, 211, 211);
    glPopMatrix();
    
    glColor3f(0.412, 0.412, 0.412);
    glPushMatrix();
    glTranslatef(0,4.950,0);
	glRotatef(-90, 1.0, 0.0, 0.0);
    disk = gluNewQuadric();
	gluDisk(disk, 0.0, 1.45, 200, 200);
    glPopMatrix();
    
    glColor3f(0.000, 0.000, 0.000);
    glPushMatrix();
    glTranslatef(0,4.950,0.7);
	glRotatef(-90, 1.0, 0.0, 0.0);
    disk = gluNewQuadric();

	gluDisk(disk, 0.0, 0.25, 200, 200);
    glPopMatrix();
   
}

//se dibuja una bolsa de basura
void bolsa(){
	glPushMatrix();
	glColor3f(0, 0, 0);
    glTranslatef(0,0,0);
    glScalef(0.1,0.3,0.1);
    glutSolidSphere(2,100,100);
    glPopMatrix();
    glPushMatrix();
	glColor3f(0, 0, 0);
    glTranslatef(0,0.65,0);
    glScalef(0.03,0.03,0.03);
    glutSolidSphere(2,100,100);
    glPopMatrix();
	
}
//Se dibuja una botella plastica
void botella(){
	  glColor3f(0.000, 0.749, 1.000);
    glPushMatrix();
	  
    
    glTranslatef(5,0,0);
	glRotatef(-90, 1.0, 0.0, 0.0);

	cylinder = gluNewQuadric();
	gluQuadricDrawStyle( cylinder, GLU_FILL );
	gluCylinder( cylinder, 0.650, 0.650, 7.0, 211, 211);
    glPopMatrix();
    
    glPushMatrix();
    cylinder = gluNewQuadric();
	gluQuadricDrawStyle( cylinder, GLU_FILL );
    glTranslatef(5,7,0);
	glRotatef(-180,0.0, 1.0, 1.0);
	gluCylinder( cylinder, 0.650, 0.20, 3.50, 211, 211);
    glPopMatrix();
        glColor3f( 	0.000, 0.392, 0.000);
    glPushMatrix();
    glTranslatef(5,10.5,0);
	glRotatef(-180,0.0, 1.0, 1.0);
	gluCylinder( cylinder, 0.250, 0.250, 0.60, 211, 211);

    glPopMatrix();	
}

//se dibuja el cielo
void cielo(){
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	define_textura(textura_sky);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-20.0f, 0.0f, -20.0f);
		glTexCoord2f(4.0f, 0.0f);glVertex3f(-20.0f, 20.0f, -20.0f);
		glTexCoord2f(4.0f, 4.0f);glVertex3f( 20.0f, 20.0f, -20.0f);
		glTexCoord2f(0.0f, 4.0f);glVertex3f( 20.0f, 0.0f, -20.0f);
	glEnd();
	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-20.0f, 20.0f, -20.0f);
		glTexCoord2f(30.0f, 0.0f);glVertex3f(-20.0f, 20.0f, 20.0f);
		glTexCoord2f(30.0f, 30.0f);glVertex3f( 20.0f, 20.0f, 20.0f);
		glTexCoord2f(0.0f, 30.0f);glVertex3f( 20.0f, 20.0f, -20.0f);
	glEnd();
	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-20.0f, 0.0f, 20.0f);
		glTexCoord2f(4.0f, 0.0f);glVertex3f(-20.0f, 20.0f, 20.0f);
		glTexCoord2f(4.0f, 4.0f);glVertex3f( 20.0f, 20.0f, 20.0f);
		glTexCoord2f(0.0f, 4.0f);glVertex3f( 20.0f, 0.0f, 20.0f);
	glEnd();
	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-20.0f, 0.0f, -20.0f);
		glTexCoord2f(4.0f, 0.0f);glVertex3f(-20.0f, 20.0f, -20.0f);
		glTexCoord2f(4.0f, 4.0f);glVertex3f(-20.0f, 20.0f, 20.0f);
		glTexCoord2f(0.0f, 4.0f);glVertex3f(-20.0f, 0.0f, 20.0f);
	glEnd();	

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(20.0f, 0.0f, -20.0f);
		glTexCoord2f(4.0f, 0.0f);glVertex3f(20.0f, 20.0f, -20.0f);
		glTexCoord2f(4.0f, 4.0f);glVertex3f(20.0f, 20.0f, 20.0f);
		glTexCoord2f(0.0f, 4.0f);glVertex3f(20.0f, 0.0f, 20.0f);
	glEnd();	
	
	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

//se dibuja el cielo del segundo esceniaro
void cieloA(){
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	define_textura(textura_skyA);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-20.0f, 0.0f, -20.0f);
		glTexCoord2f(4.0f, 0.0f);glVertex3f(-20.0f, 20.0f, -20.0f);
		glTexCoord2f(4.0f, 4.0f);glVertex3f( 20.0f, 20.0f, -20.0f);
		glTexCoord2f(0.0f, 4.0f);glVertex3f( 20.0f, 0.0f, -20.0f);
	glEnd();
	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-20.0f, 20.0f, -20.0f);
		glTexCoord2f(30.0f, 0.0f);glVertex3f(-20.0f, 20.0f, 20.0f);
		glTexCoord2f(30.0f, 30.0f);glVertex3f( 20.0f, 20.0f, 20.0f);
		glTexCoord2f(0.0f, 30.0f);glVertex3f( 20.0f, 20.0f, -20.0f);
	glEnd();
	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-20.0f, 0.0f, 20.0f);
		glTexCoord2f(4.0f, 0.0f);glVertex3f(-20.0f, 20.0f, 20.0f);
		glTexCoord2f(4.0f, 4.0f);glVertex3f( 20.0f, 20.0f, 20.0f);
		glTexCoord2f(0.0f, 4.0f);glVertex3f( 20.0f, 0.0f, 20.0f);
	glEnd();
	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-20.0f, 0.0f, -20.0f);
		glTexCoord2f(4.0f, 0.0f);glVertex3f(-20.0f, 20.0f, -20.0f);
		glTexCoord2f(4.0f, 4.0f);glVertex3f(-20.0f, 20.0f, 20.0f);
		glTexCoord2f(0.0f, 4.0f);glVertex3f(-20.0f, 0.0f, 20.0f);
	glEnd();	

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(20.0f, 0.0f, -20.0f);
		glTexCoord2f(4.0f, 0.0f);glVertex3f(20.0f, 20.0f, -20.0f);
		glTexCoord2f(4.0f, 4.0f);glVertex3f(20.0f, 20.0f, 20.0f);
		glTexCoord2f(0.0f, 4.0f);glVertex3f(20.0f, 0.0f, 20.0f);
	glEnd();	
	
	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
//se dibujan las cajas de carton
void cajas(void){
	 glPushMatrix();
     glColor3f(1,0.8,0.3);
     glTranslatef(0,0,0);
     glutSolidCube(1.5);
     glPopMatrix();
     
     glPushMatrix();
     glTranslatef(0.0,0,2.0);
     glutSolidCube(1.5);
     glPopMatrix();
     
     glPushMatrix();
     glTranslatef(0.0,1,1.0);

     glutSolidCube(1.5);
     glPopMatrix();
	
	}
	
// se dibuja una bola de palpel
void pelota (){
	glColor3f(1,1,1);
    glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTranslatef(0,7,0);
	sphere = gluNewQuadric();
	gluQuadricTexture(sphere,tex[2]);
	gluQuadricDrawStyle( sphere, GLU_FILL);
	gluQuadricNormals( sphere, GLU_SMOOTH);
	gluQuadricOrientation( sphere, GLU_OUTSIDE);
	glutSolidSphere( 2, 200, 200);
	glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

//se crea el texto informacion con la lata
void infolata(){

	glTranslatef(-15.0f, 0.0f, 20.0f);
	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	define_textura(textura_coca);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	    glTexCoord2f(0.0f, 1.0f);glVertex3f(-2, -1.0f, -0.5);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-2, 6.0f, -0.5);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(4, 6.0f, -0.5);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(4, -1.0f, -0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f( 4 , 4.5 , 10.0);
    sprintf(text, "Datos Curioso.");
    for(int i = 0; text[i] != '\0'; i++) 
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4.0 , 4.0 , 10.0);
    sprintf(text, "Más de mil millones personas en el mundo carecen de ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4 , 3.5 , 10.0);
    sprintf(text, "acceso al agua potable, 5.000 personas mueren cada ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4 , 3 , 10.0);
    sprintf(text, "dia debido a esta carencia.");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4 , 2 , 10.0);
    sprintf(text, "Informacion del objeto.");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4 , 1.5 , 10.0);
    sprintf(text, "Cada habitante consume una media de 155 envases de");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4 , 1 , 10.0);
    sprintf(text, "este tipo, que estan hechas principalmente de aluminio. ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4 , 0.5 , 10.0);
    sprintf(text, "Para fabricarlas se gasta una gran cantidad de energía, y,");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4 , -0.0 , 10.0);
    sprintf(text, "ademas, si  no se  reciclan  tardan  mas  de 10 años en ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4 , -0.5 , 10.0);
    sprintf(text, "degradarse en la naturaleza, originando óxido de hierro.");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	glRasterPos3f( 4 , -1.0 , 10.0);
    sprintf(text, " Si se reciclan se pueden convertir en nuevos productos");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4.0 , -1.5, 10.0);
    sprintf(text, "de aluminio, o también se pueden reutilizar en casa y que");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4.0 , -2.0, 10.0);
    sprintf(text, "sirvan como un recipiente para los lápices,hacer adornos ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4.0 , -2.5, 10.0);
    sprintf(text, " con las anillas");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos3f( 1.0 , 5, 10.0);
    sprintf(text, "Presionar numero 5 mas espacio para salir");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
  
	glColor3f(1.0f, 1.0f, 1.0f);
}
//se crea el texto informacion con la bottela de plastico
void infoplastico(){
	
	glTranslatef(-15.0f, 0.0f, 20.0f);
	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	define_textura(textura_botella);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	    glTexCoord2f(0.0f, 1.0f);glVertex3f(-2, -1.0f, -0.5);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-2, 6.0f, -0.5);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(4, 6.0f, -0.5);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(4, -1.0f, -0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f( 3.5 , 4.5 , 10.0);
    sprintf(text, "Datos Curioso.");
    for(int i = 0; text[i] != '\0'; i++) 
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3.50 , 4 , 10.0);
    sprintf(text, "14 mil millones libras de basura se vierten al mar");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3.5 , 3.5 , 10.0);
    sprintf(text, " cada año. La mayor parte es plástico ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3.5 , 3.0 , 10.0);
    sprintf(text, " Más de 1 millón de aves marinasy 100.000 mamíferos");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3.5 , 2.5 , 10.0);
    sprintf(text, " marinos mueren por la contaminación cada año");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3.5 , 2.0 , 10.0);
    sprintf(text, "Informacion del objeto.");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3.5 , 1.5 , 10.0);
    sprintf(text, "Como sabemos, el plástico es un derivado del petróleo,");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3.5 , 1.0 , 10.0);
    sprintf(text, "pero lo que ignoramos es la cantidad de este que gastamos");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3.5 , 0.50 , 10.0);
    sprintf(text, "en elaborar botellas.Una única botella necesita un cuarto");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3.5 , 0.0 , 10.0);
    sprintf(text, " de su volumen en petróleo para su fabricación. En un año,");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3.5 , -0.50 , 10.0);
    sprintf(text, "se estima que se utilizan 17 millones de barriles de este");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	glRasterPos3f( 3.5 , -1.0 , 10.0);
    sprintf(text, " combustiblepara elaborar botellas, una barbaridad. Además,");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3.50 , -1.50, 10.0);
    sprintf(text, " otro inconveniente importante es que si las tiramos pueden");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3.50 , -2.0, 10.0);
    sprintf(text, " tardar más de mil años en desintegrarse.");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos3f( 1.0 , -2.1, 10.0);
    sprintf(text, "Presionar numero 5 mas espacio para salir");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	glColor3f(1.0f, 1.0f, 1.0f);
}

//se crea el texto informacion con el papel
void infopapel(){
	glTranslatef(-15.0f, 0.0f, 20.0f);
	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	define_textura(textura_papel);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	    glTexCoord2f(0.0f, 1.0f);glVertex3f(-2, -1.0f, -0.5);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-2, 6.0f, -0.5);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(4, 6.0f, -0.5);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(4, -1.0f, -0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f( 4 , 5 , 10.0);
    sprintf(text, "Datos Curioso.");
    for(int i = 0; text[i] != '\0'; i++) 
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4.0 , 4.5 , 10.0);
    sprintf(text, "15.8 millones de toneladas de materiales de lectura");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4 , 4 , 10.0);
    sprintf(text, "(libros y revistas) además de muchos otros productos");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4 , 3.5 , 10.0);
    sprintf(text, "de papelería se desecharon en 2010.");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4 , 3 , 10.0);
    sprintf(text, "Informacion del objeto.");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4 , 2.5 , 10.0);
    sprintf(text, "La industria papelera ( papel y pasta de papel) por lo");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
     
    glRasterPos3f( 4 , 2 , 10.0);
    sprintf(text, "general es altamente contaminante y provoca muchos ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4 , 1.5 , 10.0);
    sprintf(text, "impactos negativos en el medio ambiente y en la ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4 , 1 , 10.0);
    sprintf(text, "salud de la población cercana a las mismas.");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4 , 0.5 , 10.0);
    sprintf(text, "La contaminación del aire con cloro, compuestos de");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	glRasterPos3f( 4 , -0 , 10.0);
    sprintf(text, " azufres, dióxinas, entre otros.Además del deterioro");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4.0 , -0.5, 10.0);
    sprintf(text, "del suelo, el consumo y la contaminación del agua ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4.0 , -1.0, 10.0);
    sprintf(text, "así como la muerte de la fauna acuática, provoca ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4.0 , -1.5, 10.0);
    sprintf(text, "lluvia ácida, deforestación, afecta a la agricultura ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 4.0 , -2.0, 10.0);
    sprintf(text, "y otras actividades rurales, genera enfermedades ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos3f( 1.0 , -2.1, 10.0);
    sprintf(text, "Presionar numero 5 mas espacio para salir");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	glColor3f(1.0f, 1.0f, 1.0f);
}

//se crea el texto informacion con la botella de  vidrio
void infobotellav(){
    glTranslatef(-16.0f, 0.0f, 20.0f);
    glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	define_textura(textura_vidrio);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	    glTexCoord2f(0.0f, 1.0f);glVertex3f(-1.0, -1.0f, -0.5);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-1.0, 6.0f, -0.5);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(3.5, 6.0f, -0.5);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(3.5, -1.0f, -0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f( 3 , 5 , 10.0);
    sprintf(text, "Datos Curioso.");
    for(int i = 0; text[i] != '\0'; i++) 
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
     
    glRasterPos3f( 3.0 , 4.5 , 10.0);
    sprintf(text, "El reciclaje previno que 85 millones de toneladas de");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , 4 , 10.0);
    sprintf(text, "materiales fueran eliminados en el 2010, frente a los");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , 3.5 , 10.0);
    sprintf(text, "  18 millones de toneladas en 1980.");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
 
    glRasterPos3f( 3 , 2.5 , 10.0);
    sprintf(text, "Informacion del objeto.");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , 2 , 10.0);
    sprintf(text, "Los envases hechos con este material son los más respetuosos");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
     
    glRasterPos3f( 3 , 1.5 , 10.0);
    sprintf(text, "con el medio ambiente pues, aunque su degradación es lenta,");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , 1 , 10.0);
    sprintf(text, "durante el proceso no se libera ninguna sustancia perjudicial.");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , 0.50 , 10.0);
    sprintf(text, "Además,su proceso de creación es barato,ya que las sustancias");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , -0.0 , 10.0);
    sprintf(text, "necesarias para ello son abundantes. Otra ventaja del vidrio ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	glRasterPos3f( 3 , -0.5 , 10.0);
    sprintf(text, "es que es reciclable,no se pierde nada durante el proceso.");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3.0 , -1.0, 10.0);
    sprintf(text, "Otro punto a su favor es que nosotros mismos podemos reutilizarlo,");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3.0 , -1.50, 10.0);
    sprintf(text, "teniendo vidas infinitas, pudiendo utilizar los tarros, por ejemplo,");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3.0 , -2.0, 10.0);
    sprintf(text, "como vasos para casa o como recipientes para congelar comida.");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos3f( 1.0 , -2.1, 10.0);
    sprintf(text, "Presionar numero 5 mas espacio para salir");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	glColor3f(1.0f, 1.0f, 1.0f);
}
//se crea el texto informacion con la bolsa
void infobolsa(){
	
	glTranslatef(-15.0f, 0.0f, 20.0f);
	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	define_textura(textura_caja);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	    glTexCoord2f(0.0f, 1.0f);glVertex3f(-2, -1.0f, -0.5);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-2, 6.0f, -0.5);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(4, 6.0f, -0.5);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(4, -1.0f, -0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f( 3 , 5 , 10.0);
    sprintf(text, "Datos Curioso.");
    for(int i = 0; text[i] != '\0'; i++) 
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3.0 , 4.5 , 10.0);
    sprintf(text, "El reciclaje previno que 85 millones de toneladas de");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , 4 , 10.0);
    sprintf(text, "materiales fueran eliminados en el 2010, frente a los");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , 3.5 , 10.0);
    sprintf(text, "18 millones de toneladas en 1980.");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , 2.5 , 10.0);
    sprintf(text, "Informacion del objeto.");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , 2 , 10.0);
    sprintf(text, "Son uno de los residuos cotidianos más contaminantes y de");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , 1.5 , 10.0);
    sprintf(text, "los que menos se reciclan, solamente alrededor de un 11 por");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , 1 , 10.0);
    sprintf(text, "ciento. Además, hay que tener en cuenta que el plástico es ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , 0.5 , 10.0);
    sprintf(text, "un derivado del petróleo, por lo que para su creación se ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , 0 , 10.0);
    sprintf(text, "necesita mucha energía. Otro hándicap es su lentísima degradación:");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	glRasterPos3f( 3 , -0.5 , 10.0);
    sprintf(text, "tardan más de 150 años en descomponerse, y mientras tanto ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3.0 , -1, 10.0);
    sprintf(text, "contaminan enormemente, sobre todo el mar, donde van a parar. ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3.0 , -1.5, 10.0);
    sprintf(text, "la mayoría. Muchísimas aves y animales marinos, como tortugas ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3.0 , -2, 10.0);
    sprintf(text, "o delfines, mueren  cada año al quedar atrapados en ellas. ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos3f( 1.0 , -2.5, 10.0);
    sprintf(text, "Presionar numero 5 mas espacio para salir");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
  glColor3f(1.0f, 1.0f, 1.0f);
}

//se crea el texto informacion con la caja
void infoCajas(){
  glTranslatef(-15.0f, 0.0f, 20.0f);
	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	define_textura(textura_caja);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	    glTexCoord2f(0.0f, 1.0f);glVertex3f(-2, -1.0f, -0.5);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-2, 6.0f, -0.5);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(4, 6.0f, -0.5);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(4, -1.0f, -0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f( 3 , 4 , 10.0);
    sprintf(text, "Datos Curioso.");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , 3.5 , 10.0);
    sprintf(text, "La contaminacion es una de las principales causas globales");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , 3 , 10.0);
    sprintf(text, "de mortalidad, afectando a más de 100 millones de personas,");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , 2.5 , 10.0);
    sprintf(text, "y comparable a enfermedades  globales como el paludismo");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , 2 , 10.0);
    sprintf(text, "o VIH.");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , 1 , 10.0);
    sprintf(text, "Informacion del objeto.");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , 0.5 , 10.0);
    sprintf(text, "El vertimiento de reciduos de  carton que van a el drenage");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , 0 , 10.0);
    sprintf(text, "pueden ocacionar taponamientos en su  vertice y ocasionar ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , -0.5 , 10.0);
    sprintf(text, "inundaciones. El  aumento  de  reciduos de carton en los ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , -1 , 10.0);
    sprintf(text, "cuerpos de agua afectan en el desarrollo  de la fauna que ");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glRasterPos3f( 3 , -1.5 , 10.0);
    sprintf(text, "en esta habita");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos3f( 1.0 , -2, 10.0);
    sprintf(text, "Presionar numero 5 mas espacio para salir");
    for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	glColor3f(1.0f, 1.0f, 1.0f);
}

void instrucciones(){
			//PANEL DE INSTRUCCIONES
		glPushMatrix();
		glColor3f(0.941, 1.000, 0.941);
		glRasterPos3f( -16 , 10 , 10);
		sprintf(text, "Instrucciones del juego Robot Trash");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		
		glRasterPos3f( -16 , 9 , 10);
		sprintf(text, "Movimiento: Teclas de desplazamiento");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

		glRasterPos3f( -16 , 8 , 10);
		sprintf(text, "Cambio de camara: Tecla 1 y 2");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

		glRasterPos3f( -16 , 7 , 10);
		sprintf(text, "Velocidad del personaje");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

		glRasterPos3f( -16 , 6 , 10);
		sprintf(text, "Velocidad normal: Tecla 7");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	 
		glRasterPos3f( -16, 5 , 10);
		sprintf(text, "Velocidad rapida: Tecla 8");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	 
		glRasterPos3f( -16 , 4 , 10);
		sprintf(text, "Velocidad modo Dios: Tecla 9");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	 
		glRasterPos3f( -16 , 3 , 10);
		sprintf(text, "Objetivo: Recojer basura y ubicar la basura");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

		glRasterPos3f( -16, 2 , 10);
		sprintf(text, "en su respectivo basurero");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

		glRasterPos3f( -16 , 1 , 10);
		sprintf(text, "Mostrar informacion de nuevo: i mas tecla izquierda");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		
		glRasterPos3f( -16 , 0 , 10);
		sprintf(text, "Mostrar informacion de objeto letra i");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

		glRasterPos3f( -16 , -1 , 10);
		sprintf(text, "Volver: 5 o 4  mas espacio");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		
		glRasterPos3f( -16 , -2 , 10);
		sprintf(text, "Iniciar: Tecla espaciadora nos permite iniciar y detener la animacion");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		
		glRasterPos3f( -16 , -3 , 10);
		sprintf(text, "Salir: Debe presionar la tecla ESC");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		
		glRasterPos3f( -16 , -4 , 10);
		sprintf(text, "Observacion: Debe Seguir las indicaciones anterior mensionadas");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		glRasterPos3f( -16 , -5 , 10);
		sprintf(text, "Si da defectos, presionar tecla 5 o 4 mas espacio y continuara donde se quedo");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		glPopMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
	}
//informacion curiosa de arboles
void infoarbol(){
			//PANEL DE INSTRUCCIONES
		glPushMatrix();
		glColor3f(0,0,1);
		glRasterPos3f( -14 , 8.5 , 10);
		sprintf(text, "Informacion");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		
		glRasterPos3f( -14 , 7 , 10);
		sprintf(text, " Los árboles son los organismos vivos más antiguos de la Tierra");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

		glRasterPos3f( -14 , 6 , 10);
		sprintf(text, "que han sobrevivido al paso del tiempo.");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

		glRasterPos3f( -14 , 5 , 10);
		sprintf(text, "Una familia de cuatro miembros requiere oxígeno de dos árboles.");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

		glRasterPos3f( -14 , 4 , 10);
		sprintf(text, "Los árboles necesitan aproximadamente 2.000 litros de agua cada año.");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	 
		glRasterPos3f( -14, 3 , 10);
		sprintf(text, "Un solo árbol elimina una tonelada de dióxido de carbono durante");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	 
		glRasterPos3f( -14 , 2 , 10);
		sprintf(text, "toda su vida. No mueren de vejez, en realidad mueren a causa de ");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	 
		glRasterPos3f( -14 , 1 , 10);
		sprintf(text, "insectos, gente, o enfermedad.El árbol vivo más viejo del mundo ");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

		glRasterPos3f( -14, 0 , 10);
		sprintf(text, "tiene 4.847 años, se llama Matusalén, referencia al personaje ");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

		glRasterPos3f( -14 , -1 , 10);
		sprintf(text, "bíblico más viejo. Se encuentra en el Bosque Nacional Inyo, en ");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		
		glRasterPos3f( -14 , -2 , 10);
		sprintf(text, "el centro de California, Estados Unidos.");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		glColor3f(1.0f, 0.0f, 0.0f);
		glRasterPos3f( -14.0 , -4, 10.0);
		sprintf(text, "Presionar numero 4 mas espacio para salir");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		glColor3f(1.0f, 1.0f, 1.0f);
		glPopMatrix();
	}
//informacion curiosa de arboles
void infoarbol1(){
			//PANEL DE INSTRUCCIONES
		glPushMatrix();
		glColor3f(0,1,0);
		glRasterPos3f( -14 , 7.5 , 10);
		sprintf(text, "Informacion");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		
		glRasterPos3f( -14 , 5.5 , 10);
		sprintf(text, "Los árboles solamente crecen hasta donde su capacidad de sostenerse");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

		glRasterPos3f( -14 , 4.5 , 10);
		sprintf(text, "les permite.");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

		glRasterPos3f( -14 , 3.5 , 10);
		sprintf(text, "Reducen la contaminación por ruido y mejoran la calidad del agua");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

		glRasterPos3f( -14 , 2.5 , 10);
		sprintf(text, "Se estima que unos 20 árboles producen una tonelada de papel. ");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	 
		glRasterPos3f( -14, 1.5 , 10);
		sprintf(text, "Por lo tanto, la industria editorial estadounidense consume ");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	 
		glRasterPos3f( -14 , 0.5 , 10);
		sprintf(text, "32 millones de árboles al año. ");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	 
		glRasterPos3f( -14 , -0.5 , 10);
		sprintf(text, "Existen aproximadamente 60 mil o 70 mil especies de árboles,");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

		glRasterPos3f( -14, -1.5 , 10);
		sprintf(text, "los cuales se pueden clasificar por infinidad de criterios ");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

		glRasterPos3f( -14 , -2.5 , 10);
		sprintf(text, "desde su uso en jardinería hasta el de la madera. Existen dos" );
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		
		glRasterPos3f( -14 , -3.5 , 10);
		sprintf(text, "tipos de árboles los que dan frutos y los que no, se clasifican");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

		glRasterPos3f( -14 , -4.5 , 10);
		sprintf(text, "según utilidad por ejemplo: árboles frutales, madereros y medicinales.");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		glColor3f(1.0f, 0.0f, 0.0f);
		glRasterPos3f( -14.0 , -6.5, 10.0);
		sprintf(text, "Presionar numero 4 mas espacio para salir");
		for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		glColor3f(1.0f, 1.0f, 1.0f);
		glPopMatrix();
	}
void camara(int w, int h)
{
	// Evitar una división por cero, cuando la ventana es demasiado pequeña
	// (No permitir una ventana de alto 0).
	if (h == 0)
	h = 1;
	float proporcion = w * 1.0 / h;

	// Usando Matrix proyección
	glMatrixMode(GL_PROJECTION);

	// Reseteando la Matrix
	glLoadIdentity();

	// configurar el viewport para una ventana completa
	glViewport(0, 0, w, h);

	// Configurando las perspectivas.
	gluPerspective(45.0f, proporcion, 0.1f, 100.0f);

	// Regresar la vista a Modelview
	glMatrixMode(GL_MODELVIEW);
}



//se crea la primera escena
void escena(void){	

    Mix_Chunk *Llanta = Mix_LoadWAV("src/Llanta.wav");
    Mix_Chunk *Pared = Mix_LoadWAV("src/Wall.wav");
    Mix_Chunk *Basura = Mix_LoadWAV("src/Basura.wav");
    Mix_Chunk *Recoge = Mix_LoadWAV("src/recoje.wav");


    int n3=-1;
    int n4=10;
   
    for (int h=0; h<=16;h++){
        if (contar[h]==1){
            n3+=1;
            n4-=1;
        }
            else{
                n3=n3;
            }
    }	
	
   
	glPushMatrix();
    char text[32];
    glColor3f(0,0,0);
    sprintf(text, "Basura :%d",n3+1);
    glRasterPos3f( X+1,2.2,Z);
    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    glPopMatrix();

	glPushMatrix();
    char text1[32];
    glColor3f(0,0,0);
    sprintf(text1, "Objetivo restante: %d",n4);
    glRasterPos3f( X+1,2.0,Z);
    for(int i = 0; text1[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text1[i]);
    glPopMatrix();
   
    glPushMatrix();
    char text5[100];
    glColor3f(0,0,0);
    sprintf(text5, "Intrucciones presionar tecla i, mas tecla de desplazamiento ");
    glRasterPos3f( X-2,2.5,Z);
    for(int i = 0; text5[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text5[i]);
    glPopMatrix();  
      
    ///////////////////////////////suelo
    glPushMatrix();
	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	define_textura(textura_ca);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-20.0f, 0.0f, -20.0f);
		glTexCoord2f(200.0f, 0.0f);glVertex3f(-20.0f, 0.0f, 20.0f);
		glTexCoord2f(200.0f, 200.0f);glVertex3f( 20.0f, 0.0f, 20.0f);
		glTexCoord2f(0.0f, 200.0f);glVertex3f( 20.0f, 0.0f, -20.0f);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	if (n4==0){
		ESD=1;
		}
	///////////////////////////cielo
	glPushMatrix(); 
	cielo();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	
	//CONTENEDORES DE RECICLAJE Basusra

	//Azul
	glPushMatrix();
	glColor3f(0.255, 0.412, 0.882);
	glTranslatef(0.5,0,6);
	barril();
	glPopMatrix();
	colicion_basurero( 0.7,-0.1, Z,X,6.5,5.7,3);

	//Rojo
	glPushMatrix();
	glColor3f(1,0,0);
	glTranslatef(0.5,0,-6);
	barril();
	glPopMatrix();
	colicion_basurero( 0.7,-0.1, Z,X,-5.4,-6.5,1);

	//verde
	glPushMatrix();
	glColor3f(0.196, 0.804, 0.196);
	glTranslatef(-8,0,-4.5);
	barril();
	glPopMatrix();
	//colicion
    colicion_basurero( -7.4,-8.5, Z,X,-3.8,-6.5,2);
	
   	
   	
	////////////////////-------------Basura-------------------///////////////////////////////
	
	//---botella plastico	
	glPushMatrix();
	if(oculto2[0]==0){
	recoger_basura( 0.7,0, Z,X,-1.6,-2.3,0);
    glTranslatef(0,0,-2);
    glScalef(0.07,0.025,0.07);
    botella();
    } else {
		glTranslatef(X+posOX,oculto2[0]-0.82,Z+posOZ);
		glScalef(0.07,0.025,0.07);
		botella();
		info();
		botV=1;
		if (idBa[pos]==1){
			oculto2[0]={-10};
            instru=0;
		}
	
	}  
    glPopMatrix();
    
    //colicionnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn
    
    glPushMatrix();
    if(oculto2[1]==0){
		recoger_basura( 9.7,9.0, Z,X,2.35,1.65,1);
		glTranslatef(9,0.0,2);
		glScalef(0.07,0.025,0.07);
		botella();
    
    }
    else{
	    glTranslatef(X+posOX,oculto2[1]-0.82,Z+posOZ);
		glScalef(0.07,0.025,0.07);
		botella();
		info();	
		botV=1;
		if (idBa[pos]==1){
		oculto2[1]={-10};
		instru=0;
		}
		
	}
    glPopMatrix();
  
  
    glPushMatrix();
    if(oculto2[2]==0){
		recoger_basura( 9.7,9.0, Z,X,-7.65,-8.35,2);
		glTranslatef(9,0.0,-8);
		glScalef(0.07,0.025,0.07);
		botella();
   }
    else{
		glTranslatef(X+posOX,oculto2[2]-0.82,Z+posOZ);
		glScalef(0.07,0.025,0.07);
		botella();
		info();
		botV=1;
		if (idBa[pos]==1){
			oculto2[2]={-10};
            instru=0;	
		}
	}
    glPopMatrix(); 
    
    //colicion    
    //botella vidrio
    glPushMatrix();
    if(oculto2[3]==0){
		recoger_basura( 0.6,0.0, Z,X,-8.65,-9.35,3);
		glTranslatef(0,0,-9);
		glScalef(0.04,0.025,0.04);
		botellaV();
    }else{
		glTranslatef(X+posOX,oculto2[3]-0.82,Z+posOZ);
		glScalef(0.07,0.025,0.07);
		botellaV();
		info();
		botV=2;
		if (idBa[pos]==2){
		oculto2[3]={-10};	
			}
		}
		glPopMatrix();
    //colicion
    
    glPushMatrix();
    if(oculto2[4]==0){
		recoger_basura( 0.6,0.0, Z,X,1.35,0.65,4);
		glTranslatef(0,0.0,1);
		glScalef(0.04,0.025,0.04);
		botellaV();
	}
    else{ 
		glTranslatef(X+posOX,oculto2[4]-0.82,Z+posOZ);
		glScalef(0.07,0.025,0.07);
		botellaV();
		info();
		botV=2;
		if (idBa[pos]==2){
			oculto2[4]={-10};	
            instru=0;
		}
	}
    glPopMatrix();
    
    //colicion
    
    
    glPushMatrix();
    if(oculto2[5]==0){
		recoger_basura( -8.4,-9.1, Z,X,-11.65,-12.35,5);
		glTranslatef(-9,0,-12);
		glScalef(0.04,0.025,0.04);
		botellaV();
		}
    else{ 
		glTranslatef(X+posOX,oculto2[5]-0.82,Z+posOZ);
		glScalef(0.07,0.025,0.07);
		botellaV();
		info();
		botV=2;
		if (idBa[pos]==2){
			oculto2[5]={-10};
            instru=0;	
		}
	}
    glPopMatrix();
    
    //colicion
    
	
	//papel
	glPushMatrix();
	if(oculto2[6]==0){
		recoger_basura( -13.7,-14.4, Z,X,2.35,1.65,6);
		glTranslatef(-14,0.0,2);
		glScalef(0.04,0.04,0.04);
		pelota();
	}
    else{
		glTranslatef((X+posOX)+0.35,oculto2[6]-1.05,Z+posOZ);
		glScalef(0.04,0.04,0.04);
		pelota();
		info();
		botV=3;
    if (idBa[pos]==3){
        oculto2[6]={-10};
        instru=0;	
		}}
    glPopMatrix();
    //colicion
    
	
	

    //cereal
	glPushMatrix();
	if(oculto2[7]==0){
	    recoger_basura(-1.65,-2.35, Z,X,-14.65,-15.35,7);
		glTranslatef(-2,0.0,-15);
		glScalef(0.081,0.051,0.051);
		contenedor();
	}
    else{
		glTranslatef((X+posOX)+0.35,oculto2[7]-0.85,Z+posOZ);
		glScalef(0.059,0.041,0.041);
		contenedor();
		info();
		botV=4;
		if (idBa[pos]==3){
			oculto2[7]={-10};
            instru=0;	
		}
	}
    glPopMatrix();  
    
    //cajas
    glPushMatrix();
    if(oculto2[8]==0){
		recoger_basura( 0.4,-0.5, Z,X,5.1,3.8,8);
		glTranslatef(0,0.0,4);
		glScalef(0.25,0.25,0.25);
		cajas();
	}
    else{
		
		glTranslatef((X+posOX)+0.3,oculto2[8]-0.82,Z+posOZ);
		glScalef(0.059,0.041,0.041);
		glRotatef(90,0,1,0);
		cajas();
		info();
		botV=4;
		if (idBa[pos]==3){
            oculto2[8]={-10};
            instru=0;	
		}
	}
    glPopMatrix();
    
    //colicion
    
    
    glPushMatrix();
    if(oculto2[9]==0){
		recoger_basura( 8.6,7.5, Z,X,-9.1,-10.4,9);
		glTranslatef(8,0,-10);
		glScalef(0.25,0.25,0.25);
		cajas();
	}
    else{
		glTranslatef((X+posOX)+0.3,oculto2[9]-0.82,Z+posOZ);
		glScalef(0.059,0.041,0.041);
		glRotatef(90,0,1,0);
		cajas();
		info();
		botV=4;
		if (idBa[pos]==3){
            oculto2[9]={-10};
            instru=0;	
		}
	}
    glPopMatrix();
    
    //colicion
    
    
    glPushMatrix();
    if(oculto2[10]==0){
		recoger_basura( 8.5,7.4, Z,X,7.1,5.6,10);
		glTranslatef(8,0,6);
		glScalef(0.25,0.25,0.25);
		cajas();
	}
    else{
		glTranslatef((X+posOX)+0.3,oculto2[10]-0.82,Z+posOZ);
		glScalef(0.059,0.041,0.041);
		glRotatef(90,0,1,0);

		cajas();
		info();
		botV=4;
		if (idBa[pos]==3){
            oculto2[10]={-10};	
            instru=0;
		}
	}
    glPopMatrix();
    //colicion
    
    
    glPushMatrix();
    if(oculto2[11]==0){
		recoger_basura( 8.4,7.4, Z,X,1.0,-0.3,11);
		glTranslatef(8,0.0,0);
		glScalef(0.25,0.25,0.25);
		cajas();
	}
    else{
		glTranslatef((X+posOX)+0.3,oculto2[11]-0.82,Z+posOZ);
		glScalef(0.059,0.041,0.041);
		glRotatef(90,0,1,0);

		cajas();
		info();
		botV=4;
		if (idBa[pos]==3){
            oculto2[11]={-10};	
            instru=0;
		}
	}
    glPopMatrix();
    //colicion
    
    
     glPushMatrix();
     if(oculto2[12]==0){
		recoger_basura( -10.4,-11.7, Z,X,-12.9,-14.1,12);
		glTranslatef(-11,0.0,-14);
		glScalef(0.25,0.25,0.25);
		cajas();
	}
    else{
		glTranslatef((X+posOX)+0.3,oculto2[12]-0.82,Z+posOZ);
		glScalef(0.059,0.041,0.041);
		glRotatef(90,0,1,0);		
		cajas();
		info();
		botV=4;
		if (idBa[pos]==3){
            oculto2[12]={-10};
            instru=0;	
		}
	}
    glPopMatrix();
    //colicion
    
    
	//lata	
    glPushMatrix();
    if(oculto2[13]==0){
		recoger_basura( 2.35,1.65, Z,X,-1.65,-2.35,13);
		glTranslatef(2,0.0,-2);
		glScalef(0.05,0.04,0.05);
		Lata(0,0);
	}
    else{
		glTranslatef((X+posOX)+0.35,oculto2[13]-0.82,Z+posOZ);
		glScalef(0.04,0.03,0.04);
		Lata(0,0);
		info();
		botV=5;
		if (idBa[pos]==2){
			oculto2[13]={-10};
            instru=0;	
		}
	}
    glPopMatrix();
     //colicion
    
    
    
    glPushMatrix();
    if(oculto2[14]==0){
		recoger_basura( -14.65,-15.35, Z,X,0.35,-0.35,14);
		glTranslatef(-15,0.0,0);
		glScalef(0.05,0.04,0.05);
		Lata(0,0);
	}
    else{
		glTranslatef((X+posOX)+0.35,oculto2[14]-0.82,Z+posOZ);
		glScalef(0.04,0.03,0.04);
		Lata(0,0);
		info();
		botV=5;
		if (idBa[pos]==2){
			oculto2[14]={-10};	
            instru=0;
		}
	}
    glPopMatrix();
    
    //colicion
   
    
    
    glPushMatrix();
    if(oculto2[15]==0){
		recoger_basura(6.35,5.65, Z,X,-7.65,-8.35,15);
		glTranslatef(6,0.0,-8);
		glScalef(0.05,0.04,0.05);
		Lata(0,0);
	}
    else{
		glTranslatef((X+posOX)+0.35,oculto2[15]-0.82,Z+posOZ);
		glScalef(0.04,0.03,0.04);
		Lata(0,0);
		info();
		botV=5;
		if (idBa[pos]==2){
		oculto2[15]={-10};	
		}
	}
    glPopMatrix();
    
    //colicion
    
    
    //colicion
    
    //bolsa
	glPushMatrix();
	if(oculto2[16]==0){
		recoger_basura( 18.5,17.3, Z,X,-17.5,-18.6,16);
		glTranslatef(18,oculto2[16],-18);
		bolsa();
	}
    else{
		glTranslatef(X,oculto2[16],Z);
		bolsa();
		info();
		botV=6;
		if (idBa[pos]==1){
            oculto2[16]={-10};
            instru=0;	
		}
	}
    glPopMatrix();
    
    glPushMatrix();
    if(oculto2[16]==0){
		recoger_basura( 18.5,17.3, Z,X,-17.5,-18.6,16);
		glTranslatef(17.8,0,-18);
		bolsa();
	}
    else{
		glTranslatef(X,oculto2[16],Z);
		bolsa();
		info();
		botV=6;
		if (idBa[pos]==1){
			oculto2[16]={-10};
            instru=0;	
		}
	}
    glPopMatrix();
    
          
          
    ////Edificios      
	glPushMatrix();
	posX=-18,posZ=-18;
    glTranslatef(-18,0,-18);
    conte(tex[0]);    
    glPopMatrix();
      
    glPushMatrix();
    glTranslatef(-8,0,-18);
    conte(tex[0]);    
    glPopMatrix();
      
      
    glPushMatrix();
    glTranslatef(2,0,-18);
    conte(tex[0]);    
    glPopMatrix();
      
    
      
    //probando
    glPushMatrix();
    posX=6,posZ=-18;
    glTranslatef(12,0,-18);
    conte(tex[0]);    
    glPopMatrix();
      
    //segunda filas de edificios
    glPushMatrix();
	posX1=-18,posZ1=-10;
    glTranslatef(-18,0,-6);
	conte(tex[0]);    
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-8,0,-6);
	conte(tex[0]);    
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(2,0,-6);
	conte(tex[0]);    
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(12,0,-6);
	conte(tex[0]);    
    glPopMatrix();
    
   //tercera linea
    glPushMatrix();
    glTranslatef(-18,0,6);
	conte(tex[0]);    
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-8,0,6);
	conte(tex[0]);    
    glPopMatrix();
   
    glPushMatrix();
    glTranslatef(2,0,6);
	conte(tex[0]);    
    glPopMatrix();
    
     glPushMatrix();
    glTranslatef(12,0,6);
	conte(tex[0]);    
    glPopMatrix();
    
    //cuarta fila
    glPushMatrix();
    glTranslatef(-18,0,18);
	conte(tex[0]);    
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-8,0,18);
	conte(tex[0]);    
    glPopMatrix();
   
    glPushMatrix();
    glTranslatef(2,0,18);
	conte(tex[0]);    
    glPopMatrix();
    
     glPushMatrix();
    glTranslatef(12,0,18);
	conte(tex[0]);    
    glPopMatrix();
    
    
    printf(" X:::%f ",X);
    printf(" Z:::%f ",Z);
    
       
	//Wall-e
    glPushMatrix();
    glRotatef(180,0,1,0);
    glTranslatef(-X,0,-Z);
    glRotatef(rotate_y,0,1,0);
    glScalef(0.1,0.1,0.1);   
    Wall();
    glColor3f(1,1,1);    
    glPopMatrix();
    
    
   //primera linea coalicion
   // derecha a izquierda
   colicion( -16.6,-19.4, Z,X,-16.6);
   colicion( -6.5,-9.4, Z,X,-16.6);
   colicion( 3.4,0.6, Z,X,-16.6);
   colicion( 13.5,10.6, Z,X,-16.6);
  //segundo linea coalicion
   //de  izquierda a derecha 
   colicion2( -16.6,-19.4, Z,X,-4.6,-7.4);
   colicion2( -6.5,-9.4, Z,X,-4.6,-7.4);
   colicion2( 3.4,0.6, Z,X,-4.6,-7.4);
   colicion2( 13.5,10.6, Z,X,-4.6,-7.4);
   
    //tercera linea coalicion
   //de  izquierda a derecha 
   colicion2( -16.6,-19.4, Z,X,7.4,4.6);
   colicion2( -6.5,-9.4, Z,X,7.4,4.6);
   colicion2( 3.4,0.6, Z,X,7.4,4.6);
   colicion2( 13.5,10.6, Z,X,7.4,4.6);
   
     //tercera linea coalicion
   //de  izquierda a derecha 
   colicion2( -16.6,-19.4, Z,X,19.4,16.6);
   colicion2( -6.5,-9.4, Z,X,19.4,16.6);
   colicion2( 3.4,0.6, Z,X,19.4,16.6);
   colicion2( 13.5,10.6, Z,X,19.4,16.6);

	if(toca==1){
		Mix_PlayChannel(-1, Pared, 0);
	}
	if(tocaB==1){
		Mix_PlayChannel(-1, Basura, 0);
	}
	if(tocaR==1){
		Mix_PlayChannel(-1, Recoge, 0);
	}
	else if(tocaL==1){
		Mix_PlayChannel(-1,Llanta, 0);
		Mix_VolumeChunk(Llanta, 32);
	}
	toca=0;
	tocaB=0;
	tocaR=0;

     
    //condicion cielo
    if(X<19.79 and X>-19.79 and (((abs(posZ)+1.7)-abs(Z))<=0.1) ){
		  pauseAnimation();
	}
	if((((abs(posX1)+1.7)-abs(X))<=0.1) and Z<19.79 and Z>-19.79   ){
		  pauseAnimation();
	}

}

void escena1(void){
	
    ///////////////////////////////suelo
    int n=0;
    int n1=24;
   
    for (int i=0; i<=24;i++){
        if (oculto3[i]==1){
            n+=1;
            n1-=1;

        }
            else{
                n=n;
            }
    }	
	
	glPushMatrix();
    char text[32];
    sprintf(text, "Arboles Plantados:%d",n);
    glRasterPos3f( X+1,2.2,Z);
    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    glPopMatrix();

	glPushMatrix();
    char text1[32];
    sprintf(text1, "Objetivo : %d",n1);
    glRasterPos3f( X+1,2.0,Z);
    for(int i = 0; text1[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text1[i]);
    glPopMatrix();

    
	if(n<=23){
    glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	define_textura(textura_flA);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-20.0f, 0.0f, -20.0f);
		glTexCoord2f(50.0f, 0.0f);glVertex3f(-20.0f, 0.0f, 20.0f);
		glTexCoord2f(50.0f, 50.0f);glVertex3f( 20.0f, 0.0f, 20.0f);
		glTexCoord2f(0.0f, 50.0f);glVertex3f( 20.0f, 0.0f, -20.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

    }else{
    glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	define_textura(textura_cs);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glColor3f(0.235, 0.702, 0.443);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-20.0f, 0.0f, -20.0f);
		glTexCoord2f(50.0f, 0.0f);glVertex3f(-20.0f, 0.0f, 20.0f);
		glTexCoord2f(50.0f, 50.0f);glVertex3f( 20.0f, 0.0f, 20.0f);
		glTexCoord2f(0.0f, 50.0f);glVertex3f( 20.0f, 0.0f, -20.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix(); 
    glColor3f(1,1,1); 
    
	glPushMatrix();
    char text2[32];
    sprintf(text2, "FELICIDADES HAS AYUDADO A SALVAR LA TIERRA!!");
    glRasterPos3f( X-1.5,1.0,Z);
    for(int i = 0; text2[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text2[i]);
    glPopMatrix();  
    }
	
	///////////////////////////cielo
	glPushMatrix(); 
	cieloA();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

    
    posX=-18,posZ=-18;
    posX1=-18,posZ1=10;    
    
	//ORIFICIOS LINEA 1
	//info1();
    glPushMatrix();
    colicion3( 10.9 ,9.1, Z,X, 0.6, -0.6,0);
    if(oculto3[0]==0){
    glPushMatrix();
    glTranslatef(10,0,0);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[0]<=1.1){
	info1();}
    glTranslatef(10,0,0);
    orificio(); 
    botV=7;
    glScalef(oculto1[0],oculto1[0],oculto1[0]);
    arbol1();
    glColor3f(1,1,1);
	glPopMatrix();
    }
    glPopMatrix();
       

    glPushMatrix();
    colicion3( 5.9 ,4.1, Z,X, 0.6, -0.6,1);  
  if(oculto3[1]==0){
  glPushMatrix();
    glTranslatef(5,0,0);
    orificio();
    instru1=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[1]<=1.1){
	info1();}
    glTranslatef(5,0,0);
    orificio();
    botV=8;
    glScalef(oculto1[1],oculto1[1],oculto1[1]);	
    arbol2();
    glColor3f(1,1,1);	
	glPopMatrix();
	}
    glPopMatrix();
	  

    glPushMatrix();
	colicion3( -4.1 ,-5.9, Z,X, 0.6, -0.6,2);   
    if(oculto3[2]==0){
    glPushMatrix();
    glTranslatef(-5,0,0);
    orificio();
    instru=0; 
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[2]<=1.1){
	info1();}
    glTranslatef(-5,0,0);
    orificio();
    botV=7;
    glScalef(oculto1[2],oculto1[2],oculto1[2]);    
    arbol1();
	}
	glColor3f(1,1,1);
	glPopMatrix();
    glPopMatrix();
     

    glPushMatrix();
    colicion3( -9.1 ,-10.9, Z,X, 0.6, -0.6,3);
    if(oculto3[3]==0){
    glPushMatrix();
    glTranslatef(-10,0,0);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[3]<=1.1){
	info1();}
    glTranslatef(-10,0,0);
    orificio();
    botV=8;
    glScalef(oculto1[3],oculto1[3],oculto1[3]);
    arbol2();
	}
	glColor3f(1,1,1);
	glPopMatrix();
	glPopMatrix();
    

   
   
	//ORIFICIOS LINEA 2
    glPushMatrix();
    colicion3( 10.9 ,9.1, Z,X, 5.6, 4.3,4); 
    if(oculto3[4]==0){
    glPushMatrix();
    glTranslatef(10,0,5);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[4]<=1.1){
	info1();}
    glTranslatef(10,0,5);
    orificio();
    botV=7;
    glScalef(oculto1[4],oculto1[4],oculto1[4]);
    arbol3();
	}
	glColor3f(1,1,1);
	glPopMatrix();
    glPopMatrix();
     

    glPushMatrix();
    colicion3( 5.9 ,4.1, Z,X, 5.6, 4.3,5);
    if(oculto3[5]==0){
    glPushMatrix();
    glTranslatef(5,0,5);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[5]<=1.1){
	info1();}
    glTranslatef(5,0,5);
    orificio();
    botV=8;
    glScalef(oculto1[5],oculto1[5],oculto1[5]);
    arbol1();
	}
	glColor3f(1,1,1);
	glPopMatrix();
    glPopMatrix();
    
    
    glPushMatrix();
    colicion3( 0.9 ,-0.7, Z,X, 5.6, 4.3,6);
    if(oculto3[6]==0){
    glPushMatrix();
    glTranslatef(0,0,5);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[6]<=1.1){
	info1();}
    glTranslatef(0,0,5);
    orificio();
    botV=7;
    glScalef(oculto1[6],oculto1[6],oculto1[6]);
    arbol1();
	}
	glColor3f(1,1,1);
	glPopMatrix();
    glPopMatrix();
    

    glPushMatrix();
    colicion3( -4.1 ,-5.9, Z,X, 5.6, 4.3,7);
    if(oculto3[7]==0){
    glPushMatrix();
    glTranslatef(-5,0,5);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[7]<=1.1){
	info1();}
    glTranslatef(-5,0,5);
    orificio();
    botV=8;
    glScalef(oculto1[7],oculto1[7],oculto1[7]);
    arbol3();
	}
	glColor3f(1,1,1);
	glPopMatrix();
    glPopMatrix();
     

    glPushMatrix();
    colicion3( -9.1 ,-10.9, Z,X, 5.6, 4.3,8); 
    if(oculto3[8]==0){
    glPushMatrix();
    glTranslatef(-10,0,5);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[8]<=1.1){
	info1();}
    glTranslatef(-10,0,5);
    orificio();
    botV=7;
    glScalef(oculto1[8],oculto1[8],oculto1[8]);
    arbol1();
	}
	glColor3f(1,1,1);
	glPopMatrix();
    glPopMatrix();
     

	//ORIFICIOS LINEA 2
    glPushMatrix();
    colicion3(10.9 ,9.1, Z,X, -4.6, -5.3,9);
    if(oculto3[9]==0){
    glPushMatrix();
    glTranslatef(10,0,-5);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[9]<=1.1){
	info1();}
    glTranslatef(10,0,-5);
    orificio();
    botV=8;
    glScalef(oculto1[9],oculto1[9],oculto1[9]);
    arbol2();
	}
	glColor3f(1,1,1);
	glPopMatrix();
    glPopMatrix();
    

    glPushMatrix();
    colicion3( 5.9 ,4.1, Z,X, -4.6, -5.3,10);
    if(oculto3[10]==0){
    glPushMatrix();
    glTranslatef(5,0,-5);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[10]<=1.1){
	info1();}
    glTranslatef(5,0,-5);
    orificio();
    botV=7;
    glScalef(oculto1[10],oculto1[10],oculto1[10]);
    arbol3();
	}
	glColor3f(1,1,1);
	glPopMatrix();
    glPopMatrix();
    

    glPushMatrix();
    colicion3( 0.9 ,-0.7, Z,X, -4.6, -5.3,11); 
    if(oculto3[11]==0){
    glPushMatrix();
    glTranslatef(0,0,-5);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[11]<=1.1){
	info1();}
    glTranslatef(0,0,-5);
    orificio();
    botV=8;
    glScalef(oculto1[11],oculto1[11],oculto1[11]);
    arbol1();
	}
	glColor3f(1,1,1);
	glPopMatrix();
    glPopMatrix();
     

    glPushMatrix();
    colicion3( -4.1 ,-5.9, Z,X, -4.6, -5.3,12);
    if(oculto3[12]==0){
    glPushMatrix();
    glTranslatef(-5,0,-5);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[12]<=1.1){
	info1();}
    glTranslatef(-5,0,-5);
    orificio();
    botV=7;
    glScalef(oculto1[12],oculto1[12],oculto1[12]);
    arbol2();
	}
	glColor3f(1,1,1);
	glPopMatrix();
    glPopMatrix();
      

    glPushMatrix();
    colicion3( -9.1 ,-10.9, Z,X, -4.6, -5.3,13);
    if(oculto3[13]==0){
    glPushMatrix();
    glTranslatef(-10,0,-5);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[13]<=1.1){
	info1();}
    glTranslatef(-10,0,-5);
    orificio();
    botV=8;
    glScalef(oculto1[13],oculto1[13],oculto1[13]);
    arbol3();
	}
	glColor3f(1,1,1);
	glPopMatrix();
    glPopMatrix();
     

	//ORIFICIOS LINEA 3
    glPushMatrix();
    colicion3( 10.9 ,9.1, Z,X, -9.6, -10.3,14);
    if(oculto3[14]==0){
    glPushMatrix();
    glTranslatef(10,0,-10);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[14]<=1.1){
	info1();}
    glTranslatef(10,0,-10);
    orificio();
    botV=7;
    glScalef(oculto1[14],oculto1[14],oculto1[14]);
    arbol1();
	}
	glColor3f(1,1,1);
	glPopMatrix();
    glPopMatrix();
    

    glPushMatrix();
    colicion3( 5.9 ,4.1, Z,X, -9.6, -10.3,15);
    if(oculto3[15]==0){
    glPushMatrix();
    glTranslatef(5,0,-10);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[15]<=1.1){
	info1();}
    glTranslatef(5,0,-10);
    orificio();
    botV=8;
    glScalef(oculto1[15],oculto1[15],oculto1[15]);
    arbol2();
	}
	glColor3f(1,1,1);
	glPopMatrix();
    glPopMatrix();
     

    glPushMatrix();
    colicion3( 0.9 ,-0.7, Z,X, -9.6, -10.3,16);
    if(oculto3[16]==0){
    glPushMatrix();
    glTranslatef(0,0,-10);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[16]<=1.1){
	info1();}
    glTranslatef(0,0,-10);
    orificio();
    botV=7;
    glScalef(oculto1[16],oculto1[16],oculto1[16]);
    arbol3();
	}
	glColor3f(1,1,1);
	glPopMatrix();
    glPopMatrix();
     

    glPushMatrix();
    colicion3( -4.1 ,-5.9, Z,X, -9.6, -10.3,17);
    if(oculto3[17]==0){
   glPushMatrix();
    glTranslatef(-5,0,-10);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[17]<=1.1){
	info1();}
    glTranslatef(-5,0,-10);
    orificio();
    botV=8;
    glScalef(oculto1[17],oculto1[17],oculto1[17]);
    arbol1();
	}
	glColor3f(1,1,1);
	glPopMatrix();
    glPopMatrix();
     

    glPushMatrix();
    colicion3( -9.1 ,-10.9, Z,X, -9.6, -10.3,18);
    if(oculto3[18]==0){
   glPushMatrix();
    glTranslatef(-10,0,-10);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[18]<=1.1){
	info1();}
    glTranslatef(-10,0,-10);
    orificio();
    botV=7;
    glScalef(oculto1[18],oculto1[18],oculto1[18]);
    arbol2();
	}
	glColor3f(1,1,1);
	glPopMatrix();
    glPopMatrix();
    

	//ORIFICIOS LINEA 4
    glPushMatrix();
    colicion3(  10.9 ,9.1, Z,X, 10.6, 9.3,19);
    if(oculto3[19]==0){
   glPushMatrix();
    glTranslatef(10,0,10);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[19]<=1.1){
	info1();}
    glTranslatef(10,0,10);
    orificio();
    glScalef(oculto1[19],oculto1[19],oculto1[19]);
    arbol3();
	}
	glColor3f(1,1,1);
	glPopMatrix();
    glPopMatrix();
     

    glPushMatrix();
    colicion3( 5.9 ,4.1, Z,X, 10.6, 9.3,20);
    if(oculto3[20]==0){
    glPushMatrix();
    glTranslatef(5,0,10);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[20]<=1.1){
	info1();}
    glTranslatef(5,0,10);
    orificio();
    glScalef(oculto1[20],oculto1[20],oculto1[20]);
    arbol1();
	}
	glColor3f(1,1,1);
	glPopMatrix();
    glPopMatrix();
    

    glPushMatrix();
    colicion3( 0.9 ,-0.7, Z,X, 10.6, 9.3,21);
    if(oculto3[21]==0){
    glPushMatrix();
    glTranslatef(0,0,10);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[21]<=1.1){
	info1();}
    glTranslatef(0,0,10);
    orificio();
    glScalef(oculto1[21],oculto1[21],oculto1[21]);
    arbol2();
	}
	glColor3f(1,1,1);
	glPopMatrix();
    glPopMatrix();
      

    glPushMatrix();
    colicion3( -4.1 ,-5.9, Z,X, 10.6, 9.3,22);
    if(oculto3[22]==0){
    glPushMatrix();
    glTranslatef(-5,0,10);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[22]<=1.1){
	info1();}
    glTranslatef(-5,0,10);
    orificio();
    glScalef(oculto1[22],oculto1[22],oculto1[22]);
    arbol3();
	}
	glColor3f(1,1,1);
	glPopMatrix();
    glPopMatrix();
      

    glPushMatrix();
    colicion3( -9.1 ,-10.9, Z,X, 10.6, 9.3,23);
    if(oculto3[23]==0){
    glPushMatrix();  
    glTranslatef(-10,0,10);
    orificio();
    instru=0;
    glPopMatrix();
    }else{
	glPushMatrix();
	if(oculto1[23]<=1.1){
	info1();}
    glTranslatef(-10,0,10);
    orificio();
    glScalef(oculto1[23],oculto1[23],oculto1[23]);
    arbol1();
	}
	glColor3f(1,1,1);
	glPopMatrix();
    glPopMatrix();

	Mix_Chunk *regar = Mix_LoadWAV("src/Regando.wav"); 
    Mix_Chunk *Llanta = Mix_LoadWAV("src/Llanta.wav");            
    if(toca2==1){
		Mix_PlayChannel(-1, regar, 0);
	}else if(tocaL==1){
		Mix_PlayChannel(-1,Llanta, 0);
		Mix_VolumeChunk(Llanta, 32);
	}
	toca2=0;    
     
	//Wall-e
    glPushMatrix();
    glRotatef(180,0,1,0);
    glTranslatef(-X,0,-Z);
    glRotatef(rotate_y,0,1,0);
    glScalef(0.1,0.1,0.1);   
    Wall();
    glColor3f(1,1,1);    
    glPopMatrix();
     

    //condicion cielo
    if(X<19.79 and X>-19.79 and (((abs(posZ)+1.7)-abs(Z))<=0.1) ){
        pauseAnimation();
	}
	if((((abs(posX1)+1.7)-abs(X))<=0.1) and Z<19.79 and Z>-19.79   ){
		pauseAnimation();
	}

}

// Manejo de escenas y pantallas de texto de ayuda
void display(void){
	// Borrar Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Reseteando transformaciones
	glLoadIdentity();
	// Configurando camara
	if(estado==0){
	  gluLookAt(X+camaX, 2.0f, Z+camaZ,X, 1.0f, Z,0.0f, 1.0f, 0.0f);
	}else if(estado==1){
	   gluLookAt(0, 20.0f, 20,0, 1.0f, 0,0.0f, 1.0f, 0.0f);  
	}
	
	if(ESD==0){
		escena();
	}
		
	if(ESD==1){
		escena1();
		
	}
	if(ESD==2){
		if(botV==0){
			instrucciones();}
		if(botV==1){
			infoplastico();
			} 
			if(botV==2){
			infobotellav();} 
			if(botV==3){
			infopapel();}
			if(botV==4){
			infoCajas();}  
			if(botV==5){
			infolata();}
			if(botV==6){
			infobolsa();}
			if(botV==7){
			infoarbol();}
			if(botV==8){
			infoarbol1();}  
	}
	glFlush();
	glutSwapBuffers();
}


// --------------- Para animación de wall-e  ------------------------------------------

int animating = 0;      // 0 sin animación 
                        // Se cambia con la llamada a las funciones startAnimation() and pauseAnimation()

void pauseAnimation() {
       // Llamamo a la función para detener la animación 
    animating = 0;
}
float estmovermano;
void updateFrame() {
   // En esta funcion agregamos el codigo que hara la secuencia de cada escena como si fuera un fotograma 
  
	//Hacemos que la tetera gire 
	if(rotate_y==0 ){
		Z-=velocidad;
		rotate_z+= 6;
	}else if(rotate_y==90){
		X-=velocidad;
		rotate_z-= 6;
   }else if(rotate_y==180){
		Z+=velocidad;
		rotate_z-= 6;
   }else if(rotate_y==270){
		X+=velocidad;
		rotate_z-= 6;
   }
   
   
   if(estmovermano<=1.2 ){
	   movermano+=0.2;
	   estmovermano+=0.2; 
   }else if(estmovermano>=1 and estmovermano<2.2){
	   movermano-=0.2;
	   estmovermano+=0.2;
   } else if(estmovermano>=2){
	   estmovermano=0.0;
	   movermano=0.0;
   }
   
   printf (" mover mano:::%f \n ", movermano);
   //Verificamos el numero de frames para detener animación 
   if(frameNumber==1000)
		{
			pauseAnimation();
			frameNumber=0;
		}
  //Almacenamos el numero de frames 
  frameNumber++;
  //printf ("Numero de Frame: %d \n", frameNumber);
} 

void timerFunction(int timerID) {
      // Invocamos la funcion para controlar el tiempo de la ejecucion de funciones 
    if (animating) {
        updateFrame();
        glutTimerFunc(50, timerFunction, 0);
        glutPostRedisplay();
    }
}

void startAnimation() {
      // llamamos la función para iniciar la animación 
   if ( ! animating ) {
       animating = 1;
       glutTimerFunc(50, timerFunction, 1);
   }
}

// --------------- Para animación arboles  ------------------------------------------

int animating2 = 0;      // 0 sin animación 
                        // Se cambia con la llamada a las funciones startAnimation() and pauseAnimation()

void pauseAnimation2() {
       // Llamamo a la función para detener la animación 
    animating2 = 0;
}

void updateFrame2() {
   // En esta funcion agregamos el codigo que hara la secuencia de cada escena como si fuera un fotograma 
  
	//Hacemos que la tetera gire 
	if (escala<1.1){
		escala+= 0.01;
    }

   for (int i4=0;i4<=9; i4+=1){
	   if(r_esfera>=-1){
		   r_esfera-=0.1;
	   }else {
		   r_esfera=2.7;
	   } 
	} 
    //r_esfera=0.0;}//else{escala=0.0;pauseAnimation2();}
   if(frameNumber2==200)
		{
			
			pauseAnimation2();
			frameNumber2=0; 
			escala=0.0;
			r_esfera=2.8;
		
		}
  //Almacenamos el numero de frames 
  frameNumber2++;
  printf ("Numero de Frame2: %d \n", frameNumber2);
}

void timerFunction2(int timerID) {
      // Invocamos la funcion para controlar el tiempo de la ejecucion de funciones 
    if (animating2) {
        updateFrame2();
        glutTimerFunc(50, timerFunction2, 0);
        glutPostRedisplay();
    }
}

void startAnimation2() {
      // llamamos la función para iniciar la animación 
   if ( ! animating2 ) {
       animating2 = 1;
       glutTimerFunc(50, timerFunction2, 1);
   }
}

// Función para controlar teclas especiales
void specialKeys( int key, int x, int y )
{ 
    //  Flecha derecha: aumentar rotación 7 grados
    if (key == GLUT_KEY_RIGHT){
			rotate_y = 270;
			frameNumber=0;
			posOX=-0.1;
			posOZ=0.0;
	}  
    //  Flecha izquierda: rotación en eje Y negativo 7 grados
    else if (key == GLUT_KEY_LEFT){
    
		 rotate_y = 90;
		 frameNumber=0;
		 posOX=-0.6;
		 posOZ=0.0;
	   
      }  
   
    //printf X;
    //  Flecha arriba: rotación en eje X positivo 7 grados
    else if (key == GLUT_KEY_UP){
     rotate_y =0;
     frameNumber=0;
     posOX=-0.35;
      posOZ=-0.3;
	}
    //  Flecha abajo: rotación en eje X negativo 7 grados
    else if (key == GLUT_KEY_DOWN){
      rotate_y = 180;
      frameNumber=0;
      posOX=-0.35;
      posOZ=+0.3;
   } 
    //  Tecla especial F2 : rotación en eje Z positivo 7 grados
    else if (key == GLUT_KEY_F2)
        rotate_y += 5;
    //  Tecla especial F2 : rotación en eje Z negativo 7 grados
    else if (key == GLUT_KEY_F1)
    {
		
        rotate_y -= 180;
        
        }
   
    //  Solicitar actualización de visualización*/
    glutPostRedisplay();
 
}


// ------------- Manejo de Teclado-----------------------------------------------
GLfloat XP=0;
GLfloat ZP=0;
int camaXP=0;
int camaZP=4;
void salir(unsigned char key, int x, int y)
{
	if ( key == ' ' ) {
		if ( animating ){
			instruccion=1;
			tocaL=0;
		    camaX=camaXP;
		    camaZ=camaZP;
			pauseAnimation();

		  }
		else{
		tocaL=1;
		   startAnimation();
		   }
	}
  if (key == 27){
  exit(0);}
  if(key== '1'){
	  estado=0;
  }
  if(key== '2'){
	  estado=1;
  }
  if(key== '3'){
	  estado=2;
  }
  if(key== '4'){
	  ESD=1;
	  X=XP;
	  Z=ZP;
	  camaX=camaXP;
	  camaZ=camaZP;
	  botV=0;
	  idBa2[pos2]={-20};
      instru=-40;
	  rotate_y=0;
	  pauseAnimation();
	
  }
  if(key== '5'){
	  ESD=0;
	  X=XP;
	  Z=ZP;
	  camaX=camaXP;
	  camaZ=camaZP;
	  botV=0;
      instru=-40;
	  rotate_y=0;
	  pauseAnimation();
	
  }
  if(key== '7'){
	  velocidad=0.1;
  }
  if(key== '8'){
	  velocidad=0.3;
  }
  if(key== '9'){
	  velocidad=0.5;
  }
  if(key == 103){
	 ESD=0;
  }
  if(key == 105){
	  XP=X;
	  ZP=Z;
	  camaXP=camaX;
	  camaZP=camaZ;
	  X=-7;
	  Z=20;
	  camaX=-7;
	  camaZ=20;
	  rotate_y=0;	  
	  instru=-20;
	  ESD=2;
	  pauseAnimation();
	
  }
 
}


void init(void)
{
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

}


int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,600);
	glutCreateWindow("ROBOT-TRASH");
	init();
	SDL_Init( SDL_INIT_AUDIO);

    // Initialize SDL mixer
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    Mix_Chunk *Llanta = Mix_LoadWAV("src/Llanta.wav");
    Mix_Chunk *Pared = Mix_LoadWAV("src/Wall.wav");
    Mix_Chunk *Basura = Mix_LoadWAV("src/Basura.wav");
    Mix_Music *Fondo = Mix_LoadMUS("src/Caketown.mp3");
	
	Mix_PlayMusic(Fondo, -1);	
    glutDisplayFunc(display);

    glutReshapeFunc(camara);
    glutKeyboardFunc(salir);
	glutSpecialFunc(specialKeys);	
	glutMainLoop(); 

    Mix_FreeMusic(Fondo);
    Mix_FreeChunk(Llanta);
	Mix_CloseAudio();
    SDL_Quit();

    // Regresar al sistema operativo
	return 0;
}
