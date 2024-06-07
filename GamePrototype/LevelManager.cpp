#include "pch.h"
#include "LevelManager.h"
#include "Utils.h"
#include <iostream>
#include "Antmanager.h"

LevelManager::LevelManager(AntManager* antmanager):
	m_AntManagerPtr{ antmanager }
{
	m_ResourceText = new Texture{ std::to_string(m_Resource), "REDENSEK.TTF", 24, Color4f{1.0f, 1.0f, 1.0f, 1.0f} };
	for (int indexROW{ GROUNDLEVEL }; indexROW < ROWS; ++indexROW)
	{
		for (int indexCOLUMN{}; indexCOLUMN < COLUMNS; ++indexCOLUMN)
		{
			m_TileArray[indexCOLUMN][indexROW] = Tile::sky;
		}
	}
	for (int index{}; index < PLANTAMOUNT; ++index)
	{
		m_TileArray[rand() % COLUMNS][GROUNDLEVEL] = Tile::plant;
	}
	m_TileArray[COLUMNS / 2][GROUNDLEVEL] = Tile::sky;
	m_TileArray[COLUMNS / 2 - 1][GROUNDLEVEL] = Tile::plant;
	m_TileArray[9][5] = Tile::tunnel;
}

LevelManager::~LevelManager()
{
	delete m_ResourceText;
}

