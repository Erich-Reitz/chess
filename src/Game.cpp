#include "Game.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdio>
#include <iostream>
#include <cmath>




Game::Game(): m_window( std::string("CHESS GAME"), sf::Vector2u(1920, 1080) ) {
}
void Game::HandleInput() {
    unsigned int currentViewPortSize = m_window.GetWindowSize().x;
    unsigned int minimumViewSize = m_window.getMinimumViewSize();
    unsigned int maximumViewSize = m_window.getMaximumViewSize();
    // get mouse position in absolute coordinates
    sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window.GetWindow());
    sf::Vector2i gameCoordinates = m_window.convertToGameCoordinates(mousePos);
    m_world.HandleInput(gameCoordinates);
}

//destructor
Game::~Game() {
    //delete m_window;
}

void Game::Update() {
    m_world.update(m_elapsed);
    sf::RenderWindow *window = m_window.GetRenderWindow();
    sf::View *view = m_window.GetView();
    window->setView(*view);
    m_window.Update();
}

void Game::Render() {
    m_window.BeginDraw();
    m_world.Render(*m_window.GetRenderWindow());
    m_window.EndDraw();
}

sf::Time Game::GetElapsed() {
    return m_elapsed;
}
void Game::RestartClock() {
    m_elapsed = m_clock.restart();
}

Window* Game::GetWindow() {
    return &m_window;
}

