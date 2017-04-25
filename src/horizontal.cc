#include "horizontal.hh"

ssize_t Horizontal::getValue(size_t x, size_t y, size_t size) const {
    ssize_t up = (*integral_)[getPos(x + size, y + size / 2)];
    up += (*integral_)[getPos(x, y)];
    up -= (*integral_)[getPos(x + size, y)];
    up -= (*integral_)[getPos(x, y + size / 2)];
    ssize_t down = (*integral_)[getPos(x + size, y + size)];
    down += (*integral_)[getPos(x, y + size / 2)];
    down -= (*integral_)[getPos(x + size, y + size / 2)];
    down -= (*integral_)[getPos(x, y + size)];
    return up - down;
}
