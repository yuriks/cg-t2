#ifndef COMBOSHOOTER_ENGINE_GAMEMANAGER_HPP
#define COMBOSHOOTER_ENGINE_GAMEMANAGER_HPP

#include "InputManager.hpp"
#include "GraphicsManager.hpp"
#include "ResourceManager.hpp"
#include "../util3d/Matrix.hpp"

#include <vector>
#include <map>
#include <set>
#include <string>
#include <functional>
#include <memory>
#include <utility>
#include "boost/noncopyable.hpp"

template <typename T, typename F = std::less<T>>
struct Deref
{
	F func;

	bool operator () (const T* lhs, const T* rhs) const
	{
		const T& l = *lhs;
		const T& r = *rhs;
		return func(l, r);
	}
};

namespace engine
{

class GameManager;

class GameScene : boost::noncopyable
{
public:
	virtual ~GameScene() {};

	virtual void update(GameManager& manager) = 0;
	virtual void draw(GameManager& manager) = 0;
};

class GameManager : boost::noncopyable
{
public:
	static const unsigned int TICKS_PER_SEC = 60u;

	GameManager();

	void update();
	void draw();

	GameScene& activeScene();
	void pushScene(std::unique_ptr<GameScene> scene);

	bool isSlow() const;
	void stopGame();

	static void main_loop();

	// Order is important!
	ResourceManager resource_manager;
	GraphicsManager graphics_manager;
	InputManager input_manager;

private:
	std::vector<std::unique_ptr<GameScene>> scene_stack;

	bool running;
	bool is_slow;
};

} // namespace engine

#endif // COMBOSHOOTER_ENGINE_GAMEMANAGER_HPP
