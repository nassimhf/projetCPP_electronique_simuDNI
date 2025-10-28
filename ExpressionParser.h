// ExpressionParser.h
#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include <string>
#include <algorithm>
#include "LogicExpression.h"
using namespace std;

// Classe pour parser les expressions logiques
class ExpressionParser {
private:
    string expression;
    int pos;

    // Enlever les espaces
    void removeSpaces();

    // Parser une expression complète
    LogicExpression* parseExpression();

    // Parser un terme (variable, NOT, ou parenthèse)
    LogicExpression* parseTerm();

    // Extraire l'opérateur
    string getOperator();

public:
    ExpressionParser(string expr);
    LogicExpression* parse();
};

#endif // EXPRESSION_PARSER_H