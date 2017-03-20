#include "haar.hh"

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

}
