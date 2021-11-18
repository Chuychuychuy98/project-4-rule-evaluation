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
    Relation Join(Relation r);
    void Unionize(Relation r); // maybe this should return a relation? not sure yet
    std::string ToString();
    std::string ToStringHeader();
    std::string ToStringTups();
    std::string GetAnswer();
    Relation Project(std::vector<int> indices); // list of indices
    Relation Rename(std::vector<std::string> newAttr); // list of attributes
    Header GetHeader() {return header;}
    int Size() {return tuples.size();}

private:
    std::set<Tuple> tuples;
    Header header;
    std::string name;
    Header CombineHeaders(Header h2);
    bool IsJoinable(Tuple t1, Tuple t2, Header h2);
    Tuple CombineTuples(Tuple t1, Tuple t2, Header h2);
};


#endif //PROJECT_3_INTERPRETER_RELATION_H
