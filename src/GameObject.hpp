#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class GameObject : public sf::Drawable {
  public:
    // constructors
    GameObject();
    GameObject(sf::Vector2f starting_pos);
    GameObject(float starting_x, float starting_y, float scale, sf::Texture *n_texture);
    GameObject(float starting_x, float starting_y, sf::Texture *texture);
    GameObject(const GameObject &other);
    
    GameObject &operator=(const GameObject &other);
    // methods


    virtual void setPosition(float x, float y);
    void setTexture(sf::Texture *texture); 


    void move(float x, float y);

    void flipDirection();
    void scale(float x, float y);
    void rotate(float x);

    // getters

    sf::FloatRect getShape() const;

    sf::Vector2f getPosition() const;
  protected:
    sf::Sprite sprite;
    sf::Texture texture;
    float size; 
};