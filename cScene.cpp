#include "core.h"

/////////////////////////////////////////////////////////////////////////////////////
// update() - update all scene assets here
/////////////////////////////////////////////////////////////////////////////////////
void cScene::update()
{
	m_Camera[m_cameraId].update();

	for (int i = 0; i < m_mesh_count; i++)
	{
		m_Mesh[i].m_objID = i;
		// update the object's transform
		// i.e. update the pos, rot, size
		m_Mesh[i].m_transform.update();
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// init() - loads all scene assets
/////////////////////////////////////////////////////////////////////////////////////
void cScene::init()
{
	// open up the .sdf file and load all required assets 
	openSDF();

	// initialize each mesh object
	for (int i = 0; i < m_mesh_count; i++)
	{
		m_Mesh[i].init();
	}

	// initialize the camera object
	m_Camera->init();


	glBindVertexArray(0);

	// creates the shaders needed to render this scene
	m_ShaderInfo.create();
}

/////////////////////////////////////////////////////////////////////////////////////
// render() - 
/////////////////////////////////////////////////////////////////////////////////////
void cScene::render()
{
	// update the scene here
	update();

	// loop through and render each mesh object in this scene
	for (int i = 0; i < m_mesh_count; i++)
	{
		m_Mesh[i].render(this, &m_ShaderInfo);
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// openSDF() - Opens up a scene descriptor file and allocates all memory needed
//			   NOTE: This function should not be changed
/////////////////////////////////////////////////////////////////////////////////////
void cScene::openSDF()
{
	// load the scene file here
	FILE* fp = NULL;
	
	// open the .sdf file
	fopen_s(&fp, "scene.sdf", "r");

	// fire an assert if the file cannot be found
	if (!fp)
		assert(0);

	// temp variables used to read data from the .sdf file
	char buffer[256] = { "\0"};
	float value;

	// initialize all counters to zero
	m_light_count = 0;
	m_mesh_count = 0;
	m_shader_count = 0;

	char* pch;

	// loop through and get the number of assets we have in the scene
	do
	{
		// LIGHT:
		fgets(buffer, 255, fp);
		pch = strstr(buffer, "LIGHT:");
		if (pch != NULL) m_light_count++;

		// MESH:
		pch = strstr(buffer, "MESH:");
		if (pch != NULL) m_mesh_count++;

		// SHADER:
		pch = strstr(buffer, "SHADER:");
		if (pch != NULL) m_shader_count++;

	} while (!feof(fp));

	// move cursor back to the start of the file
	// ready for the second pass
	rewind(fp);
	
	// Next, we load all the required assets into memory

	////////////////////////////////////////////////////////////
	// CAMERA
	////////////////////////////////////////////////////////////
	
	// allocate block of memory to store the camera
	m_Camera = new cCamera;

	// load the camera data
	fscanf_s(fp, "%s%s", buffer, 256, buffer, 256); // CAMERA {
	fscanf_s(fp, "%s%f", buffer, 256, &m_Camera->m_fov);		// FOV:	45.0
	fscanf_s(fp, "%s%f", buffer, 256, &m_Camera->m_near);		// NEAR:	0.5
	fscanf_s(fp, "%s%f", buffer, 256, &m_Camera->m_far);		// FAR:	100.0
	fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Camera->m_pos.x, &m_Camera->m_pos.y, &m_Camera->m_pos.z);		// POS:		0.0 0.0 -5.0
	fscanf_s(fp, "%s", buffer, 256);				// }
	
	m_Camera->m_target_pos = m_Camera->m_pos;


	////////////////////////////////////////////////////////////
	// LIGHTS
	////////////////////////////////////////////////////////////
	
	// allocate block of memory to store the lights..
	m_Light = new cLight[m_light_count];

	// loop through each light and load in the required data
	for (int i = 0; i < m_light_count; i++)
	{
		fscanf_s(fp, "%s%s", buffer, 256, buffer, 256);	// LIGHT: }
		m_Light[i].m_type = 0; // diffuse
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Light[i].m_pos.x, &m_Light[i].m_pos.y, &m_Light[i].m_pos.z); // POS:	-25.0 0.0 20.0
		fscanf_s(fp, "%s", buffer, 256);				// }
	}

	////////////////////////////////////////////////////////////
	// MESHES
	////////////////////////////////////////////////////////////
	char filename[256];
	char name[256];

	// allocate block of memory to store the mesh objects..
	m_Mesh = new cMesh[m_mesh_count];

	// loop through each mesh and load in the required data
	for (int i = 0; i < m_mesh_count; i++)
	{
		fscanf_s(fp, "%s%s", buffer, 256, m_Mesh[i].m_filename, 256);	//MESH: torus.obj
		fscanf_s(fp, "%s", buffer, 256);					// }
		fscanf_s(fp, "%s%s", buffer, 256, m_Mesh[i].m_name, 256);		//MESH: torus.obj
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Mesh[i].m_transform.m_pos.x, &m_Mesh[i].m_transform.m_pos.y, &m_Mesh[i].m_transform.m_pos.z);					// POS:	0.0 0.0 0.0
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Mesh[i].m_transform.m_rot.x, &m_Mesh[i].m_transform.m_rot.y, &m_Mesh[i].m_transform.m_rot.z);					// ROT : 2.0 2.0 0.0
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Mesh[i].m_transform.m_rot_incr.x, &m_Mesh[i].m_transform.m_rot_incr.y, &m_Mesh[i].m_transform.m_rot_incr.z);	// ROT_INCR:	1.0 1.0 0.0
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Mesh[i].m_transform.m_scale.x, &m_Mesh[i].m_transform.m_scale.y, &m_Mesh[i].m_transform.m_scale.z);			// SCALE : 1.25 1.25 1.25
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Mesh[i].m_transform.m_vel.x, &m_Mesh[i].m_transform.m_vel.y, &m_Mesh[i].m_transform.m_vel.z);					// VEL : 0.2 0.1 0.0
		fscanf_s(fp, "%s%d", buffer, 256, &m_Mesh[i].m_shaderID); // SHADER_ID	0

		fscanf_s(fp, "%s", buffer, 256);					// }
	}

	////////////////////////////////////////////////////////////
	// SHADERS
	////////////////////////////////////////////////////////////
	m_ShaderTable = new sShaderDetails[m_shader_count];
	
	fscanf_s(fp, "%s", buffer, 256); // SHADER:

	// loop through all shaders and load all required data
	for (int i = 0; i < m_shader_count; i++)
	{
		// init shader types..
		for( int j=0; j<2; j++ )
			m_ShaderTable[i].types[j] = 0;

		fscanf_s(fp, "%s", buffer, 256);		
		strcpy_s(m_ShaderTable[i].filename, buffer);
		
		int loop_count = 0;
		
		while (strcmp(buffer, "SHADER:") != 0)
		{
			loop_count++;

			fscanf_s(fp, "%s", buffer, 256);
			if (strcmp(buffer, "SHADER:") == 0)
				break;

			// sort the shader by type and add to list..
			if (strcmp(buffer, "VERT_SHDR") == 0)
				m_ShaderTable[i].types[0] = GL_VERTEX_SHADER;
			else
				m_ShaderTable[i].types[1] = GL_FRAGMENT_SHADER;

			// quit out of the loop if we exceed the number of shader types
			if (loop_count == 2)
				break;
		};
	}

	// house keeping - close the .sdf file
	fclose(fp);

}