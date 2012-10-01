#include "RasterizerState.h"


RasterizerState* RasterizerState::msRasterizerState = NULL;
unsigned char* RasterizerState::mColorBuffer = NULL;
unsigned char* RasterizerState::mZBuffer = NULL;

RasterizerState::RasterizerState()
{
	mWindowWidth  = 512;
	mWindowHeight = 512;
	mNoOfBytesPerPixel = 3; // lets start with RGB first!

	mProjectionMatrix = glm::mat4(1.0); // Load identity.
	mModelViewMatrix  = glm::mat4(1.0); // Load identity.
	mWindowTransformMatrix = glm::mat3(1.0); // Load identity.
}

RasterizerState* RasterizerState::getInstance()
{
	if (msRasterizerState == NULL) {
		// create the singleton instance.
		msRasterizerState = new RasterizerState();
		return msRasterizerState;
	} else {
		return msRasterizerState;
	}
}


void RasterizerState::vSetProjectionMatrix(glm::mat4 m)
{
	mProjectionMatrix = m;
}

glm::mat4 RasterizerState::getProjectionMatrix()
{
	return mProjectionMatrix;
}

void RasterizerState::vSetmodelViewMatrix(glm::mat4 m)
{
	mModelViewMatrix = m;
}

glm::mat4 RasterizerState::getmodelViewMatrix()
{
	return mModelViewMatrix;
}


void RasterizerState::vSetWindowTransformMatrix(glm::mat3 m)
{
	mWindowTransformMatrix = m;
}

glm::mat3 RasterizerState::getWindowTransformationMatrix()
{
	mWindowTransformMatrix[0] = glm::vec3(256.0f, 0.0f,   256.0f);
	mWindowTransformMatrix[1] = glm::vec3(0.0f,   256.0f, 256.0f);
	mWindowTransformMatrix[2] = glm::vec3(0.0f,   0.0f,   1.0f);

	return mWindowTransformMatrix;
}

void RasterizerState::clearColorBuffer(glm::vec3 col)
{
	for (int i = 0; i < mWindowWidth * mWindowHeight * mNoOfBytesPerPixel; i += 3) {
		mColorBuffer[i]   = (unsigned char)(col.r / 1.0f * 255);
		mColorBuffer[i+1] = (unsigned char)(col.g / 1.0f * 255);
		mColorBuffer[i+2] = (unsigned char)(col.b / 1.0f * 255);
	}
}

void RasterizerState::vUpdateColorAt(int x, int y, glm::vec3 col)
{
	//x = 250, y = 250;
	if (x > 512 || y > 512 || x < 0 || y < 0)
		return;

	int pos = (x*mWindowWidth*3) + (y*3);
	mColorBuffer[pos]     = (unsigned char)(col.r / 1.0f * 255);
	mColorBuffer[pos + 1] = (unsigned char)(col.g / 1.0f * 255);
	mColorBuffer[pos + 2] = (unsigned char)(col.b / 1.0f * 255);
}

