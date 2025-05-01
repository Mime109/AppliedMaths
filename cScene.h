#pragma once

#include "core.h"

class cMesh;

/////////////////////////////////////////////////////////
// cScene class contains all game assets...i.e. meshes, cameras, lights etc.
/////////////////////////////////////////////////////////
class cScene
{
public:

	cScene() 
	{
		// init member variables
		m_start = false;
		m_cameraId	= 0;
		m_lightId	= 0;
	}

	~cScene() 
	{
		// deconstructor
	}

	void init();
	void render();
	void update();
	void openSDF();

	// pointers to blocks of memory used to load in all game assets 
	cShaderInfo		m_ShaderInfo;
	cCamera*		m_Camera;
	cLight*			m_Light;
	cMesh*			m_Mesh;
	sShaderDetails* m_ShaderTable;

	bool m_start;
	int m_shader_count;
	int m_light_count;
	int m_mesh_count;
	int m_cameraId;
	int m_lightId;

private:

};