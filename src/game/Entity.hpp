#ifndef COMBOSHOOTER_GAME_ENTITY_HPP
#define COMBOSHOOTER_GAME_ENTITY_HPP

#include <string>

namespace game
{

class GameManager;

// Anything that needs to be updated on each engine tick
class Entity
{
public:
	virtual ~Entity();

	virtual void update(GameManager& manager) = 0;

	bool changeName(GameManager& manager, const std::string& new_name);
	const std::string& getName() const;

private:
	std::string name;
};

// Drawable layers: backgrounds, thing layers, effects, GUIs, etc.
class DrawableLayer : public Entity
{
public:
	virtual void draw(GameManager& manager) = 0;

	inline bool operator < (const DrawableLayer& rhs) const { return depth < rhs.depth; }

protected:
	int depth;
};

// "Physical" entities participating in the gameplay.
class Thing : public Entity
{
};

} // namespace game

#endif // COMBOSHOOTER_GAME_ENTITY_HPP
