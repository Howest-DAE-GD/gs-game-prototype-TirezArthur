#include "pch.h"
#include "AntManager.h"
#include "Utils.h"
#include <iostream>
#include "LevelManager.h"

AntManager::AntManager(const Rectf& screenboundary) : 
	m_ScreenBoundary{ screenboundary }
{
	for (int index{}; index < m_MaxAnts; ++index)
	{
		m_AntVector.emplace_back(Ant{ Rectf{m_ScreenBoundary.width / 10 + 5.0f, m_ScreenBoundary.height / 10 + 5.0f, 1.0f, 2.0f}, Resource::none, Vector2f{m_ScreenBoundary.width / 10 + 5.0f, m_ScreenBoundary.height / 10 + 5.0f} });
	}
}

void AntManager::Update(float elapsedSec)
{
	for (Ant& ant : m_AntVector)
	{
		if (ant.goal.Equals(Vector2f{ ant.hitbox.left, ant.hitbox.bottom }))
		{
			int direction{ rand() % 4 };
			switch (direction)
			{
			case 0:
				ant.hitbox.height = 1.0f;
				ant.hitbox.width = 2.0f;
				ant.goal.x += (std::min(float(rand() % 11), m_LevelManagerPtr->GetMaxDistance(Point2f{ ant.hitbox.left, ant.hitbox.bottom }, direction)));
				ant.goal.y = ant.hitbox.bottom;
				break;
			case 1:
				ant.hitbox.height = 1.0f;
				ant.hitbox.width = 2.0f;
				ant.goal.x -= (std::min(float(rand() % 11), m_LevelManagerPtr->GetMaxDistance(Point2f{ ant.hitbox.left, ant.hitbox.bottom }, direction)));
				ant.goal.y = ant.hitbox.bottom;
				break;
			case 2:
				ant.hitbox.height = 2.0f;
				ant.hitbox.width = 1.0f;
				ant.goal.x = ant.hitbox.left;
				ant.goal.y += (std::min(float(rand() % 11), m_LevelManagerPtr->GetMaxDistance(Point2f{ ant.hitbox.left, ant.hitbox.bottom }, direction)));
				break;
			case 3:
				ant.hitbox.height = 2.0f;
				ant.hitbox.width = 1.0f;
				ant.goal.x = ant.hitbox.left;
				ant.goal.y -= (std::min(float(rand() % 11), m_LevelManagerPtr->GetMaxDistance(Point2f{ ant.hitbox.left, ant.hitbox.bottom }, direction)));
				break;
			}
		}
		else
		{
			Vector2f position{ ant.hitbox.left, ant.hitbox.bottom };
			Vector2f goalVector{ ant.goal };
			goalVector -= position;
			if (goalVector.Length() < elapsedSec * SPEED)
			{
				ant.hitbox.left = ant.goal.x;
				ant.hitbox.bottom = ant.goal.y;
			}
			else if (abs(goalVector.x) > abs(goalVector.y))
			{
				if (goalVector.x < 0.0f)ant.hitbox.left -= SPEED * elapsedSec;
				else ant.hitbox.left += SPEED * elapsedSec;
			}
			else
			{
				if (goalVector.y < 0.0f)ant.hitbox.bottom -= SPEED * elapsedSec;
				else ant.hitbox.bottom += SPEED * elapsedSec;
			}
		}
		if (ant.carrying == Resource::none && m_LevelManagerPtr->GetTile(ant.hitbox.left, ant.hitbox.bottom) == Tile::plant)
		{
			ant.carrying = Resource::plant;
		}
		if (ant.carrying == Resource::plant && m_LevelManagerPtr->GetTile(ant.hitbox.left, ant.hitbox.bottom) == Tile::room)
		{
			ant.carrying = Resource::none;
			m_LevelManagerPtr->SetResource(m_LevelManagerPtr->GetResource() + 1);
		}
	}
}

void AntManager::Draw()
{
	for (const Ant& ant : m_AntVector)
	{
		utils::SetColor(Color4f{ 0.0f, 0.0f, 0.0f, 1.0f });
		utils::FillRect(ant.hitbox);
		switch (ant.carrying)
		{
		case Resource::plant:
			utils::SetColor(Color4f{ 0.2f, 0.6f, 0.2f, 1.0f });
			break;
		default:
			utils::SetColor(Color4f{ 0.0f, 0.0f, 0.0f, 1.0f });
			break;
		}
		utils::FillRect(Rectf{ant.hitbox.left, ant. hitbox.bottom, 1.0f, 1.0f});
	}
}

void AntManager::PassLevelManager(LevelManager* levelmanager)
{
	m_LevelManagerPtr = levelmanager;
}

void AntManager::AddAnts(int amount, float x, float y)
{
	for (int index{}; index < amount; ++index)
	{
		m_AntVector.emplace_back(Ant{ Rectf{x, y, 1.0f, 2.0f}, Resource::none, Vector2f{x, y} });
	}
}
