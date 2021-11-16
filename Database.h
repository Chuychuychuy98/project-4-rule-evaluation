//
// Created by Chandler Rowe on 10/26/21.
//

#ifndef PROJECT_3_INTERPRETER_DATABASE_H
#define PROJECT_3_INTERPRETER_DATABASE_H
#include <set>
#include <map>
#include "Relation.h"
class Database {
public:
    Database() = default;
    void AddRelation(std::string name, Relation *rel) {
        //relations.insert(rel);
        relations.insert(std::pair<std::string, Relation*>(name, rel));
    }
    bool ContainsRelation(const std::string &name) {return relations.find(name) != relations.end();}
    void RemoveRelation(const std::string &name) {relations.erase(name);}
    Relation* GetRelation(const std::string &name) {return relations.at(name);}
    std::map<std::string, Relation*> GetRelations() {return relations;}

private:
    //std::set<Relation*> relations;
    std::map<std::string, Relation*> relations;
};


#endif //PROJECT_3_INTERPRETER_DATABASE_H
