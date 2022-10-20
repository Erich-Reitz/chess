#include <exception>

struct CurrentSquareDoesNotContainPiece : public std::exception {
    const char * what () const throw () {
        return "The current square does not contain a piece to move";
    }
};