#include "pch.h"
#include "Game.h"
#include "AntManager.h"
#include "Utils.h"
#include <iostream>
#include "LevelManager.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_AntManagerPtr = new AntManager{ GetViewPort() };
	m_LevelManagerPtr = new LevelManager{ m_AntManagerPtr };
	m_TutorialText = new Texture{ "Build hallways by clicking on dirt tiles", "REDENSEK.TTF", 24, Color4f{1.0f, 1.0f, 1.0f, 1.0f} };
	m_AntManagerPtr->PassLevelManager(m_LevelManagerPtr);
}

void Game::Cleanup( )
{
	delete m_AntManagerPtr;
	delete m_LevelManagerPtr;
	if (m_tutorialTracker < 3) delete m_TutorialText;
}

void Game::Update( float elapsedSec )
{
	m_AntManagerPtr->Update(elapsedSec);
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{
	ClearBackground( );
	glPushMatrix();
	glScalef(5.0f, 5.0f, 1.0f);
	m_LevelManagerPtr->Draw();
	m_AntManagerPtr->Draw();
	glPopMatrix();
	if (m_tutorialTracker < 3) {
		m_TutorialText->Draw(Point2f{ 10.0f, 10.0f });
		utils::SetColor(Color4f{ 1.0f, 1.0f, 1.0f, 0.10f });
		if (m_tutorialTracker == 0) {
			utils::FillRect(50.0f * 9, 50.0f * 6, 50.0f, 50.f);
		}
		else if (m_tutorialTracker == 1) {
			utils::FillRect(50.0f * 9, 50.0f * 5, 50.0f, 50.f);
		}
		else if (m_tutorialTracker == 2) {
			utils::FillRect(50.0f * 9, 50.0f * 7, 50.0f, 50.f);
		}
	}
	m_LevelManagerPtr->DrawUI();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	m_LevelManagerPtr->ProcessMouseMotionEvent(e);
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	if (m_tutorialTracker == 0 && e.x > 9 * 50.0f && e.x < 10 * 50.0f && e.y > 6 * 50.0f && e.y < 7 * 50.0f) {
		m_LevelManagerPtr->ProcessMouseUpEvent(e);
		m_tutorialTracker = 1;
		delete m_TutorialText;
		m_TutorialText = new Texture{ "Upgrade hallways to rooms to get more ants", "REDENSEK.TTF", 24, Color4f{1.0f, 1.0f, 1.0f, 1.0f} };
	}
	else if (m_tutorialTracker == 1 && e.x > 9 * 50.0f && e.x < 10 * 50.0f && e.y > 5 * 50.0f && e.y < 6 * 50.0f) {
		m_LevelManagerPtr->ProcessMouseUpEvent(e);
		m_tutorialTracker = 2;
		delete m_TutorialText;
		m_TutorialText = new Texture{ "Build exits close to plants so ants can gather resources", "REDENSEK.TTF", 24, Color4f{1.0f, 1.0f, 1.0f, 1.0f} };
	}
	else if (m_tutorialTracker == 2 && e.x > 9 * 50.0f && e.x < 10 * 50.0f && e.y > 7 * 50.0f && e.y < 8 * 50.0f) {
		m_LevelManagerPtr->ProcessMouseUpEvent(e);
		m_tutorialTracker = 3;
		delete m_TutorialText;
	}
	else if (m_tutorialTracker == 3) {
		m_LevelManagerPtr->ProcessMouseUpEvent(e);
	}
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor(0.3f, 0.2f, 0.2f, 1.0f);
	glClear( GL_COLOR_BUFFER_BIT );
}
