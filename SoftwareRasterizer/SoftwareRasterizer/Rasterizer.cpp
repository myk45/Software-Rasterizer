#include "Rasterizer.h"
#include "VertexAttribBuffer.h"
#include "Transformation.h"

Rasterizer* Rasterizer::msRasterizer = NULL;

Rasterizer::Rasterizer()
{
	// Create other global singletons 
	mFileIO = FileIO::vGetInstance();
	mVertexAttribBuff = VertexAttribBuffer::getInstance();
	mRasterizerState  = RasterizerState::getInstance();
}

Rasterizer* Rasterizer::getInstance()
{
	if (!msRasterizer) {
		msRasterizer = new Rasterizer();
		return msRasterizer;
	} else {
		return msRasterizer;
#ifdef _DEBUG_
		DEBUG_MSG("Instance already created\n")
#endif
	}
}

// Open a file. Pass this handle to VertexBufferAttrib, where the reading of the file takes place.
bool Rasterizer::bReadFile(std::string& fileName)
{
	FileIO::vGetInstance()->fpFileOpen(fileName, "r");	
	FileIO::vGetInstance()->iReadFileAndFillAttribs(mVertexAttribBuff, fileName);

#ifdef _DEBUG_
	debug();
#endif
	return 1;
}

void Rasterizer::debug()
{
	printf("\n Triangle count = %d\n", mVertexAttribBuff->getInstance()->getTriangleCount());

	for (unsigned int i = 0; i < mVertexAttribBuff->getInstance()->getVertexBuffer().size(); i++) {
		printf("\nVertex data: %f %f %f %f %f %f %f %f %f %f %f",
		mVertexAttribBuff->getInstance()->getVertexBuffer()[i].mVertexCoord.x,
		mVertexAttribBuff->getInstance()->getVertexBuffer()[i].mVertexCoord.y,
		mVertexAttribBuff->getInstance()->getVertexBuffer()[i].mVertexCoord.z,
		mVertexAttribBuff->getInstance()->getVertexBuffer()[i].mVertexCoord.w,

		mVertexAttribBuff->getInstance()->getVertexBuffer()[i].mNormal.x,
		mVertexAttribBuff->getInstance()->getVertexBuffer()[i].mNormal.y,
		mVertexAttribBuff->getInstance()->getVertexBuffer()[i].mNormal.z,

		mVertexAttribBuff->getInstance()->getVertexBuffer()[i].mColor.r,
		mVertexAttribBuff->getInstance()->getVertexBuffer()[i].mColor.g,
		mVertexAttribBuff->getInstance()->getVertexBuffer()[i].mColor.b,
		mVertexAttribBuff->getInstance()->getVertexBuffer()[i].mColor.a);

		//getchar();
	}
}

void Rasterizer::setBoundingBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
	// Min
	mBoundingBox[0].x = xMin;
	mBoundingBox[0].y = yMin;
	mBoundingBox[0].z = zMin;

	// Max
	mBoundingBox[1].x = xMax;
	mBoundingBox[1].y = yMin;
	mBoundingBox[1].z = zMax;
}

void Rasterizer::vPerformModelTransform()
{
	// assume that the modelview is set
	for (unsigned int i = 0; i < mVertexAttribBuff->getInstance()->getVertexBuffer().size()-3; i += 3) {
		VertexAttrib v1, v2, v3;
		TriangleBatch t;
			
		v1.mColor  = mVertexAttribBuff->getInstance()->getVertexBuffer()[i].mColor;
		v1.mNormal = mVertexAttribBuff->getInstance()->getVertexBuffer()[i].mNormal;
		v1.mTextureCoord = mVertexAttribBuff->getInstance()->getVertexBuffer()[i].mTextureCoord;
		v1.mVertexCoord  = mRasterizerState->getInstance()->getmodelViewMatrix() * 
						   mVertexAttribBuff->getInstance()->getVertexBuffer()[i].mVertexCoord;

		v2.mColor  = mVertexAttribBuff->getInstance()->getVertexBuffer()[i+1].mColor;
		v2.mNormal = mVertexAttribBuff->getInstance()->getVertexBuffer()[i+1].mNormal;
		v2.mTextureCoord = mVertexAttribBuff->getInstance()->getVertexBuffer()[i+1].mTextureCoord;
		v2.mVertexCoord  = mRasterizerState->getInstance()->getmodelViewMatrix() * 
						   mVertexAttribBuff->getInstance()->getVertexBuffer()[i+1].mVertexCoord;

		v3.mColor  = mVertexAttribBuff->getInstance()->getVertexBuffer()[i+2].mColor;
		v3.mNormal = mVertexAttribBuff->getInstance()->getVertexBuffer()[i+2].mNormal;
		v3.mTextureCoord = mVertexAttribBuff->getInstance()->getVertexBuffer()[i+2].mTextureCoord;
		v3.mVertexCoord  = mRasterizerState->getInstance()->getmodelViewMatrix() * 
						   mVertexAttribBuff->getInstance()->getVertexBuffer()[i+2].mVertexCoord;
			

		t.vert1 = v1; t.vert2 = v2; t.vert3 = v3;

		mTriangleBatchCache.push_back(t);
	}
}


