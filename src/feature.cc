#include "feature.hh"

size_t Feature::getPos(size_t x, size_t y) {
    return x + width_ * y;
}
