#include "res_manager.hpp"
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

struct FileNode {
    std::string path;
    std::string resName;
} typedef FileNode;

std::vector<FileNode> loadDirFileNames(std::string path);

Resource_Manager::Resource_Manager() {
    load_shaders();
    load_textures();
    load_fonts();
}

Resource_Manager::~Resource_Manager() {
    for (auto &shader : m_shaders) {
        delete shader.second;
    }

    for (auto &texture : m_textures) {
        delete texture.second;
    }

    for (auto &font : m_fonts) {
        delete font.second;
    }
}

void Resource_Manager::load_shaders() {
    // m_shaders["blur"] = new sf::Shader();
    // if (!m_shaders["blur"]->loadFromFile("assets/shaders/blur.frag", sf::Shader::Fragment)) {
    //     std::cout << "Error loading shader" << std::endl;
    // }
    // m_shaders["blur"]->setUniform("dir", sf::Vector2f(1.f, 0.f));
    // m_shaders["blur"]->setUniform("nSamplesF", 1.5f);
    // m_shaders["blur"]->setUniform("radius", 0.f);
    std::vector<FileNode> files = loadDirFileNames("assets/shaders/");

    for (auto &file : files) {
        sf::Shader *shader = new sf::Shader();

        if (!shader->loadFromFile(file.path, sf::Shader::Fragment)) {
            std::cout << "Error loading shader" << std::endl;

        } else {
            std::cout << "Shader loaded: " << file.path << std::endl;
            m_shaders[file.resName] = shader;
        }
    }
}

void Resource_Manager::load_textures() {
    for (auto &file : loadDirFileNames("assets/textures/")) {
        sf::Texture *texture = new sf::Texture();

        if (!texture->loadFromFile(file.path)) {
            std::cout << "Error loading texture" << std::endl;

        } else {
            std::cout << "Loaded texture: " << file.resName << std::endl;
            m_textures[file.resName] = texture;
        }
    }
}

std::unordered_map<std::string, sf::Shader*> Resource_Manager::get_shaders() {
    return m_shaders;
}

std::unordered_map<std::string, sf::Texture*> Resource_Manager::get_textures() {
    return m_textures;
}
std::unordered_map<std::string, sf::Font*> Resource_Manager::get_fonts() {
    return m_fonts;
}

sf::Font *Resource_Manager::get_font(std::string fontName) {
    return m_fonts[fontName];
}

void Resource_Manager::load_fonts() {
    std::vector<FileNode> files = loadDirFileNames("assets/fonts/");

    for (auto &file : files) {
        sf::Font *font = new sf::Font();

        if (!font->loadFromFile(file.path)) {
            std::cout << "Error loading font" << std::endl;

        } else {
            std::cout << "Loaded font: " << file.resName << std::endl;
            m_fonts[file.resName] = font;
        }
    }
}


std::vector<FileNode> loadDirFileNames(std::string path) {
    std::vector<FileNode> files;

    // load all files in path
    for (auto &entry : fs::directory_iterator(path)) {
        FileNode file;
        file.path = entry.path().string();
        file.resName = entry.path().filename().string();
        files.push_back(file);
    }

    return files;
}
