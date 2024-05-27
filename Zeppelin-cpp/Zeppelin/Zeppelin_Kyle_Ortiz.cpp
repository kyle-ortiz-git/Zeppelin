/*******************************************************************
		   Hierarchical Multi-Part Model Example
********************************************************************/
#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <gl/glut.h>
#include <utility>
#include <vector>
#include "VECTOR3D.h"
#include "QuadMesh.h"
#include "SOIL2/SOIL2.h"
#include <iostream>
#include <random>
#include <sstream>
#include <string>
using namespace std;

const int vWidth = 1920;    // Viewport width in pixels
const int vHeight = 1080;    // Viewport height in pixels

// Note how everything depends on robot body dimensions so that can scale entire robot proportionately
// just by changing robot body scale
float zepBodyWidth = 1.5;
float zepBodyLength = zepBodyWidth;
float zepBodyDepth = 5.0;


float propellerRotate = 0.0;
// Propeller Rotation
float onlyPropRotate = 0.0;

// Forward Vector
float forwardVector = 5.2;

// CAMERA
float cameraRadius = 20.0f;
//TEXTURE MAPPING-------------------

GLuint textureID1;
GLuint textureID2;
GLuint textureID3;
GLuint textureID4;
GLuint textureID5;

GLuint zPTEXTURE1;
GLuint zPTEXTURE2;
GLuint zPTEXTURE3;
GLuint zPTEXTURE4;
GLuint zPTEXTURE5;

// BULLETS
float bulletEx = 0;
float bulletEy = 0;
float bulletEz = 0;


float bulletPx = 0;
float bulletPy = 0;
float bulletPz = 0;

float bulletSpeed = 0.2;

bool SHIELD = false;

int ENEMYHEALTH = 1;
int PLAYERHEALTH = 1;

int playerZepdone = 0.0;
int enemyZepDone = 0.0;

string ZepTexture = "zPTEXTURE1";


void loadTexture() {
	// Load texture using SOIL (or another library)
	int width, height;
	unsigned char* image = SOIL_load_image("textureimage1.bmp", &width, &height, 0, SOIL_LOAD_RGB);
	unsigned char* image2 = SOIL_load_image("textureimage2.bmp", &width, &height, 0, SOIL_LOAD_RGB);
	unsigned char* image3 = SOIL_load_image("textureimage3.bmp", &width, &height, 0, SOIL_LOAD_RGB);
	unsigned char* image4 = SOIL_load_image("textureimage4.bmp", &width, &height, 0, SOIL_LOAD_RGB);
	unsigned char* image5 = SOIL_load_image("textureimage5.png", &width, &height, 0, SOIL_LOAD_RGB);

	unsigned char* image11 = SOIL_load_image("zep1.bmp", &width, &height, 0, SOIL_LOAD_RGB);
	unsigned char* image22 = SOIL_load_image("zep2.bmp", &width, &height, 0, SOIL_LOAD_RGB);
	unsigned char* image33 = SOIL_load_image("zep3.bmp", &width, &height, 0, SOIL_LOAD_RGB);
	unsigned char* image44 = SOIL_load_image("zep4.bmp", &width, &height, 0, SOIL_LOAD_RGB);
	unsigned char* image55 = SOIL_load_image("zep5.bmp", &width, &height, 0, SOIL_LOAD_RGB);

	// Generate texture ID for the first texture
	glGenTextures(1, &textureID1);
	// Bind the texture
	glBindTexture(GL_TEXTURE_2D, textureID1);
	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	// Free image data
	SOIL_free_image_data(image);

	// Generate texture ID for the second texture
	glGenTextures(1, &textureID2);
	// Bind the second texture
	glBindTexture(GL_TEXTURE_2D, textureID2);
	// Set texture parameters for the second texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load data for the second texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	// Free image data for the second texture
	SOIL_free_image_data(image2);



	// Generate texture ID for the third texture
	glGenTextures(1, &textureID3);
	// Bind
	glBindTexture(GL_TEXTURE_2D, textureID3);
	// Set texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load data 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image3);
	// Free image data
	SOIL_free_image_data(image3);


	// Generate texture ID for the fourth texture
	glGenTextures(1, &textureID4);
	// Bind
	glBindTexture(GL_TEXTURE_2D, textureID4);
	// Set texture parameters 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image4);
	// Free image data
	SOIL_free_image_data(image4);


	// Generate texture ID for the fourth texture
	glGenTextures(1, &textureID5);
	// Bind
	glBindTexture(GL_TEXTURE_2D, textureID5);
	// Set texture parameters 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image5);
	// Free image data
	SOIL_free_image_data(image5);



	// Generate texture ID
	glGenTextures(1, &zPTEXTURE1);
	glBindTexture(GL_TEXTURE_2D, zPTEXTURE1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image11);
	SOIL_free_image_data(image11);
	// Generate texture ID
	glGenTextures(1, &zPTEXTURE2);
	glBindTexture(GL_TEXTURE_2D, zPTEXTURE2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image22);
	SOIL_free_image_data(image22);
	// Generate texture ID
	glGenTextures(1, &zPTEXTURE3);
	glBindTexture(GL_TEXTURE_2D, zPTEXTURE3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image33);
	SOIL_free_image_data(image33);
	// Generate texture ID
	glGenTextures(1, &zPTEXTURE4);
	glBindTexture(GL_TEXTURE_2D, zPTEXTURE4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image44);
	SOIL_free_image_data(image44);
	// Generate texture ID
	glGenTextures(1, &zPTEXTURE5);
	glBindTexture(GL_TEXTURE_2D, zPTEXTURE5);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image55);
	SOIL_free_image_data(image55);






	// Enable texturing
	glEnable(GL_TEXTURE_2D);
}

//----------------------------

// Lighting/shading and material properties
// Zeppellin RGBA material properties 

//for zep 1
GLfloat zepBody_mat_ambient[] = { 0.67f, 0.65f, 0.60f,0.3f };
GLfloat zepBody_mat_specular[] = { 0.66f, 0.65f, 0.63f,0.5f };
GLfloat zepBody_mat_diffuse[] = { 0.56f, 0.55f, 0.54f,0.3f };
GLfloat zepBody_mat_shininess[] = { 140.0F };

GLfloat zepFin_mat_ambient[] = { 0.37f, 0.35f, 0.30f,0.3f };
GLfloat zepFin_mat_specular[] = { 0.36f, 0.35f, 0.33f,0.5f };
GLfloat zepFin_mat_diffuse[] = { 0.56f, 0.55f, 0.54f,0.3f };
GLfloat zepFin_mat_shininess[] = { 140.0F };

GLfloat zepDarkBrown_mat_ambient[] = { 0.14f, 0.08f, 0.04f, 1.00f };
GLfloat zepDarkBrown_mat_diffuse[] = { 0.14f, 0.08f, 0.04f, 1.00f };
GLfloat zepDarkBrown_mat_specular[] = { 0.10f, 0.08f, 0.04f, 0.20f };
GLfloat zepDarkBrown_mat_shininess[] = { 220.0F };



//for zep 2
GLfloat zepBodyinvert_mat_ambient[] = { 0.67f, 0.65f, 0.60f,0.3f };
GLfloat zepBodyinvert_mat_specular[] = { 0.66f, 0.65f, 0.63f,0.5f };
GLfloat zepBodyinvert_mat_diffuse[] = { 0.56f, 0.55f, 0.54f,0.3f };
GLfloat zepBodyinvert_mat_shininess[] = { 140.0F };

GLfloat zepFininvert_mat_ambient[] = { 0.05f, 0.05f, 0.05f,1.00f };
GLfloat zepFininvert_mat_specular[] = { 0.05f, 0.05f, 0.05f,1.00f };
GLfloat zepFininvert_mat_diffuse[] = { 0.05f, 0.05f, 0.05f,1.00f };
GLfloat zepFininvert_mat_shininess[] = { 140.0F };

GLfloat zepDarkBrowninvert_mat_ambient[] = { 0.220, 0.0204f, 0.04f, 1.00f };
GLfloat zepDarkBrowninvert_mat_diffuse[] = { 0.220, 0.0204f, 0.04f, 1.00f };
GLfloat zepDarkBrowninvert_mat_specular[] = { 0.320, 0.0704f, 0.04f, 1.00f };
GLfloat zepDarkBrowninvert_mat_shininess[] = { 220.0F };

GLfloat zepHillGreen_mat_ambient[] = { 0.124f, 0.240f, 0.0984f, 1.00f };
GLfloat zepHillGreen_mat_diffuse[] = { 0.124f, 0.240f, 0.0984f, 1.00f };
GLfloat zepHillGreen_mat_specular[] = { 0.124f, 0.240f, 0.0984f, 1.00f };
GLfloat zepHillGreen_mat_shininess[] = { 220.0F };

