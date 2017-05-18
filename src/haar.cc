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


    /*for (size_t i = 0; i < width_; ++i) {
        for (size_t j = 0; j < height_; ++j) {
            std::cout << (*integral_)[getPos(i, j)] << " ";
        }
        std::cout << std::endl;
    }*/

    size_t sub_x = 10;
    size_t sub_y = 10;
    float ratio = 1.25;

    while (sub_x != height_ && sub_y != height_)
    {
        for (size_t i = 0; i < height_ - sub_y; i += ratio * sub_x)
        {
            for (int j = 0; j < width_ - sub_x; j += ratio * sub_y)
            {
                //std::cout << i << " " << j << " " << sub_x << std::endl;
                //FIXME
                features_.push_back(new Vertical(integral_, width_));
                //FIXME
                features_.push_back(new Horizontal(integral_, width_));
            }
        }
        sub_x *= ratio;
        sub_y *= ratio;

        sub_x = sub_x > height_ ? height_ : sub_x;
        sub_y = sub_y > width_ ? width_ : sub_y;
    }

    //Instantiation of all features
    features_.push_back(new Vertical(integral_, width_));
    features_.push_back(new Horizontal(integral_, width_));

}

void Haar::execHaar(size_t x, size_t y, size_t size) {
    auto res = std::vector<size_t>(3);
    res[0] = x;
    res[1] = y;
    res[2] = size;
    //Call on Haar's features
    for (auto feature: features_)
        res.push_back(feature->getValue(x, y, size));

    std::cout << res[1] << " " << res[0];

    #pragma omp critical
    values_->push_back(res);
}

void Haar::scanLine(size_t size, size_t y) {
    for (size_t i = 0; i < width_ / size; ++i)
        execHaar(i * size, y, size);
    if (width_ % size != 0)
        execHaar(width_ - size, y, size);
}

void Haar::scanImage() {
    values_ = new std::vector<std::vector<size_t>>();
    for (size_t size = MIN_SIZE; size < width_ && size < height_; size *= RATIO) {
        #pragma omp parallel for
        for (size_t j = 0; j < height_ / size; ++j) {
            scanLine(size, j * size);
        }
        if (height_ % size != 0)
            scanLine(size, height_ - size);
    }
}

std::vector<std::vector<size_t>>* Haar::getValues() {
    return values_;
}

void Haar::learn() {
    if (width_ != height_)
        std::cerr << "Width and height are different!" << std::endl;
    values_ = new std::vector<std::vector<size_t>>();
    execHaar(0, 0, width_);
}
