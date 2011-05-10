#include "PlayerShip.hpp"

namespace game
{

PlayerShip::PlayerShip(engine::LayeredScene& scene)
	: position(math::make_vec(320.f, 240.f)), speed(math::make_vec(0.f, 0.f)), angle(math::PI/2.f)
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

void PlayerShip::update(engine::GameManager& manager, engine::LayeredScene& /*scene*/)
{
	using engine::Action;
	engine::InputManager& input = manager.input_manager;

	if (input.getActionState(Action::LEFT))
	{
		angle += math::PI/64.f;
	}
	if (input.getActionState(Action::RIGHT))
	{
		angle -= math::PI/64.f;
	}
	bool accel_anim = false;
	if (input.getActionState(Action::ACCEL))
	{
		const math::vec2 accel = math::make_vec(std::cos(angle), -std::sin(angle)) * 0.1f;
		speed += accel;
		accel_anim = true;
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

		if (accel_anim)
			s.img_y = 3;
		else
			s.img_y = 0;
	}
}

} // namespace game
