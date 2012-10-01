#ifndef _RASTERIZER_
#define _RASTERIZER_

#include "CommonIncludes.h"
#include "FileIO.h"
#include "VertexAttribBuffer.h"
#include "RasterizerState.h"

typedef struct {
	VertexAttrib vert1;
	VertexAttrib vert2;
	VertexAttrib vert3;
} TriangleBatch;

// A singleton again! :D
class Rasterizer {
	private:
			Rasterizer();
			void debug();

			static Rasterizer* msRasterizer;
			FileIO *mFileIO;
			VertexAttribBuffer *mVertexAttribBuff; // a copy of the entire vertex attrib data read from the file.
			RasterizerState *mRasterizerState;

			std::vector<TriangleBatch> mTriangleBatchCache; // used in all transformations
			
			// Move VertexAttribBuffer member to a place like "model" where we can have multiple objects in the scene.
			glm::vec3 mBoundingBox[2]; //For the model. TODO: be moved to a better place.
	public:
			static Rasterizer* getInstance();
			bool bReadFile(std::string& fileName);
			void setBoundingBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);

			void vPerformModelTransform(); // Right now, we have just one model anyway :P			
			void vPerformProjection();
			void vPerformWindowTransform();
			void Run();
			void vClearTriangleBatch();
			void vScanAndColorTriangle(float, float, float, float, float, float);

			inline float winTramsformX(float x, float y)
			{
				//return m[0][0] * x + m[0][1] * y + m[0][2];
				return mRasterizerState->getInstance()->getWindowTransformationMatrix()[0][0] * x + 
				mRasterizerState->getInstance()->getWindowTransformationMatrix()[0][1] * y +
				mRasterizerState->getInstance()->getWindowTransformationMatrix()[0][2];
			}

			inline float winTramsformY(float x, float y)
			{
				//return m[1][0] * x + m[1][1] * y + m[1][2];
				return mRasterizerState->getInstance()->getWindowTransformationMatrix()[1][0] * x + 
				mRasterizerState->getInstance()->getWindowTransformationMatrix()[1][1] * y +
				mRasterizerState->getInstance()->getWindowTransformationMatrix()[1][2];
			}

			

};

#endif