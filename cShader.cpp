///////////////////////////////////////////////////////////////////////
// NOTE: DO NOT ALTER THIS FILE
///////////////////////////////////////////////////////////////////////

#include "core.h"
#include "assert.h"
#include <windows.h>
#include <direct.h>
#include <iostream>
#include <string>

extern cScene Scene;


///////////////////////////////////////////////////////////////////////
// Number of programmable shaders available. 
// Note:	The order of the ShaderTypes reflects the order within the
//			ShaderList[] - see below
///////////////////////////////////////////////////////////////////////
const int MAX_SHADERS_TYPES = 2;

GLuint ShaderTypes[MAX_SHADERS_TYPES] =
{
	GL_VERTEX_SHADER,				// vs
	GL_FRAGMENT_SHADER				// fs
};

//////////////////////////////////////////////////////////////////////////////////////////
// cShader() - constructor
//////////////////////////////////////////////////////////////////////////////////////////
cShader::cShader()
{
	m_cwd = new char[256];

	m_program = -1;
	m_vs = -1;
	m_fs = -1;
}

//////////////////////////////////////////////////////////////////////////////////////////
// clean() - delete shader object
//////////////////////////////////////////////////////////////////////////////////////////
void cShader::clean()
{
	if( m_vs )
		glDeleteShader(m_vs);
	if( m_fs )
		glDeleteShader(m_fs); 
	if( m_program )
		glDeleteProgram(m_program);
}

//////////////////////////////////////////////////////////////////////////////////////////
// CheckShader() - creates if anything went wrong in shader compile/linking
//////////////////////////////////////////////////////////////////////////////////////////
void cShader::CheckShader(GLuint id, GLuint type, GLint* ret, const char* onfail)
{
	switch (type)
	{
	case(GL_COMPILE_STATUS):
	{
		glGetShaderiv(id, type, ret);
		if (*ret == false)
		{
			int infologLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infologLength);
			GLchar buffer[512];
			GLsizei charsWritten = 0;
			std::cout << onfail << std::endl;
			glGetShaderInfoLog(id, infologLength, &charsWritten, buffer);
			std::cout << buffer << std::endl;
		}
	}
	break;
	case(GL_LINK_STATUS):
	{
		glGetProgramiv(id, type, ret);
		if (*ret == false) {
			int infologLength = 0;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infologLength);
			GLchar buffer[512];
			GLsizei charsWritten = 0;
			std::cout << onfail << std::endl;
			glGetProgramInfoLog(id, infologLength, &charsWritten, buffer);
			std::cout << buffer << std::endl;
		}
	}
	break;
	default:
		break;
	};
}

/////////////////////////////////////////////////////////////////////////////////////
// loadShaderFile() - recursively loops through and loads all shader files associated
//					  with this shader
/////////////////////////////////////////////////////////////////////////////////////
void cShader::loadShaderFile( sShaderDetails *pShader, int count )
{
	if (count >= MAX_SHADERS_TYPES)
		return;

	if (pShader->types[count])
	{
		char file_type[8] = { "\0" };

		GLuint pShaderID;

		switch (pShader->types[count])
		{
			case GL_VERTEX_SHADER: 			strcpy_s(file_type, sizeof(char) * 8, ".vs");	break;
			case GL_FRAGMENT_SHADER:		strcpy_s(file_type, sizeof(char) * 8, ".fs");	break;
		}

		pShaderID = glCreateShader(pShader->types[count]);

		char fp[256];
		char file[256];
		strcpy_s(file, sizeof(char) * 256, pShader->filename);
		strcat_s(file, sizeof(char) * 256, file_type);

		strcpy_s(fp, sizeof(char) * 256, m_cwd);
		strcat_s(fp, sizeof(char) * 256, "\\");
		strcat_s(fp, sizeof(char) * 256, file);


		char* s = textFileRead(file);

		if (!s)
		{
			printf("\n\nERROR: file: %s not found -  ", file);
			return;
		}

		GLint ret;

		glShaderSource(pShaderID, 1, &s, NULL);

		free(s);

		glCompileShader(pShaderID);
		CheckShader(pShaderID, GL_COMPILE_STATUS, &ret, "unable to compile the shader!");	

		glAttachShader(m_program, pShaderID);
	}
	
	loadShaderFile(pShader, ++count);
	return;
}

//////////////////////////////////////////////////////////////////////////////////////////
// create() - creates a new shader object
//////////////////////////////////////////////////////////////////////////////////////////
void cShader::create(sShaderDetails *pShader)
{
	char* cwd = _getcwd(m_cwd, _MAX_PATH);

	m_program = glCreateProgram();
	loadShaderFile(pShader, 0);

	GLint ret;

	glLinkProgram(m_program);
	CheckShader(m_program, GL_LINK_STATUS, &ret, "linkage failure!");
}


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
// cShaderInfo() - constructor
//////////////////////////////////////////////////////////////////////////////////////////
cShaderInfo::cShaderInfo()
{
	if (sizeof(Scene.m_ShaderTable) / sizeof(sShaderDetails) != Scene.m_shader_count)
	{
		printf("\\ERROR! SHADER_COUNT does not match number of shaders in m_ShaderTable\n\n");
		assert(0);
	}

	//	m_num_shaders = Scene.m_shader_count;
	m_pList = NULL;
	m_flags = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
// create() - allocate block of memory to hold ALL shaders
//////////////////////////////////////////////////////////////////////////////////////////
void cShaderInfo::create()
{
	m_pList = new class cShader[Scene.m_shader_count];

	for( int i=0; i< Scene.m_shader_count; i++ )
	{
		list(i)->create(&Scene.m_ShaderTable[i]);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// clean() - delete an existing shader object
//////////////////////////////////////////////////////////////////////////////////////////
void cShaderInfo::clean()
{
	if( m_pList )
	{
		for( int i=0; i< Scene.m_shader_count; i++ )
		{
			list(i)->clean();
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// setUniformLocation() - return the uniform location if one exists
//////////////////////////////////////////////////////////////////////////////////////////
bool cShaderInfo::setUniformLocation(unsigned int shader, const char* name, GLint* pLocation)
{
	*pLocation = glGetUniformLocation(shader, name);

	if (*pLocation >= 0)
		return true;
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////////////////////
// list() - returns requested element from shader list
//////////////////////////////////////////////////////////////////////////////////////////
class cShader *cShaderInfo::list(int id)
{
	if( id >= Scene.m_shader_count)
	{
		// if you get here, then you are trying to access a shader element that exceeds the shader array size.
		// try increasing the number_of_shaders created in main() - ShaderInfo.create(number_of_shaders);
		printf("ERROR: ");
		printf("array limits exceeded\n");
	}

	return &m_pList[id];
}

