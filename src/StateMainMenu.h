#pragma once
#include "BaseState.h"
#include "Button.h"
#include <map>

class StateMainMenu : public BaseState
{
public:
    StateMainMenu(StateManager* stateManager);
    virtual void OnCreate() override;
    virtual void OnDestroy() override;
    virtual void Activate() override;
    virtual void Deactivate() override;
    virtual void Update(const sf::Time &time) override;
    virtual void Draw() override;
    virtual void HandlePlayerInput(const std::optional<sf::Event> &event) override;
private:
    std::map<sf::String, Button*> m_buttons;
    sf::RectangleShape m_background;
    sf::Texture m_backgroundTexture;
    StateManager* m_stateManager;
};
