#pragma once

#include "feature.hh"

class Horizontal: public Feature {
    public:

        Horizontal(std::shared_ptr<std::vector<size_t>> integral, size_t width)
        : Feature(integral, width) { }

        virtual ssize_t getValue(size_t x, size_t y, size_t size) const;
};
