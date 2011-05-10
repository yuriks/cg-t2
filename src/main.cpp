#include "game/GameManager.hpp"

#include "util3d/gl3w.hpp"
#include "util3d/Vector.hpp"
#include "util3d/MatrixTransform.hpp"
#include "game/Entity.hpp"
#include "game/SpriteLayer.hpp"
#include "image/ImageLoader.hpp"

#include <GL/glfw.h>
#include <iostream>
#include <memory>
#include <fstream>

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

	LayeredScene* scene = new LayeredScene();
	game_manager.pushScene(std::unique_ptr<GameScene>(scene));

	auto layer = std::make_shared<SpriteLayer>(game_manager);
	scene->addEntity(layer);
	layer->setDepth(0);

	gl::Texture tex;
	{
		image::Image img;
		{
			std::ifstream f("data/ship-no-outline.png", std::ios::in | std::ios::binary);
			image::Image::loadPNGFileRGBA8(img, f);
			image::preMultiplyAlpha(img);
		}

		glActiveTexture(GL_TEXTURE0);
		tex.bind(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		tex.width = img.getWidth();
		tex.height = img.getHeight();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getWidth(), img.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getData());
	}
	layer->setTexture(tex);

	SpriteHandle sprite = layer->newSprite();
	{
		util2d::Sprite& s = *sprite.spr();
		s.img_w = 3;
		s.img_h = 4;
		s.x = 120;
		s.y = 80;
	}

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
