/*****
 * Author: Aimee Savage, Selah-Mae Ross, and Scott Dunham
 *
 * Katamari.cpp
 *
 * CS315 Final Project: Katamari
 *
 * Stencil author: David Akers
 *sources: http://www.comp.nus.edu.sg/~pavelkor/cs3241/faq.html   for first person
 *http://www.opengl.org/resources/libraries/glut/spec3/node54.html  for special keys
 *
 *****/
#include "stglew.h"
#include <math.h>
#include "cs315.h"
#include "katamari.h"
#include "mesh.h"
#include "tga.h"
#include <iostream>
#include <vector>
#include <windows.h>


#include <STShaderProgram.h>

STShaderProgram *phongShader;
const char *phongVertexShaderFilename = "phong_vertex_barebones.glsl";
const char *phongFragmentShaderFilename = "phong_fragment_barebones.glsl";
bool phong_shading_enabled = true;

using namespace std;
unsigned int mytex = 0;
unsigned int mytex2 = 0;
unsigned int mytex3 = 0;
unsigned int signtex = 0; //Added by Scott
GLuint buildingDL;
GLuint blockDL;
double lastT;
//double firstPersonZ = 0.0;
//double firstPersonX = 0.0;
const double PI = 3.1415926;
const double DEG_TO_RAD = PI / 180.0;
int mouse_lastx, mouse_lasty;
int screenHeight = 480;
int screenWidth = 640;
const double ROTATE_RATE = 0.75;
const double ZOOM_RATE = 0.05;
// Which button is being dragged right now?
int dragging;
int last_mouse_valid;
float ex, ey, ez;
float ballPositionX;
float ballPositionZ;
float distanceCalc;
float overlapCalc;
double mouse_theta;
double mouse_delta;
double firstPersonX;
double firstPersonZ;
double firstPersonRotate;
int firstPerson;
double ballMove;
int theta;
int lightPosY;
int lightPosX;
int fog;
int direction;
int game_on;
int difficulty;
Tobor kata; //Added by Scott
bool animateTobor;
  
  bool rArmMoving;
  bool lArmMoving;
  bool legsMoving;
  
  bool rArmRising;
  bool lArmRising;
  bool rForearmRising;
  bool lForearmRising;
  bool leftLegRising;
  bool leftThighRising;
  bool rightLegRising;
  bool rightThighRising;
  
  float torso_angle_y;
  float torso_angle_x;
  float right_arm_angle;
  float left_arm_angle;
  float right_forearm_angle;
  float left_forearm_angle;
  float left_thigh_angle;
  float right_thigh_angle;
  float right_leg_angle;
  float left_leg_angle;

vector<Ball> balls;
Ball player;
Mesh m;

//FOG
GLfloat fogColor[4]= {0.5f, 0.5f, 0.5f, 1.0f};
/******
 Methods you need to fill in:
******/

//Test the distance between player sphere and each enemy sphere. If they collide, transfer collision ammount to larger of the two
void Katamari::collisions(){
	for(int i=0;i<balls.size();i++){
		distanceCalc = sqrt((ballPositionX - balls[i].getX())*(ballPositionX - balls[i].getX()) + (ballPositionZ - balls[i].getZ())*(ballPositionZ - balls[i].getZ()));
		if(distanceCalc < player.getSize() + balls[i].getSize()){
			//std::cout << "Collision with Enemy #" << i << "!\n";
			overlapCalc = (player.getSize()/distanceCalc)*0.05; //multiplying by 0.05 smooths the animation by quite a bit
			if(player.getSize() > 0 && balls[i].getSize() > 0){
				if(player.getSize() > balls[i].getSize()){
					player.setSize(player.getSize() + overlapCalc);
					balls[i].setSize(distanceCalc - player.getSize() - overlapCalc);
				}
				else{
					balls[i].setSize(balls[i].getSize() + overlapCalc);
					player.setSize(distanceCalc - balls[i].getSize() - overlapCalc);
				}
			}
		}
	}
}

//Resets player and enemy spheres
void Katamari::reset_game(){
	//INITIALIZE ENEMY BALLS
	balls.clear();
	for(int i = 0; i<25*difficulty; i++){
		Ball ball;
		float xPath = CS315::RandInt(7)-2;
		float zPath = CS315::RandInt(3)-1;
		float ballSize = (CS315::RandFloat()*1.5)+0.25;
		ball.setSize(ballSize);
		//ball.setColor(MAT_GREEN);
		float ballSpeed = (CS315::RandFloat()+0.3)*10;
		ball.setSpeed(ballSpeed);
		int distance = CS315::RandInt(20)+10;
		ball.setTravelDist(distance);
		ball.setX(-12.0+xPath*20.0);
		ball.setZ(-12.0+zPath*20.0);
		ball.setTurn(1);
		int isX = CS315::RandInt(2);
		ball.xORz = isX;
		balls.push_back(ball);
	}

	//Initialize Player Sphere
	player.setColor(MAT_BLUE);
	player.setSize(1.0);
	ballPositionX = -2.25;
	ballPositionZ = 28.0;
	distanceCalc = 0.0;
	overlapCalc = 0.0;
	direction = 1;
	game_on = 0;
	ex=-2.25;
	ey=130.0;
	ez=5;
	PlaySound(TEXT("Katamari.wav"), NULL, SND_ASYNC | SND_LOOP);
}

void Katamari::game_over(){
	if(player.getSize() <= 0){
		game_on = 1; //Game over!
		cout << "Game Over!\n";
		PlaySound(TEXT("smb_gameover.wav"), NULL, SND_ASYNC);
	}
	int i = 0;
	while(i<balls.size() && balls[i].getSize() <= 0){
		i++;
	}
	if(i==balls.size()){
		game_on = 2; //You win!!!
		cout << "You win!\n";
		PlaySound(TEXT("smb_stage_clear.wav"), NULL, SND_ASYNC);
	}
}

