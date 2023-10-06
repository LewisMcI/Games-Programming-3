#version 330

precision highp float;
uniform float time;

in vec3 fPosition;
in vec3 fNormal;
in vec3 rawX;

out vec4 FragColour;

const vec3  lightV1    = vec3(0.5,1.0,0.5); // stationary light
const float lightI     = 1.0;               // only for diffuse component
const float ambientC   = 0.15;
const float diffuseC   = 0.7;
const float specularC1 = 1.0;               // For stationary light
const float specularE1 = 128.0;
const float specularE2 = 32.0;
const vec3  lightCol   = vec3(1.0,0.0,0.0);
const vec3  objectCol  = vec3(0.0,0.5,1.0); // yellow-ish orange

vec2 blinnPhongDir(vec3 lightDir, float lightInt, float Ka, float Kd, float Ks, float shininess)
{
  vec3 s = normalize(lightDir);
  vec3 v = normalize(-fPosition);
  vec3 n = normalize(fNormal);
  vec3 h = normalize(v+s);
  float diffuse = Ka + Kd * lightInt * max(0.0, dot(n, s));
  float spec =  Ks * pow(max(0.0, dot(n,h)), shininess);
  return vec2(diffuse, spec);
}

void main()
{
  float angle      = 5.0*time;
  vec3 lightV2     = vec3(sin(angle)/2,0.0,cos(angle)/2);
  float specularC2 = 90.0;  // For moving light -- make this zero to keep only stationary light

  vec3 ColorS1 = blinnPhongDir(lightV1,0.5,0.5,0.5,specularC1,specularE1).y*lightCol;
  vec3 ColorS2 = blinnPhongDir(lightV2,0.5,0.5,0.5,specularC2,specularE2).y*lightCol;
  vec3 ColorAD = blinnPhongDir(lightV1,lightI,ambientC,diffuseC,0.0      ,1.0       ).x*objectCol;
  FragColour = vec4(ColorAD+ColorS1+ColorS2,(sin(time)+1)/2);
  
  // Stripe-discard effect -- comment out to keep solid model
  if(sin(90.0*rawX.x)>0.5) discard;
}