//
// Created by Chandler Rowe on 10/26/21.
//

#include "Interpreter.h"

void Interpreter::Interpret() {
    std::cout << "Rule Evaluation" << std::endl;
    int beforeTups;
    int afterTups;
    int passes = 0;
    do {
        beforeTups = database->NumTups();
        for (Rule *rule : program->GetRules()) {
            std::cout << rule->ToString() << std::endl;
            Relation r = EvaluateRule(rule);
        }
        afterTups = database->NumTups();
        passes++;
    } while (beforeTups != afterTups);
    std::cout << std::endl;
    std::cout << "Schemes populated after " << passes << " passes through the Rules." << std::endl << std::endl;
    std::cout << "Query Evaluation" << std::endl;
    for (Predicate* query : program->GetQueries()) {
        Relation r = EvaluatePredicate(query);
        std::string myString;
        std::cout << query->ToString() << "? ";
        std::cout << r.GetAnswer();
        std::cout << r.ToStringTups();
    }
}


Relation Interpreter::EvaluatePredicate(Predicate* p) {
    std::map<std::string, int> vars;
    std::vector<std::string> varNames;
    std::vector<int> varLocs;
    //Step 1: Get Relation with the same name as the predicate
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
        }
    }
    // Project & Rename
    r = r.Project(varLocs);
    r = r.Rename(varNames);
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

std::vector<std::string> Interpreter::GetDBNames(Rule* r) {
    std::vector<std::string> names;
    for (Parameter* param : r->GetHead()->GetParameters()) {
        for (Predicate* pred : r->GetPredicates()) {
            for (int i = 0; i < pred->GetParameters().size(); ++i) {
                if (param->GetId() == pred->GetParameters().at(i)->GetId()) {
                    bool found = false;
                    for (std::string s : names) {
                        if (s == database->GetRelation(pred->GetId())->GetHeader().GetVal(i)) {
                            found = true;
                        }
                    }
                    if (!found) {
                        names.push_back(database->GetRelation(pred->GetId())->GetHeader().GetVal(i));
                    }
                }
            }
        }
    }
    return names;
}

Relation Interpreter::EvaluateRule(Rule *r) {
    std::vector<Relation> rels;
    std::vector<std::string> names = GetDBNames(r);
    //Step 1: Create relations for each predicate
    for (Predicate* p : r->GetPredicates()) {
        rels.push_back(EvaluatePredicate(p));
    }

    //Step 2: Join the applicable relations
    Relation rel = rels.at(0);
    if (rels.size() > 1) {
        for (int i = 1; i < rels.size(); ++i) {
            rel = rel.Join(rels.at(i));
        }
    }
    //Step 3: Project to remove unnecessary columns/reorder
    std::vector<int> indices;
    std::vector<std::string> newAttr;
    for (int i = 0; i < r->GetHead()->GetParameters().size(); ++i) {
        for (int j = 0; j < rel.GetHeader().Size(); ++j) {
            if (rel.GetHeader().GetVal(j) == r->GetHead()->GetParameters().at(i)->GetId()) {
                indices.push_back(j);
            }
        }
    }
    rel = rel.Project(indices);

    //Step 4: Rename the columns to match the main database relation
    rel = rel.Rename(names);
    database->GetRelation(r->GetHead()->GetId())->Unionize(rel);
    return rel;
}