#version 400

out vec4 FragColor;

in vec3 fPosition;
in vec3 fNormal;
in vec2 tC;
uniform vec3 albedo;

const float ambient_coeff   = 0.25;
const float specular_coeff  = 1.0;
const float specular_exp    = 32.0;
const vec3  light_direction = vec3(-1.0,1.0,1.0); // stationary light
const vec3  light_color     = vec3(1.0,1.0,1.0);
const vec3  object_color    = vec3(1.0,0.6,0.0); // yellow-ish orange
vec3 calculateAmbientAndSpecular();
void main()
{
	//vec3 colour = mix(, vec3(texture2D(diffuse, tC)), 1.0f);
	//FragColor = vec4(albedo, 1.0f)* clamp(vec4(calculateAmbientAndSpecular(), 1.0), 0.0f, 1.0f);
	FragColor = vec4(mix(albedo, calculateAmbientAndSpecular(), .5f), 1.0f);
}

vec3 calculateAmbientAndSpecular()
{
  vec3 l = normalize(light_direction);
  vec3 n = normalize(fNormal);
  vec3 e = normalize(-fPosition);
  vec3 h = normalize (e+l);

  vec3 ambient_color  = ambient_coeff  * object_color;
  vec3 specular_color = specular_coeff * pow(max(0.0,dot(n,h)),specular_exp) * light_color;

  vec3 newColour = ambient_color+specular_color;

  return newColour;
}