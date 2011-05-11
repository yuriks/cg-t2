#ifndef COMBOSHOOTER_ENGINE_INPUTMANAGER_HPP
#define COMBOSHOOTER_ENGINE_INPUTMANAGER_HPP

#include <array>
#include <set>
#include <utility>

namespace engine
{

struct Action
{
	enum type
	{
		LEFT, RIGHT,
		ACCEL, BRAKE,
		FIRE, CHANGE_FIRE,
		MENU, QUIT,
		MAX
	};
};

class InputManager
{
public:
	InputManager();

	void update();
	bool getActionState(Action::type action) const;
	bool getActionPressed(Action::type action) const;

	void addKeyAssignment(std::pair<int, Action::type> assignment);
	void removeKeyAssignment(std::pair<int, Action::type> assignment);

private:
	std::array<bool, Action::MAX> actions;
	std::array<bool, Action::MAX> actions_pressed;
	std::set<std::pair<int, Action::type>> assignments;
};

} // namespace engine

#endif // COMBOSHOOTER_ENGINE_INPUTMANAGER_HPP