GLfloat Sun_mat_ambient[] = { 0.950f, 0.524f, 0.0380f, 1.00f };
GLfloat Sun_mat_diffuse[] = { 0.80f, 0.803f, 0.170f, 0.001f };
GLfloat Sun_mat_specular[] = { 0.950f, 0.0380f, 0.0380f, 0.05f };
GLfloat Sun_mat_shininess[] = { 100.0F };


GLfloat zepMetal_mat_ambient[] = { 0.01f, 0.01f, 0.01f, 1.00f };
GLfloat zepMetal_mat_diffuse[] = { 0.10f, 0.10f, 0.10f, 1.00f };
GLfloat zepMetal_mat_specular[] = { 0.01f, 0.01f, 0.01f, 1.00f };
GLfloat zepMetal_mat_shininess[] = { 30.0F };

GLfloat Mountain_mat_ambient[] = { 0.08f, 0.08f, 0.08f, 1.00f };
GLfloat Mountain_mat_diffuse[] = { 0.08f, 0.08f, 0.08f, 1.00f };
GLfloat Mountain_mat_specular[] = { 0.01f, 0.01f, 0.01f, 1.00f };
GLfloat Mountain_mat_shininess[] = { 300.0F };

GLfloat zepWindowCase_mat_ambient[] = { 0.01f, 0.01f, 0.01f, 1.00f };
GLfloat zepWindowCase_mat_diffuse[] = { 0.10f, 0.10f, 0.10f, 1.00f };
GLfloat zepWindowCase_mat_specular[] = { 0.11f, 0.11f, 0.11f, 1.00f };
GLfloat zepWindowCase_mat_shininess[] = { 30.0F };


// Light properties
GLfloat light_position0[] = { 5.0F, 8.0F, 8.0F, 1.0F };
GLfloat light_position1[] = { 4.0F, 8.0F, 8.0F, 1.0F };

GLfloat light_position2[] = { bulletEx, bulletEy, bulletEz, 1.0F };

GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_ambient[] = { 0.3F, 0.3F, 0.3F, 1.0F };




// Mouse button
int currentButton;

// A flat open mesh
QuadMesh* groundMesh = NULL;

// Structure defining a bounding box, currently unused
typedef struct BoundingBox {
	VECTOR3D min;
	VECTOR3D max;
} BBox;

// Default Mesh Size
int meshSize = 16;

// Prototypes for functions in this module
void initOpenGL(int w, int h);
void display(void);
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void mouseMotionHandler(int xMouse, int yMouse);
void keyboard(unsigned char key, int x, int y);
void functionKeys(int key, int x, int y);
void animationHandler(int param);
void animationUpdater(int param);
void dieUpdater(int param);
void drawZeppelin();
void draw2Zeppelin();
void drawZepBody();
void drawZepBodyAccessories();
void drawAllTopBottomFins();
void drawMultiFinWhite();
void drawMultiFinBrown();
void drawFinTopWhite();
void drawFinTopBrown();
void drawTailFinBase();
void drawHanger();
void drawHangerCombination();
void drawHangerTotalBox();
void drawWindows();
void drawTailFinCollection();
void drawPropeller();
void drawPropellerCollection();

void draw2ZepBody();
void draw2ring();
void draw2ZepBodyAccessories();
void draw2AllTopBottomFins();
void draw2MultiFinWhite();
void draw2MultiFinBrown();
void draw2FinTopWhite();
void draw2FinTopBrown();
void draw2TailFinBase();
void draw2Hanger();
void draw2HangerCombination();
void draw2HangerTotalBox();
void draw2Windows();
void draw2TailFinCollection();
void draw2Propeller();
void draw2PropellerCollection();

bool spawnEnemy = false;
float forwardx = 0.0;
float forwardz = 0.0;
float verticaly = 0.0;
float zepstartMeX = 0;
float zepstartMeY = 0;
float zepstartMeZ = 0;
float zepstartEnemyX = 0;
float zepstartEnemyY = 0;
float zepstartEnemyZ = 0;
float zepX = zepstartMeX;
float zepY = zepstartMeY;
float zepZ = zepstartMeZ;
float zepEX = zepstartEnemyX;
float zepEY = zepstartEnemyY;
float zepEZ = zepstartEnemyZ;
float angle_deg = 0.0;
float angle_rad = 0.0;
float angle_degEnemyB = 0.0;
float angle_radEnemyB = 0.0;
float angle_radPlayerB = 0.0;
float angle_degPlayerB = 0.0;
float distanceBetween = 0;
float distanceBetweenE = 0;
float distanceBetweenP = 0;
float enemySpeed = 1.0f; // ENEMY SPEED
float dx2;
float dxP2;
float dzP2;
float dz2;
float dx;
float dxP;
float dzP;
float dz;
int playerfire = 0;

float camerax, cameraz, cameray;
int main(int argc, char** argv)
{
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(vWidth, vHeight);
	glutInitWindowPosition(200, 30);
	glutCreateWindow("Zeppelin");

	// Initialize GL
	initOpenGL(vWidth, vHeight);

	loadTexture();

	// Register callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotionHandler);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(functionKeys);

	glutTimerFunc(20, animationHandler, 0);
	// Start event loop, never returns
	glutMainLoop();


}


// Set up OpenGL. For viewport and projection setup see reshape(). 
void initOpenGL(int w, int h)
{
	// Set up and enable lighting
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2); 

	// Other OpenGL setup
	glEnable(GL_DEPTH_TEST);   // Remove hidded surfaces
	glShadeModel(GL_SMOOTH);   // Use smooth shading, makes boundaries between polygons harder to see 
	glClearColor(0.800F, 0.900F, 1.0F, 1.0F);  // Sky Color
	glClearDepth(1.0f);
	glEnable(GL_NORMALIZE);    // Renormalize normal vectors 
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);   // Nicer perspective

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();


	// Other initializatuion
	// Set up ground quad mesh

	
	VECTOR3D origin = VECTOR3D(-64.0f, 0.0f, 64.0f);
	VECTOR3D dir1v = VECTOR3D(1.0f, 0.0f, 0.0f);
	VECTOR3D dir2v = VECTOR3D(0.0f, 0.0f, -1.0f);

	groundMesh = new QuadMesh(meshSize, 32.0);
	groundMesh->InitMesh(meshSize, origin, 0.0, 0.0, dir1v, dir2v);


	VECTOR3D ambient = VECTOR3D(0.0f, 0.2f, 0.5f);// Ground Color
	VECTOR3D diffuse = VECTOR3D(0.2f, 0.3f, 0.3f);
	VECTOR3D specular = VECTOR3D(1.00f, 1.00f, 1.00f);
	float shininess = 20.2;
	groundMesh->SetMaterial(ambient, diffuse, specular, shininess);


}

float test = 0.0;

//Convert Degree to Rad function
float degToRad(float degrees) {
	return degrees * M_PI / 180.0f;
}

