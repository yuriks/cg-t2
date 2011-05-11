#ifndef COMBOSHOOTER_GAME_HUDLAYER_HPP
#define COMBOSHOOTER_GAME_HUDLAYER_HPP

#include "../engine/Entity.hpp"
#include "../util2d/Tilemap.hpp"
#include "../engine/GameManager.hpp"
#include "../util3d/gl/Texture.hpp"

#include <array>
#include <memory>

namespace game
{

class HudLayer : public engine::DrawableLayer
{
public:
	HudLayer(engine::GameManager& manager);

	virtual void update(engine::GameManager& manager, engine::LayeredScene& scene);
	virtual void draw(engine::GameManager& manager, engine::LayeredScene& scene);

	void setDepth(int depth);

	void setSelectedShot(unsigned int num);

private:
	util2d::Tilemap tilemap;
	std::shared_ptr<gl::Texture> texture;

	std::array<unsigned short, (640/8)*(480/8)> map;

	bool dirty;
	unsigned int selected_shot;
};

} // namespace game

#endif // COMBOSHOOTER_GAME_HUDLAYER_HPP
