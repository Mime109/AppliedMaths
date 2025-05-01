#pragma once

#include "core.h"

#include "glm/glm.hpp"  
#include "glm/gtc/matrix_transform.hpp" 
#include "glm/gtc/type_ptr.hpp"

using namespace glm;

/////////////////////////////////////////////////////////
// enumerator used to identify which modelling package was used to create the .obj file
/////////////////////////////////////////////////////////
enum eFileType
{
	FILE_TYPE_MAYA = 0,
	FILE_TYPE_3DSMAX,
	FILE_TYPE_BLENDER,
};

/////////////////////////////////////////////////////////
// simple structure used to store face data
/////////////////////////////////////////////////////////
struct sFace
{
	int v_id[3];	// vertex indices
	int vt_id[3];	// texCoord indices
	int vn_id[3];	// normals indices
	int mtl_id;		// material index
};

/////////////////////////////////////////////////////////
// cVec3f class
/////////////////////////////////////////////////////////
class cVec3f
{
public:

	cVec3f() {}
	cVec3f(float X, float Y, float Z)
	{
		x = X; y = Y; z = Z;
	}
	cVec3f operator +(const cVec3f v)
	{
		cVec3f out;
		out.x = this->x + v.x;
		out.y = this->y + v.y;
		out.z = this->z + v.z;

		return out;
	}

	void normalize()
	{
		float d = sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);

		this->x /= d;
		this->y /= d;
		this->z /= d;
	}

	cVec3f operator /(const cVec3f v)
	{
		cVec3f out;
		out.x = this->x / v.x;
		out.y = this->y / v.y;
		out.z = this->z / v.z;

		return out;
	}

	float x, y, z;
};

/////////////////////////////////////////////////////////
// newmtl - structure used to hold material data
/////////////////////////////////////////////////////////
struct newmtl
{
	sRGB	diffuse;
	char	tex[64];
	char	name[64];
};

/////////////////////////////////////////////////////////
// cFace class
/////////////////////////////////////////////////////////
class cFace
{
public:
	cVec3f	m_v[3];
	cVec3f	m_fn;
};

/////////////////////////////////////////////////////////
// cVertex class
/////////////////////////////////////////////////////////
class cVertex
{
public:
	cVec3f	m_v;  // vertex
	cVec3f	m_n;  // vertex normal
	sVec2f	m_uv; // texture coordinates
};

/////////////////////////////////////////////////////////
// cMesh class - contains all mesh level data
/////////////////////////////////////////////////////////
class cMesh
{
public:
	cMesh();
	~cMesh();

	// init function - called when the mesh object gets created
	void init();

	// render function - used to display the object
	void render(class cScene *pScene, class cShaderInfo *pShaderInfo);

	// functions used to load in this asset and to create the
	// necessary geometric data required to render it
	void load(const char *obj_path, const char* obj_name);
	void importMTL();
	void loadFaces();
	void createFaceNormalList();
	void createFaceList();
	void createEdgeList();

	// gets the number of faces
	inline int numFaces()
	{
		return m_f_count;
	}
	// gets the address of a specific vertex from the vertex list
	inline cVec3f *v(int index)
	{
		return &m_v[index];
	}

	// gets the address of a material from the materials list
	inline newmtl	*matList(int index)
	{
		return &m_mtlList[index];
	}

	// All mesh objects have a cTransform function - used to 
	// position, rotation and size of the mesh object
	// It is the convention to keep the transform parameters 
	// separate from the mesh (geometric) properties
	// properties
	cTransform	m_transform;

	// file pointers used to load in the mesh and material objects
	FILE		*m_fp;
	FILE		*m_mtl;

	char		m_filename[256];
	char		m_name[256];
	int			m_shaderID;

	/////////////////////////////////////////////////////////////////////////////////////
	// VBO:		Vertex Buffer Object holds an array of data. 
	//			The data contained within the VBO is typically vertex, normal, colour and 
	//			texture coordinate data
	/////////////////////////////////////////////////////////////////////////////////////
	unsigned int m_VBO = NULL;

	/////////////////////////////////////////////////////////////////////////////////////
	// VAO:		Vertex Array Object holds info about how the data stored within the VBO is  
	//			formatted. The VAO holds a pointer to the start of each vertex attribute - 
	//			i.e. vertex, normal, colour, texture coordinate, along with the number of 
	//			elements for each attribute, (a vertex has 3 elements, a texture 
	//			coordinate has 2 elements), the step size (stride) needed to move to the  
	//			beginning of the next item in the list
	/////////////////////////////////////////////////////////////////////////////////////
	unsigned int m_VAO = NULL;

	unsigned int m_tex[32];
	
	// material filename
	char m_mtl_filename[64];
	// file type - i.e. what program was used to make this 3D 
	// asset
	eFileType m_import_filetype;

	int m_objID;			// object ID
	int m_v_count;			// number of vertices
	int m_vt_count;			// number of vertex texture coordinates
	int m_vn_count;			// number of vertex normals
	int m_f_count;			// number of faces
	int m_e_count;			// number of edges
	int m_material_count;	// number of materials
	
	// shader index - used to select a shader from shader list
	int m_shdr;

	cVec3f *m_v;	// pointer to the vertex list
	sVec2f *m_vt;	// pointer to the uv coord list
	cVec3f *m_vn;	// pointer to the vertex normal list
	cVec3f* m_fn;	// pointer to the face normals list
	sFace  *m_f;	// pointer to the indices for each face vertex - i.e. m_f[0].x = m_v, m_f[0].y = m_vt, m_f[0].z = m_vn

	cVec3f	*m_eList;		// pointer to the edge list
	cVertex	*m_vList;		// pointer to the vertex list
	newmtl	*m_mtlList;		// pointer to the material list
};

