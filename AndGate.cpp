// AndGate.cpp
#include "pch.h"
#include "GraphicsUtils.h"
#include "AndGate.h"

AndGate::AndGate()
{
    entre1 = false;
    entre2 = false;
    sortie = false;
    inputGate1 = nullptr;
    inputGate2 = nullptr;
    isInput1Variable = false;
    isInput2Variable = false;
}

void AndGate::setStartPoint(CPoint pt)
{
    startPoint = pt;
    int gateHeight = 100;
    int gateWidthRect = 60;
    int arcRadius = 50;
    outputPoint = CPoint(startPoint.x + gateWidthRect + arcRadius, startPoint.y + gateHeight / 2);
    inputPoint1 = CPoint(startPoint.x, startPoint.y + 22);
    inputPoint2 = CPoint(startPoint.x, startPoint.y + 66);
}

void AndGate::draw(CClientDC& dc)
{
    // ... ton code de dessin existant ...
    int gateHeight = 100;
    int gateWidthRect = 60;
    int arcRadius = 50;

    dc.MoveTo(startPoint.x, startPoint.y + gateHeight);
    dc.LineTo(startPoint.x, startPoint.y);
    dc.LineTo(startPoint.x + gateWidthRect, startPoint.y);
    dc.MoveTo(startPoint.x, startPoint.y + gateHeight);
    dc.LineTo(startPoint.x + gateWidthRect, startPoint.y + gateHeight);

    int ellipseLeft = startPoint.x + (gateWidthRect - arcRadius);
    int ellipseTop = startPoint.y;
    int ellipseRight = startPoint.x + gateWidthRect + arcRadius;
    int ellipseBottom = startPoint.y + gateHeight;
    CPoint arcPtHaut(startPoint.x + gateWidthRect, startPoint.y);
    CPoint arcPtBas(startPoint.x + gateWidthRect, startPoint.y + gateHeight);
    dc.Arc(ellipseLeft, ellipseTop, ellipseRight, ellipseBottom,
        arcPtBas.x, arcPtBas.y, arcPtHaut.x, arcPtHaut.y);

    CString label = _T("&");
    CFont font;
    font.CreatePointFont(160, _T("Arial Bold"));
    CFont* oldFont = dc.SelectObject(&font);
    int textX = startPoint.x + gateWidthRect / 2 + 10;
    int textY = startPoint.y + (gateHeight / 2) - 20;
    dc.SetBkMode(TRANSPARENT);
    dc.TextOutW(textX, textY, label);
    dc.SelectObject(oldFont);


  
 
}

// Getters/Setters
bool AndGate::getEntre1() const { return entre1; }
bool AndGate::getEntre2() const { return entre2; }
bool AndGate::getSortie() const { return sortie; }
void AndGate::setEntre1(bool val) { entre1 = val; }
void AndGate::setEntre2(bool val) { entre2 = val; }
CPoint AndGate::getOutputPoint() const { return outputPoint; }
CPoint AndGate::getInputPoint1() const { return inputPoint1; }
CPoint AndGate::getInputPoint2() const { return inputPoint2; }

// NOUVELLES MÉTHODES
void AndGate::connectInput1Gate(AndGate* gate) {
    inputGate1 = gate;
    isInput1Variable = false;
}

void AndGate::connectInput2Gate(AndGate* gate) {
    inputGate2 = gate;
    isInput2Variable = false;
}

void AndGate::setInput1AsVariable(bool val) {
    isInput1Variable = true;
    entre1 = val;
}

void AndGate::setInput2AsVariable(bool val) {
    isInput2Variable = true;
    entre2 = val;
}

void AndGate::computeSortie()
{
    sortie = entre1 && entre2;
}

// ÉVALUATION RÉCURSIVE
bool AndGate::evaluate()
{
    // Si entrée 1 n'est pas une variable, récupérer depuis la porte connectée
    if (!isInput1Variable && inputGate1 != nullptr) {
        entre1 = inputGate1->evaluate();
    }

    // Si entrée 2 n'est pas une variable, récupérer depuis la porte connectée
    if (!isInput2Variable && inputGate2 != nullptr) {
        entre2 = inputGate2->evaluate();
    }

    // Calculer la sortie
    computeSortie();

    return sortie;
}