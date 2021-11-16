//
// Created by Chandler Rowe on 10/26/21.
//

#include "Header.h"
#include <stdexcept>

void Header::AddVal(const std::string &toAdd) {
    attr.push_back(toAdd);
}

bool Header::RemVal(int index) {
    try {
        attr.erase(attr.begin() + index);
        return true;
    }
    catch (std::out_of_range &e) {
        return false;
    }
}
