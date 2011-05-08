#include "TestScene.hpp"

#include "../image/ImageLoader.hpp"
#include <fstream>

namespace game
{

TestScene::TestScene(GameManager& manager)
	: tilemap(manager.graphics_manager, 0, 0, GraphicsManager::SCREEN_WIDTH, GraphicsManager::SCREEN_HEIGHT)
{
	image::Image img;
	{
		std::ifstream f("data/font_8x8.png", std::ios::in | std::ios::binary);
		image::Image::loadPNGFileRGBA8(img, f);
	}
	image::preMultiplyAlpha(img);

	glActiveTexture(GL_TEXTURE0);
	texture.bind(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	texture.width = img.getWidth();
	texture.height = img.getHeight();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getWidth(), img.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getData());

	tilemap.setTexture(&texture);
	map.fill(0);
	tilemap.setTilemap(&map[0], 80, 60);
}

void TestScene::update(GameManager& manager)
{
	bool do_text = manager.input_manager.getActionPressed(Action::FIRE);

	if (do_text)
	{
		std::string str1("abbbbbbbbbbbbc");
		std::string str2("gHELLO WORLD!h");
		std::string str3("deeeeeeeeeeeef");
		unsigned int i = 2*80+2;

		std::transform(str1.cbegin(), str1.cend(), map.begin() + i+80*0, [](char c) { return (unsigned short)c - ' '; });
		std::transform(str2.cbegin(), str2.cend(), map.begin() + i+80*1, [](char c) { return (unsigned short)c - ' '; });
		std::transform(str3.cbegin(), str3.cend(), map.begin() + i+80*2, [](char c) { return (unsigned short)c - ' '; });
		tilemap.setTilemap(&map[0], 80, 60);
	}
}

void TestScene::draw(GameManager&)
{
	glClearColor(.2f, .2f, .2f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	tilemap.draw();
}

} // namespace game
