#pragma once
#include "Timer.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class PopUpText
{
private:
    Timer* m_popUpTimer;
	sf::Font* m_textFont;
	sf::Text* m_popUpText;

	bool m_isTextShown;
	bool m_smoothPooping;

public:
	PopUpText(float delay = 1000.0f);
	~PopUpText();

	void update(float& timePerFrame);
	void render(sf::RenderTarget* target);

	void showText(std::string textToShow, float delay,
		bool showSmoothly);
	void hideText(float& timePerFrame);

	const bool& isTextShown();
};

