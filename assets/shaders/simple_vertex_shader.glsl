#ifdef GL_ES
# version 100
#else
# version 140
#endif

attribute vec4 vVertex;
attribute vec4 vColor;

varying lowp vec4 vVaryingColor;

void main(void)
{
	vVaryingColor = vColor;
	gl_Position = vVertex;
}