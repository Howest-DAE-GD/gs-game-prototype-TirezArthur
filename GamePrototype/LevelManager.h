#pragma once
#include "Texture.h"
class AntManager;

enum class Tile {
	dirt,
	sky,
	plant,
	tunnel,
	room,
	exit
};

class LevelManager final
{
public:
	LevelManager(AntManager* antmanager);
	~LevelManager();

	void Draw();
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	float GetMaxDistance(Point2f position, int direction);
	const Tile& GetTile(float x, float y, bool screenspace = false);
	void DrawUI();
	void SetResource(int resource);
	int GetResource();
private:
	int GetRow(float y, bool screenspace = false);
	int GetColumn(float x, bool screenspace = false);
	const float DISPLAYSCALE{ 5.0f };
	const int ROWS{ 10 };
	const int COLUMNS{ 18 };
	const int GROUNDLEVEL{ 7 };
	const int PLANTAMOUNT{ 4 };
	const float TILEWIDTH{ 10 };

	AntManager* m_AntManagerPtr{};
	Point2f m_SelectedTile{ -TILEWIDTH, -TILEWIDTH };
	Tile m_TileArray[18][10]{ Tile::dirt };
	int m_Resource{ 23 };
	Texture* m_ResourceText;
};

