#pragma once
#include "glm/glm.hpp"  
#include "glm/gtc/matrix_transform.hpp" 
#include "glm/gtc/type_ptr.hpp"

using namespace glm;

/////////////////////////////////////////////////////////
// cCamera class
/////////////////////////////////////////////////////////
class cCamera
{
public:
	cCamera();
	~cCamera();

	void init();
	void update();

	glm::mat4 projectionMatrix;		// projection matrix
	glm::mat4 viewMatrix;			// view matrix

	glm::vec3 m_pos;
	glm::vec3 m_target_pos;
	glm::vec3 m_vel;

	float m_fov;
	float m_near;
	float m_far;
};

