// ExpressionParser.h
#ifndef EXPRESSION_PARSER_H


#include <string>
#include <algorithm>
#include "LogicExpression.h"
using namespace std;

class ExpressionParser {
private:
    string expression;
    size_t pos;
    string errorMessage;  // ✅ NOUVEAU : stocker le message d'erreur
    bool hasError;        // ✅ NOUVEAU : indicateur d'erreur

    void removeSpaces();
    LogicExpression* parseExpression();
    LogicExpression* parseTerm();
    string getOperator();
    bool validateExpression();  // ✅ NOUVEAU : validation

public:
    ExpressionParser(string expr);
    LogicExpression* parse();
    bool isValid() const { return !hasError; }  // ✅ NOUVEAU
    string getError() const { return errorMessage; }  // ✅ NOUVEAU
};

#endif // EXPRESSION_PARSER_H