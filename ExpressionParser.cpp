#include "pch.h"
#include "ExpressionParser.h"

ExpressionParser::ExpressionParser(string expr)
    : expression(expr), pos(0), hasError(false), errorMessage("") {
}

void ExpressionParser::removeSpaces() {
    expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());
}

bool ExpressionParser::validateExpression() {
   
    // VÉRIFICATION FICHIER VIDE
  
    if (expression.empty()) {
        errorMessage = "ERREUR : Le fichier est vide !\n\nVeuillez entrer une expression logique valide.";
        hasError = true;
        return false;
    }

    // Vérifier si l'expression ne contient que des espaces/tabulations/retours à la ligne
    bool onlyWhitespace = true;
    for (char c : expression) {
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
            onlyWhitespace = false;
            break;
        }
    }
    if (onlyWhitespace) {
        errorMessage = "ERREUR : Le fichier ne contient que des espaces !\n\nVeuillez entrer une expression logique valide.";
        hasError = true;
        return false;
    }

   
    //  VÉRIFICATION DES CARACTÈRES INVALIDES
  
    for (size_t i = 0; i < expression.length(); i++) {
        char c = expression[i];

        // Caractères autorisés: lettres majuscules, parenthèses, espaces
        bool isValid = (c >= 'A' && c <= 'Z') ||
            c == '(' || c == ')' ||
            c == ' ' || c == '\t' || c == '\n' || c == '\r';

        if (!isValid) {
            errorMessage = "ERREUR : Caractère invalide détecté !\n\n";
            errorMessage += "Caractère : '";
            errorMessage += c;
            errorMessage += "'\n";
            errorMessage += "Position : ";
            errorMessage += to_string(i);
            errorMessage += "\n";
            errorMessage += "Code ASCII : ";
            errorMessage += to_string((int)c);
            errorMessage += "\n\n";

            // Messages spécifiques pour certains caractères
            if (c >= '0' && c <= '9') {
                errorMessage += "Les chiffres ne sont pas autorisés dans les expressions logiques.";
            }
            else if (c >= 'a' && c <= 'z') {
                errorMessage += "Utilisez uniquement des lettres MAJUSCULES (A-Z).";
            }
            else if (c == '&' || c == '|' || c == '!' || c == '^') {
                errorMessage += "Utilisez les opérateurs en toutes lettres :\n";
                errorMessage += "• AND pour ET logique\n";
                errorMessage += "• OR pour OU logique\n";
                errorMessage += "• XOR pour OU exclusif\n";
                errorMessage += "• NOT pour la négation";
            }
            else if (c == '+' || c == '*' || c == '-' || c == '/') {
                errorMessage += "Les opérateurs arithmétiques ne sont pas autorisés.\n";
                errorMessage += "Utilisez AND, OR, XOR, NOT.";
            }
            else {
                errorMessage += "Caractères autorisés : A-Z, AND, OR, XOR, NOT, ( )";
            }

            hasError = true;
            return false;
        }
    }

    //  VÉRIFICATION DES VARIABLES (UNIQUEMENT X, Y, Z)
 
    string tempExpr = expression;
    // Retirer les mots-clés pour ne garder que les variables
    size_t found;
    while ((found = tempExpr.find("AND")) != string::npos) {
        tempExpr.replace(found, 3, "   ");
    }
    while ((found = tempExpr.find("OR")) != string::npos) {
        tempExpr.replace(found, 2, "  ");
    }
    while ((found = tempExpr.find("XOR")) != string::npos) {
        tempExpr.replace(found, 3, "   ");
    }
    while ((found = tempExpr.find("NOT")) != string::npos) {
        tempExpr.replace(found, 3, "   ");
    }

    // Vérifier les lettres restantes (doivent être X, Y ou Z uniquement)
    for (size_t i = 0; i < tempExpr.length(); i++) {
        char c = tempExpr[i];
        if (c >= 'A' && c <= 'Z') {
            if (c != 'X' && c != 'Y' && c != 'Z') {
                errorMessage = "ERREUR : Variable invalide détectée !\n\n";
                errorMessage += "Variable trouvée : '";
                errorMessage += c;
                errorMessage += "'\n";
                errorMessage += "Position : ";
                errorMessage += to_string(i);
                errorMessage += "\n\n";
                errorMessage += "VARIABLES AUTORISÉES : X, Y, Z uniquement\n\n";
                errorMessage += "Les autres lettres (A, B, C, D, etc.) ne sont pas acceptées.";
                hasError = true;
                return false;
            }
        }
    }

   
    //  VÉRIFICATION DES PARENTHÈSES ÉQUILIBRÉES
 
    int parenthesesCount = 0;
    for (size_t i = 0; i < expression.length(); i++) {
        char c = expression[i];
        if (c == '(') parenthesesCount++;
        if (c == ')') {
            parenthesesCount--;
            if (parenthesesCount < 0) {
                errorMessage = "ERREUR : Parenthèses non équilibrées !\n\n";
                errorMessage += "Parenthèse fermante ')' sans '(' correspondant\n";
                errorMessage += "Position : ";
                errorMessage += to_string(i);
                hasError = true;
                return false;
            }
        }
    }
    if (parenthesesCount != 0) {
        errorMessage = "ERREUR : Parenthèses non équilibrées !\n\n";
        errorMessage += "Il manque ";
        errorMessage += to_string(parenthesesCount);
        errorMessage += " parenthèse(s) fermante(s) ')'";
        hasError = true;
        return false;
    }


    //  VÉRIFICATION DES OPÉRATEURS CONSÉCUTIFS
   
    if (expression.find("ANDAND") != string::npos ||
        expression.find("OROR") != string::npos ||
        expression.find("XORXOR") != string::npos ||
        expression.find("ANDOR") != string::npos ||
        expression.find("ORAND") != string::npos ||
        expression.find("ANDXOR") != string::npos ||
        expression.find("XORAND") != string::npos ||
        expression.find("ORXOR") != string::npos ||
        expression.find("XOROR") != string::npos ||
        expression.find("NOTAND") != string::npos ||
        expression.find("NOTOR") != string::npos ||
        expression.find("NOTXOR") != string::npos) {
        errorMessage = "ERREUR : Opérateurs consécutifs détectés !\n\n";
        errorMessage += "Il ne peut pas y avoir deux opérateurs binaires (AND, OR, XOR) consécutifs.\n";
        errorMessage += "Vérifiez la syntaxe de votre expression.";
        hasError = true;
        return false;
    }


    // 6. VÉRIFICATION FIN D'EXPRESSION
  
    // Retirer les espaces de fin
    string trimmedExpr = expression;
    while (!trimmedExpr.empty() && (trimmedExpr.back() == ' ' || trimmedExpr.back() == '\t' ||
        trimmedExpr.back() == '\n' || trimmedExpr.back() == '\r')) {
        trimmedExpr.pop_back();
    }

    if (trimmedExpr.length() >= 3) {
        string lastThree = trimmedExpr.substr(trimmedExpr.length() - 3);
        if (lastThree == "AND" || lastThree == "XOR" || lastThree == "NOT") {
            errorMessage = "ERREUR : Expression incomplète !\n\n";
            errorMessage += "L'expression ne peut pas se terminer par un opérateur (";
            errorMessage += lastThree;
            errorMessage += ").\n";
            errorMessage += "Ajoutez une variable ou une sous-expression après l'opérateur.";
            hasError = true;
            return false;
        }
    }
    if (trimmedExpr.length() >= 2) {
        string lastTwo = trimmedExpr.substr(trimmedExpr.length() - 2);
        if (lastTwo == "OR") {
            errorMessage = "ERREUR : Expression incomplète !\n\n";
            errorMessage += "L'expression ne peut pas se terminer par un opérateur (OR).\n";
            errorMessage += "Ajoutez une variable ou une sous-expression après l'opérateur.";
            hasError = true;
            return false;
        }
    }


    //  VÉRIFICATION DÉBUT D'EXPRESSION
 
    // Retirer les espaces de début
    size_t startPos = 0;
    while (startPos < trimmedExpr.length() &&
        (trimmedExpr[startPos] == ' ' || trimmedExpr[startPos] == '\t' ||
            trimmedExpr[startPos] == '\n' || trimmedExpr[startPos] == '\r')) {
        startPos++;
    }

    if (startPos + 3 <= trimmedExpr.length()) {
        string firstThree = trimmedExpr.substr(startPos, 3);
        if (firstThree == "AND" || firstThree == "XOR") {
            errorMessage = "ERREUR : Expression invalide !\n\n";
            errorMessage += "L'expression ne peut pas commencer par un opérateur binaire (";
            errorMessage += firstThree;
            errorMessage += ").\n";
            errorMessage += "Commencez par une variable (X, Y, Z), NOT, ou une parenthèse '('.";
            hasError = true;
            return false;
        }
    }
    if (startPos + 2 <= trimmedExpr.length()) {
        string firstTwo = trimmedExpr.substr(startPos, 2);
        if (firstTwo == "OR") {
            errorMessage = "ERREUR : Expression invalide !\n\n";
            errorMessage += "L'expression ne peut pas commencer par un opérateur binaire (OR).\n";
            errorMessage += "Commencez par une variable (X, Y, Z), NOT, ou une parenthèse '('.";
            hasError = true;
            return false;
        }
    }


    //  VÉRIFICATION PARENTHÈSES VIDES

    if (expression.find("()") != string::npos) {
        errorMessage = "ERREUR : Parenthèses vides détectées !\n\n";
        errorMessage += "Les parenthèses doivent contenir une expression valide.";
        hasError = true;
        return false;
    }

    return true;
}

