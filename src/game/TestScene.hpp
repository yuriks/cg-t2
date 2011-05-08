#ifndef COMBOSHOOTER_GAME_TESTSCENE_HPP
#define COMBOSHOOTER_GAME_TESTSCENE_HPP

#include "GameManager.hpp"
#include "../util2d/Tilemap.hpp"

#include <array>

namespace game
{

class TestScene : public GameScene
{
public:
	TestScene(GameManager& manager);

	virtual void update(GameManager& manager);
	virtual void draw(GameManager& manager);

private:
	util2d::Tilemap tilemap;
	gl::Texture texture;
	std::array<unsigned short, 80*60> map;
};

} // namespace game

#endif // COMBOSHOOTER_GAME_TESTSCENE_HPP