bool useFirstGluLookAt = true;
// Callback, called whenever GLUT determines that the window should be redisplayed
// or glutPostRedisplay() has been called.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	// Create Viewing Matrix V
	
	if (useFirstGluLookAt) {
		// GLU LOOK AT 1
		gluLookAt(0, 36, 250, 0.0, 0.0, -50, 0.0, 10.0, 0.0);
	}
	else {
		// GLU LOOK AT 2
		gluLookAt((cameraRadius * sinf(degToRad(propellerRotate - 90))), 0, (cameraRadius * cosf(degToRad(propellerRotate - 90))), 0.0, 0, 0, 0.0, 1.0, 0.0);
		glTranslatef(camerax- zepstartMeX, cameray - 7- zepstartMeY, cameraz- zepstartMeZ);
	}




	glPushMatrix();
	// Planet
	GLUquadric* p1 = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, textureID5);
	gluQuadricTexture(p1, GL_TRUE);
	glScalef(2.0, 2.0, 2.0);
	glTranslatef(20, 45, -20);
	gluSphere(p1, 10.0, 100, 100);
	gluDeleteQuadric(p1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();


	glPushMatrix();
	// Planet2
	GLUquadric* p2 = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, textureID4);
	gluQuadricTexture(p2, GL_TRUE);
	glScalef(1.0, 1.0, 1.0);
	glTranslatef(-20, 40, -20);
	glRotatef(-45,1,0,0);
	gluSphere(p2, 10.0, 100, 100);
	gluDeleteQuadric(p2);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	glPushMatrix();
	// Planet3
	GLUquadric* p3 = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, zPTEXTURE2);
	gluQuadricTexture(p3, GL_TRUE);
	glScalef(1.0, 1.0, 1.0);
	glTranslatef(-60, 50, -50);
	glRotatef(-45, 1, 0, 0);
	gluSphere(p3, 10.0, 100, 100);
	gluDeleteQuadric(p3);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	

	glPushMatrix();
	// Planet4
	GLUquadric* p4 = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, zPTEXTURE3);
	gluQuadricTexture(p3, GL_TRUE);
	glScalef(1.0, 1.0, 1.0);
	glTranslatef(60, 50, 50);
	glRotatef(-45, 1, 0, 0);
	gluDisk(p4, 10.0, 15, 100,100);
	gluDeleteQuadric(p4);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	glPushMatrix();
	// Planet5
	GLUquadric* p5 = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, zPTEXTURE4);
	gluQuadricTexture(p5, GL_TRUE);
	glScalef(1.0, 1.0, 1.0);
	glTranslatef(20, 40, -30);
	glRotatef(45, 1, 0, 0);
	gluDisk(p5, 10.0, 15, 100, 100);
	gluDeleteQuadric(p5);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();


	glPushMatrix();
	// Planet6
	GLUquadric* p6 = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, zPTEXTURE4);
	gluQuadricTexture(p5, GL_TRUE);
	glScalef(1.0, 1.0, 1.0);
	glTranslatef(-80, 40, -30);
	glRotatef(45, 1, 0, 0);
	gluSphere(p6, 10.0, 100, 100);
	gluDeleteQuadric(p6);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();


	glPushMatrix();
	// SKYSPHERE
	GLUquadric* skybox = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, textureID3);
	gluQuadricTexture(skybox, GL_TRUE);
	glScalef(5.0, 5.0, 5.0);
	gluSphere(skybox, 60.0, 100, 100);
	gluDeleteQuadric(skybox);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	


	// Apply modelling transformations Zeppelin
	drawZeppelin();

	if (spawnEnemy == true) {
		draw2Zeppelin();
	}

	// Draw ground
	glPushMatrix();

	glTranslatef(0.0, -40.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, textureID4);
	groundMesh->DrawMesh(meshSize);

	glPopMatrix();


	glutSwapBuffers();   // Double buffering, swap buffers
}








void drawZeppelin()
{


	
	glPushMatrix();
	
	// Move Forwards
	glTranslatef(forwardx, verticaly, forwardz);
	// Starting Pos
	glTranslatef(zepstartMeX, zepstartMeY, zepstartMeZ);
	//Rotate Zeppelin
	glRotatef(propellerRotate, 0.0, 1.0, 0.0);
	glRotatef(playerZepdone, 1.0, 1.0, 1.0);
	glScalef(playerZepdone+1, playerZepdone+1, playerZepdone+1);
	
	glPushMatrix();
	if (SHIELD) {
		glScalef(zepBodyDepth * 1.2, zepBodyDepth * 1.2, zepBodyDepth * 1.2);
	}
	else {
		glScalef(0,0,0);
	}
	glutWireSphere(2.0, 11, 11);
	glPopMatrix();

	// Player bullet
	glPushMatrix();
	glPushMatrix();
	// Rotate Bullet Player
	glRotatef(angle_degPlayerB, 0.0, 1.0, 0.0);
	// Move bullet
	glTranslatef(bulletPx, bulletPy, bulletPz);
	GLUquadric* quadric2 = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, textureID1);
	gluQuadricTexture(quadric2, GL_TRUE);
	glRotatef(90, 0, 1, 0);
	glScalef(zepBodyWidth / 1.2, zepBodyWidth / 1.2, zepBodyWidth / 1.2);
	gluSphere(quadric2, 1.0, 10, 10);
	gluDeleteQuadric(quadric2);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	glPopMatrix();









	glPushMatrix();
	// Calibrate Orientation
	glRotatef(90, 0.0, 1.0, 0.0);

	drawZepBody();
	drawZepBodyAccessories();
	drawAllTopBottomFins();
	drawTailFinCollection();
	drawHangerTotalBox();
	drawPropellerCollection();
	glPopMatrix();

	glPopMatrix();

}

void drawPropellerCollection()
{
	glPushMatrix();
	// Rotate Propellers
	glRotatef(onlyPropRotate * 5, 0.0, 0.0, 1.0);


	glPushMatrix();
	glTranslatef(0, 0, zepBodyDepth / 8);
	glScalef(0.9, 0.9, 1.0);
	glRotatef(propellerRotate / 3, 0, 0, 1);
	drawPropeller();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.9, 0.9, 1.0);
	glRotatef(propellerRotate / 2, 0, 0, 1);
	drawPropeller();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -zepBodyDepth / 8);
	drawPropeller();
	glPopMatrix();

	glPopMatrix();
}
void drawPropeller()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepBody_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepBody_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepBody_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepBody_mat_shininess);

	// Proppeller 1
	glPushMatrix();
	glTranslatef(0, 0, -zepBodyDepth * 2.7);
	glScalef(zepBodyWidth / 2, zepBodyWidth / 7, zepBodyDepth / 80);
	glutSolidSphere(2.0, 10, 10);
	glPopMatrix();

	// Proppeller 2
	glPushMatrix();
	glTranslatef(0, 0, -zepBodyDepth * 2.7);
	glScalef(zepBodyWidth / 7, zepBodyWidth / 2, zepBodyDepth / 80);
	glutSolidSphere(2.0, 10, 10);
	glPopMatrix();

}
GLuint StringToGLuint(const std::string& str)
{
	GLuint result;
	std::istringstream stream(str);
	stream >> result;
	return result;
}
void drawZepBody()
{
	// Body of Zeppelin
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepBody_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepBody_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepBody_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepBody_mat_shininess);

	glPushMatrix();
	GLUquadric* quadric2 = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, textureID1);
	gluQuadricTexture(quadric2, GL_TRUE);
	glScalef(zepBodyWidth, zepBodyLength, zepBodyDepth);
	gluSphere(quadric2, 2.0, 10, 10);
	gluDeleteQuadric(quadric2);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	


	// Brown
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepDarkBrown_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepDarkBrown_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepDarkBrown_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepDarkBrown_mat_shininess);
	// Back Tube of Zeppelin
	glPushMatrix();
	glTranslatef(0, 0, zepBodyDepth * -2);
	glScalef(zepBodyWidth, zepBodyLength / 1.5, zepBodyDepth);
	glutSolidTorus(zepBodyWidth / 3, zepBodyWidth / 2, zepBodyDepth / 1.5, 10);
	glPopMatrix();
	// Stick
	glPushMatrix();
	glTranslatef(0, 0, -zepBodyDepth * 2.5);
	glScalef(zepBodyWidth / 7, zepBodyWidth / 7, zepBodyDepth);
	glutSolidSphere(1.0, 10, 10);
	glPopMatrix();

	// Brown Donut Tube of Zeppelin
	glPushMatrix();
	glTranslatef(0, 0, zepBodyDepth * -1.5);
	glRotatef(90, 0, 1, 0);
	glScalef(zepBodyDepth / 3, 0.3, 0.5);
	glutSolidTorus(zepBodyWidth / 3, zepBodyLength * 4.0, 20, 20);
	glPopMatrix();

}
void drawTailFinCollection()
{
	glPushMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepFin_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepFin_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepFin_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepFin_mat_shininess);
	glTranslatef(0, 0, zepBodyDepth * 0.1);
	drawTailFinBase();
	glPopMatrix();


	glMaterialfv(GL_FRONT, GL_AMBIENT, zepDarkBrown_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepDarkBrown_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepDarkBrown_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepDarkBrown_mat_shininess);
	glScalef(1, 0.8, 1);
	drawTailFinBase();
	glPopMatrix();
}
void drawTailFinBase()
{
	glPushMatrix();
	//	glMaterialfv(GL_FRONT, GL_AMBIENT, zepFin_mat_ambient);
	//	glMaterialfv(GL_FRONT, GL_SPECULAR, zepFin_mat_specular);
	//	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepFin_mat_diffuse);
	glTranslatef(0, zepBodyLength / 1.3, -zepBodyDepth * 4);
	glRotatef(90, 1, 0, 0);
	glScalef(zepBodyDepth / 6, zepBodyLength * 2, zepBodyDepth / 3);
	glRotatef(90, 0, 1, 0);
	glutSolidTetrahedron();
	glPopMatrix();

	glPushMatrix();
	//	glMaterialfv(GL_FRONT, GL_AMBIENT, zepFin_mat_ambient);
	//	glMaterialfv(GL_FRONT, GL_SPECULAR, zepFin_mat_specular);
	//	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepFin_mat_diffuse);
	glTranslatef(0, -zepBodyLength / 1.3, -zepBodyDepth * 4);
	glRotatef(180, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glScalef(zepBodyDepth / 6, zepBodyLength * 2, zepBodyDepth / 3);
	glRotatef(90, 0, 1, 0);
	glutSolidTetrahedron();
	glPopMatrix();

}
void drawWindows()
{
	glPushMatrix();


	glPushMatrix();
	glTranslatef(zepBodyWidth * 1.15, zepBodyLength * -2.5, -zepBodyDepth / 3);
	glRotatef(-3, 0, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(0.7, 0.7, 0.7);


	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepDarkBrown_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepDarkBrown_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepDarkBrown_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepDarkBrown_mat_shininess);
	glutWireTorus(zepBodyWidth / 4, zepBodyWidth / 3, zepBodyDepth / 1.5, 15);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepWindowCase_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepWindowCase_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepWindowCase_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepWindowCase_mat_shininess);
	glutSolidTorus(zepBodyWidth / 3, zepBodyWidth / 4, zepBodyDepth / 1.5, 10);
	glPopMatrix();

	glPopMatrix();
	glPushMatrix();
	glTranslatef(-zepBodyWidth * 1.15, zepBodyLength * -2.5, -zepBodyDepth / 3);
	glRotatef(3, 0, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(0.7, 0.7, 0.7);
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepDarkBrown_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepDarkBrown_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepDarkBrown_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepDarkBrown_mat_shininess);
	glutWireTorus(zepBodyWidth / 4, zepBodyWidth / 3, zepBodyDepth / 1.5, 15);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepWindowCase_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepWindowCase_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepWindowCase_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepWindowCase_mat_shininess);
	glutSolidTorus(zepBodyWidth / 3, zepBodyWidth / 4, zepBodyDepth / 1.5, 10);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}
