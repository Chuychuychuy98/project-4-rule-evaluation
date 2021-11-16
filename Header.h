//
// Created by Chandler Rowe on 10/26/21.
//

#ifndef PROJECT_3_INTERPRETER_HEADER_H
#define PROJECT_3_INTERPRETER_HEADER_H
#include <vector>
#include <string>

class Header {
public:
    Header(std::vector<std::string> attr) : attr(std::move(attr)) {};
    void AddVal(const std::string &toAdd);
    bool RemVal(int index);
    bool operator< (const Header &rhs) const {
        return attr < rhs.attr;
    }
    std::string GetVal(int i) {return attr.at(i);}
    int Size() {return attr.size();}

private:
    std::vector<std::string> attr;
};


#endif //PROJECT_3_INTERPRETER_HEADER_H
