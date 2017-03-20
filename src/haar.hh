#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Haar {
    public:
        Haar(std::vector<unsigned char>& img, size_t width, size_t height)
        : img_(img)
        , width_(width)
        , height_(height)
        { }

        Haar() {}

        void genIntegral();

    private:
        size_t getPos(size_t x, size_t y);
        std::shared_ptr<std::vector<size_t>> grayscale(const std::vector<unsigned char>&);
        std::vector<unsigned char> img_;
        std::shared_ptr<std::vector<size_t>> integral_;
        size_t width_;
        size_t height_;
};
