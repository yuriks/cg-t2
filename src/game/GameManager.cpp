#include "GameManager.hpp"

namespace game
{

GameManager::GameManager()
	: running(true), is_slow(false)
{
}

void GameManager::update()
{
	input_manager.update();

	activeScene().update(*this);
}

void GameManager::draw()
{
	activeScene().draw(*this);

	graphics_manager.swapBuffers();
}

GameScene& GameManager::activeScene()
{
	return *scene_stack.back().get();
}

void GameManager::pushScene(std::unique_ptr<GameScene> scene)
{
	scene_stack.push_back(std::move(scene));
}

bool GameManager::isSlow() const
{
	return is_slow;
}

void GameManager::stopGame()
{
	running = false;
}

} // namespace game
