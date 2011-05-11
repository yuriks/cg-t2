#ifndef COMBOSHOOTER_ENGINE_BULLETLAYER_HPP
#define COMBOSHOOTER_ENGINE_BULLETLAYER_HPP

#include "Entity.hpp"
#include "../util2d/SpriteBatch.hpp"
#include "../util3d/gl/Texture.hpp"
#include "../util3d/Vector.hpp"

#include <memory>

namespace engine
{

struct Bullet
{
	math::vec2 position;
	math::vec2 speed;
	float angle; float accel;
	unsigned int life; unsigned int life_fade;
	unsigned char img_x, img_y;
	unsigned char img_w, img_h;

	// Allows for additive blending
	unsigned char alpha_mult;

private:
	util2d::Sprite* sprite;
	friend class BulletLayer;
};

class BulletLayer : public DrawableLayer
{
public:
	BulletLayer(GameManager& manager);

	virtual void update(GameManager& manager, LayeredScene& scene);
	virtual void draw(GameManager& manager, LayeredScene& scene);

	void setTexture(gl::Texture* tex);
	void setDepth(int depth);

	void addBullet(const Bullet& bullet);

private:
	util2d::SpriteBatch sprite_batch;

	std::vector<Bullet> bullets;
	unsigned int num_bullets;
};

} // namespace engine

#endif // COMBOSHOOTER_ENGINE_BULLETLAYER_HPP