void Katamari::loadModel(const char *filename){
 // Load the model
  m.init(filename);

  if (m.getFTotal() == 0) return;

  // Scale it to fit in a small box
  float minx, maxx;
  float miny, maxy;
  float minz, maxz;

  static const float MAX_SIZE = 1.0f;
  
   int nvertices = m.getVList().size();

  int i;

  for(i=1; i<nvertices; i++) {
    // note: first vertex is "default vertex" - avoid using this as part of size calculations
    Vec3 v = m.getVList()[i];
    if (i == 1 || (v[0] < minx)) minx = v[0];
    if (i == 1 || (v[1] < miny)) miny = v[1];
    if (i == 1 || (v[2] < minz)) minz = v[2];
    if (i == 1 || (v[0] > maxx)) maxx = v[0];
    if (i == 1 || (v[1] > maxy)) maxy = v[1];
    if (i == 1 || (v[2] > maxz)) maxz = v[2];      
  }

  float xcenter = (maxx + minx) / 2.0;
  float ycenter = (maxy + miny) / 2.0;
  float zcenter = (maxz + minz) / 2.0;

  // Find the largest axis
  float span = maxx-minx;
  if (maxy - miny > span) span = maxy-miny;
  if (maxz - minz > span) span = maxz-minz;

  float scale_factor = MAX_SIZE / span;
  
  // Scale and translate each vertex to put the object in
  // a nice box

  for(i=0; i<nvertices; i++) {
    Vec3 v = m.getVList()[i];

    v[0] -= xcenter;
    v[1] -= ycenter;
    v[2] -= zcenter;

    v[0] *= scale_factor;
    v[1] *= scale_factor;
    v[2] *= scale_factor;

    m.getVList()[i] = v;
    
  }

      
}


GLUquadric* qobj;
void Katamari::initializeKatamari(void) {
	// initialize varables
	dragging = -1;
	last_mouse_valid = 0;
	ex=-2.25;
	ey=130.0;
	ez=5;
	ballPositionX = -2.25;
	ballPositionZ = 28.0;
	distanceCalc = 0.0;
	overlapCalc = 0.0;
	mouse_theta = 90.0;
	mouse_delta = 90.0;
	firstPersonX = -2.25;
	firstPersonZ = 28.0;
	firstPersonRotate = 0.0;
	firstPerson = 0;
	ballMove = 0.0;
	theta = 90;
	lightPosY = 0.0;
	lightPosX = 0.0;
	fog = 0;
	direction = 1;
	game_on = 0;
	difficulty = 1;
	qobj = gluNewQuadric();
	gluQuadricNormals(qobj, GLU_SMOOTH);
	lastT = CS315::getTime();
	loadModel("Katamari_barrier.obj");
	
	kata.initializeTobor(); //Added by Scott
	
	
	//BUILDING DISPLAY LIST
	buildingDL = glGenLists(1);
	glNewList(buildingDL, GL_COMPILE);
	setGLMaterial(MAT_WHITE);
	glEnable (GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mytex2);
	glBegin (GL_QUADS);

		glTexCoord2f(0.0f,0.0f);
		glNormal3f(0.0,0.0,1.0);
		glVertex3f (1.0f, 0.0f, 1.0f);
				
		glTexCoord2f(1.0f,0.0f);
		glVertex3f (1.0f, 9.0f, 1.0f);
				
		glTexCoord2f(1.0f,1.0f);
		glVertex3f (-1.0f, 9.0f, 1.0f);
				
		glTexCoord2f(0.0f,1.0f);
		glVertex3f (-1.0f, 0.0f, 1.0f);
	glEnd ();
	glBegin (GL_QUADS);

		glTexCoord2f(0.0f,0.0f);
		glNormal3f(0.0,0.0,-1.0);
		glVertex3f (-1.0f, 0.0f, -1.0f);
				
		glTexCoord2f(1.0f,0.0f);
		glVertex3f (-1.0f, 9.0f, -1.0f);
				
		glTexCoord2f(1.0f,1.0f);
		glVertex3f (1.0f, 9.0f, -1.0f);
				
		glTexCoord2f(0.0f,1.0f);
		glVertex3f (1.0f, 0.0f, -1.0f);
	glEnd ();
	glBegin (GL_QUADS);
		glTexCoord2f(0.0f,0.0f);
		glNormal3f(1.0,0.0,0.0);
		glVertex3f (1.0f, 0.0f, -1.0f);
				
		glTexCoord2f(1.0f,0.0f);
		glVertex3f (1.0f, 9.0f, -1.0f);
				
		glTexCoord2f(1.0f,1.0f);
		glVertex3f (1.0f, 9.0f, 1.0f);
				
		glTexCoord2f(0.0f,1.0f);
		glVertex3f (1.0f, 0.0f, 1.0f);
	glEnd ();
	glBegin (GL_QUADS);
		glTexCoord2f(0.0f,0.0f);
		glNormal3f(-1.0,0.0,0.0);
		glVertex3f (-1.0f, 0.0f, 1.0f);
				
		glTexCoord2f(1.0f,0.0f);
		glVertex3f (-1.0f, 9.0f, 1.0f);
				
		glTexCoord2f(1.0f,1.0f);
		glVertex3f (-1.0f, 9.0f, -1.0f);
				
		glTexCoord2f(0.0f,1.0f);
		glVertex3f (-1.0f, 0.0f, -1.0f);
	glEnd ();
	setGLMaterial(MAT_GRAY);
	glBegin (GL_QUADS);
		glNormal3f(0.0,1.0,0.0);
		glVertex3f (-1.0f, 9.0f, 1.0f);
				
		glVertex3f (1.0f, 9.0f, 1.0f);
				
		glVertex3f (1.0f, 9.0f, -1.0f);
				
		glVertex3f (-1.0f, 9.0f, -1.0f);
	glEnd ();
	glDisable (GL_TEXTURE_2D);
	glEndList();


	//BLOCK DISPLAY LIST
		blockDL = glGenLists(1);
		glNewList(blockDL, GL_COMPILE);
		for(float z = -5.0; z<=2.0; z=z+2){
			for(float x = -5.0; x<=2.0; x=x+2){
			glPushMatrix();
				float height = CS315::RandFloat() * (1 - 0.5) + 0.5;
				glTranslatef(x,0.0,z);
				glScalef(1.0,height,1.0);
				glCallList(buildingDL);
			glPopMatrix();
			}
		}
		glEndList();
		//Set enemy and player spheres
		reset_game();
}

