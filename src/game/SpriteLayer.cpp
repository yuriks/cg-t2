#include "SpriteLayer.hpp"

#include "../util2d/SpriteBatch.hpp"

#include <cassert>
#include <vector>
#include <boost/noncopyable.hpp>

namespace game
{

SpriteHandle::SpriteHandle(SpriteHandle&& o)
	: sprite(std::move(o.sprite)), helper(std::move(o.helper)), index(o.index)
{
}

SpriteHandle::~SpriteHandle()
{
	if (sprite)
	{
		sprite->img_w = sprite->img_h = 0;
		helper->sprites[index].second = false;
		helper->num_sprites -= 1;
	}
}

SpriteHandle::SpriteHandle(util2d::Sprite* spr, const std::shared_ptr<SpriteLayer>& helper, unsigned int index)
	: sprite(spr), helper(helper), index(index)
{
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

void SpriteLayer::setTexture(gl::Texture& tex)
{
	sprite_batch.setTexture(&tex);
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
			[](const std::pair<util2d::Sprite *const, bool>& spr) { return spr.second == false; });

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

} // namespace game
