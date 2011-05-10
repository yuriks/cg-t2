#ifndef COMBOSHOOTER_ENGINE_SPRITELAYER_HPP
#define COMBOSHOOTER_ENGINE_SPRITELAYER_HPP

#include "Entity.hpp"
#include "../util2d/SpriteBatch.hpp"
#include "../util3d/gl/Texture.hpp"

#include <memory>

namespace engine
{

class SpriteLayer;

class SpriteHandle
{
public:
	SpriteHandle();
	SpriteHandle(SpriteHandle&& o);
	~SpriteHandle();

	SpriteHandle& operator=(SpriteHandle&& o);

	util2d::Sprite* spr() { return sprite; }
	void swap(SpriteHandle& o);

private:
	SpriteHandle(util2d::Sprite* spr, const std::shared_ptr<SpriteLayer>& layer, unsigned int index);

	// Disabled
	SpriteHandle(const SpriteHandle&);
	SpriteHandle& operator=(const SpriteHandle&);

	util2d::Sprite* sprite;
	std::shared_ptr<SpriteLayer> layer;
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

} // namespace engine

namespace std
{

template <>
inline void swap(engine::SpriteHandle& a, engine::SpriteHandle& b)
{
	a.swap(b);
}

} // namespace std

#endif // COMBOSHOOTER_ENGINE_SPRITELAYER_HPP
