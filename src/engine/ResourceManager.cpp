#include "ResourceManager.hpp"

#include <fstream>

namespace engine
{

std::shared_ptr<gl::Texture> ResourceManager::loadTexture(const std::string& fname)
{
	auto i = textures.find(fname);

	if (i != textures.end())
	{
		if (!i->second.expired())
			return i->second.lock();
		else
			textures.erase(i);
	}

	auto tex = std::make_shared<gl::Texture>();
	auto img = loadImage(fname, true);

	tex->bind(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	tex->width = img->getWidth();
	tex->height = img->getHeight();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->getData());

	textures.insert(std::make_pair(fname, std::weak_ptr<gl::Texture>(tex)));

	return tex;
}

std::shared_ptr<image::Image> ResourceManager::loadImage(const std::string& fname, bool pre_multiply)
{
	auto i = images.find(fname);

	if (i != images.end())
	{
		if (!i->second.expired())
			return i->second.lock();
		else
			images.erase(i);
	}

	auto img = std::make_shared<image::Image>();
	std::ifstream f(fname, std::ios::in | std::ios::binary);
	image::Image::loadPNGFileRGBA8(*img, f);

	if (pre_multiply)
		image::preMultiplyAlpha(*img);

	images.insert(std::make_pair(fname, std::weak_ptr<image::Image>(img)));

	return img;
}

} // namespace engine
