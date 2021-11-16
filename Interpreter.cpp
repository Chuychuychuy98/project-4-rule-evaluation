//
// Created by Chandler Rowe on 10/26/21.
//

#include "Interpreter.h"

void Interpreter::Interpret() {
    for (Predicate* query : program->GetQueries()) {
        Relation r = EvaluatePredicate(query);
        std::string myString;
        std::cout << query->ToString() << "? ";
        std::cout << r.GetAnswer();
        std::cout << r.ToStringTups();
//        myString += query->ToString();
//        myString += "? ";
//        myString += r.GetAnswer();
//        myString += r.ToStringTups();
    }
}

Relation Interpreter::EvaluatePredicate(Predicate* p) {
    std::map<std::string, int> vars;
    std::vector<std::string> varNames;
    std::vector<int> varLocs;
    //Step 1: Get Relation
    Relation r(*(database->GetRelation(p->GetId())));
    //std::cout << "Evaluating Query:\n\tCurrent state of table:\n" << r->ToString();
    //Step 2: For each parameter...
    for (unsigned int i = 0; i < p->GetParameters().size(); ++i) {
        Parameter* para = p->GetParameters().at(i);
        // Step 3: Select for each constant
        if (para->IsConst()) {
            r = r.Select(i, para->GetId());
            //std::cout << "\tState of table after selecting for " << para->GetId() << ":\n" << r->ToString();
        }
        // Step 4: Select for each matching variable
        else if (vars.find(para->GetId()) != vars.end()) {
            r = r.Select(vars.at(para->GetId()), i);
            //std::cout << "\tState of table after selecting for matching " << para->GetId() << " at " << i << ":\n" << r->ToString();
        }
        //Step 5: Add new variables to map
        else {
            vars.insert(std::pair<std::string, int>(para->GetId(), i));
            varNames.push_back(para->GetId());
            varLocs.push_back(i);
            //std::cout << "\t" << para->GetId() << " found at " << i << "\n";
        }
    }
    //std::cout << "\tFinal state of table before project:\n" << r->ToString();
    r = r.Project(varLocs);
    //std::cout << "\tState after project:\n" << r->ToString();
    r = r.Rename(varNames);
    //std::cout << "\tFinal state:\n" << r->ToString();
    return r;

}

void Interpreter::AddScheme(Predicate* scheme) {
    std::vector<std::string> vals;
    for (const Parameter* para : scheme->GetParameters()) {
        vals.push_back(para->GetId());
    }
    database->AddRelation(scheme->GetId(), new Relation(scheme->GetId(), Header(vals)));
}
void Interpreter::AddFact(Predicate* fact) {
    Tuple t;
    for (const Parameter* para : fact->GetParameters()) {
        t.AddVal(para->GetId());
    }
    database->GetRelation(fact->GetId())->AddTuple(t);
}

std::string Interpreter::ToString() {
    std::string toReturn;
    for (auto rel : database->GetRelations()) {
        toReturn += rel.second->ToString() + "\n";
    }
    return toReturn;
}