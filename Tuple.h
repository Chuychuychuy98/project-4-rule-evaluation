//
// Created by Chandler Rowe on 10/26/21.
//

#ifndef PROJECT_3_INTERPRETER_TUPLE_H
#define PROJECT_3_INTERPRETER_TUPLE_H
#include <vector>
#include <string>
#include <iostream>

class Tuple {
public:
    Tuple() = default;
    void AddVal(const std::string &toAdd);
    bool RemVal(int index);
    bool operator< (const Tuple &rhs) const {
        return vals < rhs.vals;
    }
    std::string GetVal(int i) {return vals.at(i);}
    int Size() {return vals.size();}
    std::string ToString();

private:
    std::vector<std::string> vals;
};


#endif //PROJECT_3_INTERPRETER_TUPLE_H
