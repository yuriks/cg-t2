#include "Entity.hpp"

#include "GameManager.hpp"

namespace game
{

bool Entity::changeName(LayeredScene& scene, const std::string& new_name)
{
	if (scene.renameEntity(shared_from_this(), new_name))
	{
		name = new_name;
		return true;
	}
	else
		return false;
}

const std::string& Entity::getName() const
{
	return name;
}

void LayeredScene::update(GameManager& manager)
{
	for (auto i = entities.begin(), end = entities.end(); i != end; ++i)
	{
		(*i)->update(manager, *this);
	}
}

void LayeredScene::draw(GameManager& manager)
{
	for (auto i = layers.begin(), end = layers.end(); i != end; ++i)
	{
		(*i)->draw(manager, *this);
	}
}

void LayeredScene::addEntity(std::shared_ptr<Entity> entity)
{
	if (!entities.insert(entity).second)
		return;

	if (!entity->getName().empty())
		named_entities.insert(make_pair(entity->getName(), entity.get()));

	if (DrawableLayer* layer = dynamic_cast<DrawableLayer*>(entity.get()))
	{
		layers.insert(layer);
	}

	if (Thing* thing = dynamic_cast<Thing*>(entity.get()))
	{
		things.insert(thing);
	}
}

void LayeredScene::removeEntity(std::shared_ptr<Entity>& entity)
{
	if (!entities.erase(entity))
		return;

	if (!entity->getName().empty())
		named_entities.erase(entity->getName());

	if (DrawableLayer* layer = dynamic_cast<DrawableLayer*>(entity.get()))
	{
		layers.erase(layer);
	}

	if (Thing* thing = dynamic_cast<Thing*>(entity.get()))
	{
		things.erase(thing);
	}
}

std::shared_ptr<Entity> LayeredScene::lookupEntity(const std::string& name)
{
	auto i = named_entities.find(name);

	if (i == named_entities.end())
		return nullptr;
	else
		return i->second->shared_from_this();
}

bool LayeredScene::renameEntity(const std::shared_ptr<Entity>& entity, const std::string& new_name)
{
	auto lb = named_entities.lower_bound(new_name);

	if (lb != named_entities.end() && !(named_entities.key_comp()(new_name, lb->first)))
	{
		return false;
	}
	else
	{
		named_entities.erase(entity->getName());
		if (!new_name.empty())
			named_entities.insert(lb, make_pair(new_name, entity.get()));
		return true;
	}
}

} // namespace game
