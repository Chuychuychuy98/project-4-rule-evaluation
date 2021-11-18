//
// Created by Chandler Rowe on 10/26/21.
//

#include "Database.h"

int Database::NumTups() {
    int num = 0;
    for (auto p : relations) {
        num += p.second->Size();
    }
    return num;
}