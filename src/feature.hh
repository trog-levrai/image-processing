#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Feature {
    public:
        Feature(std::shared_ptr<std::vector<size_t>> integral, size_t width)
        : integral_(integral)
        , width_(width)
        { }

        Feature() { }

        virtual ~Feature() = default;

        virtual ssize_t getValue(size_t x, size_t y, size_t size) const = 0;

    protected:
        std::shared_ptr<std::vector<size_t>> integral_;
        size_t width_;
        size_t getPos(size_t x, size_t y) const;
};
