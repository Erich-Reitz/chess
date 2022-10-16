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
    // m_window.setMouseCursorVisible(true);
}
void Window::Destroy() {
    m_window.close();
}

void Window::Update() {
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
        if (event.type == sf::Event::Resized) {
            m_view.setSize(event.size.width, event.size.height);
            m_window.setView(m_view);
        }
    }
}

void Window::Zoom(float l_zoom) {
    historicalZoom += l_zoom;
    m_view.zoom(1-l_zoom);
    m_window.setView(m_view);
}

unsigned int Window::getMinimumViewSize() {
    return minimumViewSize;
}

unsigned int Window::getMaximumViewSize() {
    return maximumViewSize;
}

sf::View* Window::GetView() {
    return &m_view;
}

void Window::SetView(sf::View *l_view) {
    m_view = *l_view;
    m_window.setView(m_view);
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
sf::Vector2u Window::GetWindowSize() {
    return m_windowSize;
}
void Window::Draw(sf::Drawable&l_drawable) {
    m_window.draw(l_drawable);
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

sf::Vector2f Window::getScaleOfWindowSizeToView() {
    sf::Vector2u windowSize = GetWindowSize();
    sf::Vector2f viewSize = GetView()->getSize();
    return sf::Vector2f(windowSize.x / viewSize.x, windowSize.y / viewSize.y);
}



