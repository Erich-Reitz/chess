#include "GameObject.hpp"
#include <SFML/System/Vector2.hpp>

GameObject::GameObject() {
}

GameObject::GameObject(sf::Vector2f starting_pos) {
    sprite.setPosition(starting_pos) ;
    sprite.setOrigin(sprite.getLocalBounds().width/ 2, sprite.getLocalBounds().height/ 2);
}


GameObject::GameObject(float starting_x, float starting_y, float scale, sf::Texture *n_texture) {
    sprite.setPosition(starting_x, starting_y);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    this->scale(scale, scale);
    this->texture = *n_texture;
    sprite.setTexture(texture);
    this->size = scale;
}


GameObject::GameObject(float starting_x, float starting_y, sf::Texture *n_texture) {
    this->texture = *n_texture;
    sprite.setTexture(texture);
    sprite.setPosition(starting_x, starting_y);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, (sprite.getLocalBounds().height / 2));
}

GameObject &GameObject::operator=(const GameObject &other) {
    if (this != &other) {
        sprite = other.sprite;
        texture = other.texture;
    }

    return *this;
}

GameObject::GameObject(const GameObject &other) : sprite(other.sprite), texture(other.texture) {
    sprite.setTexture(texture);
    sprite.setPosition(other.sprite.getPosition());
}

void GameObject::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void GameObject::setTexture(sf::Texture *texture) {
    this->texture = *texture; 
    this->sprite.setTexture(this->texture) ; 
}

void GameObject::move(float x, float y) {
    sprite.move(x, y);
}

void GameObject::flipDirection() {
    sprite.setRotation(sprite.getRotation() + 180);
}

sf::FloatRect GameObject::getShape() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f GameObject::getPosition() const {
    return sprite.getPosition();
}

void GameObject::scale(float x, float y) {
    sprite.setScale(x, y);
}

void GameObject::rotate(float angle) {
    sprite.rotate(angle);
}