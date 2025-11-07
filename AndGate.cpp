// AndGate.cpp
#include "pch.h"
#include "GraphicsUtils.h"
#include "AndGate.h"
#include "Colors.h"

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

}

void AndGate::draw(CClientDC& dc, float scale)
{
    const int baseHeight = 100;
    const int baseWidthRect = 60;
    const int baseArcRadius = 50;

    // --- Dimensions échelonnées ---
    int gateHeight = int(baseHeight * scale);
    int gateWidthRect = int(baseWidthRect * scale);
    int arcRadius = int(baseArcRadius * scale);

    // --- Création du pinceau et du stylo ---
    CBrush fillBrush(APP_COLOR_GATE_FILL);
    CPen borderPen(PS_SOLID, int(1 * scale), APP_COLOR_GATE_BORDER); // épaisseur proportionnelle
    CBrush* oldBrush = dc.SelectObject(&fillBrush);
    CPen* oldPen = dc.SelectObject(&borderPen);

    // --- 1. Corps rectangulaire gauche ---
    dc.MoveTo(startPoint.x, startPoint.y + gateHeight);
    dc.LineTo(startPoint.x, startPoint.y);
    dc.LineTo(startPoint.x + gateWidthRect, startPoint.y);
    dc.MoveTo(startPoint.x, startPoint.y + gateHeight);
    dc.LineTo(startPoint.x + gateWidthRect, startPoint.y + gateHeight);

    // --- 2. Arc de droite ---
    int ellipseLeft = startPoint.x + (gateWidthRect - arcRadius);
    int ellipseTop = startPoint.y;
    int ellipseRight = startPoint.x + gateWidthRect + arcRadius;
    int ellipseBottom = startPoint.y + gateHeight;

    CPoint arcPtHaut(startPoint.x + gateWidthRect, startPoint.y);
    CPoint arcPtBas(startPoint.x + gateWidthRect, startPoint.y + gateHeight);

    dc.Arc(ellipseLeft, ellipseTop, ellipseRight, ellipseBottom,
        arcPtBas.x, arcPtBas.y, arcPtHaut.x, arcPtHaut.y);

    // --- 3. Points d’entrée et de sortie (proportionnels à la taille) ---
    inputPoint1 = CPoint(startPoint.x, startPoint.y + int(gateHeight * 0.25)); // entrée 1 à 25%
    inputPoint2 = CPoint(startPoint.x, startPoint.y + int(gateHeight * 0.75)); // entrée 2 à 75%
    outputPoint = CPoint(startPoint.x + gateWidthRect + arcRadius, startPoint.y + int(gateHeight * 0.5)); // sortie au centre

    // --- 4. Texte sur les entrées ---
    CFont font;
    font.CreatePointFont(int(100 * scale), _T("Arial"));
    CFont* oldFont = dc.SelectObject(&font);
    dc.SetBkMode(TRANSPARENT);

    CString input1(entre1 ? "1" : "0");
    dc.SetTextColor(entre1 ? APP_COLOR_HIGH : APP_COLOR_LOW);
    dc.TextOut(inputPoint1.x - int(26 * scale), inputPoint1.y - int(20 * scale), input1);

    CString input2(entre2 ? "1" : "0");
    dc.SetTextColor(entre2 ? APP_COLOR_HIGH : APP_COLOR_LOW);
    dc.TextOut(inputPoint2.x - int(26 * scale), inputPoint2.y - int(20 * scale), input2);

    dc.SelectObject(oldFont);

    // --- 5. (Optionnel) Fil de sortie ---
    // dc.MoveTo(outputPoint);
    // dc.LineTo(outputPoint.x + int(20 * scale), outputPoint.y);

    // --- Restauration des objets GDI ---
    dc.SelectObject(oldPen);
    dc.SelectObject(oldBrush);
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