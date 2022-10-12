#include <SFML/Graphics.hpp>
#include "Game.hpp"


int main() {
    Game game;
    while(!game.GetWindow()->IsDone()) {
        game.HandleInput();
        game.Update();
        game.Render();
    }
    return 0;
}