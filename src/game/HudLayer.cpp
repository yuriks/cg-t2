#include "HudLayer.hpp"

#include "../engine/ResourceManager.hpp"

#include <algorithm>
#include <string>
#include <sstream>

namespace
{

unsigned short remap_char(char c) {
	return (unsigned short)(c - ' ');
}

} // namespace

namespace game
{

HudLayer::HudLayer(engine::GameManager& manager)
	: tilemap(manager.graphics_manager, 0, 0, 640, 480), texture(manager.resource_manager.loadTexture("data/font_8x8.png")),
	dirty(true), selected_shot(1)
{
	map.fill(0);

	{
		const std::string str = "SELECTED SHOT:";
		std::transform(str.cbegin(), str.cend(), map.begin() + 80+1, remap_char);
	}

	{
		std::vector<std::string> strs;
		strs.push_back("CONTROLS:");
		strs.push_back("ARROWS - THRUST, BREAK, STEER");
		strs.push_back("Z - SHOOT");
		strs.push_back("X - CHANGE SHOT TYPE");
		strs.push_back("ESC - QUIT");
		strs.push_back("\x7f YURI K. SCHLESNER 2011");

		int y = 60 - 1 - strs.size();
		for (auto i = strs.cbegin(), end = strs.cend(); i != end; ++i, ++y)
		{
			std::transform(i->cbegin(), i->cend(), map.begin() + 80*y+1, remap_char);
		}
	}

	tilemap.setTexture(texture.get());
	tilemap.setColor(17/255.f, 133/255.f, 209/255.f, .0f);
}

void HudLayer::update(engine::GameManager& manager, engine::LayeredScene&)
{
	using engine::Action;
	engine::InputManager& input = manager.input_manager;

	if (input.getActionPressed(Action::MENU) || input.getActionPressed(Action::QUIT))
		manager.stopGame();
}

void HudLayer::draw(engine::GameManager&, engine::LayeredScene&)
{
	if (dirty)
	{
		std::ostringstream ss;
		ss << selected_shot;
		const std::string& str = ss.str();

		std::transform(str.cbegin(), str.cend(), map.begin() + 80+1+15, remap_char);

		tilemap.setTilemap(&map[0], 640/8, 480/8);
	}
	tilemap.draw();
}

void HudLayer::setDepth(int depth_)
{
	depth = depth_;
}

void HudLayer::setSelectedShot(unsigned int num)
{
	selected_shot = num;
	dirty = true;
}

} // namespace game
