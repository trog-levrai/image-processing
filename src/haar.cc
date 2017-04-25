#include "haar.hh"

Haar::~Haar() {

    //Deletion of used features
    for (auto feature: features_)
        delete feature;
}

std::shared_ptr<std::vector<size_t>> Haar::grayscale(const std::vector<unsigned char> &img) {
    auto ans = std::make_shared<std::vector<size_t>>(img.size() / 3);

    #pragma omp parallel for simd
    for (size_t i = 0; i < img.size(); i += 3) {
        unsigned char pixel = (unsigned char)((float)img[i] * 0.21);
        pixel += (unsigned char)((float)img[i + 1] * 0.71);
        pixel += (unsigned char)((float)img[i + 2] * 0.08);
        (*ans)[i / 3] = pixel;
    }
    return ans;
}

size_t Haar::getPos(size_t x, size_t y) {
    return x + width_ * y;
}

void Haar::genIntegral() {
    integral_ = grayscale(img_);

    #pragma omp parallel for simd
    for (size_t j = 0; j < height_; ++j) {
        for (size_t i = 1; i < width_; ++i)
            (*integral_)[getPos(i, j)] += (*integral_)[getPos(i - 1, j)];
    }

    #pragma omp parallel for simd
    for (size_t i = 0; i < width_; ++i) {
        for (size_t j = 1; j < height_; ++j) {
            (*integral_)[getPos(i, j)] += (*integral_)[getPos(i, j - 1)];
        }
    }

    //Instantiation of all features
    features_.push_back(new Vertical(integral_, width_));
    features_.push_back(new Horizontal(integral_, width_));
}

void Haar::execHaar(size_t x, size_t y, size_t size) {
    //Call on Haar's features
}

void Haar::scanLine(size_t size, size_t j) {
    for (size_t i = 0; i < width_ / size; ++i) {
        execHaar(i * size, j * size, size);
    }
    if (width_ % size != 0)
        execHaar(width_ - size, j * size, size);
}

void Haar::scanImage() {
    for (size_t size = MIN_SIZE; size < width_ && size < height_; size *= RATIO) {
        //OpenMP here
        for (size_t j = 0; j < height_ / size; ++j) {
            scanLine(size, j);
        }
        if (height_ % size != 0)
            scanLine(size, height_ - size);
    }
}
