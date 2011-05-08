#include "GameManager.hpp"

namespace game
{

GameManager::~GameManager()
{
	for (auto i = entities.begin(), end = entities.end(); i != end; ++i)
		delete *i;
}

void GameManager::update()
{
	for (auto i = entities.begin(), end = entities.end(); i != end; ++i)
	{
		(*i)->update(*this);
	}
}

void GameManager::draw()
{
	for (auto i = layers.begin(), end = layers.end(); i != end; ++i)
	{
		(*i)->draw(*this);
	}
}

void GameManager::addEntity(Entity* entity)
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

void GameManager::removeEntity(Entity* entity)
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

Entity* GameManager::lookupEntity(const std::string& name)
{
	auto i = named_entities.find(name);

	if (i == named_entities.end())
		return nullptr;
	else
		return i->second;
}

bool GameManager::renameEntity(Entity* entity, const std::string& new_name)
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

void GameManager::main_loop()
{
	// TODO
}

} // namespace game
