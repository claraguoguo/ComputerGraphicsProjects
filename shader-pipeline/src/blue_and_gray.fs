// Set the pixel color to blue or gray depending on is_moon.
//
// Uniforms:
uniform bool is_moon;
// Outputs:
out vec3 color;
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code:
  if (is_moon) {
    // if moon, set to grey
    color = vec3(0.5, 0.5, 0.5);
  }
  else {
    // else, set to blue 
    color = vec3(0, 0, 1);
  }
  /////////////////////////////////////////////////////////////////////////////
}
