#pragma once

// These libraries are needed to link the program (Visual Studio specific)
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"glew32s.lib")
#pragma comment(lib,"glew32.lib")

#define GLEW_STATIC
#include "GL/glew.h" 
#include "GLFW/glfw3.h"

#include <Windows.h>
#include <stdio.h>
#include "assert.h"

#include "globals.h""
#include "textfile.h"
#include "cShader.h"
#include "cCamera.h"
#include "cLight.h"
#include "cTransform.h"
#include "cMesh.h"
#include "cScene.h"
