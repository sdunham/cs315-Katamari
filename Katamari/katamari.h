// Header guard:
#ifndef PP3_H_INC
#define PP3_H_INC
#include "mesh.h"
// Define your class(es) here.
class MaterialInfo {
private:

  float specular[4];
  float ambient [4];
  float diffuse [4];
  float shininess;

public:

  MaterialInfo (float r, float g, float b) {
    specular[0] = ambient[0] = diffuse[0] = r;
    specular[1] = ambient[1] = diffuse[1] = g;
    specular[2] = ambient[2] = diffuse[2] = b;
    specular[3] = ambient[3] = diffuse[3] = 1.0;
    shininess = 100.0;
  }

  MaterialInfo (float r, float g, float b, float a) {
    specular[0] = ambient[0] = diffuse[0] = r;
    specular[1] = ambient[1] = diffuse[1] = g;
    specular[2] = ambient[2] = diffuse[2] = b;
    specular[3] = ambient[3] = diffuse[3] = a;
    shininess = 100.0;
  }

  MaterialInfo() { }

  float *getSpecular() { return specular; }
  float *getDiffuse() { return diffuse; }
  float *getAmbient() { return ambient; }
  float getShininess() { return shininess; }

};

class Ball{
public:
	Ball();
	virtual ~Ball();
	float getSize();
	float getX();
	float getZ();
	float getTurn();
	float getSpeed();
	MaterialInfo getColor();
	void setSize(float rad);
	void setX(float xPos);
	void setZ(float zPos);
	void setTravelDist(float dist);
	void setTurn(float whenTurn);
	void setSpeed(float vel);
	void setColor(MaterialInfo m);
	float traveldist;
	float speed;
	float turn;
	int xORz;
private:
	float size;
	float x;
	float z;

	MaterialInfo color;

};

class Tobor {
 public:
  // PUBLIC METHODS:
  Tobor(); // Constructor
  virtual ~Tobor(); // Destructor
  void initializeTobor();  
  void drawTobor();   // Draws your robot (called by redraw())
  void set_animate(bool command); //Allow animation
  bool get_animate(){return animateTobor;}

  bool animateTobor;
  
  bool rArmMoving;
  bool lArmMoving;
  bool legsMoving;
  bool get_rArmMoving(){return rArmMoving;}
  bool get_lArmMoving(){return lArmMoving;}
  bool get_legsMoving(){return legsMoving;}
  void set_rArmMoving(bool flag){rArmMoving = flag;}
  void set_lArmMoving(bool flag){lArmMoving = flag;}
  void set_legsMoving(bool flag){legsMoving = flag;}
  
  bool rArmRising;
  bool lArmRising;
  bool rForearmRising;
  bool lForearmRising;
  bool leftLegRising;
  bool leftThighRising;
  bool rightLegRising;
  bool rightThighRising;
  bool get_rArmRising(){return rArmRising;}
  bool get_lArmRising(){return lArmRising;}
  bool get_rForearmRising(){return rForearmRising;}
  bool get_lForearmRising(){return lForearmRising;}
  bool get_leftLegRising(){return leftLegRising;}
  bool get_leftThighRising(){return leftThighRising;}
  bool get_rightLegRising(){return rightLegRising;}
  bool get_rightThighRising(){return rightThighRising;}
  void set_rArmRising(bool flag){rArmRising = flag;}
  void set_lArmRising(bool flag){lArmRising = flag;}
  void set_rForearmRising(bool flag){rForearmRising = flag;}
  void set_lForearmRising(bool flag){lForearmRising = flag;}
  void set_leftLegRising(bool flag){leftLegRising = flag;}
  void set_leftThighRising(bool flag){leftThighRising = flag;}
  void set_rightLegRising(bool flag){rightLegRising = flag;}
  void set_rightThighRising(bool flag){rightThighRising = flag;}
  
  //Angles
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
  float get_torso_angle_y(){return torso_angle_y;}
  float get_torso_angle_x(){return torso_angle_x;}
  float get_right_arm_angle(){return right_arm_angle;}
  float get_left_arm_angle(){return left_arm_angle;}
  float get_right_forearm_angle(){return right_forearm_angle;}
  float get_left_forearm_angle(){return left_forearm_angle;}
  float get_left_thigh_angle(){return left_thigh_angle;}
  float get_right_thigh_angle(){return right_thigh_angle;}
  float get_right_leg_angle(){return right_leg_angle;}
  float get_left_leg_angle(){return left_leg_angle;}
  void set_torso_angle_y(float angle){torso_angle_y = angle;}
  void set_torso_angle_x(float angle){torso_angle_x = angle;}
  void set_right_arm_angle(float angle){right_arm_angle = angle;}
  void set_left_arm_angle(float angle){left_arm_angle = angle;}
  void set_right_forearm_angle(float angle){right_forearm_angle = angle;}
  void set_left_forearm_angle(float angle){left_forearm_angle = angle;}
  void set_left_thigh_angle(float angle){left_thigh_angle = angle;}
  void set_right_thigh_angle(float angle){right_thigh_angle = angle;}
  void set_right_leg_angle(float angle){right_leg_angle = angle;}
  void set_left_leg_angle(float angle){left_leg_angle = angle;}

 private:
  // PRIVATE METHODS:

  
  void setGLMaterial(MaterialInfo m);

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
  
};

class Katamari{
public:
	Katamari();
	virtual ~Katamari();
	Mesh m;
	void draw_axes();
	void draw_axis(double length);
	void initializeKatamari();
	void keyDown(unsigned char key, int x, int y);
	void keyUp(unsigned char key, int x, int y);
	void specialKey(int key,int x,int y);
	void idle();
	void redraw();
	void reshape(int w, int h);
	void initGL();
	void collisions();
	void reset_game();
	void game_over();

private:
	void drawMesh();
	void loadModel(const char *filename);
	void drawKatamari();
	void setGLMaterial(MaterialInfo m);
	void lights(void);
	void crazyLights(void);
};
static Katamari *instance = NULL;

MaterialInfo MAT_WHITE (1.0,1.0,1.0);
MaterialInfo MAT_GRAY  (0.5,0.5,0.5);
MaterialInfo MAT_BLUE  (0.1,0.1,0.6);
MaterialInfo MAT_GREEN (0.0,1.0,0.0);
MaterialInfo MAT_RED   (0.6,0.1,0.1);
MaterialInfo MAT_YELLOW(0.5,0.5,0.0);
MaterialInfo MAT_BROWN(0.6,0.4,0.3);
MaterialInfo MAT_PURPLE(0.7,0.3,0.7);
MaterialInfo MAT_DARKGRAY(0.3,0.3,0.3);
MaterialInfo MAT_TRANSBLUE(0.0,0.0,1,0.5);

#endif