#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <string>
#include <stdio.h>


class Piece : public sf::Drawable {
  public:
    Piece() ; 
    virtual ~Piece(); 
    virtual bool canMove(int original_x, int original_y, int dest_x, int dest_y) const = 0; 

    void draw(sf::RenderTarget &window) const ; 
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setXPos(float x); 
    void setYPos(float y);
    void setPosition(float x, float y); 
    void setRadius(float radius); 
    
  private:
    bool white;
    sf::CircleShape piece; 
};
