#include "SpriteLayer.hpp"

#include "../util2d/SpriteBatch.hpp"

#include <cassert>
#include <vector>
#include <boost/noncopyable.hpp>

namespace game
{

namespace detail
{

struct SpriteLayerHelper : boost::noncopyable
{
	SpriteLayerHelper(GraphicsManager& manager)
		: sprite_batch(manager), num_sprites(0)
	{
	}

	util2d::SpriteBatch sprite_batch;

	std::vector<std::pair<util2d::Sprite *const, bool>> sprites;
	unsigned int num_sprites;
};

} // namespace detail

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

SpriteHandle::SpriteHandle(util2d::Sprite* spr, const std::shared_ptr<detail::SpriteLayerHelper>& helper, unsigned int index)
	: sprite(spr), helper(helper), index(index)
{
}

SpriteLayer::SpriteLayer(GameManager& manager)
	: helper(std::make_shared<detail::SpriteLayerHelper>(manager.graphics_manager))
{

}

void SpriteLayer::update(GameManager&, LayeredScene&)
{
}

void SpriteLayer::draw(GameManager&, LayeredScene&)
{
	helper->sprite_batch.draw();
}

void SpriteLayer::setTexture(gl::Texture& tex)
{
	helper->sprite_batch.setTexture(&tex);
}

void SpriteLayer::setDepth(int depth_)
{
	depth = depth_;
}

SpriteHandle SpriteLayer::newSprite()
{
	util2d::Sprite* spr;
	unsigned int index;
	auto& sprites = helper->sprites;

	if (sprites.size() > helper->num_sprites)
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
		spr = helper->sprite_batch.newSprite();
		index = sprites.size();
		sprites.push_back(std::make_pair(spr, true));
		helper->num_sprites += 1;
	}

	return SpriteHandle(spr, helper, index);
}

} // namespace game
