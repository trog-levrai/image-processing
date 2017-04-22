#include "vertical.hh"

ssize_t Vertical::getValue(size_t x, size_t y, size_t size) const {
    ssize_t left = (*integral_)[getPos(x + size / 2, y + size)];
    left += (*integral_)[getPos(x, y)];
    left -= (*integral_)[getPos(x + size / 2, y)];
    left -= (*integral_)[getPos(x, y + size)];
    ssize_t right = (*integral_)[getPos(x + size, y + size)];
    right += (*integral_)[getPos(x + size / 2, y)];
    right -= (*integral_)[getPos(x + size / 2, y + size)];
    right -= (*integral_)[getPos(x + size, y)];
    return left - right;
}
