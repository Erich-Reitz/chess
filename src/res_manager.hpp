#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

class Resource_Manager {
  public:
    Resource_Manager();
    ~Resource_Manager();

    std::unordered_map<std::string, sf::Shader*> get_shaders();
    std::unordered_map<std::string, sf::Texture*> get_textures();
    std::unordered_map< std::string, sf::Font*> get_fonts();
    sf::Font *get_font(std::string fontName);

  private:
    void load_shaders();
    void load_textures();
    void load_fonts();

    std::unordered_map<std::string, sf::Shader*> m_shaders;
    std::unordered_map<std::string, sf::Texture*> m_textures;
    std::unordered_map<std::string, sf::Font*> m_fonts;
};