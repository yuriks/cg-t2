#ifndef COMBOSHOOTER_GAME_INPUTMANAGER_HPP
#define COMBOSHOOTER_GAME_INPUTMANAGER_HPP

#include <array>
#include <set>
#include <utility>

namespace game
{

struct Action
{
	enum type
	{
		LEFT, RIGHT,
		ACCEL, BRAKE,
		FIRE,
		MAX
	};
};

class InputManager
{
public:
	InputManager();

	void update();
	bool getActionState(Action::type action) const;

	void addKeyAssignment(std::pair<int, Action::type> assignment);
	void removeKeyAssignment(std::pair<int, Action::type> assignment);

private:
	std::array<bool, Action::MAX> actions;
	std::set<std::pair<int, Action::type>> assignments;
};

} // namespace game

#endif // COMBOSHOOTER_GAME_INPUTMANAGER_HPP