void Katamari::drawMesh(){
	if (m.getFList().size() > 0) {

    float* vertices = (float*)(&(m.getVList()[0]));
    float* normals = (float*)(&(m.getNList()[0]));
	float* textures = (float*)(&(m.getTList()[0])); //Added by Scott

    //glDisable (GL_COLOR_MATERIAL);

    glBegin(GL_TRIANGLES);

	// For each face in the model:
    for(unsigned int i=0; i < m.getFList().size(); i++) {
      Face f = m.getFList()[i];
	  Material mat;
	  mat = m.getMaterial()[f[0].getMaterialIndex()];
	  GLfloat mat_shininess[1];
	  
	  // some meshes have a shininess of zero, which causes problems.
	  mat_shininess[0] = (mat.Ns > 0) ? mat.Ns : 50.0f;

	  glMaterialfv ( GL_FRONT_AND_BACK, GL_AMBIENT, mat.Ka);
	  glMaterialfv ( GL_FRONT_AND_BACK, GL_DIFFUSE, mat.Kd);
	  glMaterialfv ( GL_FRONT_AND_BACK, GL_SPECULAR, mat.Ks);
	  glMaterialfv ( GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

      
	  glNormal3f( normals[3*f[0].getNormalIndex()+0]  , normals[3*f[0].getNormalIndex()+1]  , normals[3*f[0].getNormalIndex()+2] );
	  glTexCoord2f( textures[3*f[0].getTextureIndex()+0] , textures[3*f[0].getTextureIndex()+1] ); //Added by Scott
      glVertex3f( vertices[3*f[0].getVertexIndex()+0] , vertices[3*f[0].getVertexIndex()+1] , vertices[3*f[0].getVertexIndex()+2] );
      
      mat = m.getMaterial()[f[1].getMaterialIndex()];
	  
	  // some meshes have a shininess of zero, which causes problems.
	  mat_shininess[0] = (mat.Ns > 0) ? mat.Ns : 50.0f;

	  glMaterialfv ( GL_FRONT_AND_BACK, GL_AMBIENT, mat.Ka);
	  glMaterialfv ( GL_FRONT_AND_BACK, GL_DIFFUSE, mat.Kd);
	  glMaterialfv ( GL_FRONT_AND_BACK, GL_SPECULAR, mat.Ks);
	  glMaterialfv ( GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

      
	  glNormal3f( normals[3*f[1].getNormalIndex()+0]  , normals[3*f[1].getNormalIndex()+1]  , normals[3*f[1].getNormalIndex()+2] );
	  glTexCoord2f( textures[3*f[1].getTextureIndex()+0] , textures[3*f[1].getTextureIndex()+1] ); //Added by Scott
      glVertex3f( vertices[3*f[1].getVertexIndex()+0] , vertices[3*f[1].getVertexIndex()+1] , vertices[3*f[1].getVertexIndex()+2] );
     
	  mat = m.getMaterial()[f[2].getMaterialIndex()];
	  
	  // some meshes have a shininess of zero, which causes problems.
	  mat_shininess[0] = (mat.Ns > 0) ? mat.Ns : 50.0f;

	  glMaterialfv ( GL_FRONT_AND_BACK, GL_AMBIENT, mat.Ka);
	  glMaterialfv ( GL_FRONT_AND_BACK, GL_DIFFUSE, mat.Kd);
	  glMaterialfv ( GL_FRONT_AND_BACK, GL_SPECULAR, mat.Ks);
	  glMaterialfv ( GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

      
	  glNormal3f( normals[3*f[2].getNormalIndex()+0]  , normals[3*f[2].getNormalIndex()+1]  , normals[3*f[2].getNormalIndex()+2] );
	  glTexCoord2f( textures[3*f[2].getTextureIndex()+0] , textures[3*f[2].getTextureIndex()+1] ); //Added by Scott
      glVertex3f( vertices[3*f[2].getVertexIndex()+0] , vertices[3*f[2].getVertexIndex()+1] , vertices[3*f[2].getVertexIndex()+2] );
      
    }
    glEnd();
  }
}

Ball::Ball(){

}

Ball::~Ball(){

}

float Ball::getSize(){
	return size;
}

float Ball::getX(){
	return x;
}

float Ball::getZ(){
	return z;
}

float Ball::getSpeed(){
	return speed;
}

float Ball::getTurn(){
	return turn;
}

MaterialInfo Ball::getColor(){
	return color;
}

void Ball::setColor(MaterialInfo m){
	color = m;
}

void Ball::setSize(float rad){
	size = rad;
}

void Ball::setX(float xPos){
	x = xPos;
}
void Ball::setZ(float zPos){
	z = zPos;
}
void Ball::setTravelDist(float dist){
	traveldist = dist;
}
void Ball::setSpeed(float vel){
	speed = vel;
}

void Ball::setTurn(float whenTurn){
	turn = whenTurn;
}

Tobor::Tobor()
{
  // Initialize fields:

   rArmMoving =       false;
   lArmMoving =       false;
   legsMoving =       false;
   
   rArmRising =       true;
   lArmRising =       true;
   rForearmRising =   true;
   lForearmRising =   true;
   leftLegRising =    true;
   leftThighRising =  true;
   rightLegRising =   false;
   rightThighRising = false;
   
   torso_angle_y       = 0.0f;
   torso_angle_x       = 0.0f;
   right_arm_angle     = 0.0f;
   left_arm_angle      = 0.0f;
   right_forearm_angle = 0.0f;
   left_forearm_angle  = 0.0f;
   left_thigh_angle    = 0.0f;
   right_thigh_angle   = 0.0f;
   right_leg_angle     = 0.0f;
   left_leg_angle      = 0.0f;

   animateTobor = false;
}


//***************************************************************************
// DESTRUCTOR
//***************************************************************************
Tobor::~Tobor()
{
  // Nothing to do!
}

void Tobor::initializeTobor(void) {
  // Initialize display lists for body parts...

  construct_head();
  construct_torso();
  construct_pelvis();
  construct_right_thigh();
  construct_left_thigh();
  construct_right_arm();
  construct_left_arm();
  construct_right_forearm();
  construct_left_forearm();
  construct_right_leg();
  construct_left_leg();
  
}

void Tobor::construct_torso(void) {
  
  TOBOR_TORSO_DL = glGenLists(1);
  glNewList(TOBOR_TORSO_DL,GL_COMPILE);
  setGLMaterial(MAT_GRAY);
  glScalef(1.8,1.0,1.0);
  glutSolidSphere(0.6,10,5);
  glTranslatef(0.0,-0.75,0.0);
  setGLMaterial(MAT_YELLOW);
  glutSolidCube(0.5);
  glTranslatef(0,0.3,0);
  setGLMaterial(MAT_GRAY);
  glutSolidSphere(0.5,5,5);
  glScalef(1.0,0.2,1.0);
  glEndList();

}


void Tobor::construct_pelvis(void) {

  TOBOR_PELVIS_DL = glGenLists(1);
  glNewList(TOBOR_PELVIS_DL,GL_COMPILE); 
  setGLMaterial(MAT_YELLOW);
  glTranslatef(0.0,-0.75,0.0);
  glScalef(0.5,2.0,1.0);
  glutSolidCube(0.5);
  glEndList();
}


void Tobor::construct_right_arm(void) {
  
  TOBOR_RIGHT_ARM_DL = glGenLists(1);
  glNewList(TOBOR_RIGHT_ARM_DL,GL_COMPILE);
  setGLMaterial(MAT_GRAY);
  glTranslatef(-1.1,0.25,0.0);
  glScalef(0.5,0.5,0.5);
  glutSolidSphere(0.5,20,20);

  glTranslatef(0.0,-1.10,0.0);
  glScalef(0.5,1.5,0.5);
  setGLMaterial(MAT_WHITE);
  glutSolidCube(1.0);
  glEndList();

}

void Tobor::construct_right_forearm(void) {

  TOBOR_RIGHT_FOREARM_DL = glGenLists(1);
  glNewList(TOBOR_RIGHT_FOREARM_DL,GL_COMPILE); 
  glTranslatef(-1.1,-0.7,0.0);
  glScalef(0.5,0.5,0.5);
  setGLMaterial(MAT_GRAY);
  glutSolidSphere(0.4,20,20);
  
  glTranslatef(0.0,-1.3,0.0);
  glScalef(0.8,2.0,1.0);
  setGLMaterial(MAT_RED);
  glutSolidCube(1.0);
  
  glScalef(.5,1.0,1.0);
  glTranslatef(0.0,-0.4,0.0);
  glutSolidCube(.5);
  
  glTranslatef(0.0,-0.25,0.0);
  glutSolidCube(.3);
  glEndList();

}


void Tobor::construct_left_arm(void) {

  TOBOR_LEFT_ARM_DL = glGenLists(1);
  glNewList(TOBOR_LEFT_ARM_DL,GL_COMPILE);
  
  glTranslatef(1.1,0.25,0.0);
  glScalef(0.5,0.5,0.5);
  setGLMaterial(MAT_GRAY);
  glutSolidSphere(0.5,20,20);

  glTranslatef(0.0,-1.10,0.0);
  glScalef(0.5,1.5,0.5);
  setGLMaterial(MAT_WHITE);
  glutSolidCube(1.0);
  glEndList();

}


void Tobor::construct_left_forearm(void) {

  TOBOR_LEFT_FOREARM_DL = glGenLists(1);
  glNewList(TOBOR_LEFT_FOREARM_DL,GL_COMPILE);
  
  glTranslatef(1.1,-0.7,0.0);
  glScalef(0.5,0.5,0.5);
  setGLMaterial(MAT_GRAY);
  glutSolidSphere(0.4,20,20);
  
  glTranslatef(0.0,-1.3,0.0);
  glScalef(0.8,2.0,1.0);
  setGLMaterial(MAT_RED);
  glutSolidCube(1.0);
  
  glScalef(.5,1.0,1.0);
  glTranslatef(0.0,-0.4,0.0);
  glutSolidCube(.5);
  
  glTranslatef(0.0,-0.25,0.0);
  glutSolidCube(.3);
  glEndList();

}


void Tobor::construct_left_thigh(void) {

  TOBOR_LEFT_THIGH_DL = glGenLists(1);
  glNewList(TOBOR_LEFT_THIGH_DL,GL_COMPILE);
  
  glTranslatef(0.3,-1.2,0.0);
  glScalef(2.0,2.0,2.0);
  setGLMaterial(MAT_GRAY);
  glutSolidSphere(0.1,20,20);

  glTranslatef(0.0,-0.3,0.0);
  glScalef(0.5,1.5,0.5);
  setGLMaterial(MAT_WHITE);
  glutSolidCube(0.3);
  glEndList();
}


void Tobor::construct_left_leg(void) {

  TOBOR_LEFT_LEG_DL = glGenLists(1);
  glNewList(TOBOR_LEFT_LEG_DL,GL_COMPILE);
  
  glTranslatef(0.3,-2.3,0.0);
  glScalef(2.0,1.3,2.0);
  setGLMaterial(MAT_GRAY);
  glutSolidSphere(0.1,20,20);
  
  glTranslatef(0.0,-0.5,0.0);
  glScalef(0.5,2.0,0.5);
  setGLMaterial(MAT_BLUE);
  glutSolidCube(0.5);
  
  //foot      
  setGLMaterial(MAT_RED);
  glTranslatef(0.0,-0.25,0.1);
  glScalef(0.8,0.1,1.4);
  glutSolidCube(0.5);
  glEndList();
}


void Tobor::construct_right_thigh(void) {

  TOBOR_RIGHT_THIGH_DL = glGenLists(1);
  glNewList(TOBOR_RIGHT_THIGH_DL,GL_COMPILE);
  glTranslatef(-0.3,-1.2,0.0);
  glScalef(2.0,2.0,2.0);
  setGLMaterial(MAT_GRAY);
  glutSolidSphere(0.1,20,20);

  glTranslatef(0.0,-0.3,0.0);
  glScalef(0.5,1.5,0.5);
  setGLMaterial(MAT_WHITE);
  glutSolidCube(0.3);
  glEndList();
}


void Tobor::construct_right_leg(void) {

  TOBOR_RIGHT_LEG_DL = glGenLists(1);
  glNewList(TOBOR_RIGHT_LEG_DL,GL_COMPILE);

  glTranslatef(-0.3,-2.3,0.0);
  glScalef(2.0,1.3,2.0);
  setGLMaterial(MAT_GRAY);
  glutSolidSphere(0.1,20,20);
  
  glTranslatef(0.0,-0.5,0.0);
  glScalef(0.5,2.0,0.5);
  setGLMaterial(MAT_BLUE);
  glutSolidCube(0.5);
  
  //foot
  setGLMaterial(MAT_RED);
  glTranslatef(0.0,-0.25,0.1);
  glScalef(0.8,0.1,1.4);
  glutSolidCube(0.5);


  glEndList();
}


void Tobor::construct_head(void) {

  TOBOR_HEAD_DL = glGenLists(1);
  glNewList(TOBOR_HEAD_DL,GL_COMPILE);
  
  setGLMaterial(MAT_YELLOW);
  glTranslatef(0,6,0);

  glScalef(0.3,2.0,0.5);
  glScalef(1.0,1.3,1.0);
  glutSolidSphere(0.5,10,10);
  
  glEndList();
}

void Tobor::set_animate(bool command){
	animateTobor = command;
}

void Tobor::setGLMaterial(MaterialInfo m) {

  float *diffuse = m.getDiffuse();
  glMaterialfv(GL_FRONT, GL_SPECULAR,  m.getSpecular());
  glMaterialf (GL_FRONT, GL_SHININESS, m.getShininess());
  glMaterialfv(GL_FRONT, GL_AMBIENT,   m.getAmbient());
  glMaterialfv(GL_FRONT, GL_DIFFUSE,   m.getDiffuse());
  glColor4f(diffuse[0],diffuse[1],diffuse[2],1.0);
}

void Tobor::drawTobor(void) {
  
  glPushMatrix(); 
    glRotatef(kata.get_torso_angle_y(),0,1,0);
    glRotatef(kata.get_torso_angle_x(),1,0,0);
    glPushMatrix();
      glCallList(TOBOR_TORSO_DL);
      glCallList(TOBOR_HEAD_DL);
    glPopMatrix();
    
    
    // Right arm
    glPushMatrix();
      glTranslatef(0,0.25,0);
      glRotatef(kata.get_right_arm_angle(),1,0,0);
      glTranslatef(0,-0.25,0);
      glPushMatrix();
        glCallList(TOBOR_RIGHT_ARM_DL);
      glPopMatrix();
      
      glPushMatrix();
        glTranslatef(1.25,-0.7,0);
        glRotatef(kata.get_right_forearm_angle(),1,0,0); 
        glTranslatef(-1.25,0.7,0);
        glCallList(TOBOR_RIGHT_FOREARM_DL);
      glPopMatrix();
    glPopMatrix();
    

    
    // Left arm
    glPushMatrix();
      glTranslatef(0,0.25,0);
      glRotatef(kata.get_left_arm_angle(),1,0,0);
      glTranslatef(0,-0.25,0);
      glPushMatrix();
        glCallList(TOBOR_LEFT_ARM_DL);
      glPopMatrix();

      glPushMatrix();
        glTranslatef(1.25,-0.7,0);
        glRotatef(kata.get_left_forearm_angle(),1,0,0);  
        glTranslatef(-1.25,0.7,0);
        glCallList(TOBOR_LEFT_FOREARM_DL);
      glPopMatrix();

    glPopMatrix();
    
    

    // Pelvis
    glPushMatrix();
      glPushMatrix();
        glCallList(TOBOR_PELVIS_DL);
      glPopMatrix();
    
      // Right thigh
      glPushMatrix();
      glTranslatef(-0.3,-1.2,0.0);
      glRotatef(kata.get_right_thigh_angle(),1.0,0.0,0.0);
      glTranslatef(0.3,1.2,0.0);  
        glPushMatrix();
          glCallList(TOBOR_RIGHT_THIGH_DL);
        glPopMatrix();

        glPushMatrix();
          glTranslatef(-0.3,-2.3,0.0);
          glRotatef(kata.get_right_leg_angle(),1.0,0.0,0.0);
          glTranslatef(0.3,2.3,0.0);
          glCallList(TOBOR_RIGHT_LEG_DL);
        glPopMatrix();
      glPopMatrix();

      // Left leg
      glPushMatrix();
        glTranslatef(0.3,-1.2,0.0);
        glRotatef(kata.get_left_thigh_angle(),1.0,0.0,0.0);
        glTranslatef(-0.3,1.2,0.0);
        glPushMatrix();
          glCallList(TOBOR_LEFT_THIGH_DL);
        glPopMatrix();

        glPushMatrix();
          glTranslatef(0.3,-2.3,0.0);
          glRotatef(kata.get_left_leg_angle(),1.0,0.0,0.0);
          glTranslatef(-0.3,2.3,0.0);
          glCallList(TOBOR_LEFT_LEG_DL);
        glPopMatrix();
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();

}

void Katamari::drawKatamari(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	//ENEMY SPHERES!
	//Turning on Phong Shading
	phongShader->Bind();
	for(int i = 0; i<balls.size(); i++){
		glPushMatrix();
			if(balls[i].getSize() > player.getSize()){
				setGLMaterial(MAT_RED);
				glTranslatef(balls[i].getX(),balls[i].getSize(),balls[i].getZ());  //DO THIS FOR EVERY SPHERE, remember to set color and size
				glutSolidSphere(balls[i].getSize(),20,20);
			}
			else{
				
				setGLMaterial(MAT_GREEN);
				glTranslatef(balls[i].getX(),balls[i].getSize(),balls[i].getZ());  //DO THIS FOR EVERY SPHERE, remember to set color and size
				glutSolidSphere(balls[i].getSize(),20,20);
			}
			
		glPopMatrix();
	}
	
	//Turning off Phong Shading
	phongShader->UnBind();
	
	
	/*glPushMatrix();
	setGLMaterial(MAT_GREEN);

	glTranslatef(ballPositionX, 0.5,ballPositionZ);
	//glRotatef(firstPersonRotate,0,1,0);
	glutSolidSphere(1,20,20);
	glPopMatrix();*/

	//FOG
	glClearColor(0.3f, 0.4f, 0.8f, 0.0f);
	if(fog ==1){
	glClearColor(0.5f,0.5f,0.5f,1.0f);
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.02f);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogf(GL_FOG_START, 5.0f);
	glFogf(GL_FOG_END, 20.0f); 
	glEnable(GL_FOG);                   
	}
	

	//DRAW BUILDINGS
	for(float x = -60.0; x<80.0; x=x+20.0){
		for(float z = -40.0; z<30.0; z=z+20.0){
			glPushMatrix();
			glTranslatef(x,0.0,z);
			glCallList(blockDL);
			glPopMatrix();
		}
	}


	//DRAW GROUND
	setGLMaterial(MAT_DARKGRAY);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mytex);
	glPushMatrix();
		glBegin (GL_QUADS);
		glTexCoord2f(0.0f,0.0f);
		glNormal3f(0.0,1.0,0.0);
		glVertex3f (-70.0f, 0.0f, 30.0f);
				
		glTexCoord2f(30.0f,0.0f);
		glVertex3f (70.0f, 0.0f, 30.0f);
				
		glTexCoord2f(30.0f,30.0f);
		glVertex3f (70.0f, 0.0f, -50.0f);
				
		glTexCoord2f(0.0f,30.0f);
		glVertex3f (-70.0f, 0.0f, -50.0f);
		glEnd ();
		glDisable (GL_TEXTURE_2D);
	glPopMatrix();

	//Draw Mesh
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D,signtex); //Added by Scott
		glEnable(GL_TEXTURE_2D); //Added by Scott
		glTranslatef(0.5,1.0,28.0);
		glScalef(2.0,2.0,2.0);
		glRotatef(-90.0,1.0,0.0,0.0);
		drawMesh();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-5.0,1.0,28.0);
		glScalef(2.0,2.0,2.0);
		glRotatef(180.0,0.0,1.0,0.0);
		glRotatef(-90.0,1.0,0.0,0.0);
		drawMesh();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Tobor!
	glPushMatrix();
		//glTranslatef(ballPositionX,3.75,ballPositionZ+(player.getSize()+1));
		glTranslatef(ballPositionX,3.75+player.getSize()*2,ballPositionZ);
		glRotatef(180.0,0.0,1.0,0.0);
		kata.drawTobor();
	glPopMatrix();

	//Player Sphere
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glColor4f(0.0,0.0,1.0,0.5);
		setGLMaterial(MAT_TRANSBLUE);
		glTranslatef(ballPositionX,player.getSize(),ballPositionZ);
		glutSolidSphere(player.getSize(),20,20);
		glDisable(GL_BLEND);
	glPopMatrix();

}

