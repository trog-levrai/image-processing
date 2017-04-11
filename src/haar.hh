#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#define MIN_SIZE 24
#define RATIO 1.25
#define SHIFT 0.5

class Haar {
    public:
        Haar(std::vector<unsigned char>& img, size_t width, size_t height)
        : img_(img)
        , width_(width)
        , height_(height)
        { }

        Haar() {}

        void genIntegral();

        void scanImage();

    private:

        void execHaar(size_t x, size_t y, size_t size);
        void scanLine(size_t size, size_t j);
        size_t getPos(size_t x, size_t y);
        std::shared_ptr<std::vector<size_t>> grayscale(const std::vector<unsigned char>&);
        std::vector<unsigned char> img_;
        std::shared_ptr<std::vector<size_t>> integral_;
        size_t width_;
        size_t height_;
};
