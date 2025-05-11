#pragma once
#include <optional>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Button
{
private:
	sf::Text m_buttonText;
	sf::Color m_buttonHoverColor;
	sf::Color m_buttonIdleColor;
	

	//initialize private Functions
	void initColors();
public:
	//Constructors / Descructors
	Button(sf::Vector2f buttonPosition = sf::Vector2f{0.0f, 0.0f},
		std::string buttonText = "", float buttonTextSize = 0.0f,
		sf::Color buttonColor = sf::Color::White);
	~Button();

	//Button logic
	void buttonHover(sf::RenderWindow* window);
	bool isButtonClicked(sf::RenderWindow* window);
    bool isButtonClicked(sf::RenderWindow* window, const std::optional<sf::Event>& event);

	void drawButton(sf::RenderTarget* target);


	//Modifiers
	void setPosition(const float x, const float y);
	void setFillColor(sf::Color buttonColor);
	void setCharacterSize(const float characterSize);
	void setString(std::string buttonText);

	//Accesors
	const sf::FloatRect& getGlobalBounds() const;
	
};