// A function (that you need to fill in) to handle keystrokes
void Katamari::keyDown(unsigned char key, int x, int y) {
	switch (key){
	case '1': {
		difficulty = 1;
		cout << "Difficulty is now set to 'easy,' you chicken.\n";
		reset_game();
		break;
			  }
	case '2': {
		difficulty = 2;
		cout << "Difficulty is now set to 'medium'.\n";
		reset_game();
		break;
			  }
	case '3': {
		difficulty = 3;
		cout << "Difficulty is now set to 'hard,' you brave soul.\n";
		reset_game();
		break;
			  }
	case '4': {
		difficulty = 4;
		fog = 1;
		firstPerson = 1;
		cout << "OMG INSANE TECHNO MODE ENABLED!!!!!\n";
		reset_game();
		PlaySound(TEXT(""), NULL, SND_ASYNC);
		PlaySound(TEXT("Techno.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
			  }
	case 'd': {
		firstPerson = 0;
		break;
			  }
	case 'a': {
		if(firstPerson == 1)
		{firstPerson = 0;}
		else{firstPerson = 1;}
		break;
			  }
	case 27: {
		exit (0);
		break;
			  }
	case 'r': {
		reset_game();
		break;
			  }
	case 'f': {
		if(fog==1){
			fog = 0;
			glDisable(GL_FOG);
		}else{fog=1;}
		break;
			  }
	}
}
void specialKey(int key,int x,int y){
		switch (key){
	case GLUT_KEY_UP : {
		direction = 1;
		ballPositionZ = ballPositionZ - 0.5;
		kata.set_animate(true);
		break;
		} 
	case GLUT_KEY_DOWN : {
		direction = 2;
		ballPositionZ = ballPositionZ + 0.5;
		kata.set_animate(true);
		break;
		}
	case GLUT_KEY_LEFT : {
		direction = 3;
		ballPositionX = ballPositionX - 0.5;
		kata.set_animate(true);
		break;
		}
	case GLUT_KEY_RIGHT : {
		direction = 4;
		ballPositionX = ballPositionX + 0.5;
		kata.set_animate(true);
		break;
		}
	case GLUT_KEY_PAGE_UP: {
		firstPersonX = firstPersonX - 0.1 * sin((double)firstPersonRotate);
		firstPersonZ = firstPersonZ + 0.1 * cos((double)firstPersonRotate);
		kata.set_animate(true);
		break;
			  }
	case GLUT_KEY_PAGE_DOWN: {
		firstPersonX = firstPersonX + 0.1 * sin((double)firstPersonRotate);
		firstPersonZ = firstPersonZ - 0.1 * cos((double)firstPersonRotate);
		kata.set_animate(true);
		break;
			  }

	}
}

// A function (that you need to fill in) to handle keystrokes
void Katamari::keyUp(unsigned char key, int x, int y) {
	//cout << "Key released!";
	kata.set_animate(false);
}


// An idle function (that you need to fill in) to do animation
int turn1 = 0;
void Katamari::idle() {
	if(game_on == 0){
		double deltaT = CS315::getTime() - lastT;
		lightPosX = cos(lastT*50.0) + 1;
		for(int x = 0; x<balls.size(); x++){
			if(balls[x].turn == 1.0){
				if(balls[x].xORz == 1){
					balls[x].setX(balls[x].getX()+deltaT*balls[x].getSpeed());
					if(balls[x].getX()>=balls[x].traveldist){
					balls[x].turn = 0;
					}
				}else{
					balls[x].setZ(balls[x].getZ()+deltaT*balls[x].getSpeed());
					if(balls[x].getZ()>=balls[x].traveldist){
					balls[x].turn = 0;
					}
				}

			}
			else{
				if(balls[x].xORz ==1){
				balls[x].setX(balls[x].getX()-deltaT*balls[x].getSpeed());
				if(balls[x].getX()<=-balls[x].traveldist){
					balls[x].turn = 1;
				}
				}else{
					balls[x].setZ(balls[x].getZ()-deltaT*balls[x].getSpeed());
					if(balls[x].getZ()<=-balls[x].traveldist){
						balls[x].turn = 1;
					}
				}
			}

		}
	
		collisions(); //Test for collisions
		game_over(); //Test to see if game is over

		//Tobor Animation
		if(kata.get_animate())
		{
			if(kata.get_rArmRising())
			{
			  kata.set_right_arm_angle(kata.get_right_arm_angle()-1000*deltaT);
			  if(kata.get_right_arm_angle() < -180.0)
				kata.set_rArmRising(false); 
			}
			else
			{
			  kata.set_right_arm_angle(kata.get_right_arm_angle()+1000*deltaT);
			  if(kata.get_right_arm_angle() > 0.0)
				kata.set_rArmRising(true);
			}
			if(kata.get_left_forearm_angle() > 0)
			   kata.set_lForearmRising(true);      

			if(kata.get_lForearmRising())
			{
			  kata.set_left_forearm_angle(kata.get_left_forearm_angle()-1000*deltaT);
			  if(kata.get_left_forearm_angle() < -100.0)
				kata.set_lForearmRising(false); 
			}
			else
			{
			  kata.set_left_forearm_angle(kata.get_left_forearm_angle()+1000*deltaT);
			  if(kata.get_left_forearm_angle() > 0.0)
				kata.set_lForearmRising(true);  
			}
			if(kata.get_lArmRising())
			{
			  kata.set_left_arm_angle(kata.get_left_arm_angle()-1000*deltaT);
			  if(kata.get_left_arm_angle() < -90.0)
				kata.set_lArmRising(false); 
			}
			else
			{
			  kata.set_left_arm_angle(kata.get_left_arm_angle()+1000*deltaT);
			  if(kata.get_left_arm_angle() > 0.0)
				kata.set_lArmRising(true);
			}
			// Left Leg
			if(kata.get_left_leg_angle() > 45)
			   kata.set_leftLegRising(false);
       
			if(kata.get_left_leg_angle() < -45)
			   kata.set_leftLegRising(true);
       
			if(kata.get_leftLegRising())
			{
			  kata.set_left_leg_angle(kata.get_left_leg_angle()+1000*deltaT);
			}
			else
			{
			  kata.set_left_leg_angle(kata.get_left_leg_angle()-1000*deltaT);
			}
    
			if(kata.get_left_thigh_angle() > 30)
			  kata.set_leftThighRising(false);
			if(kata.get_left_thigh_angle() < -20)
			  kata.set_leftThighRising(true);
      
			if(kata.get_leftThighRising())
			{
			  kata.set_left_thigh_angle(kata.get_left_thigh_angle()+1000*deltaT);
			}
			else
			{
			  kata.set_left_thigh_angle(kata.get_left_thigh_angle()-1000*deltaT);
			}
    
			// Right Leg
			if(kata.get_right_leg_angle() > 45)
			   kata.set_rightLegRising(false);
       
			if(kata.get_right_leg_angle() < -45)
			   kata.set_rightLegRising(true);
       
			if(kata.get_rightLegRising())
			{
			  kata.set_right_leg_angle(kata.get_right_leg_angle()+1000*deltaT);
			}
			else
			{
			  kata.set_right_leg_angle(kata.get_right_leg_angle()-1000*deltaT);
			}
    
			if(kata.get_right_thigh_angle() > 30)
			  kata.set_rightThighRising(false);
			if(kata.get_right_thigh_angle() < -20)
			  kata.set_rightThighRising(true);
      
			if(kata.get_rightThighRising())
			{
			  kata.set_right_thigh_angle(kata.get_right_thigh_angle()+1000*deltaT);
			}
			else
			{
			  kata.set_right_thigh_angle(kata.get_right_thigh_angle()-1000*deltaT);
			}
		}
	}
	lastT=CS315::getTime();
	glutPostRedisplay();
}




/************************
 Functions we've given you... you don't need to worry about
 anything below this point (although you're encouraged to
 poke around).
*************************/

// Resize and initialize the GL window
GLvoid Katamari::reshape(GLint width, GLint height) {
	screenHeight = height;
  glViewport(0,0,width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Set up a perspective projection based on the window's aspect ratio
  gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,500.0f);

  // Back to modelview mode to be nice
  glMatrixMode(GL_MODELVIEW);             
  glLoadIdentity();

}

// Initialize OpenGL
void Katamari::initGL() {
  
  //TEXTURE
  glGenTextures(1,&mytex);
  int retval = Tga::loadTGA("asphalt.tga", mytex, 1);
  glGenTextures(1,&mytex2);
  int retval2 = Tga::loadTGA("building1_lo.tga", mytex2, 1);
  /*glGenTextures(1,&mytex3);
  int retval3 = Tga::loadTGA("CastleDoor4.tga", mytex3, 1);*/
  glGenTextures(1,&signtex); //Added by Scott
  int retval4 = Tga::loadTGA("constrp.tga" , signtex, 1); //Added by Scott
  printf("LoadTGA = %d\n", retval);
  printf("LoadTGA = %d\n", retval2);
	// Enable smooth shading
  glShadeModel(GL_SMOOTH);              

  // black Background
  glClearColor(0.3f, 0.4f, 0.8f, 0.0f);       
  glEnable(GL_DEPTH_TEST);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glFrontFace(GL_CCW);
  glPolygonMode(GL_FRONT,GL_FILL);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  // Initialize GLEW (OpenGL extension wrangler):
  glewInit();
  phongShader = new STShaderProgram();
  phongShader->LoadVertexShader(phongVertexShaderFilename);
  phongShader->LoadFragmentShader(phongFragmentShaderFilename);

}


// Turn the light on
void Katamari::lights(void){

  // The position of the first light
  GLfloat position[] =  {20,30,-11.0, 1.0};

  GLfloat dcolor[] = {0.5,0.5,0.5,1};
  GLfloat acolor[] = {0.6,0.6,0.6,1};
  GLfloat scolor[] = {0.2,0.2,0.2,1};
  
  if(difficulty == 4){
	cout << " GOT HERE" << endl;
	GLfloat dcolor[] = {lightPosX,lightPosX,lightPosX,1};
	GLfloat acolor[] = {lightPosX,lightPosX,lightPosX,1};
	GLfloat scolor[] = {lightPosX,lightPosX,lightPosX,1};
	}

 //glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, acolor);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, dcolor);
  glLightfv(GL_LIGHT0, GL_SPECULAR, scolor);

  // The position of the second light
  GLfloat position2[] =  {20,15,30, 1.0};

  GLfloat dcolor2[] = {0.2,0.2,0.6,1};
  GLfloat acolor2[] = {0.1,0.1,0.2,1};
  GLfloat scolor2[] = {0.5,0.5,1,1};
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT1);
  
  glLightfv(GL_LIGHT1, GL_POSITION, position2);
  glLightfv(GL_LIGHT1, GL_AMBIENT, acolor2);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, dcolor2);
  glLightfv(GL_LIGHT1, GL_SPECULAR, scolor2);
  

}

