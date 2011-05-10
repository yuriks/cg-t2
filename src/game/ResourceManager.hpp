#ifndef COMBOSHOOTER_GAME_RESOURCEMANAGER_HPP
#define COMBOSHOOTER_GAME_RESOURCEMANAGER_HPP

#include "../util3d/gl/Texture.hpp"
#include "../image/ImageLoader.hpp"

#include <memory>
#include <string>
#include <map>

namespace game
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

} // namespace game

#endif // COMBOSHOOTER_GAME_RESOURCEMANAGER_HPP
