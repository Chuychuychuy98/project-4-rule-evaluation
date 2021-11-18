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
                toReturn += ", ";
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
    Relation r(name, Header(vals));

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

Relation Relation::Join(Relation r) {
    Header newHeader = CombineHeaders(r.header);
    Relation newRelation(name, newHeader);
    for (auto t1 : tuples) {
        for (auto t2 : r.tuples) {
            if (IsJoinable(t1, t2, r.header)) {
                newRelation.AddTuple(CombineTuples(t1, t2, r.header));
            }
        }
    }
    return newRelation;
}
Header Relation::CombineHeaders(Header h2) {
    std::vector<std::string> newAttr;
    for (int i = 0; i < header.Size(); ++i) {
        newAttr.push_back(header.GetVal(i));
    }
    for (int i = 0; i < h2.Size(); ++i) {
        bool shouldAdd = true;
        for (auto s : newAttr) {
            if (s == h2.GetVal(i)) {
                shouldAdd = false;
            }
        }
        if (shouldAdd) {
            newAttr.push_back(h2.GetVal(i));
        }
    }
    return Header(newAttr);
}

bool Relation::IsJoinable(Tuple t1, Tuple t2, Header h2) {

    for (int i = 0; i < header.Size(); ++i) { // For each element in header 1
        for (int j = 0; j < h2.Size(); ++j) { // For each element in header 2
            if (header.GetVal(i) == h2.GetVal(j)) { // If the headers match:
                if (t1.GetVal(i) != t2.GetVal(j)) { // If the values in each tuple don't match
                    return false; // They can't be joined
                }
            }
        }
    } //If you make it all the way through:
    return true; // They can be joined
}

Tuple Relation::CombineTuples(Tuple t1, Tuple t2, Header h2) {
    Tuple newTuple;
    for (int i = 0; i < header.Size(); ++i) {
        newTuple.AddVal(t1.GetVal(i));
    }
    for (int i = 0; i < h2.Size(); ++i) {
        bool isUnique = true;
        for (int j = 0; j < header.Size(); ++j) {
            if (h2.GetVal(i) == header.GetVal(j)) {
                isUnique = false;
                break;
            }
        }
        if (isUnique) {
            newTuple.AddVal(t2.GetVal(i));
        }
    }

    return newTuple;
}

void Relation::Unionize(Relation r) {
    for (Tuple t : r.tuples) {
        if (tuples.insert(t).second) {
            std::cout << "  ";
            for (int i = 0; i < header.Size(); ++i) {
                std::cout << header.GetVal(i) << "=" << t.GetVal(i);
                if (i < header.Size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
    }
}