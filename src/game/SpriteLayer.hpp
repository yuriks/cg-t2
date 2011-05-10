#ifndef COMBOSHOOTER_GAME_SPRITELAYER_HPP
#define COMBOSHOOTER_GAME_SPRITELAYER_HPP

#include "Entity.hpp"
#include "../util2d/SpriteBatch.hpp"
#include "../util3d/gl/Texture.hpp"

#include <memory>

namespace game
{

class SpriteLayer;

class SpriteHandle
{
public:
	SpriteHandle(SpriteHandle&& o);
	~SpriteHandle();

	util2d::Sprite* spr() { return sprite; }

private:
	SpriteHandle(util2d::Sprite* spr, const std::shared_ptr<SpriteLayer>& helper, unsigned int index);

	// Disabled
	SpriteHandle(const SpriteHandle&);
	SpriteHandle& operator=(const SpriteHandle&);

	util2d::Sprite* sprite;
	std::shared_ptr<SpriteLayer> helper;
	unsigned int index;

	friend class SpriteLayer;
};

class SpriteLayer : public DrawableLayer
{
public:
	SpriteLayer(GameManager& manager);

	virtual void update(GameManager& manager, LayeredScene& scene);
	virtual void draw(GameManager& manager, LayeredScene& scene);

	void setTexture(gl::Texture* tex);
	void setDepth(int depth);

	SpriteHandle newSprite();

private:
	util2d::SpriteBatch sprite_batch;

	std::vector<std::pair<util2d::Sprite *const, bool>> sprites;
	unsigned int num_sprites;

	friend class SpriteHandle;
};

} // namespace game

#endif // COMBOSHOOTER_GAME_SPRITELAYER_HPP
