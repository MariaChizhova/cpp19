#include "Figure.hpp"

Figure::Figure(int id, int x, int y) {
    this->id = id;
    this->x = x;
    this->y = y;
}

void Figure::move(int new_x, int new_y) {
    x = new_x;
    y = new_y;
}

int Figure::get_id() const {
    return id;
}
