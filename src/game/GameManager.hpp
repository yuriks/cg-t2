#ifndef COMBOSHOOTER_GAME_GAMEMANAGER_HPP
#define COMBOSHOOTER_GAME_GAMEMANAGER_HPP

#include "Entity.hpp"

#include <vector>
#include <map>
#include <set>
#include <string>
#include <functional>
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

class GameManager : boost::noncopyable
{
public:
	~GameManager();

	void update();
	void draw();

	void addEntity(Entity* entity); // entity is now owned by GameManager
	void removeEntity(Entity* entity); // entity is not owned by GameManager anymore

	Entity* lookupEntity(const std::string& name);
	bool renameEntity(Entity* entity, const std::string& new_name);

	static void main_loop();

private:

	// This owns all entities inserted into it
	std::set<Entity*> entities;

	// These don't own anything and are just references to objects inside `entities`.
	std::map<std::string, Entity*> named_entities;
	std::set<DrawableLayer*, Deref<DrawableLayer>> layers;
	std::set<Thing*> things;
};

} // namespace game

#endif // COMBOSHOOTER_GAME_GAMEMANAGER_HPP
