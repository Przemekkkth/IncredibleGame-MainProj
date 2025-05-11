#include "StateMainMenu.h"
#include "AuxiliaryVariables.h"
#include "StateManager.h"

StateMainMenu::StateMainMenu(StateManager *stateManager)
    : BaseState(stateManager), m_stateManager(stateManager)
{
    if (!m_backgroundTexture.loadFromFile("assets/Textures/MainMenuBackground.png"))
    {
        std::exit(EXIT_FAILURE);
    }

    m_background.setSize(sf::Vector2f{
        static_cast<float>(Constants::WindowWidth),
        static_cast<float>(Constants::WindowHeigth)
    }
                         );

    m_background.setTexture(&m_backgroundTexture);


}

void StateMainMenu::OnCreate()
{
    m_buttons["newGameButton"] = new Button{ sf::Vector2f{
                                                         Constants::WindowWidth/2.0f - 100, 250.0f},
                                            "New game!", 60.0f };

    m_buttons["quitButton"] = new Button{ sf::Vector2f{
                                                      Constants::WindowWidth / 2.0f - 100, 320.0f},
                                         "Quit game", 60.0f };
}

void StateMainMenu::OnDestroy()
{
    delete m_buttons["newGameButton"];
    delete m_buttons["quitButton"];
}

void StateMainMenu::Activate()
{

}

void StateMainMenu::Deactivate()
{

}

void StateMainMenu::Update(const sf::Time &time)
{
    sf::RenderWindow* window = m_stateManager->GetContext()->m_window;
    m_buttons["newGameButton"]->buttonHover(window);
    m_buttons["quitButton"]->buttonHover(window);
}

void StateMainMenu::Draw()
{
    m_stateManager->GetContext()->m_window->draw(m_background);
    m_buttons["newGameButton"]->drawButton(m_stateManager->GetContext()->m_window);
    m_buttons["quitButton"]->drawButton(m_stateManager->GetContext()->m_window);
}

void StateMainMenu::HandlePlayerInput(const std::optional<sf::Event> &event)
{
    sf::RenderWindow* window = m_stateManager->GetContext()->m_window;
    if (m_buttons["newGameButton"]->isButtonClicked(window, event))
    {
        m_stateManager->SwitchTo(StateType::Game);
    }
    if(m_buttons["quitButton"]->isButtonClicked(window, event))
    {
        window->close();
    }
}
