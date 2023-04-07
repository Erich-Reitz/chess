#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Window {
  public:
    Window();
    Window( std::string l_title, sf::Vector2u l_size);
    ~Window();
    void BeginDraw(); // Clear the window.
    void EndDraw(); // Display the changes.
    void Update();
    bool IsDone();
    bool IsFullscreen();
    sf::RenderWindow* GetRenderWindow();
    sf::View *GetView();
    unsigned int getMinimumViewSize();
    unsigned int getMaximumViewSize();
    sf::Window *GetWindow();
    void ToggleFullscreen();
    sf::Vector2f convertToGameCoordinates(sf::Vector2i viewportCoordinates);
    sf::RenderWindow m_window;
    bool isMouseUp();
    bool isMouseDown();
  private:
    void Setup(const std::string& l_title, const sf::Vector2u& l_size);

    void Destroy();
    void Create();

    sf::View m_view;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isDone;
    bool m_isFullscreen;

    bool m_down = false;
    bool lastMouseDownState = false;
    float historicalZoom = 1;

};