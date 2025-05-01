
#include "core.h"
#include <math.h>
#include "cMesh.h"
#include "cCamera.h"

#include "glm/glm.hpp"  
#include "glm/gtc/matrix_transform.hpp" 
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

using namespace std;
using namespace glm;


/////////////////////////////////////////////////////////////////////////////////////
// global variables
/////////////////////////////////////////////////////////////////////////////////////
cScene Scene;

unsigned int initWidth = 800;
unsigned int initHeight = 600;

/////////////////////////////////////////////////////////////////////////////////////
// resize() - callback used when the window gets resized
/////////////////////////////////////////////////////////////////////////////////////
void resize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);		// Draw into entire window
}

/////////////////////////////////////////////////////////////////////////////////////
// keyboard() - callback function used to capture keyboard inputs
/////////////////////////////////////////////////////////////////////////////////////
void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	// ignore key up (key release) events
	if (action == GLFW_RELEASE) 
		return;	

	cCamera* pCamera = Scene.m_Camera;

	// process keyboard inputs here..
	switch (key)
	{
		// quit the application..
		case GLFW_KEY_ESCAPE:
		case GLFW_KEY_X:
			glfwSetWindowShouldClose(window, true);
		break;

		case GLFW_KEY_SPACE:
		{
		}break;

		case GLFW_KEY_A:
		{
		}break;

		case GLFW_KEY_D:
		{
		}break;

		default:
		{
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// renderScene
/////////////////////////////////////////////////////////////////////////////////////
void render()
{
	// set OpenGL render flags
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(true);

	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	////////////////////////////////////////////////////////////////////////////////
	// Render mesh objects here..
	////////////////////////////////////////////////////////////////////////////////
	Scene.render();

	glBindVertexArray(0);       	
}

/////////////////////////////////////////////////////////////////////////////////////
// printDebugInfo() - print version info to console
/////////////////////////////////////////////////////////////////////////////////////
void printDebugInfo()
{
	// Print info of GPU and supported OpenGL version
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

#ifdef GL_SHADING_LANGUAGE_VERSION
	printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
#endif

	printf("Using GLEW version %s.\n", glewGetString(GLEW_VERSION));
	printf("------------------------------\n");
	printf("Press ESCAPE or 'X' or 'x' to exit.\n");
}

/////////////////////////////////////////////////////////////////////////////////////
// DebugOutput
// Used to output openGL debug info
// KHR_debug runs on all systems running openGL4.3 or later
/////////////////////////////////////////////////////////////////////////////////////
void DebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data)
{
	cout << "debug call: " << msg << endl;
}

/////////////////////////////////////////////////////////////////////////////////////
// main()
/////////////////////////////////////////////////////////////////////////////////////
int main() 
{
	// initialise glfw
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	GLFWwindow* window = glfwCreateWindow(initWidth, initHeight, "GraphicsTemplate", NULL, NULL);
	if (window == NULL)
	{
		fprintf(stdout, "Failed to create GLFW window!\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	
	// initialise glew
	glewInit();

	// print version info 
	printDebugInfo();

	glDebugMessageCallback(DebugOutput, NULL);

	// Set callback function for resizing the window
	glfwSetFramebufferSizeCallback(window, resize);

	// Set callback for keyboard events
	glfwSetKeyCallback(window, keyboard);

	resize(window, initWidth, initHeight);

	////////////////////////////////////////////////////
	// initialise scene - geometry and shaders etc
	////////////////////////////////////////////////////
	Scene.init();

	// This is the GAME LOOP...
	// keep playing the game until mum shouts 
	// you down for a cup of tea
	while (!glfwWindowShouldClose(window)) 
	{
		// Because we are in the game loop, 
		// all functions within this loop get 
		// called every frame. 
		// We can use this to animate mesh objects 
		// by changing the position on each iteration 
		// of the loop. 
		// You can do this in the render() function 
		render();

		// display the newly updated contents of the rendered image
		glfwSwapBuffers(window);	
		// check if any event has fired off...
		glfwPollEvents();			
	}

	// quit out of the program
	glfwTerminate();
	return 0;
}

