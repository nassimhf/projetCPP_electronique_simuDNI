#include "pch.h"
#include "ExpressionParser.h"

ExpressionParser::ExpressionParser(string expr)
    : expression(expr), pos(0), hasError(false), errorMessage("") {
    

}

void ExpressionParser::removeSpaces() {
    expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());
}

bool ExpressionParser::validateExpression() {
    // Vérifier si l'expression est vide
    if (expression.empty()) {
        errorMessage = "L'expression est vide !";
        hasError = true;
        return false;
    }

    // Vérifier les parenthèses équilibrées
    int parenthesesCount = 0;
    for (char c : expression) {
        if (c == '(') parenthesesCount++;
        if (c == ')') parenthesesCount--;
        if (parenthesesCount < 0) {
            errorMessage = "Parenthèses non équilibrées : ')' sans '(' correspondant !";
            hasError = true;
            return false;
        }
    }
    if (parenthesesCount != 0) {
        errorMessage = "Parenthèses non équilibrées : '(' sans ')' correspondant !";
        hasError = true;
        return false;
    }

    // Vérifier les opérateurs consécutifs (AND AND, OR OR, etc.)
    if (expression.find("ANDAND") != string::npos ||
        expression.find("OROR") != string::npos ||
        expression.find("XORXOR") != string::npos ||
        expression.find("ANDOR") != string::npos ||
        expression.find("ORAND") != string::npos ||
        expression.find("ANDXOR") != string::npos ||
        expression.find("XORAND") != string::npos ||
        expression.find("ORXOR") != string::npos ||
        expression.find("XOROR") != string::npos) {
        errorMessage = "Opérateurs consécutifs détectés !";
        hasError = true;
        return false;
    }

    // Vérifier que l'expression ne se termine pas par un opérateur
    if (expression.length() >= 3) {
        string lastThree = expression.substr(expression.length() - 3);
        if (lastThree == "AND" || lastThree == "XOR") {
            errorMessage = "L'expression ne peut pas se terminer par un opérateur (AND/XOR) !";
            hasError = true;
            return false;
        }
    }
    if (expression.length() >= 2) {
        string lastTwo = expression.substr(expression.length() - 2);
        if (lastTwo == "OR") {
            errorMessage = "L'expression ne peut pas se terminer par un opérateur (OR) !";
            hasError = true;
            return false;
        }
    }

    // Vérifier que l'expression ne commence pas par un opérateur binaire
    if (expression.length() >= 3) {
        string firstThree = expression.substr(0, 3);
        if (firstThree == "AND" || firstThree == "XOR") {
            errorMessage = "L'expression ne peut pas commencer par un opérateur binaire (AND/XOR) !";
            hasError = true;
            return false;
        }
    }
    if (expression.length() >= 2) {
        string firstTwo = expression.substr(0, 2);
        if (firstTwo == "OR") {
            errorMessage = "L'expression ne peut pas commencer par un opérateur binaire (OR) !";
            hasError = true;
            return false;
        }
    }

    return true;
}

LogicExpression* ExpressionParser::parse() {
    // ✅ VALIDATION AVANT LE PARSING
    if (!validateExpression()) {
        return nullptr;
    }

    LogicExpression* result = parseExpression();

    // ✅ Vérifier si le parsing a échoué
    if (!result) {
        if (errorMessage.empty()) {
            errorMessage = "Erreur de syntaxe dans l'expression !";
        }
        hasError = true;
        return nullptr;
    }

    // ✅ Vérifier si toute l'expression a été parsée
    if (pos < expression.length()) {
        errorMessage = "Expression invalide : caractères non reconnus à la position " + to_string(pos);
        hasError = true;
        delete result;
        return nullptr;
    }

    return result;
}

LogicExpression* ExpressionParser::parseExpression() {
    LogicExpression* left = parseTerm();

    if (!left) {
        errorMessage = "Erreur lors du parsing d'un terme !";
        hasError = true;
        return nullptr;
    }

    while (pos < expression.length()) {
        string op = getOperator();
        if (op.empty()) break;

        LogicExpression* right = parseTerm();
        if (!right) {
            errorMessage = "Opérateur '" + op + "' sans opérande droite !";
            hasError = true;
            delete left;
            return nullptr;
        }

        LogicExpression* node = new LogicExpression();
        node->type = op;
        node->left = left;
        node->right = right;
        left = node;
    }

    return left;
}

LogicExpression* ExpressionParser::parseTerm() {


    //gere les espaces
    while (pos < expression.length() && expression[pos] == ' ') {
        pos++;
    }


    // Gérer les parenthèses
    if (pos < expression.length() && expression[pos] == '(') {
        pos++; // Sauter '('
        LogicExpression* exp = parseExpression();

        if (!exp) {
            return nullptr;
        }

        if (pos >= expression.length() || expression[pos] != ')') {
            errorMessage = "Parenthèse fermante ')' manquante !";
            hasError = true;
            delete exp;
            return nullptr;
        }
        pos++; // Sauter ')'
        return exp;
    }

    // Gérer NOT
    if (pos + 3 <= expression.length() && expression.substr(pos, 3) == "NOT") {
        pos += 3;
        LogicExpression* node = new LogicExpression();
        node->type = "NOT";
        node->left = parseTerm();

        if (!node->left) {
            errorMessage = "Opérateur NOT sans opérande !";
            hasError = true;
            delete node;
            return nullptr;
        }
        return node;
    }

    // Variable simple (X, Y, Z, A, B, C, etc.)
    if (pos < expression.length() && isalpha(expression[pos])) {
        LogicExpression* node = new LogicExpression();
        node->type = "VAR";
        node->varName = expression[pos];
        pos++;
        return node;
    }

    errorMessage = "Caractère invalide ou terme manquant à la position " + to_string(pos);
    hasError = true;
    return nullptr;
}

string ExpressionParser::getOperator() {
   
    // Sauter les espaces avant l'opérateur
    while (pos < expression.length() && expression[pos] == ' ') {
        pos++;
    }


    // Vérifier XOR AVANT OR (3 caractères)
    if (pos + 3 <= expression.length() && expression.substr(pos, 3) == "XOR") {
        OutputDebugStringA("-> Trouvé XOR\n");
        pos += 3;
        return "XOR";
    }

    // Vérifier AND (3 caractères)
    if (pos + 3 <= expression.length() && expression.substr(pos, 3) == "AND") {
        OutputDebugStringA("-> Trouvé AND\n");
        pos += 3;
        return "AND";
    }

    // Vérifier OR (2 caractères) - APRÈS XOR
    if (pos + 2 <= expression.length() && expression.substr(pos, 2) == "OR") {
        OutputDebugStringA("-> Trouvé OR\n");
        pos += 2;
        return "OR";
    }

    OutputDebugStringA("-> Aucun opérateur trouvé\n");
    return "";
}