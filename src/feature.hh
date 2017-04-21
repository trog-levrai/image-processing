#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Feature {
    public:
        Feature(size_t x, size_t y, size_t size, size_t width)
        : x_(x)
        , y_(y)
        , size_(size)
        , width_(width)
        { }

        Feature() { }

        ssize_t getValue(std::shared_ptr<std::vector<size_t>> integral const) const = 0;

    private:
        size_t x_, y_, size_, width_;

        size_t getPos(size_t x, size_t y);
};
