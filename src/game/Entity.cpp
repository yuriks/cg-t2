#include "Entity.hpp"

#include "GameManager.hpp"

namespace game
{

bool Entity::changeName(GameScene& scene, const std::string& new_name)
{
	if (scene.renameEntity(this, new_name))
	{
		name = new_name;
		return true;
	}
	else
		return false;
}

const std::string& Entity::getName() const
{
	return name;
}

} // namespace game