// Turn the light on
void Katamari::crazyLights(void){

  // The position of the first light
  GLfloat position[] =  {20,30,-11.0, 1.0};

	GLfloat dcolor[] = {lightPosX,lightPosX,lightPosX,1};
	GLfloat acolor[] = {lightPosX,lightPosX,lightPosX,1};
	GLfloat scolor[] = {lightPosX,lightPosX,lightPosX,1};

 //glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, acolor);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, dcolor);
  glLightfv(GL_LIGHT0, GL_SPECULAR, scolor);

  // The position of the second light
  GLfloat position2[] =  {20,15,30, 1.0};

  GLfloat dcolor2[] = {0.2,0.2,0.6,1};
  GLfloat acolor2[] = {0.1,0.1,0.2,1};
  GLfloat scolor2[] = {0.5,0.5,1,1};
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT1);
  
  glLightfv(GL_LIGHT1, GL_POSITION, position2);
  glLightfv(GL_LIGHT1, GL_AMBIENT, acolor2);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, dcolor2);
  glLightfv(GL_LIGHT1, GL_SPECULAR, scolor2);
  

}

// Set the current material 
void Katamari::setGLMaterial(MaterialInfo m) {

  float *diffuse = m.getDiffuse();
  glMaterialfv(GL_FRONT, GL_SPECULAR,  m.getSpecular());
  glMaterialf (GL_FRONT, GL_SHININESS, m.getShininess());
  glMaterialfv(GL_FRONT, GL_AMBIENT,   m.getAmbient());
  glMaterialfv(GL_FRONT, GL_DIFFUSE,   m.getDiffuse());
  glColor4f(diffuse[0],diffuse[1],diffuse[2],1.0);
}

