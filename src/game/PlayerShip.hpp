#ifndef COMBOSHOOTER_GAME_PLAYERSHIP_HPP
#define COMBOSHOOTER_GAME_PLAYERSHIP_HPP

#include "../engine/Entity.hpp"
#include "../util3d/Vector.hpp"
#include "../engine/SpriteLayer.hpp"

namespace game
{

class PlayerShip : public engine::Entity
{
public:
	PlayerShip(engine::LayeredScene& scene);

	virtual void update(engine::GameManager& manager, engine::LayeredScene& scene);

	math::vec2 position;
	math::vec2 speed;
	float angle;

protected:
	engine::SpriteHandle sprite[4];
};

} // namespace game

#endif // COMBOSHOOTER_GAME_PLAYERSHIP_HPP