void drawHangerTotalBox()
{
	// Windows
	glPushMatrix();
	glPushMatrix();
	glTranslatef(0, zepBodyLength / 1.5, -zepBodyDepth / 3);
	glScalef(1.05, 1.05, 1.05);
	drawWindows();

	glPopMatrix();
	drawWindows();
	glPopMatrix();



	// Hanger Teapot Collection
	glPushMatrix();
	glTranslatef(0, zepBodyLength * -0.5, 0);


	glPushMatrix();
	glTranslatef(zepBodyWidth * 0.2, 0, 0);
	glRotatef(-12, 0, 0, 1);
	drawHangerCombination();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(zepBodyWidth * -0.2, 0, 0);
	glRotatef(12, 0, 0, 1);
	drawHangerCombination();
	glPopMatrix();


	// Hanger Sphere Connections
	glPushMatrix();

	glTranslatef(0, -zepBodyLength * 0.9, zepBodyDepth / 5.5);
	glRotatef(15, 0, 0, 1);
	glRotatef(25, 1, 0, 0);
	glScalef(zepBodyWidth * 1.2, zepBodyLength * 2, zepBodyDepth * 0.80);
	glutSolidSphere(0.7, 25, 25);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0, -zepBodyLength * 0.9, zepBodyDepth / 5.5);
	glRotatef(-15, 0, 0, 1);
	glRotatef(25, 1, 0, 0);
	glScalef(zepBodyWidth * 1.2, zepBodyLength * 2, zepBodyDepth * 0.80);
	glutSolidSphere(0.7, 25, 25);

	glPopMatrix();

	glPopMatrix();

}
void drawHangerCombination()
{
	glPushMatrix();
	glTranslatef(0, zepBodyLength * -0.7, -zepBodyDepth * 0.65);
	drawHanger();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, zepBodyLength * -0.9, -zepBodyDepth * 0.60);
	drawHanger();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, zepBodyLength * -1.1, -zepBodyDepth * 0.55);
	drawHanger();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, zepBodyLength * -1.3, -zepBodyDepth * 0.5);
	drawHanger();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, zepBodyLength * -1.5, -zepBodyDepth * 0.45);
	drawHanger();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, zepBodyLength * -1.7, -zepBodyDepth * 0.4);
	drawHanger();
	glPopMatrix();
}
void drawHanger()
{

	glMaterialfv(GL_FRONT, GL_AMBIENT, zepDarkBrown_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepDarkBrown_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepDarkBrown_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepDarkBrown_mat_shininess);
	glPushMatrix();
	glScalef(zepBodyWidth, zepBodyLength * 1.5, zepBodyDepth);
	glRotatef(70, 1, 0, 0);
	glRotatef(-90, 0, 1, 0);
	glutSolidTeapot(1.0);
	glPopMatrix();
}
void drawZepBodyAccessories()
{

	glMaterialfv(GL_FRONT, GL_AMBIENT, zepDarkBrown_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepDarkBrown_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepDarkBrown_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepDarkBrown_mat_shininess);

	// ** Sharp Point 
	glPushMatrix();
	glTranslatef(0, 0, zepBodyDepth * 1.7);
	glScalef(zepBodyWidth, zepBodyLength * 1.5, zepBodyDepth);
	glutSolidCone(1.0, 1.0, 4, 4);
	glPopMatrix();

	// ** Side Encasing
	//--Back Encase
	glPushMatrix();
	glPushMatrix();
	glTranslatef(0, 0, -zepBodyDepth / 6);
	glScalef(zepBodyWidth * 1.2, zepBodyLength * 1.2, zepBodyDepth / 15);
	glutSolidSphere(2.0, 10, 10);
	glPopMatrix();
	//--Middle Encase
	glPushMatrix();
	glScalef(zepBodyWidth * 1.2, zepBodyLength * 1.2, zepBodyDepth / 5);
	glutWireSphere(2.0, 50, 5);
	glPopMatrix();
	//--Foward Encase
	glPushMatrix();
	glTranslatef(0, 0, zepBodyDepth / 6);
	glScalef(zepBodyWidth * 1.2, zepBodyLength * 1.2, zepBodyDepth / 15);
	glutSolidSphere(2.0, 10, 10);
	glPopMatrix();
	glPopMatrix();

	// ** Forward Round Total Encasing
	glPushMatrix();
	glScalef(zepBodyWidth / 3, zepBodyLength * 1.2, zepBodyDepth + zepBodyDepth / 8);
	glutSolidSphere(2.0, 10, 10);
	glPopMatrix();

	// ** Side Round Total Encasing
	glPushMatrix();
	glScalef(zepBodyWidth * 1.2, zepBodyLength / 2.7, zepBodyDepth + zepBodyDepth / 8);
	glutSolidSphere(2.0, 10, 10);
	glPopMatrix();

	// ** Donut Side Decal Left
	glPushMatrix();
	glTranslatef(zepBodyWidth * -1.51, 0, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(1.7, 0.6, 1);
	glutSolidTorus(zepBodyWidth / 3, zepBodyWidth * 2.1, zepBodyDepth / 1.5, 30);
	glPopMatrix();
	// ** Donut Side Decal Right
	glPushMatrix();
	glTranslatef(zepBodyWidth * 1.51, 0, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(1.7, 0.6, 1);
	glutSolidTorus(zepBodyWidth / 3, zepBodyWidth * 2.1, zepBodyDepth / 1.5, 30);
	glPopMatrix();

	// ** Box Top
	glPushMatrix();
	glTranslatef(0, zepBodyLength * 2.0, 0);
	glScalef(zepBodyWidth / 2, zepBodyLength / 2, zepBodyDepth / 5);
	glutSolidDodecahedron();
	glPopMatrix();


	// ** Metal Ring Sides
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepMetal_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepMetal_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepMetal_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepMetal_mat_shininess);
	glPushMatrix();
	glTranslatef(zepBodyWidth * 2.25, 0, 0);
	glRotatef(90, 0, 1, 0);
	glutWireTorus(zepBodyWidth / 4, zepBodyWidth / 3, zepBodyDepth / 1.5, 15);
	glutSolidTorus(zepBodyWidth / 3, zepBodyWidth / 2, zepBodyDepth / 1.5, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(zepBodyWidth * -2.25, 0, 0);
	glRotatef(90, 0, 1, 0);
	glutWireTorus(zepBodyWidth / 4, zepBodyWidth / 3, zepBodyDepth / 1.5, 15);
	glutSolidTorus(zepBodyWidth / 3, zepBodyWidth / 2, zepBodyDepth / 1.5, 10);
	glPopMatrix();




}
void drawAllTopBottomFins()
{



	// Draw Entire Top Back Fin
	glPushMatrix();
	drawMultiFinWhite();
	glPopMatrix();
	glPushMatrix();
	drawMultiFinBrown();
	glPopMatrix();

	// Draw Entire Bottom Back Fins
	glPushMatrix();
	glTranslatef(0, zepBodyWidth * -0.2, 0);

	glPushMatrix();
	glRotatef(-20, 0, 0, 1);
	glRotatef(180, 0, 0, 1);
	glPushMatrix();
	drawMultiFinWhite();
	drawMultiFinBrown();
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glRotatef(20, 0, 0, 1);
	glRotatef(180, 0, 0, 1);
	glPushMatrix();
	drawMultiFinWhite();
	drawMultiFinBrown();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	// Draw Entire Top Front Fin
	glPushMatrix();
	glTranslatef(0, zepBodyLength * 0.2, zepBodyDepth * 1.8);
	glScalef(1.0, 0.8, 0.8);
	drawMultiFinWhite();
	drawMultiFinBrown();
	glPopMatrix();

}
void drawMultiFinWhite()
{

	// Back Fin Top (#3)
	glPushMatrix();
	glTranslatef(0, zepBodyLength, zepBodyDepth * 0.6);
	glScalef(1.5, 1.0, 1.0);
	drawFinTopWhite();
	glPopMatrix();

	// Back Fin Top (#2)
	glPushMatrix();
	glTranslatef(0, zepBodyLength / 2, zepBodyDepth * 0.3);
	glScalef(1.3, 1.0, 1.0);
	drawFinTopWhite();
	glPopMatrix();

	// (Far) Back Fin Top (#1)
	drawFinTopWhite();
}
void drawMultiFinBrown()
{
	glPushMatrix();
	//Scale and translate  brown top fin to be smaller than white
	glScalef(0.7, 1.0, 1.0);
	glTranslatef(0, zepBodyLength * 0.2, zepBodyDepth * 0.001);

	// Back Fin Top (#3)
	glPushMatrix();
	glTranslatef(0, zepBodyLength, zepBodyDepth * 0.6);
	glScalef(1.5, 1.0, 1.0);
	drawFinTopBrown();
	glPopMatrix();

	// Back Fin Top (#2)
	glPushMatrix();
	glTranslatef(0, zepBodyLength / 2, zepBodyDepth * 0.3);
	glScalef(1.3, 1.0, 1.0);
	drawFinTopBrown();
	glPopMatrix();

	// (Far) Back Fin Top (#1)

	drawFinTopBrown();
	glPopMatrix();
}
void drawFinTopBrown()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepDarkBrown_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepDarkBrown_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepDarkBrown_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepDarkBrown_mat_shininess);
	// Rotate Fin to Position (Translated out for new rotational anchor point)
	glPushMatrix();
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(zepBodyWidth, 0, -zepBodyDepth * 1.8);

	// ** Build Fin Base
	// 
	// Second Extension
	glPushMatrix();
	glTranslatef(zepBodyLength / 5, 0, zepBodyDepth / 4.5);
	glRotatef(-10, 0.0, 1.0, 0.0);
	glScalef(zepBodyWidth * 2, zepBodyWidth / 4, zepBodyDepth / 2);
	glutSolidCube(1.0);
	glPopMatrix();

	//Front Extention
	glPushMatrix();
	glTranslatef(zepBodyWidth / -1.2, 0, zepBodyDepth / 1.5);
	glRotatef(-45, 0.0, 1.0, 0.0);
	glScalef(zepBodyWidth * 2, zepBodyWidth / 4, zepBodyDepth);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
}
void drawFinTopWhite()
{

	glMaterialfv(GL_FRONT, GL_AMBIENT, zepFin_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepFin_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepFin_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepFin_mat_shininess);
	// Rotate Fin to Position (Translated out for new rotational anchor point)
	glPushMatrix();
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(zepBodyWidth, 0, -zepBodyDepth * 1.8);

	// ** Build Fin Base
	// 
	// Second Extension
	glPushMatrix();
	glTranslatef(zepBodyLength / 5, 0, zepBodyDepth / 4.5);
	glRotatef(-10, 0.0, 1.0, 0.0);
	glScalef(zepBodyWidth * 2, zepBodyWidth / 4, zepBodyDepth / 2);
	glutSolidCube(1.0);
	glPopMatrix();

	//Front Extention
	glPushMatrix();
	glTranslatef(zepBodyWidth / -1.2, 0, zepBodyDepth / 1.5);
	glRotatef(-45, 0.0, 1.0, 0.0);
	glScalef(zepBodyWidth * 2, zepBodyWidth / 4, zepBodyDepth);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
}
double generateRandomAngle(double min, double max) {
	// Seed the random number generator with a random device
	std::random_device rd;

	// Use the Mersenne Twister engine
	std::mt19937 gen(rd());

	// Define the distribution for the desired range [0, 360)
	std::uniform_real_distribution<double> distrib(min, max);

	// Generate and return a random number
	return distrib(gen);
}


