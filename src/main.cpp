#include "game/GameManager.hpp"

#include "util3d/gl3w.hpp"
#include "util3d/Vector.hpp"
#include "util3d/MatrixTransform.hpp"
#include "game/TestScene.hpp"

#include <GL/glfw.h>
#include <iostream>
#include <memory>

int main()
{
	game::GameManager::main_loop();
}

namespace game
{

void GameManager::main_loop()
{
	GameManager game_manager;
	game_manager.input_manager.addKeyAssignment(std::make_pair('Z', Action::FIRE));
	game_manager.pushScene(std::unique_ptr<GameScene>(new TestScene(game_manager)));

	double elapsed_game_time = 0.;
	double elapsed_real_time = 0.;
	double last_frame_time;

	while (game_manager.running)
	{
		double frame_start = glfwGetTime();

		int i;
		for (i = 0; elapsed_game_time < elapsed_real_time && i < 5; ++i)
		{
			game_manager.update();
			elapsed_game_time += 1./TICKS_PER_SEC;
		}

		game_manager.draw();

		double tmp = elapsed_real_time + (glfwGetTime() - frame_start);
		if (elapsed_game_time > tmp)
			glfwSleep(elapsed_game_time - tmp);

		last_frame_time = glfwGetTime() - frame_start;
		elapsed_real_time += last_frame_time;
		if (i == 5)
			elapsed_game_time = elapsed_real_time;
	}
}

} // namespace game
