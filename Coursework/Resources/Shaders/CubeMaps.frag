#version 420

layout (binding = 0) uniform samplerCube tex_cubemap;

in VS_OUT
{
	vec3 tC;
} fs_in;

layout (location = 0) out vec4 color;

void main(void)
{
	color = texture(tex_cubemap, fs_in.tC);
}