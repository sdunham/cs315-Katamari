/*****
 * TOBOR SOLUTION
 * 
 * tobor_sln.cpp
 *
 * CS315 project 2: TOBOR
 *
 * Authors: David Akers and Dan Morris
 *
 *****/

#include <math.h>
#include "cs315.h"
#include "tobor_sln.h"


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

/******
 Methods you need to fill in:
******/


// A function (that you need to fill in) that creates the display lists for
// your body parts. This gets called for you by the main function when the program first starts:
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


// A function (that you need to fill in) that draws your robot
void Tobor::drawTobor(void) {
  
  glPushMatrix(); 
    glRotatef(torso_angle_y,0,1,0);
    glRotatef(torso_angle_x,1,0,0);
    glPushMatrix();
      glCallList(TOBOR_TORSO_DL);
      glCallList(TOBOR_HEAD_DL);
    glPopMatrix();
    
    
    // Right arm
    glPushMatrix();
      glTranslatef(0,0.25,0);
      glRotatef(right_arm_angle,1,0,0);
      glTranslatef(0,-0.25,0);
      glPushMatrix();
        glCallList(TOBOR_RIGHT_ARM_DL);
      glPopMatrix();
      
      glPushMatrix();
        glTranslatef(1.25,-0.7,0);
        glRotatef(right_forearm_angle,1,0,0); 
        glTranslatef(-1.25,0.7,0);
        glCallList(TOBOR_RIGHT_FOREARM_DL);
      glPopMatrix();
    glPopMatrix();
    

    
    // Left arm
    glPushMatrix();
      glTranslatef(0,0.25,0);
      glRotatef(left_arm_angle,1,0,0);
      glTranslatef(0,-0.25,0);
      glPushMatrix();
        glCallList(TOBOR_LEFT_ARM_DL);
      glPopMatrix();

      glPushMatrix();
        glTranslatef(1.25,-0.7,0);
        glRotatef(left_forearm_angle,1,0,0);  
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
      glRotatef(right_thigh_angle,1.0,0.0,0.0);
      glTranslatef(0.3,1.2,0.0);  
        glPushMatrix();
          glCallList(TOBOR_RIGHT_THIGH_DL);
        glPopMatrix();

        glPushMatrix();
          glTranslatef(-0.3,-2.3,0.0);
          glRotatef(right_leg_angle,1.0,0.0,0.0);
          glTranslatef(0.3,2.3,0.0);
          glCallList(TOBOR_RIGHT_LEG_DL);
        glPopMatrix();
      glPopMatrix();

      // Left leg
      glPushMatrix();
        glTranslatef(0.3,-1.2,0.0);
        glRotatef(left_thigh_angle,1.0,0.0,0.0);
        glTranslatef(-0.3,1.2,0.0);
        glPushMatrix();
          glCallList(TOBOR_LEFT_THIGH_DL);
        glPopMatrix();

        glPushMatrix();
          glTranslatef(0.3,-2.3,0.0);
          glRotatef(left_leg_angle,1.0,0.0,0.0);
          glTranslatef(-0.3,2.3,0.0);
          glCallList(TOBOR_LEFT_LEG_DL);
        glPopMatrix();
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();

}

