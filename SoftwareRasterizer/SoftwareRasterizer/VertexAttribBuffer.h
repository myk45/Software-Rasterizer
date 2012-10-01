#ifndef _VERTEX_BUFFER_
#define _VERTEX_BUFFER_

#include "CommonIncludes.h"

// Class to store all the vertices. make this a singleton as well.
// This will have all per vertex data. i.e normals, texture coords, color and the vertex itself.

typedef struct  {
	glm::vec4 mVertexCoord;
	glm::vec4 mColor;
	glm::vec2 mTextureCoord; // (x, y) currently
	glm::vec3 mNormal;			 
} VertexAttrib;

class VertexAttribBuffer {
	private:
			VertexAttribBuffer(); // Private constructor.

			// group these?
			std::vector<VertexAttrib> mVertexAttribs;

			unsigned int mNumberOfTriangle;
			static VertexAttribBuffer* msVertexAttribBuff;
	public:
			inline void pushVertexData(VertexAttrib v) 
			{
				mVertexAttribs.push_back(v);
			}
			
			inline std::vector<VertexAttrib>& getVertexBuffer()
			{
				return mVertexAttribs;
			}

			inline void setTriangleCount(int trlCount)
			{
				mNumberOfTriangle = trlCount;
			}

			inline int getTriangleCount()
			{
				return mNumberOfTriangle;
			}

			static VertexAttribBuffer* getInstance();
			void vFillAttribs();
			
};
#endif