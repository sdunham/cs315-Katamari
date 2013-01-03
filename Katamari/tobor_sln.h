// tobor_sln.h
//
// SOLUTION
//

// A class representing a camera
//
// A camera remembers where it is and where it's looking
// (you probably don't need to edit this)
//class CameraInfo {
//
//private:
//
//  float x,y,z;      // position of camera
//  float ax,ay,az;   // point we're looking at...
//
//public:
//
//  // Sets up the camera at the correct position
//  void setup() {
//    glLoadIdentity();
//    glRotatef(360-ay,0,1,0);
//    glTranslatef(-x,-y,-z);
//  }
//
//  void setX(float newX) { x = newX; }
//  void setY(float newY) { y = newY; }
//  void setZ(float newZ) { z = newZ; }
//
//  // Default constructor
//  CameraInfo() { ax = 0.0; ay = 0.0; az = 0.0; x = 0.0; y = 0.0; z = 0.0; }
//
//};
//
//
//// A class representing a colored material
//// (you probably don't need to edit this)
//class MaterialInfo {
//private:
//
//  float specular[4];
//  float ambient [4];
//  float diffuse [4];
//  float shininess;
//
//public:
//
//  MaterialInfo (float r, float g, float b) {
//    specular[0] = ambient[0] = diffuse[0] = r;
//    specular[1] = ambient[1] = diffuse[1] = g;
//    specular[2] = ambient[2] = diffuse[2] = b;
//    specular[3] = ambient[3] = diffuse[3] = 1.0;
//    shininess = 100.0;
//  }
//
//  MaterialInfo() { }
//
//  float *getSpecular() { return specular; }
//  float *getDiffuse() { return diffuse; }
//  float *getAmbient() { return ambient; }
//  float getShininess() { return shininess; }
//
//};


// A class representing our program
// You will likely need to modify this (to add fields to the class):

class Tobor {
 public:
  // PUBLIC METHODS:

  Tobor(); // Constructor
  virtual ~Tobor(); // Destructor
  void initializeTobor();                         // Data structure initialization method (called by main)
  //void keyDown(unsigned char key, int x, int y);  // Key pressed GLUT callback
  //void idle();                                    // idle GLUT callback

  //void redraw();                                  // Redraw GLUT callback
  //void reshape (int w, int h);                    // Window reshape GLUT callback
  //void initGL();                                  // OpenGL initialization (called by main)

 private:
  // PRIVATE METHODS:

  // Draws your robot (called by redraw())
  void drawTobor();                               

  //// You can use this to change the current rendering material
  //void setGLMaterial(MaterialInfo m);
  //
  //// Turns on the lights
  //void lights(void);
  //
  //// Draws an x,y,z coordinate frame (call this to help you
  //// find your current origin)
  //void draw_axes();

  //// Draws an axis representation along the z-axis:
  //void draw_axis(double length);  

  // Added for the solution:
  void construct_torso(void);
  void construct_pelvis(void);
  void construct_right_thigh(void);
  void construct_left_thigh(void);
  void construct_right_arm(void);
  void construct_left_arm(void);
  void construct_right_forearm(void);
  void construct_left_forearm(void);
  void construct_right_leg(void);
  void construct_left_leg(void);
  void construct_head(void);

  // PRIVATE FIELDS:

  // Display lists for each of our body parts
  int TOBOR_TORSO_DL;   
  int TOBOR_PELVIS_DL;        
  int TOBOR_RIGHT_ARM_DL;     
  GLuint TOBOR_LEFT_ARM_DL;    
  int TOBOR_RIGHT_THIGH_DL;   
  int TOBOR_LEFT_THIGH_DL;    
  int TOBOR_RIGHT_FOREARM_DL; 
  int TOBOR_LEFT_FOREARM_DL;  
  int TOBOR_RIGHT_LEG_DL;     
  int TOBOR_LEFT_LEG_DL;     
  int TOBOR_HEAD_DL;      
  
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
  
};

//// GLOBAL variables (constants):
//
//// Some materials you can use in your program
//MaterialInfo MAT_WHITE (1.0,1.0,1.0);
//MaterialInfo MAT_GRAY  (0.5,0.5,0.5);
//MaterialInfo MAT_BLUE  (0.1,0.1,0.6);
//MaterialInfo MAT_GREEN (0.0,1.0,0.0);
//MaterialInfo MAT_RED   (0.6,0.1,0.1);
//MaterialInfo MAT_YELLOW(0.5,0.5,0.0);
//
//static const double PI = 3.141593; // Pi, rounded up for Philip
//
//static Tobor *instance = NULL; // Hack to make GLUT play nicely with C++.


