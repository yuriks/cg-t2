#include "InputManager.hpp"

#include <GL/glfw.h>

namespace engine
{

namespace
{

bool close_requested;

int GLFWCALL close_callback()
{
	close_requested = true;
	return GL_FALSE;
}

} // namespace

InputManager::InputManager()
{
	actions.fill(false);
	actions_pressed.fill(false);

	glfwSetWindowCloseCallback(close_callback);
}

void InputManager::update()
{
	std::copy(actions.cbegin(), actions.cend(), actions_pressed.begin());
	actions.fill(false);

	int key = 0;

	for (auto i = assignments.cbegin(), end = assignments.cend(); i != end; ++i)
	{
		bool state;

		if (key != i->first)
			state = glfwGetKey(i->first) == GLFW_PRESS;

		actions[i->second] = actions[i->second] || state;
	}

	if (close_requested)
	{
		close_requested = false;
		actions[Action::QUIT] = true;
	}

	std::transform(actions.cbegin(), actions.cend(), actions_pressed.cbegin(), actions_pressed.begin(),
		[](bool a, bool old_a) { return a && !old_a; });
}

bool InputManager::getActionState(Action::type action) const
{
	return actions[action];
}

bool InputManager::getActionPressed(Action::type action) const
{
	return actions_pressed[action];
}

void InputManager::addKeyAssignment(std::pair<int, Action::type> assignment)
{
	assignments.insert(assignment);
}

void InputManager::removeKeyAssignment(std::pair<int, Action::type> assignment)
{
	assignments.erase(assignment);
}

} // namespace engine
