// Set the pixel color using Blinn-Phong shading (e.g., with constant blue and
// gray material color) with a bumpy texture.
// 
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
//                     linearly interpolated from tessellation evaluation shader
//                     output
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
//               rgb color of this pixel
out vec3 color;
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  mat4 model = model(is_moon, animation_seconds);
  
  float theta = animation_seconds*(M_PI/4.0);
  vec4 light_homo = view * vec4(-2*sin(theta), 1.0, 2*cos(theta), 1.0);

  vec3 light = light_homo.xyz / light_homo.w;
  vec3 point_to_eye = -1 * (view_pos_fs_in.xyz/view_pos_fs_in.w);

  vec3 T, B; 
  tangent(normal_fs_in, T, B);
  vec3 bump_pos = bump_position(is_moon, sphere_fs_in);
  vec3 bump_normal = cross(bump_position(is_moon, sphere_fs_in + T/10000) - bump_pos,
                          bump_position(is_moon, sphere_fs_in + B/10000) - bump_pos);

  if (dot(sphere_fs_in, bump_normal) < 0) bump_normal = -1 * bump_normal;

  vec3 ka, kd, ks;
  ka = vec3(0.02, 0.02, 0.02);         // ambient 
  kd = vec3(0.4, 0.5, 0.6);            // diffuse
  ks = vec3(0.8, 0.8, 0.8);            // specular
  float p = 10;                        // specular exponent (shininess)

  vec3 n, v, l;
  v = normalize(point_to_eye);         // v  unit direction from point on object to eye
  l = normalize(light+point_to_eye);   // l  unit light direction
  
  n = (transpose(inverse(view * model))*vec4(bump_normal, 1.0)).xyz;
  n = normalize(n);                    // n  unit surface normal direction

  if (is_moon) {
    color = blinn_phong(ka, kd, ks, p, n, v, l);
  }
  else{
    kd = vec3(0.0, 0.05, 0.4);          // diffuse
    color = blinn_phong(ka, kd, ks, p, n, v, l);
  }
  
  /////////////////////////////////////////////////////////////////////////////
}