void LevelManager::Draw()
{
	for (int indexROW{}; indexROW < ROWS; ++indexROW)
	{
		for (int indexCOLUMN{}; indexCOLUMN < COLUMNS; ++indexCOLUMN)
		{
			Tile currentTile{ m_TileArray[indexCOLUMN][indexROW] };
			switch (currentTile)
			{
			case Tile::dirt:
				break;
			case Tile::sky:
				utils::SetColor(Color4f{ 0.4f, 0.4f, 0.8f, 1.0f });
				utils::FillRect(Rectf{ (float)indexCOLUMN * TILEWIDTH, (float)indexROW * TILEWIDTH, TILEWIDTH, TILEWIDTH });
				break;
			case Tile::plant:
				utils::SetColor(Color4f{ 0.2f, 0.6f, 0.2f, 1.0f });
				utils::FillRect(Rectf{ (float)indexCOLUMN * TILEWIDTH, (float)indexROW * TILEWIDTH, TILEWIDTH, TILEWIDTH });
				break;
			case Tile::room:
				utils::SetColor(Color4f{ 0.2f, 0.15f, 0.15f, 1.0f });
				utils::FillRect(Rectf{ (float)indexCOLUMN * TILEWIDTH + 2.0f, (float)indexROW * TILEWIDTH + 2.0f, TILEWIDTH - 4.0f, TILEWIDTH - 4.0f });
			case Tile::tunnel:
				utils::SetColor(Color4f{ 0.2f, 0.15f, 0.15f, 1.0f });
				if (indexCOLUMN > 0 && (m_TileArray[indexCOLUMN - 1][indexROW] == Tile::tunnel || m_TileArray[indexCOLUMN - 1][indexROW] == Tile::room || m_TileArray[indexCOLUMN - 1][indexROW] == Tile::exit)) {
					utils::FillRect(Rectf{ (float)indexCOLUMN * TILEWIDTH, (float)indexROW * TILEWIDTH + 3.0f, TILEWIDTH * 0.5f, 4.0f });
				}
				if (indexCOLUMN < COLUMNS - 1 && (m_TileArray[indexCOLUMN + 1][indexROW] == Tile::tunnel || m_TileArray[indexCOLUMN + 1][indexROW] == Tile::room || m_TileArray[indexCOLUMN + 1][indexROW] == Tile::exit)) {
					utils::FillRect(Rectf{ (float)indexCOLUMN * TILEWIDTH + TILEWIDTH * 0.5f, (float)indexROW * TILEWIDTH + 3.0f, TILEWIDTH * 0.5f, 4.0f });
				}
				if (indexROW > 0 && (m_TileArray[indexCOLUMN][indexROW - 1] == Tile::tunnel || m_TileArray[indexCOLUMN][indexROW - 1] == Tile::room || m_TileArray[indexCOLUMN][indexROW - 1] == Tile::exit)) {
					utils::FillRect(Rectf{ (float)indexCOLUMN * TILEWIDTH + 3.0f, (float)indexROW * TILEWIDTH, 4.0f, TILEWIDTH * 0.5f });
				}
				if (indexROW < ROWS - 1 && (m_TileArray[indexCOLUMN][indexROW + 1] == Tile::tunnel || m_TileArray[indexCOLUMN][indexROW + 1] == Tile::room || m_TileArray[indexCOLUMN][indexROW + 1] == Tile::exit)) {
					utils::FillRect(Rectf{ (float)indexCOLUMN * TILEWIDTH + 3.0f, (float)indexROW * TILEWIDTH + TILEWIDTH * 0.5f, 4.0f, TILEWIDTH * 0.5f });
				}
				utils::FillRect(Rectf{ (float)indexCOLUMN * TILEWIDTH + 3.0f, (float)indexROW * TILEWIDTH + 3.0f, TILEWIDTH - 6.0f, TILEWIDTH - 6.0f });
				break;
			case Tile::exit:
				utils::SetColor(Color4f{ 0.4f, 0.4f, 0.8f, 1.0f });
				utils::FillRect(Rectf{ (float)indexCOLUMN * TILEWIDTH, (float)indexROW * TILEWIDTH, TILEWIDTH, TILEWIDTH });
				utils::SetColor(Color4f{ 0.2f, 0.15f, 0.15f, 1.0f });
				utils::FillRect(Rectf{ (float)indexCOLUMN * TILEWIDTH + 2.0f, (float)indexROW * TILEWIDTH, TILEWIDTH - 4.0f, 1.0f });
				utils::FillRect(Rectf{ (float)indexCOLUMN * TILEWIDTH + 3.0f, (float)indexROW * TILEWIDTH + 1.0f, TILEWIDTH - 6.0f, 1.0f });
				utils::FillRect(Rectf{ (float)indexCOLUMN * TILEWIDTH + 4.0f, (float)indexROW * TILEWIDTH + 1.0f, TILEWIDTH - 8.0f, 2.0f });
				break;
			default:
				break;
			}
		}
	}
	utils::SetColor(Color4f{ 1.0f, 1.0f, 1.0f, 0.3f });
	utils::DrawRect(Rectf{ m_SelectedTile.x, m_SelectedTile.y, TILEWIDTH, TILEWIDTH });
}

void LevelManager::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	int ROW{ GetRow((float)e.y, true) };
	int COLUMN{ GetColumn((float)e.x, true) };
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		if (m_TileArray[COLUMN][ROW] == Tile::dirt && m_Resource >= 5)
		{
			m_TileArray[COLUMN][ROW] = Tile::tunnel;
			SetResource(m_Resource - 5);
		}
		else if (m_TileArray[COLUMN][ROW] == Tile::tunnel && m_Resource >= 10)
		{
			m_TileArray[COLUMN][ROW] = Tile::room;
			SetResource(m_Resource - 10);
			m_AntManagerPtr->AddAnts(10, m_SelectedTile.x + TILEWIDTH / 2, m_SelectedTile.y + TILEWIDTH / 2);
		}
		else if (m_TileArray[COLUMN][ROW] == Tile::sky && (m_TileArray[COLUMN][ROW - 1] == Tile::tunnel || m_TileArray[COLUMN][ROW - 1] == Tile::room) && m_Resource >= 8)
		{
			m_TileArray[COLUMN][ROW] = Tile::exit;
			SetResource(m_Resource - 8);
		}
		break;
	case SDL_BUTTON_RIGHT:
		if (m_TileArray[COLUMN][ROW] == Tile::plant)
		{
			SetResource(m_Resource + 1);
		}
		break;
	default:
		break;
	} 
}

