#include "engine/GameManager.hpp"

#include "util3d/gl3w.hpp"
#include "util3d/Vector.hpp"
#include "util3d/MatrixTransform.hpp"
#include "engine/Entity.hpp"
#include "engine/SpriteLayer.hpp"
#include "image/ImageLoader.hpp"
#include "game/PlayerShip.hpp"

#include <GL/glfw.h>
#include <iostream>
#include <memory>
#include <fstream>

int main()
{
	engine::GameManager::main_loop();
}

namespace engine
{

void GameManager::main_loop()
{
	GameManager game_manager;
	game_manager.input_manager.addKeyAssignment(std::make_pair(GLFW_KEY_LEFT, Action::LEFT));
	game_manager.input_manager.addKeyAssignment(std::make_pair(GLFW_KEY_RIGHT, Action::RIGHT));
	game_manager.input_manager.addKeyAssignment(std::make_pair(GLFW_KEY_UP, Action::ACCEL));
	game_manager.input_manager.addKeyAssignment(std::make_pair('Z', Action::FIRE));

	LayeredScene* scene = new LayeredScene();
	game_manager.pushScene(std::unique_ptr<GameScene>(scene));

	auto layer = std::make_shared<SpriteLayer>(game_manager);
	layer->changeName(*scene, "gameplay_sprite_layer");
	layer->setDepth(0);
	scene->addEntity(layer);

	std::shared_ptr<gl::Texture> tex = game_manager.resource_manager.loadTexture("data/ship-no-outline.png");
	layer->setTexture(tex.get());

	scene->addEntity(std::make_shared<game::PlayerShip>(*scene));

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

} // namespace engine
