#include "Window.hpp"
#include <SFML/System/Vector2.hpp>
#include <iostream>

Window::Window() {
    Setup("Window", sf::Vector2u(800,600));
}
Window::Window( std::string l_title,
                sf::Vector2u l_size) {
    Setup(l_title,l_size);
}
Window::~Window() {
    Destroy();
}

void Window::Setup(const std::string &l_title, const sf::Vector2u& l_size) {
    m_windowTitle = l_title;
    m_windowSize = l_size;
    m_isFullscreen = false;
    m_isDone = false;
    Create();
}

void Window::Create() {
    auto style = (m_isFullscreen ? sf::Style::Fullscreen
                  : sf::Style::Default);
    m_window.create({ m_windowSize.x, m_windowSize.y, 32 },
                    m_windowTitle, style);
    m_view = sf::View(sf::FloatRect(0.f, 0.f, m_windowSize.x, m_windowSize.y));
    // activate it
    m_window.setFramerateLimit(60);
    m_window.setView(m_view);
    // m_window.setVerticalSyncEnabled(true);
    m_window.setMouseCursorVisible(true);
}
void Window::Destroy() {
    m_window.close();
}

void Window::Update() {
    lastMouseDownState = m_down;
    sf::Event event {};

    while (
        m_window.pollEvent(event)
    ) {
        if (event.type == sf::Event::Closed) {
            m_isDone = true;
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                m_isDone = true;
            }
        }

        if (!m_down && event.type == sf::Event::MouseButtonPressed) {
            m_down = true;
        }

        if (m_down && event.type == sf::Event::MouseButtonReleased) {
            m_down = false;
        }

        if (event.type == sf::Event::Resized) {
            m_view.setSize(event.size.width, event.size.height);
            m_window.setView(m_view);
        }
    }
}


sf::View* Window::GetView() {
    return &m_view;
}


void Window::ToggleFullscreen() {
    m_isFullscreen = !m_isFullscreen;
    Destroy();
    Create();
}

void Window::BeginDraw() {
    m_window.clear();
}
void Window::EndDraw() {
    m_window.display();
}

bool Window::IsDone() {
    return m_isDone;
}
bool Window::IsFullscreen() {
    return m_isFullscreen;
}

sf::RenderWindow* Window::GetRenderWindow() {
    return &m_window;
}

sf::Window *Window::GetWindow() {
    return &m_window;
}



sf::Vector2f Window::convertToGameCoordinates(sf::Vector2i mousePos) {
    // convert it to world coordinates
    sf::Vector2f worldPos = m_window.mapPixelToCoords(mousePos);
    return worldPos;
}

bool Window::isMouseUp() {
    if (!m_down && lastMouseDownState) {
        return true;
    }

    return false;
}

bool Window::isMouseDown() {
    if (m_down && !lastMouseDownState) {
        return true;
    }

    return false;
}