void Rasterizer::vPerformProjection()
{
	// assume that the modelview is set
	for (unsigned int i = 0; i < mTriangleBatchCache.size(); i++) {
		VertexAttrib &v1 = mTriangleBatchCache[i].vert1;
		VertexAttrib &v2 = mTriangleBatchCache[i].vert2;
		VertexAttrib &v3 = mTriangleBatchCache[i].vert3;
			
		v1.mVertexCoord = mRasterizerState->getInstance()->getProjectionMatrix() * v1.mVertexCoord;
		v2.mVertexCoord = mRasterizerState->getInstance()->getProjectionMatrix() * v2.mVertexCoord;
		v3.mVertexCoord = mRasterizerState->getInstance()->getProjectionMatrix() * v3.mVertexCoord;						
	}
}

extern float ang;

void Rasterizer::vPerformWindowTransform()
{
	glm::vec3 vA, vB, vC;
	
	for (unsigned int i = 0; i < mTriangleBatchCache.size(); i++) {
		VertexAttrib &v1 = mTriangleBatchCache[i].vert1;
		VertexAttrib &v2 = mTriangleBatchCache[i].vert2;
		VertexAttrib &v3 = mTriangleBatchCache[i].vert3;				

		/* Window transformation */
		float x1 = winTramsformX(glm::vec3(v1.mVertexCoord).x, glm::vec3(v1.mVertexCoord).y),
			  y1 = winTramsformY(glm::vec3(v1.mVertexCoord).x, glm::vec3(v1.mVertexCoord).y);

		float x2 = winTramsformX(glm::vec3(v2.mVertexCoord).x, glm::vec3(v2.mVertexCoord).y), 
			  y2 = winTramsformY(glm::vec3(v2.mVertexCoord).x, glm::vec3(v2.mVertexCoord).y);

		float x3 = winTramsformX(glm::vec3(v3.mVertexCoord).x, glm::vec3(v3.mVertexCoord).y),
			  y3 = winTramsformY(glm::vec3(v3.mVertexCoord).y, glm::vec3(v3.mVertexCoord).y);

		float xmin = (x1 < x2) ? (x1 < x3 ? x1 : x3) : (x2 < x3 ? x2 : x3);
		float xmax = (x1 > x2) ? (x1 > x3 ? x1 : x3) : (x2 > x3 ? x2 : x3);
		float ymin = (y1 < y2) ? (y1 < y3 ? y1 : y3) : (y2 < y3 ? y2 : y3);
		float ymax = (y1 > y2) ? (y1 > y3 ? y1 : y3) : (y2 > y3 ? y2 : y3);

		glm::vec3 col;
		col.r = v1.mColor.r;
		col.g = v1.mColor.g;
		col.b = v1.mColor.b;
		mRasterizerState->getInstance()->vUpdateColorAt((int)xmax, (int)ymax, col);
	}	
}

bool flag;
void Rasterizer::Run()
{
	if (!flag) {
		Rasterizer::getInstance()->bReadFile(std::string("apple.txt"));
		flag = true;
	}

	RasterizerState::getInstance()->vSetmodelViewMatrix(Transformation::mGetRotationMatrix(ang += 1, 1.0, 0.0, 0.0));
	RasterizerState::getInstance()->vSetProjectionMatrix(Transformation::mGetOrthographicProjectionMatrix(-4, 4, -4, 4, -100, 100));

	Rasterizer::getInstance()->vPerformModelTransform();
	Rasterizer::getInstance()->vPerformProjection();
	Rasterizer::getInstance()->vPerformWindowTransform();
}