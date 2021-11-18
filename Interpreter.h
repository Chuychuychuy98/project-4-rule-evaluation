//
// Created by Chandler Rowe on 10/26/21.
//

#ifndef PROJECT_3_INTERPRETER_INTERPRETER_H
#define PROJECT_3_INTERPRETER_INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"
#include <set>
#include <tuple>

class Interpreter {
public:
    Interpreter(DatalogProgram *program) : program(program) {
        for (Predicate* scheme : program->GetSchemes()) {
            AddScheme(scheme);
        }
        for (Predicate* fact : program->GetFacts()) {
            AddFact(fact);
        }
    }
    std::string ToString();
    void Interpret();
    Relation EvaluatePredicate(Predicate* p);
    Relation EvaluateRule(Rule* r);

private:
    DatalogProgram *program;
    Database *database = new Database();
    void AddScheme(Predicate* scheme);
    void AddFact(Predicate* fact);
    std::vector<std::string> GetDBNames(Rule* r);
};


#endif //PROJECT_3_INTERPRETER_INTERPRETER_H
