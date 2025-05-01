///////////////////////////////////////////////////////////////////////
// NOTE: DO NOT ALTER THIS FILE
///////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
// cShader.h
//////////////////////////////////////////////////////////////////////////////////////////

#pragma once



/////////////////////////////////////////////////////////
// cShader class
/////////////////////////////////////////////////////////
class cShader
{
public:

	cShader();
	~cShader(){}

	inline void			cwd(char *path){ strcpy_s( m_cwd, sizeof(char)*32, path );}
	inline char			*cwd(){return m_cwd;}
	
	inline unsigned int	program(){return m_program;}

	void CheckShader(GLuint id, GLuint type, GLint* ret, const char* onfail);
	void clean();
	void create(struct sShaderDetails* pShader);
	void loadShaderFile(struct sShaderDetails* pShader, int count);

private:

	char* m_cwd;

	GLuint m_vs;	// vertex shader
	GLuint m_fs;	// fragment shader

	unsigned int m_program;
};


class cShaderInfo
{
public:

	cShaderInfo();
	~cShaderInfo(){}
	void create();//int count);
	void clean();

	inline cShader	*getList(){	return m_pList;}
	bool setUniformLocation(unsigned int shader, const char* name, GLint* pLocation);
	class cShader *list(int id);

	void set_flags(unsigned int value)
	{
		m_flags = value;
	}

	unsigned int get_flags()
	{
		return m_flags;
	}

	inline void shaderCount(int count)
	{ 
		m_num_shaders = count;
	}
	inline int  shaderCount()
	{
		return m_num_shaders;
	}
	

private:
	class cShader		*m_pList;

	int				m_num_shaders;
	unsigned int	m_flags;		// used to render individual maps
};
