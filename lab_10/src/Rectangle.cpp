#include <cstdlib>
#include "Rectangle.hpp"

Rectangle::Rectangle(int id, int x, int y, int width, int height) {
    this->id = id;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id, x, y, width, height);
}

bool Rectangle::is_inside(int x, int y) const {
    return abs(this->x - x) * 2 <= width && abs(this->y - y) * 2 <= height;
}

void Rectangle::zoom(int factor) {
    width *= factor;
    height *= factor;
}