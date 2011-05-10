#ifndef COMBOSHOOTER_ENGINE_TESTSCENE_HPP
#define COMBOSHOOTER_ENGINE_TESTSCENE_HPP

#include "GameManager.hpp"
#include "../util2d/Tilemap.hpp"

#include <array>

namespace engine
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

} // namespace engine

#endif // COMBOSHOOTER_ENGINE_TESTSCENE_HPP
