#ifndef _RASTERIZER_STATE
#define _RASTERIZER_STATE

#include "CommonIncludes.h"

class RasterizerState {
	private:
			glm::mat4 mProjectionMatrix;
			glm::mat4 mModelViewMatrix; 
			glm::mat3 mWindowTransformMatrix;

			static unsigned char *mColorBuffer; 
			static unsigned char *mZBuffer;

			RasterizerState();
			static RasterizerState* msRasterizerState;
	
			int mWindowWidth; // same size used for FrameBuffer also
			int mWindowHeight;
			int mNoOfBytesPerPixel;

	public:
		    static RasterizerState* getInstance();
			
			void vSetProjectionMatrix(glm::mat4 m);
			glm::mat4 getProjectionMatrix();

			void vSetmodelViewMatrix(glm::mat4 m);
			glm::mat4 getmodelViewMatrix();

			void vSetWindowTransformMatrix(glm::mat3 m);
			glm::mat3 getWindowTransformationMatrix();

			// one instance of the Color Buffer only.
			inline unsigned char* getColorBuffer()
			{
				if (!mColorBuffer) {
					mColorBuffer = new unsigned char[mWindowWidth * mWindowHeight * mNoOfBytesPerPixel];
					return mColorBuffer ;
				} else {
					return mColorBuffer;
				}
			}

			// one instance of the Z Buffer only.
			inline unsigned char* getZBuffer()
			{
				if (!mZBuffer) {
					mZBuffer = new unsigned char[mWindowWidth * mWindowHeight * mNoOfBytesPerPixel];
					return mZBuffer ;
				} else {
					return mZBuffer;
				}
			}

			inline void RasterizerState::vUpdateColorBuffer(unsigned char* colArr)
			{
				for (int i = 0; i < mWindowWidth * mWindowHeight * mNoOfBytesPerPixel; i++) {
					mColorBuffer[i] = colArr[i];					
				}
			}


			void clearColorBuffer(glm::vec3 col);
			void vUpdateColorAt(int x, int y, glm::vec3 col);

};

#endif