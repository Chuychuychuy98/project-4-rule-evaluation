//
// Created by Chandler Rowe on 10/26/21.
//

#ifndef PROJECT_3_INTERPRETER_RELATION_H
#define PROJECT_3_INTERPRETER_RELATION_H
#include <set>
#include "Tuple.h"
#include "Header.h"


class Relation {
public:
    Relation(std::string name, Header header) : header(header), name(name) {}
    Relation(const Relation& r) : tuples(r.tuples), header(r.header), name(r.name) {}
    void AddTuple(Tuple tup) {if (tup.Size() == header.Size()) tuples.insert(tup);}
    Relation Select(int i, std::string val);
    Relation Select(int i, int j);
    std::string ToString();
    std::string ToStringHeader();
    std::string ToStringTups();
    std::string GetAnswer();
    Relation Project(std::vector<int> indices); // list of indices
    Relation Rename(std::vector<std::string> newAttr); // list of attributes

private:
    std::set<Tuple> tuples;
    Header header;
    std::string name;
};


#endif //PROJECT_3_INTERPRETER_RELATION_H
