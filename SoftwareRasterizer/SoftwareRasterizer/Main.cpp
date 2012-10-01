#include <iostream>
#include "glm/glm.hpp"

#include "CommonIncludes.h"
#include "Rasterizer.h"
#include "Transformation.h"
#include <Windows.h>
#include <GL/glut.h>


float ang = 0.0;

void draw()
{	
	RED_COLOR
	RasterizerState::getInstance()->clearColorBuffer(red);		

	Rasterizer::getInstance()->Run();
	glDrawPixels(512, 512, GL_RGB, GL_UNSIGNED_BYTE, RasterizerState::getInstance()->getColorBuffer());
}

void idle()
{
	glutPostRedisplay();
	Sleep(1000);
}

void initialiseGLUT(int argc, char **argv)
{
	// Do this now. TODO: Find alternative!
	RasterizerState::getInstance()->getColorBuffer();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Rasterizer");	
	glutDisplayFunc(draw);
	glutIdleFunc(idle);
	glutMainLoop();	
}

int main(int argc, char **argv)
{	
	initialiseGLUT(argc, argv);		
	return 0;
}