// A function (that you need to fill in) to handle keystrokes
void Tobor::keyDown(unsigned char key, int x, int y) {
  switch (key) {
      case 'a':  
      {
        torso_angle_y-=5.2f; 
        break;
      }
      
      case 's':  
      {
        torso_angle_y+=5.2f; 
        break;
      }

      case '1':
      {
        right_arm_angle-=5.2f;
        break;
      }
      case 'q':
      {
        right_arm_angle+=5.2f;
        break;
      }

      case '2':
      {
        right_forearm_angle-=5.2f;
        if (right_forearm_angle<-100.0f) right_forearm_angle=-100.0f;
        break;
      }
      case 'w':
      {
        right_forearm_angle+=5.2f;
        if (right_forearm_angle>100.0f) right_forearm_angle=100.0f;
        break;
      }

      case '3':
      {
        left_arm_angle -=5.2f;
        break;
      }
      case 'e':
      {
        left_arm_angle +=5.2f;
        break;
      }

      case '4':
      {
        left_forearm_angle-=5.2f;
        if (left_forearm_angle<-100.0f) left_forearm_angle=-100.0f;
        break;
      }
      case 'r':
      {
        left_forearm_angle+=5.2f;
        if (left_forearm_angle>100.0f) left_forearm_angle=100.0f;
        break;
      }

      case '5':
      {
        left_thigh_angle-=5.2f;
        if (left_thigh_angle<-100.0f) left_thigh_angle=-100.0f;
        break;
      }
      case 't':
      {
        left_thigh_angle+=5.2f;
        if (left_thigh_angle>100.0f) left_thigh_angle=100.0f;
        break;

      }

      case '6':
      {
        left_leg_angle+=5.2f;
        if (left_leg_angle>100.0f) left_leg_angle=100.0f;
        break;
      }
      case 'y':
      {
        left_leg_angle-=5.2f;
        if (left_leg_angle<-100.0f) left_leg_angle=-100.0f;
        break;
      }

      case '7':
      {
        right_thigh_angle-=5.2f;
        if (right_thigh_angle<-100.0f) right_thigh_angle=-100.0f;
        break;
      }
      case 'u':
      {
        right_thigh_angle+=5.2f;
        if (right_thigh_angle>100.0f) right_thigh_angle=100.0f;
        break;
      }

      case '8':
      {
        right_leg_angle+=5.2f;
        if (right_leg_angle>100.0f) right_leg_angle=100.0f;
        break;

      }
      case 'i':
      {
        right_leg_angle-=5.2f;
        if (right_leg_angle<-100.0f) right_leg_angle=-100.0f;
        break;
      }

      case 'z':
      {
        rArmMoving = !rArmMoving;
        break;
      }
      case 'x':
      {
        lArmMoving = !lArmMoving;
        break;
      }
      case 'c':
      {
        legsMoving = !legsMoving;
        break;
      }
      case 'd':
      {
        bool enabled = glIsEnabled(GL_DEPTH_TEST);
        if (enabled) glDisable(GL_DEPTH_TEST);
        else glEnable(GL_DEPTH_TEST);
        break;
      }
  }
  glutPostRedisplay();
}

// An idle function (that you need to fill in) to do animation
void Tobor::idle() {
   if(rArmMoving)
  {
    if(rArmRising)
    {
      right_arm_angle-=0.2f;
      if(right_arm_angle < -180.0)
        rArmRising = false; 
    }
    else
    {
      right_arm_angle+=0.2f;
      if(right_arm_angle > 0.0)
        rArmRising = true;
    }
  }

  if(lArmMoving)
  {
    if(left_forearm_angle > 0)
       lForearmRising = true;      

    if(lForearmRising)
    {
      left_forearm_angle-=0.2f;
      if(left_forearm_angle < -100.0)
        lForearmRising = false; 
    }
    else
    {
      left_forearm_angle+=0.2f;
      if(left_forearm_angle > 0.0)
        lForearmRising = true;  
    }
    if(lArmRising)
    {
      left_arm_angle-=0.05f;
      if(left_arm_angle < -90.0)
        lArmRising = false; 
    }
    else
    {
      left_arm_angle+=0.05f;
      if(left_arm_angle > 0.0)
        lArmRising = true;
    }
  }
  
  if(legsMoving)
  {
    // Left Leg
    if(left_leg_angle > 45)
       leftLegRising = false;
       
    if(left_leg_angle < -45)
       leftLegRising = true;
       
    if(leftLegRising)
    {
      left_leg_angle += 0.1;
    }
    else
    {
      left_leg_angle -= 0.1;
    }
    
    if(left_thigh_angle > 30)
      leftThighRising = false;
    if(left_thigh_angle < -20)
      leftThighRising = true;
      
    if(leftThighRising)
    {
      left_thigh_angle+=0.0622;
    }
    else
    {
      left_thigh_angle-=0.051;
    }
    
    // Right Leg
    if(right_leg_angle > 45)
       rightLegRising = false;
       
    if(right_leg_angle < -45)
       rightLegRising = true;
       
    if(rightLegRising)
    {
      right_leg_angle += 0.1;
    }
    else
    {
      right_leg_angle -= 0.1;
    }
    
    if(right_thigh_angle > 30)
      rightThighRising = false;
    if(right_thigh_angle < -20)
      rightThighRising = true;
      
    if(rightThighRising)
    {
      right_thigh_angle+=0.0622;
    }
    else
    {
      right_thigh_angle-=0.051;
    }
  }  
      
  glutPostRedisplay();
}




