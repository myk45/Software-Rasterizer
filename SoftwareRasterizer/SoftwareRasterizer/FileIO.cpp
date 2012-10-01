#include "CommonIncludes.h"
#include "FileIO.h"
#include "VertexAttribBuffer.h"
#include "Rasterizer.h"

FileIO* FileIO::m_psFileIO = NULL;

// See comments in class declaration
FILE* FileIO::fpFileOpen(std::string fileName, std::string mode)
{	
	FILE *fp = fopen(fileName.c_str(), mode.c_str());

	if (fp == NULL) {		
		printf("Unable to open file %s", fileName.c_str());		
		return (FILE*)NULL; // check this
	} else {
		printf("\nOpened File %s", fileName.c_str()); 
		mMFileMap[fileName] = fp; // Map from string -> FILE*.
		return fp;
	}
}
		   


// See comments in class declaration
bool FileIO::bClose(const std::string& fileName)
{
	if (mMFileMap[fileName]) {
		if (fclose(mMFileMap[fileName])) {
			mMFileMap[fileName] = NULL;
			printf("File closed");		
		} else {
			printf("Not able to close file!\n");
		}
		return true;
	} else {
		printf("Cannot close file");
		assert(0);
		return 0; // Not really needed :D
	}
}



// See comments in class declaration
FileIO::FileIO()
{

}


// See comments in class declaration
FileIO* FileIO::vGetInstance()
{
	if (m_psFileIO == NULL) {
		// create the singleton instance.
		m_psFileIO = new FileIO();
		return m_psFileIO;
	} else {
		return m_psFileIO;
	}
}


// See comments in class declaration
int FileIO::iReadBytes(unsigned char *dest, int num, FILE *fp)
{
	int iElemsRead = fread(dest, 1, num, fp);

	if (iElemsRead != EOF) {
		printf("\nElements read");
		return iElemsRead;
	} else {
		printf("\nEOF reached!");
		assert(0); // remove this later?
		return EOF;
	}
}

int FileIO::iReadLine(char *buff, std::string fileName)
{
	int noOfBytes;

	if (noOfBytes = fscanf(mMFileMap[fileName], "%[^\n]\n", buff)) {
		return noOfBytes;
	} else {
		return 0;
	}
}


// -triangleCount-
// x y z
// nx ny nz
// r g b a
int FileIO::iReadFileAndFillAttribs(VertexAttribBuffer* vertAttrib, std::string fileName)
{
	float minX =  FLT_MAX, 
		  maxX = -FLT_MAX, 
		  minY =  FLT_MAX,
		  maxY = -FLT_MAX,
		  minZ =  FLT_MAX, 
		  maxZ = -FLT_MAX;

	if (!feof(mMFileMap[fileName])) {
		// read first number.
		int trlCount;
		fscanf(mMFileMap[fileName], "%d", &trlCount); 
		vertAttrib->getInstance()->setTriangleCount(trlCount);

		// read rest of the file
		while (!feof(mMFileMap[fileName])) {
			float x, y, z, nx, ny, nz, r, g, b, a;
			fscanf(mMFileMap[fileName], "%f %f %f %f %f %f %f %f %f %f", &x, &y, &z, &nx, &ny, &nz, &r, &g, &b, &a);
			VertexAttrib v;

			v.mVertexCoord.x = x;
			v.mVertexCoord.y = y;
			v.mVertexCoord.z = z;
			v.mVertexCoord.w = 1.0;

			v.mColor.r = r;
			v.mColor.g = g;
			v.mColor.b = b;
			v.mColor.a = a;

			v.mNormal.x = nx;
			v.mNormal.y = ny;
			v.mNormal.z = nz;			

			vertAttrib->getInstance()->pushVertexData(v);		
			minX = x < minX ? x : minX;
			maxX = x > maxX ? x : maxX;

			minY = y < minY ? y : minY;
			maxY = y > maxY ? y : maxY;

			minZ = z < minZ ? z : minZ;
			maxZ = z > maxZ ? z : maxZ;
		}
	}
	Rasterizer::getInstance()->setBoundingBox(minX, maxX, minY, maxY, minZ, maxZ);
	return 1; // TODO: return number of bytes or maybe number of expected triangles?
}