void LevelManager::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	int ROW{ GetRow((float)e.y, true) };
	int COLUMN{ GetColumn((float)e.x, true) };
	m_SelectedTile = Point2f{ COLUMN * TILEWIDTH, ROW * TILEWIDTH };
}

float LevelManager::GetMaxDistance(Point2f position, int direction)
{
	int Column{ GetColumn(position.x) };
	int Row{ GetRow(position.y) };
	if (m_TileArray[Column][Row] == Tile::sky) return 0.0f;
	Tile adjacentTile{ m_TileArray[Column][Row] };
	switch (direction)
	{
	case 0:
		if (Column < COLUMNS) adjacentTile = m_TileArray[Column + 1][Row];
		if (Column < COLUMNS - 1 && (adjacentTile == Tile::tunnel || adjacentTile == Tile::room || adjacentTile == Tile::exit || (adjacentTile == Tile::plant && m_TileArray[Column][Row] == Tile::exit))) return 10.0f;
		return (Column + 1) * TILEWIDTH - position.x - 3.0f;
		break;
	case 1:
		if (Column > 0) adjacentTile = m_TileArray[Column - 1][Row];
		if (Column > 0 && (adjacentTile == Tile::tunnel || adjacentTile == Tile::room || adjacentTile == Tile::exit || (adjacentTile == Tile::plant && m_TileArray[Column][Row] == Tile::exit))) return 10.0f;
		return position.x - Column * TILEWIDTH - 2.0f;
		break;
	case 2:
		if (Row < ROWS - 1) adjacentTile = m_TileArray[Column][Row + 1];
		if (Row < ROWS - 1 && (adjacentTile == Tile::tunnel || adjacentTile == Tile::room)) return 10.0f;
		else if (Row < ROWS - 1 && adjacentTile == Tile::exit) return (Row + 1) * TILEWIDTH - position.y + 2.0f;
		else if (m_TileArray[Column][Row] == Tile::exit || m_TileArray[Column][Row] == Tile::plant) return 0.0f;
		return (Row + 1) * TILEWIDTH - position.y - 3.0f;
		break;
	case 3:
		if (Row > 0) adjacentTile = m_TileArray[Column][Row - 1];
		if (Row > 0 && (adjacentTile == Tile::tunnel || adjacentTile == Tile::room)) return 10.0f;
		return position.y - Row * TILEWIDTH - 2.0f;
		break;
	default:
		return -1.0f;
		break;
	}
}

const Tile& LevelManager::GetTile(float x, float y, bool screenspace)
{
	return m_TileArray[GetColumn(x, screenspace)][GetRow(y, screenspace)];
}

void LevelManager::DrawUI()
{
	utils::SetColor(Color4f{ 0.2f, 0.6f, 0.2f, 1.0f });
	utils::FillRect(Rectf{ 5.0f, TILEWIDTH * ROWS * DISPLAYSCALE - 20.0f, 15.0f, 15.0f });
	m_ResourceText->Draw(Point2f{ 25.0f, TILEWIDTH * ROWS * DISPLAYSCALE - 23.0f });
}

int LevelManager::GetRow(float y, bool screenspace)
{
	if (screenspace) y = y / DISPLAYSCALE;
	return int(y / TILEWIDTH);
}

int LevelManager::GetColumn(float x, bool screenspace)
{
	if (screenspace) x = x / DISPLAYSCALE;
	return int(x / TILEWIDTH);
}

void LevelManager::SetResource(int resource)
{
	delete m_ResourceText;
	m_Resource = resource;
	m_ResourceText = new Texture{ std::to_string(m_Resource), "REDENSEK.TTF", 24, Color4f{1.0f, 1.0f, 1.0f, 1.0f} };
}

int LevelManager::GetResource()
{
	return m_Resource;
}
