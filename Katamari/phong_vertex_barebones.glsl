// MINIMAL VERTEX PROGRAM:

varying vec3 NEye;
varying vec4 PEye;

void main ()
{
  
  PEye = gl_ModelViewMatrix * gl_Vertex;                  // Point in eye space (we'll need this for lighting)
 
  NEye = gl_NormalMatrix * gl_Normal;                     // Normal in eye space (we'll need this for lighting)

  gl_Position = gl_ModelViewProjectionMatrix*gl_Vertex;   // Multiply by the modelview/projection matrix!

  gl_FrontColor = gl_Color;                               // whatever was passed in to glColor3f 
							  // becomes the "front color" of the vertex.
}