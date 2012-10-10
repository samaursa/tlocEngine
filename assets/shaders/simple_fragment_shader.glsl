#ifdef GL_ES
# version 100
#else
# version 140
#endif

varying lowp vec4 vVaryingColor;

void main(void)
{
	gl_FragColor = vVaryingColor;
}
