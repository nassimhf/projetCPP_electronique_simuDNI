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

    // Parser une expression compl�te
    LogicExpression* parseExpression();

    // Parser un terme (variable, NOT, ou parenth�se)
    LogicExpression* parseTerm();

    // Extraire l'op�rateur
    string getOperator();

public:
    ExpressionParser(string expr);
    LogicExpression* parse();
};

#endif // EXPRESSION_PARSER_H