#version 140

out vec4 vFragColor;
in  vec4 vVaryingColor;

void main(void)
{
	vFragColor = vVaryingColor;
}