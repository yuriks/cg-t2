#include "SpriteLayer.hpp"

#include "../util2d/SpriteBatch.hpp"

#include <cassert>
#include <vector>
#include <algorithm>
#include "boost/noncopyable.hpp"

namespace engine
{

SpriteHandle::SpriteHandle()
	: sprite(0), layer(0), index(0)
{
}

SpriteHandle::SpriteHandle(SpriteHandle&& o)
	: sprite(0), layer(0), index(0)
{
	swap(o);
}

SpriteHandle::~SpriteHandle()
{
	if (sprite)
	{
		sprite->img_w = sprite->img_h = 0;
		layer->sprites[index].second = false;
		layer->num_sprites -= 1;
	}
}

SpriteHandle& SpriteHandle::operator=(SpriteHandle&& o)
{
	swap(o);
	return *this;
}

SpriteHandle::SpriteHandle(util2d::Sprite* spr, const std::shared_ptr<SpriteLayer>& layer, unsigned int index)
	: sprite(spr), layer(layer), index(index)
{
}

void SpriteHandle::swap(SpriteHandle& o)
{
	std::swap(sprite, o.sprite);
	std::swap(layer, o.layer);
	std::swap(index, o.index);
}

SpriteLayer::SpriteLayer(GameManager& manager)
	: sprite_batch(manager.graphics_manager)
{

}

void SpriteLayer::update(GameManager&, LayeredScene&)
{
}

void SpriteLayer::draw(GameManager&, LayeredScene&)
{
	sprite_batch.draw();
}

void SpriteLayer::setTexture(gl::Texture* tex)
{
	sprite_batch.setTexture(tex);
}

void SpriteLayer::setDepth(int depth_)
{
	depth = depth_;
}

SpriteHandle SpriteLayer::newSprite()
{
	util2d::Sprite* spr;
	unsigned int index;

	if (sprites.size() > num_sprites)
	{
		auto it = std::find_if(sprites.begin(), sprites.end(),
			[](const std::pair<util2d::Sprite*, bool>& spr) { return spr.second == false; });

		assert(it != sprites.end());

		it->second = true;
		spr = it->first;
		index = sprites.begin() - it;
	}
	else
	{
		spr = sprite_batch.newSprite();
		index = sprites.size();
		sprites.push_back(std::make_pair(spr, true));
		num_sprites += 1;
	}

	return SpriteHandle(spr, std::static_pointer_cast<SpriteLayer>(shared_from_this()), index);
}

} // namespace engine
