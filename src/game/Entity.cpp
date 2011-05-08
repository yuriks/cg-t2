#include "Entity.hpp"

#include "GameManager.hpp"

namespace game
{

bool Entity::changeName(GameManager& manager, const std::string& new_name)
{
	if (manager.renameEntity(this, new_name))
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
