//
// Created by Chandler Rowe on 9/22/21.
//

#ifndef PROJECT_2_PARSER_PARAMETER_H
#define PROJECT_2_PARSER_PARAMETER_H
#include <string>

class Parameter {
public:
    Parameter() = default;
    Parameter(std::string id, bool isConst) : id(move(id)), isConst(isConst) {}
    std::string GetId() const {return id;}
    bool IsConst() const {return isConst;}
private:
    std::string id;
    bool isConst;
};


#endif //PROJECT_2_PARSER_PARAMETER_H