LogicExpression* ExpressionParser::parse() {
    // VALIDATION AVANT LE PARSING
    if (!validateExpression()) {
        return nullptr;
    }

    LogicExpression* result = parseExpression();

    //  Vérifier si le parsing a échoué
    if (!result) {
        if (errorMessage.empty()) {
            errorMessage = "ERREUR : Erreur de syntaxe dans l'expression !\n\n";
            errorMessage += "Vérifiez que votre expression est bien formée.";
        }
        hasError = true;
        return nullptr;
    }

    // Vérifier si toute l'expression a été parsée
    if (pos < expression.length()) {
        errorMessage = "ERREUR : Expression invalide !\n\n";
        errorMessage += "Caractères non reconnus à la position ";
        errorMessage += to_string(pos);
        errorMessage += "\n\nReste à parser : '";
        errorMessage += expression.substr(pos);
        errorMessage += "'";
        hasError = true;
        delete result;
        return nullptr;
    }

    return result;
}

LogicExpression* ExpressionParser::parseExpression() {
    LogicExpression* left = parseTerm();

    if (!left) {
        if (errorMessage.empty()) {
            errorMessage = "ERREUR : Impossible de parser l'expression !";
        }
        hasError = true;
        return nullptr;
    }

    while (pos < expression.length()) {
        string op = getOperator();
        if (op.empty()) break;

        LogicExpression* right = parseTerm();
        if (!right) {
            errorMessage = "ERREUR : Opérateur '";
            errorMessage += op;
            errorMessage += "' sans opérande droite !\n\n";
            errorMessage += "Position : ";
            errorMessage += to_string(pos);
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
    // Gérer les espaces
    while (pos < expression.length() && (expression[pos] == ' ' ||
        expression[pos] == '\t' || expression[pos] == '\n' || expression[pos] == '\r')) {
        pos++;
    }

    // Gérer les parenthèses
    if (pos < expression.length() && expression[pos] == '(') {
        pos++; // Sauter '('
        LogicExpression* exp = parseExpression();

        if (!exp) {
            return nullptr;
        }

        // Gérer les espaces avant ')'
        while (pos < expression.length() && (expression[pos] == ' ' ||
            expression[pos] == '\t' || expression[pos] == '\n' || expression[pos] == '\r')) {
            pos++;
        }

        if (pos >= expression.length() || expression[pos] != ')') {
            errorMessage = "ERREUR : Parenthèse fermante ')' manquante !\n\n";
            errorMessage += "Position attendue : ";
            errorMessage += to_string(pos);
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
            errorMessage = "ERREUR : Opérateur NOT sans opérande !\n\n";
            errorMessage += "Position : ";
            errorMessage += to_string(pos);
            hasError = true;
            delete node;
            return nullptr;
        }
        return node;
    }

    // Variable simple (X, Y, Z uniquement)
    if (pos < expression.length() && isalpha(expression[pos])) {
        char varName = expression[pos];

        // Validation supplémentaire (normalement déjà faite dans validateExpression)
        if (varName != 'X' && varName != 'Y' && varName != 'Z') {
            errorMessage = "ERREUR : Variable invalide '";
            errorMessage += varName;
            errorMessage += "' !\n\n";
            errorMessage += "Seules les variables X, Y et Z sont autorisées.";
            hasError = true;
            return nullptr;
        }

        LogicExpression* node = new LogicExpression();
        node->type = "VAR";
        node->varName = varName;
        pos++;
        return node;
    }

    errorMessage = "ERREUR : Caractère invalide ou terme manquant !\n\n";
    errorMessage += "Position : ";
    errorMessage += to_string(pos);
    if (pos < expression.length()) {
        errorMessage += "\nCaractère : '";
        errorMessage += expression[pos];
        errorMessage += "'";
    }
    hasError = true;
    return nullptr;
}

string ExpressionParser::getOperator() {
    // Sauter les espaces avant l'opérateur
    while (pos < expression.length() && (expression[pos] == ' ' ||
        expression[pos] == '\t' || expression[pos] == '\n' || expression[pos] == '\r')) {
        pos++;
    }

    // Vérifier XOR AVANT OR (3 caractères)
    if (pos + 3 <= expression.length() && expression.substr(pos, 3) == "XOR") {
        pos += 3;
        return "XOR";
    }

    // Vérifier AND (3 caractères)
    if (pos + 3 <= expression.length() && expression.substr(pos, 3) == "AND") {
        pos += 3;
        return "AND";
    }

    // Vérifier OR (2 caractères) - APRÈS XOR
    if (pos + 2 <= expression.length() && expression.substr(pos, 2) == "OR") {
        pos += 2;
        return "OR";
    }

    return "";
}