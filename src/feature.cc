#include "feature.hh"

size_t Feature::getPos(size_t x, size_t y) const {
    return x + width_ * y;
}
