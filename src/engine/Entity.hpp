#ifndef COMBOSHOOTER_ENGINE_ENTITY_HPP
#define COMBOSHOOTER_ENGINE_ENTITY_HPP

#include "GameManager.hpp"

#include <string>
#include <memory>

namespace engine
{

class LayeredScene;

// Anything that needs to be updated on each engine tick
class Entity : public std::enable_shared_from_this<Entity>
{
public:
	virtual ~Entity() {}

	virtual void update(GameManager& manager, LayeredScene& scene) = 0;

	bool changeName(LayeredScene& scene, const std::string& new_name);
	const std::string& getName() const;

private:
	std::string name;
};

// Drawable layers: backgrounds, thing layers, effects, GUIs, etc.
class DrawableLayer : public Entity
{
public:
	virtual void draw(GameManager& manager, LayeredScene& scene) = 0;

	inline bool operator < (const DrawableLayer& rhs) const { return depth < rhs.depth; }

protected:
	int depth;
};

// "Physical" entities participating in the gameplay.
class Thing : public Entity
{
};

class LayeredScene : public GameScene
{
public:
	virtual void update(GameManager& manager);
	virtual void draw(GameManager& manager);

	void addEntity(std::shared_ptr<Entity> entity);
	void removeEntity(std::shared_ptr<Entity>& entity);

	std::shared_ptr<Entity> lookupEntity(const std::string& name);
	bool renameEntity(const std::shared_ptr<Entity>& entity, const std::string& new_name);

private:
	
	std::set<std::shared_ptr<Entity>> entities;

	// These don't own anything and are just references to objects inside `entities`.
	std::map<std::string, Entity*> named_entities;
	std::set<DrawableLayer*, Deref<DrawableLayer>> layers;
	std::set<Thing*> things;
};

} // namespace engine

#endif // COMBOSHOOTER_ENGINE_ENTITY_HPP
