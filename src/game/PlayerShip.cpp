#include "PlayerShip.hpp"

#include "HudLayer.hpp"

#include <array>
#include <cstdlib>

namespace
{

struct ShootType
{
	float speed;
	float spread;
	float accel;
	unsigned int life; unsigned int life_fade;
	unsigned char img_x, img_y;
	unsigned char img_w, img_h;
	unsigned char alpha_mult;
	unsigned int cooloff;
};

const std::array<ShootType, 3> shoot_types =
{{
	{4.f, 0.f, 0.f, 120, 10, 0, 1, 2, 1, 192, 8},
	{4.f, math::PI / 2, 0.05f, 100, 10, 0, 1, 2, 1, 192, 0},
	{1.f, 0.f, -0.25f, 120, 10, 3, 0, 1, 2, 192, 12}
}};

} // namespace

namespace game
{

PlayerShip::PlayerShip(engine::LayeredScene& scene)
	: position(math::make_vec(320.f, 240.f)), speed(math::make_vec(0.f, 0.f)), angle(math::PI/2.f), shoot_cooloff(0), current_shoot(0)
{
	{
		auto layer = scene.lookupEntity("gameplay_sprite_layer");
		auto& slayer = dynamic_cast<engine::SpriteLayer&>(*layer);

		for (unsigned int i = 0; i < 4; ++i)
		{
			sprite[i] = slayer.newSprite();
	
			{
				util2d::Sprite& s = *(sprite[i].spr());
				s.img_x = s.img_y = 0;
				s.img_w = 4;
				s.img_h = 3;
				s.x = (short)position[0];
				s.y = (short)position[1];
			}
		}
	}

	{
		auto layer = scene.lookupEntity("player_bullet_layer");
		bullet_layer = std::static_pointer_cast<engine::BulletLayer>(scene.lookupEntity("player_bullet_layer"));
	}
}

void PlayerShip::update(engine::GameManager& manager, engine::LayeredScene& scene)
{
	using engine::Action;
	engine::InputManager& input = manager.input_manager;

	const float speed_s = 1.f / (math::vec::length(speed)/6.f + 1.f);

	if (input.getActionState(Action::LEFT))
	{
		angle += math::PI/64.f * speed_s;
	}
	if (input.getActionState(Action::RIGHT))
	{
		angle -= math::PI/64.f * speed_s;
	}
	unsigned char anim_frame = 0;
	if (input.getActionState(Action::ACCEL))
	{
		const math::vec2 accel = math::make_vec(std::cos(angle), -std::sin(angle)) * 0.05f;
		speed += accel;
		anim_frame = 1;
	}
	else if (input.getActionState(Action::BRAKE))
	{
		speed *= 0.98;
		anim_frame = 2;
	}
	if (input.getActionPressed(Action::CHANGE_FIRE))
	{
		current_shoot += 1;
		if (current_shoot == shoot_types.size())
			current_shoot = 0;

		auto layer = scene.lookupEntity("hud_layer");
		auto& hlayer = dynamic_cast<HudLayer&>(*layer);

		hlayer.setSelectedShot(current_shoot + 1);
	}

	position += speed;

	if (position[0] < 0.f)
		position[0] += 640.f;
	if (position[0] >= 640.f)
		position[0] -= 640.f;
	if (position[1] < 0.f)
		position[1] += 480.f;
	if (position[1] >= 480.f)
		position[1] -= 480.f;

	const short wrap_table[4*2] = {
		0, 0,
		1, 0,
		0, 1,
		1, 1
	};

	for (unsigned int i = 0; i < 4; ++i)
	{
		util2d::Sprite& s = *(sprite[i].spr());

		short offx = wrap_table[i*2+0] * 640;
		short offy = wrap_table[i*2+1] * 480;
		if (position[0] > 320.f)
			offx = -offx;
		if (position[1] > 240.f)
			offy = -offy;

		s.x = (short)position[0] + offx - 16;
		s.y = (short)position[1] + offy - 12;

		const float cos = std::cos(angle);
		const float sin = std::sin(angle);

		s.transform(0, 0) = cos;
		s.transform(1, 0) = -sin;
		s.transform(0, 1) = sin;
		s.transform(1, 1) = cos;

		s.img_y = anim_frame * 3;
	}

	if (shoot_cooloff == 0 && input.getActionState(Action::FIRE))
	{
		const ShootType& s = shoot_types[current_shoot];

		engine::Bullet b;
		b.position = position;

		float shoot_angle = angle + (((float)std::rand() / RAND_MAX) - .5f) * s.spread;

		math::vec2 bspeed = math::make_vec(std::cos(shoot_angle), -std::sin(shoot_angle)) * s.speed;
		bspeed += speed;
		b.speed = bspeed;

		b.angle = shoot_angle;
		b.accel = s.accel;
		b.life = s.life;
		b.life_fade = s.life_fade;
		b.img_x = s.img_x;
		b.img_y = s.img_y;
		b.img_w = s.img_w;
		b.img_h = s.img_h;
		b.alpha_mult = s.alpha_mult;

		bullet_layer->addBullet(b);

		shoot_cooloff = s.cooloff;
	}

	if (shoot_cooloff > 0)
		--shoot_cooloff;
}

} // namespace game