/************************
 Functions we've given you... you don't need to worry about
 anything below this point (although you're encouraged to
 poke around).
*************************/

// Resize and initialize the GL window
GLvoid Tobor::reshape(GLint width, GLint height) {

  glViewport(0,0,width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Set up a perspective projection based on the window's aspect ratio
  gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,50.0f);

  // Back to modelview mode to be nice
  glMatrixMode(GL_MODELVIEW);             
  glLoadIdentity();

}

// Initialize OpenGL
void Tobor::initGL() {
  
  // Enable smooth shading
  glShadeModel(GL_SMOOTH);              

  // black Background
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);       
  glEnable(GL_DEPTH_TEST);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glFrontFace(GL_CCW);
  glPolygonMode(GL_FRONT,GL_FILL);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

}


// Turn the light on
void Tobor::lights(void){

  // The position of the light
  GLfloat position[] =  {0.0, 0.0, 3.0, 1.0};

  GLfloat color[] = {1,1,1,1};
  GLfloat acolor[] = {0,0,0,1};
  

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 80.0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, acolor);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
  glLightfv(GL_LIGHT0, GL_SPECULAR, color);

  // Show the user where the light is...
  /*
  glPushMatrix();
  glTranslatef(position[0],position[1],position[2]);
  glDisable(GL_LIGHTING);
  glColor3f(1,1,1);
  glutWireCube(0.1);
  glEnable(GL_LIGHTING);
  glPopMatrix();
  */

  // Normally we wouldn't do this since it's really slow, but we want
  // to let you use scales in this assignment
  glEnable(GL_NORMALIZE);
}

// Set the current material 
void Tobor::setGLMaterial(MaterialInfo m) {

  float *diffuse = m.getDiffuse();
  glMaterialfv(GL_FRONT, GL_SPECULAR,  m.getSpecular());
  glMaterialf (GL_FRONT, GL_SHININESS, m.getShininess());
  glMaterialfv(GL_FRONT, GL_AMBIENT,   m.getAmbient());
  glMaterialfv(GL_FRONT, GL_DIFFUSE,   m.getDiffuse());
  glColor4f(diffuse[0],diffuse[1],diffuse[2],1.0);
}

void Tobor::redraw(void) {

  // Clear screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // Set up the camera
  camera.setup();

  // Set up lights
  lights();

  // Draw the robot  
  drawTobor();

  // Show the result to the user
  glutSwapBuffers();
  
}



// Draws an axis vector (line + cone) along the z axis
void Tobor::draw_axis(double length) {
	glPushMatrix();
	glBegin(GL_LINES);
		glVertex3d(0,0,0); 
		glVertex3d(0,0,length); 
	glEnd();
	glTranslated(0,0, length-0.2);
	glutSolidCone(0.04, 0.2, 12, 9);
	glPopMatrix();
}


void Tobor::draw_axes() {

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


//***************************************************************************
// Constructor
//***************************************************************************
Tobor::Tobor()
{
  // Set up a nice camera position
  camera.setX(0.0);
  camera.setY(-2.0);
  camera.setZ(10.0);

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
}


//***************************************************************************
// DESTRUCTOR
//***************************************************************************
Tobor::~Tobor()
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

  instance = new Tobor();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(640,480);
  glutInitWindowPosition(100,150);
  glutCreateWindow("TOBOR");
  glutIdleFunc(idleCallback);
  glutDisplayFunc(redrawCallback);
  glutReshapeFunc(reshapeCallback);
  glutKeyboardFunc(keyDownCallback);
  instance->initGL();
  instance->initializeTobor();
  glutMainLoop();

  return 0;
}