double randomAngle = generateRandomAngle(0,360);


// Enemy zep
void draw2Zeppelin()
{
	
	//Starting coordinates
	glTranslatef(zepstartEnemyX, zepstartEnemyY, zepstartEnemyZ);
	glPushMatrix();
	glTranslatef(0, -enemyZepDone/2, 0);
	// Move Forwards
	glTranslatef(zepEX, verticaly-4, zepEZ);


	//Rotate Zeppelin
	glRotatef(-angle_deg, 0.0, 1.0, 0.0);
	glRotatef(enemyZepDone, 1.0, 1.0, 1.0);
	
	

	// Enemy BULLET
	glPushMatrix();
	glPushMatrix();
	// Rotate Bullet Enemy
	glRotatef(angle_degEnemyB, 0.0, 1.0, 0.0);
	// Move bullet
	glTranslatef(bulletEx, bulletEy, bulletEz);
	GLUquadric* quadric2 = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, textureID1);
	gluQuadricTexture(quadric2, GL_TRUE);
	glTranslatef(0, zepBodyLength*4.5, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(zepBodyWidth / 1.5, zepBodyWidth / 1.5, zepBodyWidth / 1.5);
	gluSphere(quadric2, 1.0, 10, 10);
	gluDeleteQuadric(quadric2);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	// Calibrate Orientation
	glRotatef(90, 0.0, 1.0, 0.0);
	draw2ZepBody();
	draw2ZepBodyAccessories();
	draw2AllTopBottomFins();
	draw2TailFinCollection();
	draw2HangerTotalBox();
	draw2PropellerCollection();
	glPopMatrix();

	glPopMatrix();

}
void draw2PropellerCollection()
{
	glPushMatrix();
	// Rotate Propellers
	glRotatef(onlyPropRotate * 5, 0.0, 0.0, 1.0);


	glPushMatrix();
	glTranslatef(0, 0, zepBodyDepth / 8);
	glScalef(0.9, 0.9, 1.0);
	glRotatef(propellerRotate / 3, 0, 0, 1);
	draw2Propeller();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.9, 0.9, 1.0);
	glRotatef(propellerRotate / 2, 0, 0, 1);
	draw2Propeller();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -zepBodyDepth / 8);
	draw2Propeller();
	glPopMatrix();

	glPopMatrix();
}
void draw2Propeller()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepFininvert_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepFininvert_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepFininvert_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepFininvert_mat_shininess);

	// Proppeller 1
	glPushMatrix();
	glTranslatef(0, 0, -zepBodyDepth * 2.7);
	glScalef(zepBodyWidth / 2, zepBodyWidth / 7, zepBodyDepth / 80);
	glutSolidSphere(2.0, 10, 10);
	glPopMatrix();

	// Proppeller 2
	glPushMatrix();
	glTranslatef(0, 0, -zepBodyDepth * 2.7);
	glScalef(zepBodyWidth / 7, zepBodyWidth / 2, zepBodyDepth / 80);
	glutSolidSphere(2.0, 10, 10);
	glPopMatrix();

}
void draw2ring() {
	glTranslatef(0, 0, zepBodyDepth * 0.5);
	glutSolidTorus(zepBodyWidth / 2.5, zepBodyWidth / 1.5, 20, 20);
}
void draw2ZepBody()
{

	// Body of Zeppelin
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepBodyinvert_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepBodyinvert_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepBodyinvert_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepBodyinvert_mat_shininess);

	glPushMatrix();
	GLUquadric* quadric2 = gluNewQuadric();
	gluQuadricTexture(quadric2, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D, textureID2);
	glScalef(zepBodyWidth, zepBodyLength, zepBodyDepth);
	gluSphere(quadric2, 2.0, 10, 10);
	gluDeleteQuadric(quadric2);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	

	// Black
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepFininvert_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepFininvert_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepFininvert_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepFininvert_mat_shininess);
	
	//tube gun
	glPushMatrix();
	glTranslatef(0, zepBodyLength * 3.5, zepBodyDepth * 0);
	glRotatef(45, 1, 1, 0);
	glScalef(zepBodyWidth/3, zepBodyLength*1, zepBodyDepth/7);
	glutSolidDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, 0.5);
	glTranslatef(0, zepBodyLength * 4.5, zepBodyDepth * 0.8);
	glutSolidTorus(zepBodyWidth / 2.5, zepBodyWidth / 1.5,20,20);
	glScalef(1, 1, 0.5);
	draw2ring();
	draw2ring();
	draw2ring();
	draw2ring();
	draw2ring();
	draw2ring();
	draw2ring();
	draw2ring();
	draw2ring();
	draw2ring();
	draw2ring();
	draw2ring();
	glPopMatrix();

	// Red
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepDarkBrowninvert_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepDarkBrowninvert_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepDarkBrowninvert_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepDarkBrowninvert_mat_shininess);
	//WIRE gun
	glPushMatrix();
	glTranslatef(0, zepBodyLength*4.5, zepBodyDepth * 1.2);
	glScalef(zepBodyWidth / 6, zepBodyLength/6, zepBodyDepth/4);
	glutWireSphere(zepBodyDepth /1.0, 20, 20);
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepFininvert_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepFininvert_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepFininvert_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepFininvert_mat_shininess);
	glScalef(0.5, 0.5, 1);
	glutSolidSphere(zepBodyDepth, 20, 20);
	glPopMatrix();


	
	//Back Tube of Zeppelin
	glPushMatrix();
	glTranslatef(0, 0, zepBodyDepth * -2);
	glScalef(zepBodyWidth, zepBodyLength / 1.5, zepBodyDepth);
	glutSolidTorus(zepBodyWidth / 3, zepBodyWidth / 2, zepBodyDepth / 1.5, 10);
	glPopMatrix();
	// Stick
	glPushMatrix();
	glTranslatef(0, 0, -zepBodyDepth * 2.5);
	glScalef(zepBodyWidth / 7, zepBodyWidth / 7, zepBodyDepth);
	glutSolidSphere(1.0, 10, 10);
	glPopMatrix();

	// Brown Donut Tube of Zeppelin
	glPushMatrix();
	glTranslatef(0, 0, zepBodyDepth * -1.5);
	glRotatef(90, 0, 1, 0);
	glScalef(zepBodyDepth / 3, 0.3, 0.5);
	glutSolidTorus(zepBodyWidth / 3, zepBodyLength * 4.0, 20, 20);
	glPopMatrix();

}
void draw2TailFinCollection()
{
	glPushMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepFininvert_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepFininvert_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepFininvert_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepFininvert_mat_shininess);
	glTranslatef(0, 0, zepBodyDepth * 0.1);
	draw2TailFinBase();
	glPopMatrix();


	glMaterialfv(GL_FRONT, GL_AMBIENT, zepDarkBrowninvert_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepDarkBrowninvert_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepDarkBrowninvert_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepDarkBrowninvert_mat_shininess);
	glScalef(1, 0.8, 1);
	draw2TailFinBase();
	glPopMatrix();
}
void draw2TailFinBase()
{
	glPushMatrix();
	//	glMaterialfv(GL_FRONT, GL_AMBIENT, zepFininvert_mat_ambient);
	//	glMaterialfv(GL_FRONT, GL_SPECULAR, zepFininvert_mat_specular);
	//	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepFininvert_mat_diffuse);
	glTranslatef(0, zepBodyLength / 1.3, -zepBodyDepth * 4);
	glRotatef(90, 1, 0, 0);
	glScalef(zepBodyDepth / 6, zepBodyLength * 2, zepBodyDepth / 3);
	glRotatef(90, 0, 1, 0);
	glutSolidTetrahedron();
	glPopMatrix();

	glPushMatrix();
	//	glMaterialfv(GL_FRONT, GL_AMBIENT, zepFininvert_mat_ambient);
	//	glMaterialfv(GL_FRONT, GL_SPECULAR, zepFininvert_mat_specular);
	//	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepFininvert_mat_diffuse);
	glTranslatef(0, -zepBodyLength / 1.3, -zepBodyDepth * 4);
	glRotatef(180, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glScalef(zepBodyDepth / 6, zepBodyLength * 2, zepBodyDepth / 3);
	glRotatef(90, 0, 1, 0);
	glutSolidTetrahedron();
	glPopMatrix();

}
void draw2Windows()
{
	glPushMatrix();


	glPushMatrix();
	glTranslatef(zepBodyWidth * 1.15, zepBodyLength * -2.5, -zepBodyDepth / 3);
	glRotatef(-3, 0, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(0.7, 0.7, 0.7);


	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepDarkBrowninvert_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepDarkBrowninvert_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepDarkBrowninvert_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepDarkBrowninvert_mat_shininess);
	glutWireTorus(zepBodyWidth / 4, zepBodyWidth / 3, zepBodyDepth / 1.5, 15);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepWindowCase_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepWindowCase_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepWindowCase_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepWindowCase_mat_shininess);
	glutSolidTorus(zepBodyWidth / 3, zepBodyWidth / 4, zepBodyDepth / 1.5, 10);
	glPopMatrix();

	glPopMatrix();
	glPushMatrix();
	glTranslatef(-zepBodyWidth * 1.15, zepBodyLength * -2.5, -zepBodyDepth / 3);
	glRotatef(3, 0, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(0.7, 0.7, 0.7);
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepDarkBrowninvert_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepDarkBrowninvert_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepDarkBrowninvert_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepDarkBrowninvert_mat_shininess);
	glutWireTorus(zepBodyWidth / 4, zepBodyWidth / 3, zepBodyDepth / 1.5, 15);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepWindowCase_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepWindowCase_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepWindowCase_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepWindowCase_mat_shininess);
	glutSolidTorus(zepBodyWidth / 3, zepBodyWidth / 4, zepBodyDepth / 1.5, 10);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}
