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
	//Sleep(100);
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
	glm::vec4 Position = glm::vec4(glm::vec3(0.0), 1.0);
	glm::mat4 Model = glm::mat4(1.0);
	Model[3] = glm::vec4(1.0, 1.0, 0.0, 1.0);
	glm::vec4 Transformed = Model * Position;	

	initialiseGLUT(argc, argv);		

	return 0;
}

