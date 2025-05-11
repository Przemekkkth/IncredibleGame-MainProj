#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "State.h"
#include <stack>

struct SharedContext {
    sf::RenderWindow* m_window;
};