void draw2HangerTotalBox()
{
	// Windows
	glPushMatrix();
	glPushMatrix();
	glTranslatef(0, zepBodyLength / 1.5, -zepBodyDepth / 3);
	glScalef(1.05, 1.05, 1.05);
	draw2Windows();

	glPopMatrix();
	draw2Windows();
	glPopMatrix();



	// Hanger Teapot Collection
	glPushMatrix();
	glTranslatef(0, zepBodyLength * -0.5, 0);


	glPushMatrix();
	glTranslatef(zepBodyWidth * 0.2, 0, 0);
	glRotatef(-12, 0, 0, 1);
	draw2HangerCombination();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(zepBodyWidth * -0.2, 0, 0);
	glRotatef(12, 0, 0, 1);
	draw2HangerCombination();
	glPopMatrix();


	// Hanger Sphere Connections
	glPushMatrix();

	glTranslatef(0, -zepBodyLength * 0.9, zepBodyDepth / 5.5);
	glRotatef(15, 0, 0, 1);
	glRotatef(25, 1, 0, 0);
	glScalef(zepBodyWidth * 1.2, zepBodyLength * 2, zepBodyDepth * 0.80);
	glutSolidSphere(0.7, 25, 25);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0, -zepBodyLength * 0.9, zepBodyDepth / 5.5);
	glRotatef(-15, 0, 0, 1);
	glRotatef(25, 1, 0, 0);
	glScalef(zepBodyWidth * 1.2, zepBodyLength * 2, zepBodyDepth * 0.80);
	glutSolidSphere(0.7, 25, 25);

	glPopMatrix();

	glPopMatrix();

}
void draw2HangerCombination()
{
	glPushMatrix();
	glTranslatef(0, zepBodyLength * -0.7, -zepBodyDepth * 0.65);
	draw2Hanger();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, zepBodyLength * -0.9, -zepBodyDepth * 0.60);
	draw2Hanger();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, zepBodyLength * -1.1, -zepBodyDepth * 0.55);
	draw2Hanger();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, zepBodyLength * -1.3, -zepBodyDepth * 0.5);
	draw2Hanger();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, zepBodyLength * -1.5, -zepBodyDepth * 0.45);
	draw2Hanger();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, zepBodyLength * -1.7, -zepBodyDepth * 0.4);
	draw2Hanger();
	glPopMatrix();
}
void draw2Hanger()
{

	glMaterialfv(GL_FRONT, GL_AMBIENT, zepDarkBrowninvert_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepDarkBrowninvert_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepDarkBrowninvert_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepDarkBrowninvert_mat_shininess);
	glPushMatrix();
	glScalef(zepBodyWidth, zepBodyLength * 1.5, zepBodyDepth);
	glRotatef(70, 1, 0, 0);
	glRotatef(-90, 0, 1, 0);
	glutSolidTeapot(1.0);
	glPopMatrix();
}
void draw2ZepBodyAccessories()
{

	glMaterialfv(GL_FRONT, GL_AMBIENT, zepDarkBrowninvert_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepDarkBrowninvert_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepDarkBrowninvert_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepDarkBrowninvert_mat_shininess);

	// ** Sharp Point 
	glPushMatrix();
	glTranslatef(0, 0, zepBodyDepth * 1.7);
	glScalef(zepBodyWidth, zepBodyLength * 1.5, zepBodyDepth);
	glutSolidCone(1.0, 1.0, 4, 4);
	glPopMatrix();

	// ** Side Encasing
	//--Back Encase
	glPushMatrix();
	glPushMatrix();
	glTranslatef(0, 0, -zepBodyDepth / 6);
	glScalef(zepBodyWidth * 1.2, zepBodyLength * 1.2, zepBodyDepth / 15);
	glutSolidSphere(2.0, 10, 10);
	glPopMatrix();
	//--Middle Encase
	glPushMatrix();
	glScalef(zepBodyWidth * 1.2, zepBodyLength * 1.2, zepBodyDepth / 5);
	glutWireSphere(2.0, 50, 5);
	glPopMatrix();
	//--Foward Encase
	glPushMatrix();
	glTranslatef(0, 0, zepBodyDepth / 6);
	glScalef(zepBodyWidth * 1.2, zepBodyLength * 1.2, zepBodyDepth / 15);
	glutSolidSphere(2.0, 10, 10);
	glPopMatrix();
	glPopMatrix();

	// ** Forward Round Total Encasing
	glPushMatrix();
	glScalef(zepBodyWidth / 3, zepBodyLength * 1.2, zepBodyDepth + zepBodyDepth / 8);
	glutSolidSphere(2.0, 10, 10);
	glPopMatrix();

	// ** Side Round Total Encasing
	glPushMatrix();
	glScalef(zepBodyWidth * 1.2, zepBodyLength / 2.7, zepBodyDepth + zepBodyDepth / 8);
	glutSolidSphere(2.0, 10, 10);
	glPopMatrix();

	// ** Donut Side Decal Left
	glPushMatrix();
	glTranslatef(zepBodyWidth * -1.51, 0, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(1.7, 0.6, 1);
	glutSolidTorus(zepBodyWidth / 3, zepBodyWidth * 2.1, zepBodyDepth / 1.5, 30);
	glPopMatrix();
	// ** Donut Side Decal Right
	glPushMatrix();
	glTranslatef(zepBodyWidth * 1.51, 0, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(1.7, 0.6, 1);
	glutSolidTorus(zepBodyWidth / 3, zepBodyWidth * 2.1, zepBodyDepth / 1.5, 30);
	glPopMatrix();

	// ** Box Top
	glPushMatrix();
	glTranslatef(0, zepBodyLength * 2.0, 0);
	glScalef(zepBodyWidth / 2, zepBodyLength / 2, zepBodyDepth / 5);
	glutSolidDodecahedron();
	glPopMatrix();


	// ** Metal Ring Sides
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepMetal_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepMetal_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepMetal_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepMetal_mat_shininess);
	glPushMatrix();
	glTranslatef(zepBodyWidth * 2.25, 0, 0);
	glRotatef(90, 0, 1, 0);
	glutWireTorus(zepBodyWidth / 4, zepBodyWidth / 3, zepBodyDepth / 1.5, 15);
	glutSolidTorus(zepBodyWidth / 3, zepBodyWidth / 2, zepBodyDepth / 1.5, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(zepBodyWidth * -2.25, 0, 0);
	glRotatef(90, 0, 1, 0);
	glutWireTorus(zepBodyWidth / 4, zepBodyWidth / 3, zepBodyDepth / 1.5, 15);
	glutSolidTorus(zepBodyWidth / 3, zepBodyWidth / 2, zepBodyDepth / 1.5, 10);
	glPopMatrix();




}
void draw2AllTopBottomFins()
{



	// draw2 Entire Top Back Fin
	glPushMatrix();
	draw2MultiFinWhite();
	glPopMatrix();
	glPushMatrix();
	draw2MultiFinBrown();
	glPopMatrix();

	// draw2 Entire Bottom Back Fins
	glPushMatrix();
	glTranslatef(0, zepBodyWidth * -0.2, 0);

	glPushMatrix();
	glRotatef(-20, 0, 0, 1);
	glRotatef(180, 0, 0, 1);
	glPushMatrix();
	draw2MultiFinWhite();
	draw2MultiFinBrown();
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glRotatef(20, 0, 0, 1);
	glRotatef(180, 0, 0, 1);
	glPushMatrix();
	draw2MultiFinWhite();
	draw2MultiFinBrown();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	// draw2 Entire Top Front Fin
	glPushMatrix();
	glTranslatef(0, zepBodyLength * 0.2, zepBodyDepth * 1.8);
	glScalef(1.0, 0.8, 0.8);
	draw2MultiFinWhite();
	draw2MultiFinBrown();
	glPopMatrix();

}
void draw2MultiFinWhite()
{

	// Back Fin Top (#3)
	glPushMatrix();
	glTranslatef(0, zepBodyLength, zepBodyDepth * 0.6);
	glScalef(1.5, 1.0, 1.0);
	draw2FinTopWhite();
	glPopMatrix();

	// Back Fin Top (#2)
	glPushMatrix();
	glTranslatef(0, zepBodyLength / 2, zepBodyDepth * 0.3);
	glScalef(1.3, 1.0, 1.0);
	draw2FinTopWhite();
	glPopMatrix();

	// (Far) Back Fin Top (#1)
	draw2FinTopWhite();
}
void draw2MultiFinBrown()
{
	glPushMatrix();
	//Scale and translate  brown top fin to be smaller than white
	glScalef(0.7, 1.0, 1.0);
	glTranslatef(0, zepBodyLength * 0.2, zepBodyDepth * 0.001);

	// Back Fin Top (#3)
	glPushMatrix();
	glTranslatef(0, zepBodyLength, zepBodyDepth * 0.6);
	glScalef(1.5, 1.0, 1.0);
	draw2FinTopBrown();
	glPopMatrix();

	// Back Fin Top (#2)
	glPushMatrix();
	glTranslatef(0, zepBodyLength / 2, zepBodyDepth * 0.3);
	glScalef(1.3, 1.0, 1.0);
	draw2FinTopBrown();
	glPopMatrix();

	// (Far) Back Fin Top (#1)

	draw2FinTopBrown();
	glPopMatrix();
}
void draw2FinTopBrown()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, zepDarkBrowninvert_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepDarkBrowninvert_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepDarkBrowninvert_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepDarkBrowninvert_mat_shininess);
	// Rotate Fin to Position (Translated out for new rotational anchor point)
	glPushMatrix();
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(zepBodyWidth, 0, -zepBodyDepth * 1.8);

	// ** Build Fin Base
	// 
	// Second Extension
	glPushMatrix();
	glTranslatef(zepBodyLength / 5, 0, zepBodyDepth / 4.5);
	glRotatef(-10, 0.0, 1.0, 0.0);
	glScalef(zepBodyWidth * 2, zepBodyWidth / 4, zepBodyDepth / 2);
	glutSolidCube(1.0);
	glPopMatrix();

	//Front Extention
	glPushMatrix();
	glTranslatef(zepBodyWidth / -1.2, 0, zepBodyDepth / 1.5);
	glRotatef(-45, 0.0, 1.0, 0.0);
	glScalef(zepBodyWidth * 2, zepBodyWidth / 4, zepBodyDepth);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
}
void draw2FinTopWhite()
{

	glMaterialfv(GL_FRONT, GL_AMBIENT, zepFininvert_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zepFininvert_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zepFininvert_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, zepFininvert_mat_shininess);
	// Rotate Fin to Position (Translated out for new rotational anchor point)
	glPushMatrix();
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(zepBodyWidth, 0, -zepBodyDepth * 1.8);

	// ** Build Fin Base
	// 
	// Second Extension
	glPushMatrix();
	glTranslatef(zepBodyLength / 5, 0, zepBodyDepth / 4.5);
	glRotatef(-10, 0.0, 1.0, 0.0);
	glScalef(zepBodyWidth * 2, zepBodyWidth / 4, zepBodyDepth / 2);
	glutSolidCube(1.0);
	glPopMatrix();

	//Front Extention
	glPushMatrix();
	glTranslatef(zepBodyWidth / -1.2, 0, zepBodyDepth / 1.5);
	glRotatef(-45, 0.0, 1.0, 0.0);
	glScalef(zepBodyWidth * 2, zepBodyWidth / 4, zepBodyDepth);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
}



