#version 100

varying lowp vec4 vVaryingColor;

void main(void)
{
	gl_FragColor = vVaryingColor;
}
