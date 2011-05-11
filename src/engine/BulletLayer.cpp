#include "BulletLayer.hpp"

#include <iostream>
#include <algorithm>

namespace engine
{

BulletLayer::BulletLayer(GameManager& manager)
	: sprite_batch(manager.graphics_manager), num_bullets(0)
{
}

void BulletLayer::update(GameManager&, LayeredScene&)
{
	for (auto i = bullets.begin(), end = bullets.end(); i != end; ++i)
	{
		if (i->life == 0)
			continue;

		i->position += i->speed;
		float l = math::vec::length(i->speed);
		i->speed *= l / (l + i->accel);
		i->life -= 1;
	}
}

void BulletLayer::draw(GameManager&, LayeredScene&)
{
	for (auto i = bullets.cbegin(), end = bullets.cend(); i != end; ++i)
	{
		util2d::Sprite& s = *i->sprite;
		if (i->life == 0)
		{
			s.img_w = s.img_h = 0;
			continue;
		}
		
		s.x = (short)i->position[0] - i->img_w;
		s.y = (short)i->position[1] - i->img_h;

		s.r = s.g = s.b = 255;
		s.a = 255 * i->alpha_mult / 255;
		if (i->life < i->life_fade)
		{
			unsigned int a = (i->life * 255 / i->life_fade);
			s.r = s.g = s.b = (unsigned char)a;
			s.a = (unsigned char)(a * i->alpha_mult / 255);
		}
	}

	sprite_batch.draw();
}

void BulletLayer::setTexture(gl::Texture* tex)
{
	sprite_batch.setTexture(tex);
}

void BulletLayer::setDepth(int depth_)
{
	depth = depth_;
}

void BulletLayer::addBullet(const Bullet& bullet)
{
	auto i = std::find_if(bullets.begin(), bullets.end(), [](const Bullet& b) { return b.life == 0; });

	if (i == bullets.end())
	{
		bullets.push_back(bullet);
		i = bullets.end() - 1;
		i->sprite = sprite_batch.newSprite();
	}
	else
	{
		util2d::Sprite* spr = i->sprite;
		*i = bullet;
		i->sprite = spr;
	}

	util2d::Sprite& s = *i->sprite;

	s.img_x = i->img_x;
	s.img_y = i->img_y;
	s.img_w = i->img_w;
	s.img_h = i->img_h;

	i->img_w = i->img_w * 8 / 2;
	i->img_h = i->img_h * 8 / 2;

	const float cos = std::cos(i->angle);
	const float sin = std::sin(i->angle);

	s.transform(0, 0) = cos;
	s.transform(1, 0) = -sin;
	s.transform(0, 1) = sin;
	s.transform(1, 1) = cos;
}

} // namespace engine
