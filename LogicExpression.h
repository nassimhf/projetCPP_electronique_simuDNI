// LogicExpression.h
#ifndef LOGIC_EXPRESSION_H
#define LOGIC_EXPRESSION_H

#include <string>
#include "pch.h"
using namespace std;



// Structure pour représenter une expression logique
class LogicExpression {
public:
    string type;            // "AND", "OR", "XOR", "NOT", "VAR"
    string varName;         // Si c'est une variable: "A", "B", "C"...
    LogicExpression* left;  // Opérande gauche
    LogicExpression* right; // Opérande droite
    bool isNegated;         // Si précédé de NOT
	bool result;        // Résultat de l'évaluation

    LogicExpression();
    ~LogicExpression();
};

#endif // LOGIC_EXPRESSION_H