// Callback, called at initialization and whenever user resizes the window.
void reshape(int w, int h)
{
	// Set up viewport, projection, then change to modelview matrix mode - 
	// display function will then set up camera and do modeling transforms.
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLdouble)w / h, 0.1, 650.0);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	// Set up the camera at position (0, 6, 22) looking at the origin, up along positive y axis
	//gluLookAt(0.0, 20.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

bool stop = false;

// Callback, handles input from the keyboard, non-arrow keys
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		forwardx += forwardVector * cosf(degToRad(propellerRotate));
		forwardz -= forwardVector * sinf(degToRad(propellerRotate));
		stop = false;
		camerax -= forwardVector * cosf(degToRad(propellerRotate));
		cameraz += forwardVector * sinf(degToRad(propellerRotate));
		glutTimerFunc(10, animationUpdater, 0);
		break;
	case 's':
		spawnEnemy = !spawnEnemy;

		glutTimerFunc(10, animationUpdater, 0);
		break;
	case ' ':
		//Player Fire
		if (!SHIELD){
		playerfire = 1;
		}
		break;
	case 'q':
		//Player Fire
		SHIELD = !SHIELD;
		break;
	case 'r':
		//Switch Perspective
		useFirstGluLookAt = !useFirstGluLookAt;
		break;

		
	}

	glutPostRedisplay();   // Trigger a window redisplay
}

