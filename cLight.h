#pragma once

#include "cLight.h"

#include "glm/glm.hpp"  
#include "glm/gtc/matrix_transform.hpp" 
#include "glm/gtc/type_ptr.hpp"

using namespace glm;

/////////////////////////////////////////////////////////
// cLight class
/////////////////////////////////////////////////////////
class cLight
{
public:
	cLight() 
	{
		m_type = 0;
		m_pos.x = 0.0f;
		m_pos.y = 0.0f;
		m_pos.z = 0.0f;
	}
	~cLight() {}

	void init(float x, float y, float z)
	{
		m_pos.x = x;
		m_pos.y = y;
		m_pos.z = z;
	}

	void update(float mx, float my);

	int	m_type; // POINT_LIGHT = 0;
	vec3 m_pos;	

private:
};