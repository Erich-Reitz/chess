#pragma once

#include <SFML/System/Vector2.hpp>
#include "Window.hpp"
#include "World.hpp"

class Game {
  public:
    Game();
    ~Game();
    void HandleInput();
    void Update();
    void Render();
    Window* GetWindow();
    sf::Time GetElapsed();

    void RestartClock();
  private:
    Window m_window;
    sf::Clock m_clock;
    sf::Time m_elapsed = sf::Time(sf::seconds(1/60.f));
    World m_world;
    sf::Shader m_blur;
};