float running = 0.5;
float rotPassive = 0;
float aquistitionDistance = 150;
int figureEight = 1;
float randomRotationSpeed = generateRandomAngle(1, 4);
int fire = 0;
int dragLength = 10;
string ENEMYATTACK = "IDLE";
string PLAYERATTACK = "IDLE";
int bulletTimer = 60;
void animationHandler(int param)
{	
	if(!stop){
	if(spawnEnemy==true){
		if (distanceBetween > aquistitionDistance) {

			// Update rotation angle (Figure 8)
			rotPassive += randomRotationSpeed * figureEight;
			if (rotPassive >= 360 || rotPassive <= 0) {
				figureEight *= -1;  // Change direction when reaching 0 or 360 degrees
				randomRotationSpeed = generateRandomAngle(1, 5);
			}


			angle_deg = rotPassive;
			zepEX += enemySpeed / 2 * cosf(degToRad(rotPassive));
			zepEZ += enemySpeed / 2 * sinf(degToRad(rotPassive));
	}

	//Update Enemy Rotation
	zepX = +forwardx;
	zepZ = +forwardz;
	dx = zepX + zepstartMeX - zepEX;
	dz = zepZ + zepstartMeZ - zepEZ;

	if (distanceBetween < aquistitionDistance && ENEMYHEALTH > 0) {
		angle_deg = atan2(dz, dx) * (180.0 / M_PI);
		angle_rad = angle_deg * M_PI / 180.0;
	}
	//Calculate Distance between Me and Enemy
	distanceBetween = sqrt(pow(zepX + zepstartMeX - (zepEX + zepstartEnemyX), 2) + pow(zepZ + zepstartMeZ - (zepEZ - zepstartEnemyZ), 2));

	if (distanceBetween > 20 && distanceBetween < aquistitionDistance) {
		dx2 = enemySpeed * cos(angle_rad) * cos(enemySpeed) * cos(enemySpeed);
		dz2 = enemySpeed * sin(angle_rad) * sin(enemySpeed) * sin(enemySpeed);
		//Update Enemy Position
		if (ENEMYHEALTH > 0) {
		zepEX += dx2;
		zepEZ += dz2;
		}
	}
	

	//Calculate Distance Ebullet and Me (for Collision)
	if (ENEMYHEALTH > 0){
	distanceBetweenE = sqrt(pow((zepX) - (bulletEx + zepEX), 2) + pow((zepZ) - (bulletEz + zepEZ), 2));

	if (distanceBetweenE < aquistitionDistance || fire == 0) {
			angle_degEnemyB = atan2(dz, dx) * (180.0 / M_PI);
			angle_radEnemyB = angle_degEnemyB * M_PI / 180.0;
			dx2 = 10* bulletSpeed * cosf(angle_radEnemyB);
			dz2 = 10* bulletSpeed * sinf(angle_radEnemyB);
			fire = 1;
	}
	else if (distanceBetweenE >= aquistitionDistance) {
		bulletEx = 0;
		bulletEy = 0;
		bulletEz = 0;
		fire = 0;
	}

	if (distanceBetween >= aquistitionDistance) {
		bulletEx = -10000;
		bulletEy = -10000;
		bulletEz = -10000;
	}
	else {
		bulletEx += dx2;
		bulletEz += dz2;
	}
	}
	}
	/*
	std::cout << "\nx: " << bulletEx;
	std::cout << "\ty: " << bulletEy;
	std::cout << "\tz: " << bulletEz;
	*/

	if (spawnEnemy==true){
	//Calculate Distance Pbullet and Enemy (for Collision)
	distanceBetweenP = sqrt(pow((zepEX) - (bulletPx + zepX), 2) + pow((zepEZ) - (bulletPz + zepZ), 2));
	}

	if (bulletTimer <= 0) {
		bulletPx = 0;
		bulletPy = 0;
		bulletPz = 0;
		playerfire = 0;
		bulletTimer = 60;
	}
	if (playerfire == 1 && bulletTimer > 0) {
		dxP = zepEX + zepstartEnemyX - zepX;
		dzP = zepEZ + zepstartEnemyZ - zepZ;
		angle_degPlayerB = (atan2(dzP, dxP) * (180.0 / M_PI));
		angle_radPlayerB = angle_degPlayerB * M_PI / 180.0;
		dxP2 = 20 * bulletSpeed * cosf(angle_radPlayerB);
		dzP2 = 20 * bulletSpeed * sinf(angle_radPlayerB);
		bulletTimer -= 1;

	}
	else {
		bulletPx = 0;
		bulletPy = 0;
		bulletPz = 0;
		playerfire = 0;
		
	}
	bulletPx += dxP2;
	bulletPz += dzP2;



	// ENEMY HITS PLAYER
	if (distanceBetweenE < 20 && spawnEnemy == true && !SHIELD) {
		ENEMYATTACK = "HIT";
		PLAYERHEALTH -= 1;

		if (PLAYERHEALTH < 0) {
			glutTimerFunc(20, dieUpdater, 0);
		}

	}
	else if (distanceBetweenE < 20 && spawnEnemy == true && SHIELD) {
		ENEMYATTACK = "BLOCKED";
	}
	else {
		ENEMYATTACK = "IDLE";
	}

	// PLAYER HITS ENEMY
	if (distanceBetweenP < 20 && spawnEnemy == true) {
		PLAYERATTACK = "HIT";
		ENEMYHEALTH -= 1;
		if (ENEMYHEALTH < 0) {
			glutTimerFunc(20, dieUpdater, 0);
		}
	}
	else {
		PLAYERATTACK = "IDLE";
	}
	/*
	std::cout << "\nDmged:" << ENEMYATTACK;
	std::cout << "| Ph:" << PLAYERHEALTH;

	std::cout << "| MeHit:" << PLAYERATTACK;
	std::cout << "| Eh:" << ENEMYHEALTH;
	*/
	onlyPropRotate += 20;
	glutTimerFunc(20, animationHandler, 0);

	}
	glutPostRedisplay();
	
}

void animationUpdater(int param){

glutPostRedisplay();
}

void dieUpdater(int param) {
	if (PLAYERHEALTH < 0) {
		playerZepdone -= 10;
	} else if(ENEMYHEALTH < 0){
		enemyZepDone -= 10;
	}
	glutTimerFunc(20, animationHandler, 0);
	glutPostRedisplay();
}


// Callback, handles input from the keyboard, function and arrow -  keys
void functionKeys(int key, int x, int y)
{
	// Help key
	if (key == GLUT_KEY_LEFT)
	{
		propellerRotate += 8.0;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		propellerRotate -= 8.0;
	}
	else if (key == GLUT_KEY_UP)
	{
		verticaly += 1;
		cameray = -verticaly;
	}
	else if (key == GLUT_KEY_DOWN)
	{
		verticaly -= 1;
		cameray = -verticaly;
	}
	else if (key == GLUT_KEY_F1) {
		test += 1;
		printf("%f\n", test);
	}
	else if (key == GLUT_KEY_F2) {
		test -= 1;
		printf("%f\n", test);
	}

	glutPostRedisplay();   // Trigger a window redisplay
}


// Mouse button callback - use only if you want to 
void mouse(int button, int state, int x, int y)
{
	currentButton = button;

	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{

		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{

		}
		break;
	default:
		break;
	}

	glutPostRedisplay();   // Trigger a window redisplay
}


// Mouse motion callback - use only if you want to 
void mouseMotionHandler(int xMouse, int yMouse)
{
	if (currentButton == GLUT_LEFT_BUTTON)
	{
		;
	}

	glutPostRedisplay();   // Trigger a window redisplay
}

