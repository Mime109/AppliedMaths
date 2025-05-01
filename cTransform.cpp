#include "core.h"

using namespace glm;


//////////////////////////////////////////////////////////////////////////////////////////
// update() - create a new matrix for this mesh object
//////////////////////////////////////////////////////////////////////////////////////////
void cTransform::update()
{
    m_rot += m_rot_incr;
    
    m_ModelMatrix = glm::translate(mat4(1.0), vec3(m_pos));
    m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
    
    m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(m_scale));
}

