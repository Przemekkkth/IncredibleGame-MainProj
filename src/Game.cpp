#include "headers.h"
#include "Game.h"

Game::Game()
    : m_elapsed(0.0f), m_stateManager(&m_sharedContext)
{
	m_popUpText = new PopUpText{};
	GameResources::initResources();

	this->initWindow();
	this->initStates();
    m_clock.restart();
    m_sharedContext.m_window = m_window;
    m_stateManager.SwitchTo(StateType::MainMenu);
}

Game::~Game()
{
	GameResources::deleteResources();
	delete m_window;
	delete m_popUpText;
}


//Public Functions
void Game::gameLoop()
{
	while (m_window->isOpen())
	{
        handleEvents();

        float timestep = 1.0f / FPS;
        while(m_elapsed >= timestep){
            deltaTime::timePerFrame = 1.0f / FPS;
            m_stateManager.Update(sf::seconds(timestep));
            this->update();
            m_elapsed -= timestep;

        }
        this->render();
        restartClock();
	}
}

sf::Time Game::getElapsed()
{
    return m_clock.getElapsedTime();
}

void Game::restartClock()
{
    m_elapsed += m_clock.restart().asSeconds();
}

void Game::update()
{

	if (!m_states.empty())
	{
        float dt = 1.0f / FPS;
        m_popUpText->update(dt);
		m_states.top()->update(m_window);

		if (m_states.top()->getQuit() == true)
		{
			delete m_states.top();
			m_states.pop();
		}

	}
	else
	{
		m_window->close();
	}

	this->realeseBoolsReset();
}

void Game::handleEvents()
{
    while (const std::optional event = m_window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_window->close();
        }
        m_states.top()->handlePlayerInput(event);
        m_stateManager.HandlePlayerInput(event);
    }
    // while (m_window->pollEvent(m_event))
    // {
    // 	if (m_event.type == sf::Event::Closed)
    // 		m_window->close();

    // 	this->updateButtonRealese();
    // }
}

void Game::updateButtonRealese()
{
    // if (m_event.type == sf::Event::KeyReleased &&
 //        m_event.key.code == sf::Keyboard::Scancode::Escape)
    // {
    // 	RealeseDetection::Escape = true;
    // }
    // else if (m_event.type == sf::Event::MouseButtonReleased &&
 //               m_event.mouseButton.button == sf::Mouse::Button::Left)
    // {
    // 	RealeseDetection::mouseLeftButton = true;
    // }
    // else if (m_event.type == sf::Event::KeyReleased &&
 //               m_event.key.code == sf::Keyboard::Scancode::W)
    // {

    // 	RealeseDetection::W = true;
    // }
}

void Game::render()
{
	m_window->clear();

    // if (!m_states.empty())
    // {
    // 	m_states.top()->render(m_window);
    // }

    // m_popUpText->render(m_window);

    m_stateManager.Draw();
	m_window->display();
}

void Game::realeseBoolsReset()
{
	RealeseDetection::Escape = false;
	RealeseDetection::mouseLeftButton = false;
	RealeseDetection::W = false;
}

void Game::initWindow()
{
    m_window = new sf::RenderWindow{ sf::VideoMode{sf::Vector2u{Constants::WindowWidth, Constants::WindowHeigth}},
                                    "Incredible Game", sf::Style::Close | sf::Style::Titlebar };
}

void Game::initStates()
{
    m_states.push(new MainMenuState{ &m_states, m_window, m_popUpText});
}
