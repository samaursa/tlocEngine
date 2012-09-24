#version 140

in vec4 vVertex;
in vec4 vColor;

out vec4 vVaryingColor;

void main(void)
{
	vVaryingColor = vColor;
	gl_Position = vVertex;
}