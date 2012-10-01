#ifndef _COMMON_INCLUDES_
#define _COMMON_INCLUDES_

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cassert>
#include <float.h>
#include <math.h>
#include "glm\glm.hpp"

#define _DEBUG_
#undef _DEBUG_

#ifdef _DEBUG_
#define DEBUG_MSG(MSG) printf(MSG);
#endif

#define RED_COLOR glm::vec3 red; \
		red.r = 0.0f;\
		red.g = 0.0f;\
		red.b = 0.0f;

#endif