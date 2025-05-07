#pragma once

#include "State.h"
#include "MainMenuState.h"

class Game
{
private:
    static constexpr int FPS = 60;
	//States stack
	std::stack<State*> m_states;

	//Variables
	sf::RenderWindow* m_window;
    //sf::Event m_event;
	PopUpText* m_popUpText;

	//Initialize private functions
	void initWindow();
	void initStates();

    sf::Clock m_clock;
    float m_elapsed;
public:
	//Contructors / Descructors
	Game();
	~Game();
	//Public Functions

	//Update
	void update();
	void updateEvents();
	void updateButtonRealese();

	//Render
	void render();

	void realeseBoolsReset();

	//Game loop
	void gameLoop();

    sf::Time getElapsed();
    void restartClock();
};

