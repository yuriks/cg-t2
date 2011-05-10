#ifndef COMBOSHOOTER_ENGINE_RESOURCEMANAGER_HPP
#define COMBOSHOOTER_ENGINE_RESOURCEMANAGER_HPP

#include "../util3d/gl/Texture.hpp"
#include "../image/ImageLoader.hpp"

#include <memory>
#include <string>
#include <map>

namespace engine
{

class ResourceManager
{
public:
	std::shared_ptr<gl::Texture> loadTexture(const std::string& fname);
	std::shared_ptr<image::Image> loadImage(const std::string& fname, bool pre_multiply);

private:
	std::map<std::string, std::weak_ptr<gl::Texture>> textures;
	std::map<std::string, std::weak_ptr<image::Image>> images;
};

} // namespace engine

#endif // COMBOSHOOTER_ENGINE_RESOURCEMANAGER_HPP
