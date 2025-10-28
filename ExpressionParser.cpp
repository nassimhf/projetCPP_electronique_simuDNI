
#include "pch.h"
#include "ExpressionParser.h"

ExpressionParser::ExpressionParser(string expr) : expression(expr), pos(0) {
    removeSpaces();
}

void ExpressionParser::removeSpaces() {

    expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());
}

LogicExpression* ExpressionParser::parse() {
    return parseExpression();
}

LogicExpression* ExpressionParser::parseExpression() {
    LogicExpression* left = parseTerm();

    // Chercher les opérateurs binaires (AND, OR, XOR)
    while (pos < expression.length()) {
        string op = getOperator();
        if (op.empty()) break;

        LogicExpression* node = new LogicExpression();
        node->type = op;
        node->left = left;
        node->right = parseTerm();
        left = node;
    }

    return left;
}

LogicExpression* ExpressionParser::parseTerm() {
    // Gérer les parenthèses
    if (pos < expression.length() && expression[pos] == '(') {
        pos++; // Sauter '('
        LogicExpression* exp = parseExpression();
        if (pos < expression.length() && expression[pos] == ')') {
            pos++; // Sauter ')'
        }
        return exp;
    }

    // Gérer NOT
    if (pos + 3 <= expression.length() && expression.substr(pos, 3) == "NOT") {
        pos += 3;
        LogicExpression* node = new LogicExpression();
        node->type = "NOT";
        node->left = parseTerm();
        return node;
    }

    // Variable simple (A, B, C, etc.)
    if (pos < expression.length()) {
        LogicExpression* node = new LogicExpression();
        node->type = "VAR";
        node->varName = expression[pos];
        pos++;
        return node;
    }

    return nullptr;
}

string ExpressionParser::getOperator() {
    if (pos + 3 <= expression.length() && expression.substr(pos, 3) == "AND") {
        pos += 3;
        return "AND";
    }
    if (pos + 2 <= expression.length() && expression.substr(pos, 2) == "OR") {
        pos += 2;
        return "OR";
    }
    if (pos + 3 <= expression.length() && expression.substr(pos, 3) == "XOR") {
        pos += 3;
        return "XOR";
    }
    return "";
}