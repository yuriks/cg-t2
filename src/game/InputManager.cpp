#include "InputManager.hpp"

#include <GL/glfw.h>

namespace game
{

InputManager::InputManager()
{
	actions.fill(false);
}

void InputManager::update()
{
	actions.fill(false);

	int key = 0;

	for (auto i = assignments.cbegin(), end = assignments.cend(); i != end; ++i)
	{
		bool state;

		if (key != i->first)
			state = glfwGetKey(i->first) == GLFW_PRESS;

		actions[i->second] = actions[i->second] || state;
	}
}

bool InputManager::getActionState(Action::type action) const
{
	return actions[action];
}

void InputManager::addKeyAssignment(std::pair<int, Action::type> assignment)
{
	assignments.insert(assignment);
}

void InputManager::removeKeyAssignment(std::pair<int, Action::type> assignment)
{
	assignments.erase(assignment);
}

} // namespace game
