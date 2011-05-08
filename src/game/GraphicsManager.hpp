#ifndef COMBOSHOOTER_GAME_GRAPHICSMANAGER_HPP
#define COMBOSHOOTER_GAME_GRAPHICSMANAGER_HPP

#include "../util3d/Matrix.hpp"

#include <boost/noncopyable.hpp>

namespace game
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

} // namespace game

#endif // COMBOSHOOTER_GAME_GRAPHICSMANAGER_HPP
