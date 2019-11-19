//
// Created by Joshua2018 on 2019/11/14.
//

#ifndef HW7_3_TEMPLATE__DYNAMICARRAY_H_
#define HW7_3_TEMPLATE__DYNAMICARRAY_H_

#include <iostream>

template <typename ElementType>
class dynamic_array {
public:
    dynamic_array();
    explicit dynamic_array(unsigned int size);
    dynamic_array(dynamic_array<ElementType> &other);
    unsigned int size();
    void set_size(unsigned int size);
    bool empty();
    ElementType& operator[](unsigned int index);
    bool binary_search_contains(ElementType element);
private:
    ElementType *elements_;
    unsigned int size_;
};

template <typename ElementType>
std::ostream &operator<<(std::ostream &os, dynamic_array<ElementType> &array);

#include "dynamicarray.hpp"

#endif //HW7_3_TEMPLATE__DYNAMICARRAY_H_
