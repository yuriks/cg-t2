#ifndef COMBOSHOOTER_ENGINE_GRAPHICSMANAGER_HPP
#define COMBOSHOOTER_ENGINE_GRAPHICSMANAGER_HPP

#include "../util3d/Matrix.hpp"

#include <boost/noncopyable.hpp>

namespace engine
{

class GraphicsManager : boost::noncopyable
{
public:
	static const unsigned int SCREEN_WIDTH = 640u;
	static const unsigned int SCREEN_HEIGHT = 480u;

	GraphicsManager();
	~GraphicsManager();

	void swapBuffers();

	math::mat4 projection_matrix;
};

} // namespace engine

#endif // COMBOSHOOTER_ENGINE_GRAPHICSMANAGER_HPP