void Katamari::redraw(void) {

  // Clear screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // CAMERA MODES
  glLoadIdentity();
if(firstPerson == 0){
	gluLookAt(ex,ey,ez,-2.25,0.0,0.0,0.0,1.0,0.0);
}else if(firstPerson == 1){
	gluLookAt(ballPositionX,player.getSize()+5,ballPositionZ+(player.getSize()+10),ballPositionX,player.getSize(),ballPositionZ-5,0.0,1.0,0.0);
}
  
  if(difficulty == 4){
	// Set up lights
  crazyLights();
  }
  else{
	// Set up lights
  lights();
  }
  

  // Draw the robot  
  drawKatamari();

  // Show the result to the user
  glutSwapBuffers();
  
}



// Draws an axis vector (line + cone) along the z axis
void Katamari::draw_axis(double length) {
	glPushMatrix();
	glBegin(GL_LINES);
		glVertex3d(0,0,0); 
		glVertex3d(0,0,length); 
	glEnd();
	glTranslated(0,0, length-0.2);
	glutSolidCone(0.04, 0.2, 12, 9);
	glPopMatrix();
}


void Katamari::draw_axes() {

  #define AXIS_LENGTH 3.0

  // draw the axes
  glDisable(GL_LIGHTING);
  glLineWidth(2.0);

  // Draw the z axis
	glColor3d(0, 0, 1.0);
	draw_axis(AXIS_LENGTH);

  // Draw the x and y axes
	glPushMatrix();
	  glRotated(90, 0, 1, 0);
	  glColor3d(1., 0, 0);
	  draw_axis(0.5);
	  glRotated(-90, 1, 0, 0);
	  glColor3d(0, 1., 0);
	  draw_axis(0.5);
	glPopMatrix();
	
  glEnable(GL_LIGHTING);

}

