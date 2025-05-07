#include "headers.h"
#include "Game.h"

//Initialize private Functions
void Game::initWindow()
{
    m_window = new sf::RenderWindow{ sf::VideoMode{sf::Vector2u{Constants::WindowWidth, Constants::WindowHeigth}},
        "Incredible Game", sf::Style::Close | sf::Style::Titlebar };

}

void Game::initStates()
{
	m_states.push(new MainMenuState{ &m_states, m_window, m_popUpText});
}

//Constructors / Descructors
Game::Game()
    : m_elapsed(0.0f)
{
	m_popUpText = new PopUpText{};

	GameResources::initResources();
	this->initWindow();
	this->initStates();
    m_clock.restart();
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
        float timestep = 1.0f / FPS;
        while(m_elapsed >= timestep){
            deltaTime::timePerFrame = 1.0f / FPS;
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
	this->updateEvents();
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
	this->showFPS();
}

void Game::updateEvents()
{
    while (const std::optional event = m_window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_window->close();
        }
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

void Game::showFPS()
{
	float deltaTime{ m_timePerFrame };
    std::cout << "TEST " << std::endl;
    //std::cout << "FPS: " << static_cast<int>(1 / deltaTime) << '\n';
}

void Game::render()
{
	m_window->clear();

	if (!m_states.empty())
	{
		m_states.top()->render(m_window);
	}

	m_popUpText->render(m_window);

	m_window->display();
}

void Game::realeseBoolsReset()
{
	RealeseDetection::Escape = false;
	RealeseDetection::mouseLeftButton = false;
	RealeseDetection::W = false;
}
