// LogicExpression.cpp
#include "pch.h"
#include "LogicExpression.h"

LogicExpression::LogicExpression()
    : left(nullptr), right(nullptr), isNegated(false), type(""), varName("") {
}

LogicExpression::~LogicExpression() {
    // Libérer la mémoire récursivement
    if (left) {
        delete left;
        left = nullptr;
    }
    if (right) {
        delete right;
        right = nullptr;
    }
}