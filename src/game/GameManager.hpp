#ifndef COMBOSHOOTER_GAME_GAMEMANAGER_HPP
#define COMBOSHOOTER_GAME_GAMEMANAGER_HPP

#include "Entity.hpp"

#include "InputManager.hpp"
#include "GraphicsManager.hpp"
#include "../util3d/Matrix.hpp"

#include <vector>
#include <map>
#include <set>
#include <string>
#include <functional>
#include <memory>
#include <utility>
#include <boost/noncopyable.hpp>

template <typename T, typename F = std::less<T>>
struct Deref
{
	F func;

	bool operator () (const T* lhs, const T* rhs) const
	{
		const T& l = *lhs;
		const T& r = *rhs;
		return func(l, r);
	}
};

namespace game
{

class GameScene : boost::noncopyable
{
public:
	virtual ~GameScene();

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

class GameManager : boost::noncopyable
{
public:
	static const unsigned int TICKS_PER_SEC = 60u;

	GameManager();

	void update();
	void draw();

	GameScene& activeScene();
	void pushScene(std::unique_ptr<GameScene> scene);

	bool isSlow() const;
	void stopGame();

	static void main_loop();

	// Order is important!
	GraphicsManager graphics_manager;
	InputManager input_manager;

private:
	std::vector<std::unique_ptr<GameScene>> scene_stack;

	bool running;
	bool is_slow;
};

} // namespace game

#endif // COMBOSHOOTER_GAME_GAMEMANAGER_HPP
