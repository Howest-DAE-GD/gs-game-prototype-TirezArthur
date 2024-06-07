#pragma once
#include <vector>
#include "Vector2f.h"
#include <utils.h>
class LevelManager;

enum class Resource {
	none,
	plant
};

struct Ant {
	Rectf hitbox;
	Resource carrying;
	Vector2f goal;
};

class AntManager final
{
public:
	AntManager(const Rectf& screenboundary);

	void Update(float elapsedSec);
	void Draw();
	void PassLevelManager(LevelManager* levelmanager);
	void AddAnts(int amount, float x, float y);
private:
	const float TILEWIDTH{ 10 };
	const Rectf m_ScreenBoundary;
	const float SPEED{ 15.0f };
	int m_MaxAnts{0};
	LevelManager* m_LevelManagerPtr{};
	std::vector<Ant> m_AntVector;
};

