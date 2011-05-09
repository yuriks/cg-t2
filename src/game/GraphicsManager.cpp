#include "GraphicsManager.hpp"

#include "GameManager.hpp"
#include "../util3d/gl3w.hpp"
#include "../util3d/Vector.hpp"
#include "../util3d/MatrixTransform.hpp"

#include <GL/glfw.h>
#include <stdexcept>
#include <iostream>
#include <cassert>

namespace game
{

namespace
{

void APIENTRY debug_callback(GLenum /*source*/, GLenum /*type*/, GLuint /*id*/, GLenum /*severity*/, GLsizei /*length*/, const GLchar* message, GLvoid* /*userParam*/)
{
	std::cerr << message << std::endl;
	assert(false);
}

} // namespace

GraphicsManager::GraphicsManager()
{
	if (glfwInit() != GL_TRUE) {
		throw std::runtime_error("Failed to initialize GLFW.");
	}

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwOpenWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (glfwOpenWindow(SCREEN_WIDTH, SCREEN_HEIGHT, 8, 8, 8, 8, 24, 8, GLFW_WINDOW) != GL_TRUE) {
		throw std::runtime_error("Failed to open window.");
	}

	if (gl3wInit() != 0) {
		throw std::runtime_error("Failed to initialize gl3w.");
	} else if (!gl3wIsSupported(3, 3)) {
		throw std::runtime_error("OpenGL 3.3 not supported.");
	}

	if (glDebugMessageCallbackARB) {
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE);
		glDebugMessageCallbackARB(debug_callback, 0);
	}

	{
		math::vec3 s = {{2.f/SCREEN_WIDTH, -2.f/SCREEN_HEIGHT, 1.f}};
		math::vec3 t = {{-1.f, 1.f, 0.f}};
		projection_matrix = math::mat_transform::translate(t) * math::mat_transform::scale(s);
	}

	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

GraphicsManager::~GraphicsManager()
{
	glfwTerminate();
}

void GraphicsManager::swapBuffers()
{
	glfwSwapBuffers();
}

} // namespace game
