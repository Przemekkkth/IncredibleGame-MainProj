#include "headers.h"
#include "GameResources.h"

sf::Font* GameResources::font = new sf::Font{};
sf::Texture* GameResources::grassTexture = new sf::Texture;

sf::Texture* GameResources::heartTexture = new sf::Texture;
sf::Texture* GameResources::halfHeartTexture = new sf::Texture;
sf::Texture* GameResources::emptyHeartTexture = new sf::Texture;
sf::Texture* GameResources::rifleTexture = new sf::Texture;
sf::Texture* GameResources::ninjaTexture = new sf::Texture;
sf::Texture* GameResources::batTexture = new sf::Texture;
sf::Texture* GameResources::playerTexture = new sf::Texture;
sf::Texture* GameResources::birdTexture = new sf::Texture;
sf::Texture* GameResources::stoneTexture = new sf::Texture;
sf::Texture* GameResources::doorTexture = new sf::Texture;
sf::Texture* GameResources::starTexture = new sf::Texture;
sf::Texture* GameResources::spikeTexture = new sf::Texture;
sf::Texture* GameResources::nestTexture = new sf::Texture;

void GameResources::initFont()
{
    if (!GameResources::font->openFromFile("assets/Fonts/PixellettersFull.ttf"))
	{
        std::exit(EXIT_FAILURE);
	}
}

void GameResources::initTextures()
{
	
    if (!GameResources::grassTexture->loadFromFile("assets/Textures/grassTexture.jpg"))
	{
        std::exit(EXIT_FAILURE);
	}

    if (!GameResources::heartTexture->loadFromFile("assets/Textures/heartTexture.png"))
	{
        std::exit(EXIT_FAILURE);
	}

    if (!GameResources::halfHeartTexture->loadFromFile("assets/Textures/halfHeartTexture.png"))
	{
        std::exit(EXIT_FAILURE);
	}

    if (!GameResources::emptyHeartTexture->loadFromFile("assets/Textures/emptyHeartTexture.png"))
	{
        std::exit(EXIT_FAILURE);
	}
	
    if (!GameResources::spikeTexture->loadFromFile("assets/Textures/spikeTexture.png"))
	{
        std::exit(EXIT_FAILURE);
	}

    if (!GameResources::rifleTexture->loadFromFile("assets/Textures/rifleTexture.png"))
	{
        std::exit(EXIT_FAILURE);
	}

    if (!GameResources::ninjaTexture->loadFromFile("assets/Textures/ninjaTexture.png"))
	{
        std::exit(EXIT_FAILURE);
	}

    if (!GameResources::batTexture->loadFromFile("assets/Textures/batTexture.png"))
	{
        std::exit(EXIT_FAILURE);
	}

    if (!GameResources::playerTexture->loadFromFile("assets/Textures/playerTexture.png"))
	{
        std::exit(EXIT_FAILURE);
	}

    if (!GameResources::birdTexture->loadFromFile("assets/Textures/birdTexture.png"))
	{
        std::exit(EXIT_FAILURE);
	}

    if (!GameResources::stoneTexture->loadFromFile("assets/Textures/stoneTexture.jpg"))
	{
        std::exit(EXIT_FAILURE);
	}
	
    if (!GameResources::doorTexture->loadFromFile("assets/Textures/doorTexture.png"))
	{
        std::exit(EXIT_FAILURE);
	}

    if (!GameResources::starTexture->loadFromFile("assets/Textures/starTexture.png"))
	{
        std::exit(EXIT_FAILURE);
	}

    if (!GameResources::nestTexture->loadFromFile("assets/Textures/nestTexture.png"))
	{
        std::exit(EXIT_FAILURE);
	}
}


void GameResources::initResources()
{
	GameResources::initFont();
	GameResources::initTextures();
}

void GameResources::deleteResources()
{
	delete GameResources::font;
	delete GameResources::grassTexture;
	delete GameResources::heartTexture;
	delete GameResources::halfHeartTexture;
	delete GameResources::emptyHeartTexture;
	delete GameResources::spikeTexture;
	delete GameResources::ninjaTexture;
	delete GameResources::batTexture;
	delete GameResources::playerTexture;
	delete GameResources::birdTexture;
	delete GameResources::stoneTexture;
	delete GameResources::doorTexture;
	delete GameResources::starTexture;
	delete GameResources::nestTexture;
}
