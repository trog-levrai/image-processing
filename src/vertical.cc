#include "vertical.hh"

ssize_t Vertical::getValue(std::shared_ptr<std::vector<size_t>> integral const) const {
    ssize_t left = (*integral)[getPos(x_ + size_ / 2, y_ + size_)];
    left += (*integral)[getPos(x_, y_)];
    left -= (*integral)[getPos(x_ + size_ / 2, y_)];
    left -= (*integral)[getPos(x_, y_ + size_)];
    ssize_t right = (*integral)[getPos(x_ + size_, y_ + size_)];
    right += (*integral)[getPos(x_ + size_ / 2, y_)];
    right -= (*integral)[getPos(x_ + size_ / 2, y_ + size_)];
    right -= (*integral)[getPos(x_ + size_, y_)];
    return left - right;
}
