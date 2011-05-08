#include "GameManager.hpp"

namespace game
{

GameManager::GameManager()
	: running(true), is_slow(false)
{
}

GameScene::~GameScene()
{
	for (auto i = entities.begin(), end = entities.end(); i != end; ++i)
		delete *i;
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

void GameScene::update(GameManager& manager)
{
	for (auto i = entities.begin(), end = entities.end(); i != end; ++i)
	{
		(*i)->update(manager, *this);
	}
}

void GameScene::draw(GameManager& manager)
{
	for (auto i = layers.begin(), end = layers.end(); i != end; ++i)
	{
		(*i)->draw(manager, *this);
	}
}

void GameScene::addEntity(Entity* entity)
{
	if (!entities.insert(entity).second)
		return;

	if (!entity->getName().empty())
		named_entities.insert(make_pair(entity->getName(), entity));

	if (DrawableLayer* layer = dynamic_cast<DrawableLayer*>(entity))
	{
		layers.insert(layer);
	}

	if (Thing* thing = dynamic_cast<Thing*>(entity))
	{
		things.insert(thing);
	}
}

void GameScene::removeEntity(Entity* entity)
{
	if (!entities.erase(entity))
		return;

	if (!entity->getName().empty())
		named_entities.erase(entity->getName());

	if (DrawableLayer* layer = dynamic_cast<DrawableLayer*>(entity))
	{
		layers.erase(layer);
	}

	if (Thing* thing = dynamic_cast<Thing*>(entity))
	{
		things.erase(thing);
	}
}

Entity* GameScene::lookupEntity(const std::string& name)
{
	auto i = named_entities.find(name);

	if (i == named_entities.end())
		return nullptr;
	else
		return i->second;
}

bool GameScene::renameEntity(Entity* entity, const std::string& new_name)
{
	auto lb = named_entities.lower_bound(new_name);

	if (lb != named_entities.end() && !(named_entities.key_comp()(new_name, lb->first)))
	{
		return false;
	}
	else
	{
		named_entities.erase(entity->getName());
		named_entities.insert(lb, make_pair(new_name, entity));
		return true;
	}
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
