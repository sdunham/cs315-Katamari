#version 120

varying vec3 NEye;
varying vec4 PEye;

// Function that computes the color of a fragment, using the standard OpenGL lighting model:

vec4 lighting (vec3 n, vec4 p)
{
  n = normalize(n);

  vec3 s = normalize(gl_LightSource[0].position - p).xyz; // vector from p to light #0
  vec3 s2 = normalize(gl_LightSource[1].position - p).xyz;

  // Compute the diffuse reflectance (u_s dot u_n):
  float diffuseReflectance = clamp(dot(s, n), 0.0, 1.0);  // dot product involved in diffuse reflection
  float diffuseReflectance2 = clamp(dot(s2, n), 0.0, 1.0);

  // Multiply this by the product of light color (light #0) and material color:
  vec4 diffuseComponent = gl_FrontLightProduct[0].diffuse*diffuseReflectance;
  vec4 diffuseComponent2 = gl_FrontLightProduct[1].diffuse*diffuseReflectance2;

  // Computer r and v vectors needed for specular lighting:
  vec3 r = normalize(-s - 2.0*dot(-s, n)*n); // light vector reflected around the normal
  vec3 r2 = normalize(-s2 - 2.0*dot(-s2, n)*n);
  vec3 v = normalize(-p.xyz);                // vector toward eye (0,0,0) from point p

  // Compute the specular reflectance (u_r dot u_v)^f:
  float specularReflectance = pow(max(0.0, dot(r, v)), gl_FrontMaterial.shininess);
  float specularReflectance2 = pow(max(0.0, dot(r2, v)), gl_FrontMaterial.shininess);
 
  // Multiply this by the product of light color (light #0) and material color:
  vec4 specularComponent = gl_FrontLightProduct[0].specular*specularReflectance;
  vec4 specularComponent2 = gl_FrontLightProduct[1].specular*specularReflectance2;

  // Compute ambient component:
  vec4 ambientComponent = gl_FrontLightProduct[0].ambient; 
  vec4 ambientComponent2 = gl_FrontLightProduct[1].ambient;

  // Compute the global ambient light (as described in Lab #4). Note that this is 
  // for the whole scene, and is not tied to any particular light:
  vec4 globalAmbientComponent = gl_FrontLightModelProduct.sceneColor;

  // Total color just adds all these up...
  vec4 totalColor = ambientComponent + diffuseComponent + specularComponent + globalAmbientComponent + ambientComponent2 + diffuseComponent2 + specularComponent2;

  return clamp(totalColor, vec4(0.0), vec4(1.0));
}

// Main fragment program: computes a color by calling our 'lighting' function:
void main ()
{
  gl_FragColor = lighting(NEye, PEye);
}




