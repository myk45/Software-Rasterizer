#include "CommonIncludes.h"
#include "Transformation.h"

void Transformation::vTransformToWorldSpace(glm::vec4& v, glm::mat4& mv)
{
	v = mv * v;
}
			
void vTransformToEyeSpace(glm::vec4& v, glm::mat4& mv)
{
	v = mv * v;
}


void vTransformToClipSpace(glm::vec4& v, glm::mat4& proj)
{
	v = proj * v;
}

void vPerformPerspectiveDivide(glm::vec4& v)
{
}
			

glm::mat4 Transformation::mGetOrthographicProjectionMatrix(float l, float r, float b, float t, float f, float n)
{		
	glm::mat4 m;
	
	m[0][0] = 2 / (r - l);
	m[1][1] = 2 / (t - b);
	m[2][2] = -2 / (f - n);
	m[0][3] = -(r + l) / (r - l);
	m[1][3] = -(t + b) / (t - b);
	m[2][3] = -(f + n) / (f - n);

	return m;
}

glm::mat4 Transformation::mGetRotationMatrix(float ang, float x, float y, float z)
{
	glm::mat4 m(glm::vec4(1.0, 0.0, 0.0, 0.0), 
				glm::vec4(0.0, cos(ang), -sin(ang), 0.0),
				glm::vec4(0.0, sin(ang),  cos(ang), 0.0),
				glm::vec4(0.0, 0.0, 0.0, 1.0));
				
	//glm::mat4 m(glm::vec4(1.0, 0.0, 0.0, 0.0), 
	//			glm::vec4(0.0, 2.0, 0.0, 0.0),
	//			glm::vec4(0.0, 0.0, 2.0, 0.0),
	//			glm::vec4(0.0, 0.0, 0.0, 1.0));

	return m;
}