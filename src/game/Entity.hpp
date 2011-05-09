#ifndef COMBOSHOOTER_GAME_ENTITY_HPP
#define COMBOSHOOTER_GAME_ENTITY_HPP

#include "GameManager.hpp"

#include <string>

namespace game
{

class LayeredScene;

// Anything that needs to be updated on each engine tick
class Entity
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
	virtual ~LayeredScene();

	virtual void update(GameManager& manager);
	virtual void draw(GameManager& manager);

	void addEntity(Entity* entity); // entity is now owned by GameManager
	void removeEntity(Entity* entity); // entity is not owned by GameManager anymore

	Entity* lookupEntity(const std::string& name);
	bool renameEntity(Entity* entity, const std::string& new_name);

private:
	
	// This owns all entities inserted into it
	std::set<Entity*> entities;

	// These don't own anything and are just references to objects inside `entities`.
	std::map<std::string, Entity*> named_entities;
	std::set<DrawableLayer*, Deref<DrawableLayer>> layers;
	std::set<Thing*> things;
};

} // namespace game

#endif // COMBOSHOOTER_GAME_ENTITY_HPP