void myMouse(int button, int state, int mousex, int mousey) {

  int x = mousex;
  int y = screenHeight - mousey;

  // If this is the first time myMouse was called...
  if (last_mouse_valid == 0) {
    last_mouse_valid = 1;
    mouse_lastx = x;
    mouse_lasty = y;
  }

  // Record which button was pressed
  if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
    mouse_lastx = x;
    mouse_lasty = y;
    dragging = GLUT_LEFT_BUTTON;
  }

  else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {
    mouse_lastx = x;
    mouse_lasty = y;
    dragging = GLUT_RIGHT_BUTTON;
  }

  else dragging = -1;

}
void myMovedMouse(int mousex, int mousey) {
  
  int x = mousex;
  int y = screenHeight - mousey;

  if (dragging == GLUT_LEFT_BUTTON) {
  
    // Update rotation 
    mouse_theta -= (double)(x - mouse_lastx) * ROTATE_RATE;
	mouse_delta -= (double)(y - mouse_lasty) * ROTATE_RATE;
    mouse_lastx = x;
    mouse_lasty = y;
  
    // Recompute look position (polar coords)
    double radius = sqrt(ez*ez+ex*ex);
    ex = radius * cos(DEG_TO_RAD * mouse_theta); 
    ez = radius * sin(DEG_TO_RAD * mouse_theta);
	ey = radius * cos(DEG_TO_RAD * mouse_delta)+5;
	if(ey<0.2){
		ey = 0.2;
	}

  }

  else if (dragging == GLUT_RIGHT_BUTTON) {

    // Move in or out along our current look axis
    int dy = y - mouse_lasty;
    mouse_lastx = x;
    mouse_lasty = y;
    ex += ((float)dy) * ex / 100.0;
    ey += ((float)dy) * ey / 100.0;
    ez += ((float)dy) * ez / 100.0;
    
  }

  // Redraw
  glutPostRedisplay();

}

