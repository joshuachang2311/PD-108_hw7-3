#include <stdexcept>
#include "dynamicarray.h"

template<typename ElementType>
dynamic_array<ElementType>::dynamic_array() {
    elements_ = nullptr;
    size_ = 0;
}

template<typename ElementType>
dynamic_array<ElementType>::dynamic_array(unsigned int size) {
    elements_ = new ElementType[size];
    size_ = size;
}

template<typename ElementType>
dynamic_array<ElementType>::dynamic_array(dynamic_array<ElementType> &other) {
    elements_ = new ElementType[other.size()];
    size_ = other.size();

    for (unsigned int i = 0; i < size_; ++i) {
        elements_[i] = other[i];
    }
}

template<typename ElementType>
unsigned int dynamic_array<ElementType>::size() {
    return size_;
}

template<typename ElementType>
void dynamic_array<ElementType>::set_size(unsigned int size) {
    elements_ = new ElementType[size];
    size_ = size;
}

template<typename ElementType>
bool dynamic_array<ElementType>::empty() {
    return size_ == 0;
}

template<typename ElementType>
ElementType& dynamic_array<ElementType>::operator[](unsigned int index) {
    if (index >= size_) {
        throw std::out_of_range("index larger than array size");
    } else {
        return elements_[index];
    }
}
template<typename ElementType>
bool dynamic_array<ElementType>::binary_search_contains(ElementType element) {
    unsigned int left = 0, right = size_;
    while (left < right) {
        unsigned int medium = (left + right) / 2;
        if (elements_[medium] == element) {
            return true;
        } else if (elements_[medium] > element) {
            right = medium;
        } else {
            left = medium + 1;
        }
    }
    return false;
}

template <typename ElementType>
std::ostream &operator<<(std::ostream &os, dynamic_array<ElementType> &array) {
    if (array.empty()) {
        return os;
    }

    os << array[0];
    for (unsigned int i = 1; i < array.size(); ++i) {
        os << ", " << array[i];
    }
    return os;
}
