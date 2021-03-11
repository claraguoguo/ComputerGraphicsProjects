// Add (hard code) an orbiting (point or directional) light to the scene. Light
// the scene using the Blinn-Phong Lighting Model.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
out vec3 color;
// expects: PI, blinn_phong
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  float theta = animation_seconds*(M_PI/4);
  vec4 light_homo = view * vec4(-4*sin(theta), 2.0, 4*cos(theta), 1.0);
  
  vec3 light = light_homo.xyz / light_homo.w;

  vec3 point_to_eye = -1 * (view_pos_fs_in.xyz/view_pos_fs_in.w);

  vec3 ka, kd, ks;
  ka = vec3(0.05, 0.05, 0.05);  // ambient 
  kd = vec3(0.4, 0.5, 0.6);     // diffuse
  ks = vec3(1, 1, 1);           // specular
  float p = 1000;               // specular exponent (shininess)

  vec3 n, v, l;
  n = normalize(normal_fs_in);         // n  unit surface normal direction
  v = normalize(point_to_eye);         // v  unit direction from point on object to eye
  l = normalize(light+point_to_eye);   // l  unit light direction
  if (is_moon) {
    color = blinn_phong(ka, kd, ks, p, n, v, l);
  }
  else{
    kd = vec3(0.0, 0.05, 0.4);  // diffuse
    color = blinn_phong(ka, kd, ks, p, n, v, l);
  }
  /////////////////////////////////////////////////////////////////////////////
}