//***************************************************************************
// Constructor
//***************************************************************************
Katamari::Katamari()
{
}


//***************************************************************************
// DESTRUCTOR
//***************************************************************************
Katamari::~Katamari()
{
  // Nothing to do!
}

//***************************************************************************
// Callback function - is called by GLUT when key is pressed:
//***************************************************************************

void keyDownCallback(unsigned char key, int x, int y)
{
  instance->keyDown(key, x, y);
}

//***************************************************************************
// Callback function - is called by GLUT when key is released:
//***************************************************************************

void keyUpCallback(int key,int x,int y)
{
  instance->keyUp(key, x, y);
}


//void specialCallback(void (*func)(int key, int x, int y))
//{
//  instance->specialDown(*func, x, y);
//}
//***************************************************************************
// Callback function - is called by GLUT whenever redraw needs to happen
//***************************************************************************
void redrawCallback()
{
  instance->redraw();
}

//***************************************************************************
// Callback function - is called by GLUT whenever window has been resized
//***************************************************************************
void reshapeCallback(int w, int h) {
  instance->reshape(w, h);
}


//***************************************************************************
// Callback function - is called by GLUT whenever interaction is idle
//***************************************************************************
void idleCallback() {
  instance->idle();
}

//***************************************************************************
// Main function 
//***************************************************************************

int main(int argc, char** argv) {

  instance = new Katamari();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(640,480);
  glutInitWindowPosition(100,150);
  glutCreateWindow("Katamari");
  glutIdleFunc(idleCallback);
  glutDisplayFunc(redrawCallback);
  glutReshapeFunc(reshapeCallback);
  glutKeyboardFunc(keyDownCallback);
  glutSpecialUpFunc(keyUpCallback);
  glutSpecialFunc(specialKey);
  glutMouseFunc(myMouse);
  glutMotionFunc(myMovedMouse);
  instance->initGL();
  instance->initializeKatamari();
  glutMainLoop();

  return 0;
}
