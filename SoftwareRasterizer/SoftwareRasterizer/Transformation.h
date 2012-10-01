#ifndef _TRANSFORMATION_
#define _TRANSFORMATION_

#include "CommonIncludes.h"

class Transformation {
	public:
			static glm::mat4 mGetRotationMatrix(float angle, float x, float y, float z);
			static glm::mat4 mGetPerspectiveProjectionMatrix(float left, float right, float bottom, float top, float near, float far);
			static glm::mat4 mGetOrthographicProjectionMatrix(float left, float right, float bottom, float top, float back, float front);

			// Object space to world space transform -> model transform.
			void vTransformToWorldSpace(glm::vec4& v, glm::mat4& mv);
			
			// World space to eye space transform -> view transform. 
			void vTransformToEyeSpace(glm::vec4& v, glm::mat4& mv);

			// Eye space to clip space transform -> Projection. 
			void vTransformToClipSpace(glm::vec4& v, glm::mat4& proj);

			// Eye space to clip space transform -> Projection. 
			void vPerformPerspectiveDivide(glm::vec4& v);

			// Window transform needed
};

#endif