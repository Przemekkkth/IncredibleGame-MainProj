#include "headers.h"
#include "State.h"


//Constructors / Descrutors
State::State(std::stack<State*>* states, sf::RenderWindow* window, PopUpText* popUpText) :
	m_states{ states }, m_window{window}, m_popUpText{popUpText}
{
	m_quit = false;
	m_isPaused = false;
	m_keyTime = 0.0f;
	m_keyTimeMax = 10.0f;

}

State::~State()
{
}

void State::updateKeyTime(const float& timePerFrame)
{
	if (m_keyTime < m_keyTimeMax + 1.0f)
	{
		m_keyTime += 30.0f * timePerFrame;
	}
}

void State::endState()
{
	m_quit = true;
}

const bool& State::getQuit() const
{
	return m_quit;
}

void State::updateMousePositions(sf::View& camera)
{
	//All map position
	sf::Vector2f viewLeftCorner{
		camera.getCenter().x - camera.getSize().x /2.0f,
		camera.getCenter().y - camera.getSize().y / 2.0f
	};

	m_mousePositionMap = sf::Mouse::getPosition(*m_window);

	m_mousePositionMap.x += viewLeftCorner.x;
	m_mousePositionMap.y += viewLeftCorner.y;

	//Window pos
	m_mousePositionWindow = sf::Mouse::getPosition(*m_window);

	//View pos
	m_mousePositionView = m_window->mapPixelToCoords(m_mousePositionWindow);

	//Grid pos
	m_mouseGridPosition.x = m_mousePositionWindow.x / Constants::gridSizeU;
	m_mouseGridPosition.y = m_mousePositionWindow.y / Constants::gridSizeU;

}

void State::pauseON()
{
	m_isPaused = true;
}

void State::pauseOFF()
{
	m_isPaused = false;
}

const bool State::getKeyTime()
{
	if (m_keyTime > m_keyTimeMax)
	{
		m_keyTime = 0.0f;
		return true;
	}

	return false;
}
