#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class PawnPromotionDialog : public sf::Drawable {
  public:
    PawnPromotionDialog() {
        this->pawnPromotionDialog = sf::RectangleShape(sf::Vector2f(200, 200));
        this->pawnPromotionDialog.setFillColor(sf::Color::Red) ;
        this->pawnPromotionDialog.setOrigin(sf::Vector2f(100, 100));
    }
    ~PawnPromotionDialog() = default; 

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
      target.draw(this->pawnPromotionDialog) ; 
    }

    void setPosition(sf::Vector2f view_center) {
      this->pawnPromotionDialog.setPosition(view_center) ; 
    }

  private:

    sf::RectangleShape pawnPromotionDialog ;

};
