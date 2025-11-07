

#include <afxwin.h>
#include "pch.h"
#include "OrGate.h"
#include "GraphicsUtils.h"
#include "Colors.h"

OrGate::OrGate()
{
    entre1 = false;
    entre2 = false;
    sortie = false;
    inputGate1 = nullptr;
    inputGate2 = nullptr;
    isInput1Variable = false;
    isInput2Variable = false;
}
void OrGate::setStartPoint(CPoint pt)
{
    startPoint = pt;
}




void OrGate::draw(CClientDC& dc,float scale)
{
    // DIMENSIONS GLOBALES POUR LA PORTE OR:
    // Largeur totale: ~95 px (augmentée)
    // Hauteur totale: 88 px (augmentée)
    // La porte OR est composée de:
    // 1. Une courbe d'entrée (côté gauche) - petit arc convexe
    // 2. Deux courbes de sortie (haut et bas) - arcs qui se rejoignent à droite

    // --- 1. Dessiner la courbe d'entrée (côté gauche) ---
    // Petit arc convexe qui forme l'entrée de la porte OR
    // Rectangle englobant pour l'arc d'entrée (largeur ~36px)
    int width = int(95 * scale);
    int height = int(88 * scale);

    // --- 1. Arc d'entrée (côté gauche) ---
    int inputArcLeft = startPoint.x - int(18 * scale);
    int inputArcTop = startPoint.y;
    int inputArcRight = startPoint.x + int(18 * scale);
    int inputArcBottom = startPoint.y + height;

    CPoint inputArcTop_pt(startPoint.x, startPoint.y);
    CPoint inputArcBottom_pt(startPoint.x, startPoint.y + height);

    dc.Arc(inputArcLeft, inputArcTop, inputArcRight, inputArcBottom,
        inputArcBottom_pt.x, inputArcBottom_pt.y,
        inputArcTop_pt.x, inputArcTop_pt.y);

    // --- 2. Courbe supérieure ---
    POINT topCurve[4];
    topCurve[0] = CPoint(startPoint.x, startPoint.y);
    topCurve[1] = CPoint(startPoint.x + int(36 * scale), startPoint.y - int(18 * scale));
    topCurve[2] = CPoint(startPoint.x + int(69 * scale), startPoint.y + int(9 * scale));
    topCurve[3] = CPoint(startPoint.x + width, startPoint.y + int(44 * scale));
    dc.PolyBezier(topCurve, 4);

    // --- 3. Courbe inférieure ---
    POINT bottomCurve[4];
    bottomCurve[0] = CPoint(startPoint.x + width, startPoint.y + int(44 * scale));
    bottomCurve[1] = CPoint(startPoint.x + int(69 * scale), startPoint.y + int(79 * scale));
    bottomCurve[2] = CPoint(startPoint.x + int(36 * scale), startPoint.y + int(106 * scale));
    bottomCurve[3] = CPoint(startPoint.x, startPoint.y + height);
    dc.PolyBezier(bottomCurve, 4);

    // --- 4. Point de sortie ---
    outputPoint = CPoint(startPoint.x + width, startPoint.y + int(44 * scale));

    // --- 5. Points d'entrée (position proportionnelle à la hauteur) ---
    inputPoint1 = CPoint(startPoint.x, startPoint.y + int(height * 0.25)); // 25% du haut
    inputPoint2 = CPoint(startPoint.x, startPoint.y + int(height * 0.75)); // 75% du haut

    // --- 6. Affichage des états logiques ---
    CFont font;
    font.CreatePointFont(int(100 * scale), _T("Arial"));
    CFont* oldFont = dc.SelectObject(&font);
    dc.SetBkMode(TRANSPARENT);

    // Entrée 1
    CString input1(entre1 ? "1" : "0");
    dc.SetTextColor(entre1 ? APP_COLOR_HIGH : APP_COLOR_LOW);
    dc.TextOut(inputPoint1.x - int(15 * scale), inputPoint1.y - int(20 * scale), input1);

    // Entrée 2
    CString input2(entre2 ? "1" : "0");
    dc.SetTextColor(entre2 ? APP_COLOR_HIGH : APP_COLOR_LOW);
    dc.TextOut(inputPoint2.x - int(15 * scale), inputPoint2.y - int(20 * scale), input2);

    dc.SelectObject(oldFont);

}

// Getters/Setters
bool OrGate::getEntre1() const { return entre1; }
bool OrGate::getEntre2() const { return entre2; }
bool OrGate::getSortie() const { return sortie; }
void OrGate::setEntre1(bool val) { entre1 = val; }
void OrGate::setEntre2(bool val) { entre2 = val; }
CPoint OrGate::getOutputPoint() const { return outputPoint; }
CPoint OrGate::getInputPoint1() const { return inputPoint1; }
CPoint OrGate::getInputPoint2() const { return inputPoint2; }

// NOUVELLES MÉTHODES
void OrGate::connectInput1Gate(OrGate* gate) {
    inputGate1 = gate;
    isInput1Variable = false;
}

void OrGate::connectInput2Gate(OrGate* gate) {
    inputGate2 = gate;
    isInput2Variable = false;
}

void OrGate::setInput1AsVariable(bool val) {
    isInput1Variable = true;
    entre1 = val;
}

void OrGate::setInput2AsVariable(bool val) {
    isInput2Variable = true;
    entre2 = val;
}

void OrGate::computeSortie()
{
    sortie = entre1 || entre2;
}

// ÉVALUATION RÉCURSIVE
bool OrGate::evaluate()
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