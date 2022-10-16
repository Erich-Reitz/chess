#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Window{
    public:
        Window();
        Window( std::string l_title, sf::Vector2u l_size);
        ~Window();
        void BeginDraw(); // Clear the window.
        void EndDraw(); // Display the changes.
        void Update();
        bool IsDone();
        bool IsFullscreen();
        sf::Vector2u GetWindowSize();
        sf::RenderWindow* GetRenderWindow();
        sf::View *GetView();
        void SetView(sf::View *l_view);
        unsigned int getMinimumViewSize();
        unsigned int getMaximumViewSize();
        sf::Window *GetWindow();
        void ToggleFullscreen();
        void Draw(sf::Drawable& l_drawable);
        void Zoom(float l_zoom);
        sf::Vector2f convertToGameCoordinates(sf::Vector2i viewportCoordinates);
        sf::RenderWindow m_window;
        sf::Vector2f getScaleOfWindowSizeToView();
        private:
            void Setup(const std::string& l_title, const sf::Vector2u& l_size);
            
            void Destroy();
            void Create();
            
            sf::View m_view;
            sf::Vector2u m_windowSize;
            std::string m_windowTitle;
            bool m_isDone;
            bool m_isFullscreen;

            // these have to do with zoom, can't zoom out or in past these values.
            int minimumViewSize = 100;
            int maximumViewSize = 3000;


            float historicalZoom = 1;
            
};