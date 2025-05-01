#pragma once

#include "core.h"

#include "glm/glm.hpp"  
#include "glm/gtc/matrix_transform.hpp" 
#include "glm/gtc/type_ptr.hpp"

using namespace glm;

/////////////////////////////////////////////////////////
// cTransform class - used to create the modelMatrix
// to control the object size, position and rotation
/////////////////////////////////////////////////////////
class cTransform
{
public:
	cTransform()
	{
		m_ModelMatrix = mat4(1.0f);

		m_rot = vec3(0, 0, 0);
		m_pos = vec3(0, 0, 0);
		m_scale = vec3(1, 1, 1);
		m_rot_incr = vec3(0, 0, 0);
	}
	~cTransform() 
	{
	}

	void update();
	
	vec3		m_pos;
	vec3		m_rot;		// current rotation angle used to create the rotation matrix
	vec3		m_rot_incr;	// rotation incrementor
	vec3		m_scale;
	vec3		m_vel;

	glm::mat4	m_ModelMatrix;			// model matrix  
	glm::mat3	m_NormalMatrix;			// normal matrix

	glm::mat4	m_ModelView;
	glm::mat4	m_ModelViewProj;
};





