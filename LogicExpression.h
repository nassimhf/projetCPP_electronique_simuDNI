// LogicExpression.h
#ifndef LOGIC_EXPRESSION_H
#define LOGIC_EXPRESSION_H

#include <string>
#include "pch.h"
using namespace std;



// Structure pour repr�senter une expression logique
class LogicExpression {
public:
    string type;            // "AND", "OR", "XOR", "NOT", "VAR"
    string varName;         // Si c'est une variable: "A", "B", "C"...
    LogicExpression* left;  // Op�rande gauche
    LogicExpression* right; // Op�rande droite
    bool isNegated;         // Si pr�c�d� de NOT
	bool result;        // R�sultat de l'�valuation

    LogicExpression();
    ~LogicExpression();
};

#endif // LOGIC_EXPRESSION_H