//
// Created by Chandler Rowe on 10/26/21.
//

#include "Relation.h"

std::string Relation::ToString() {
    std::string toReturn = ToStringHeader();
    toReturn += ToStringTups();
    return toReturn;
}

std::string Relation::GetAnswer() {
    std::string toReturn;
    if (tuples.empty()) {
        toReturn += "No\n";
        return toReturn;
    }
    toReturn += "Yes(" + std::to_string(tuples.size()) + ")\n";
    return toReturn;
}

std::string Relation::ToStringHeader() {
    std::string toReturn = name + "(";
    for (int i = 0; i < header.Size(); ++i) {
        toReturn += header.GetVal(i);
        if (i < header.Size() - 1) {
            toReturn += ",";
        }
    }
    toReturn += ")? ";

    toReturn += GetAnswer();
    return toReturn;
}

std::string Relation::ToStringTups() {
    std::string toReturn;
    for (auto tup : tuples) {
        if (tup.Size() == 0) {
            break;
        }
        toReturn += "  ";
        for (int i = 0; i < tup.Size(); ++i) {
            toReturn += header.GetVal(i) + "=" + tup.GetVal(i);
            if (i < tup.Size() - 1) {
                toReturn += ",";
            }
        }
        toReturn += "\n";
    }

    return toReturn;
}

Relation Relation::Select(int i, std::string val) {
    Relation newRel(name, header);
    for (Tuple tup : tuples) {
        if (tup.GetVal(i) == val) {
            newRel.AddTuple(tup);
        }
    }
    return newRel;
}
Relation Relation::Select(int i, int j) {
    Relation newRel(name, header);
    for (Tuple tup : tuples) {
        if (tup.GetVal(i) == tup.GetVal(j)) {
            newRel.AddTuple(tup);
        }
    }
    return newRel;
}

Relation Relation::Project(std::vector<int> indices) {
    std::vector<std::string> vals;
    for (int i : indices) {
        vals.push_back(header.GetVal(i));
    }
    Header newHead(vals);
    Relation r(name, newHead);

    for (Tuple tup : tuples) {
        Tuple newTup;
        for (int i : indices) {
            newTup.AddVal(tup.GetVal(i));
        }
        r.AddTuple(newTup);
    }
    return r;
}

Relation Relation::Rename(std::vector<std::string> newAttr) {

    Header newHeader(newAttr);
    Relation r(name, newHeader);
    for (auto t : tuples) {
        r.AddTuple(t);
    }
    return r;
}
