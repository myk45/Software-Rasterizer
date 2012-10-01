#include "VertexAttribBuffer.h"

VertexAttribBuffer* VertexAttribBuffer::msVertexAttribBuff = NULL;


VertexAttribBuffer::VertexAttribBuffer()
{
	mNumberOfTriangle = 0;
}

VertexAttribBuffer* VertexAttribBuffer::getInstance()
{
	if (!msVertexAttribBuff) {
		msVertexAttribBuff = new VertexAttribBuffer();
		return msVertexAttribBuff;
	} else {
		return msVertexAttribBuff;
#ifdef _DEBUG_
		DEBUG_MSG("Instance already created\n")
#endif
	}
}

// Remove?
void VertexAttribBuffer::vFillAttribs()
{
}