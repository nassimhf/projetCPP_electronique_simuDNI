

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

    // Dimensions doublées (×2)
    int gateHeight = 120;   // hauteur totale (60 * 2)
    int gateWidth = 160;    // largeur totale (80 * 2)
    int offset = 30;        // décalage pour l’arc interne (15 * 2)

    // --- Calcul du point de sortie ---
    // À l’extrémité droite du grand arc
    outputPoint = CPoint(startPoint.x + gateWidth + 30, startPoint.y + gateHeight / 2);

    // --- Points d’entrée (deux entrées espacées verticalement) ---
    inputPoint1 = CPoint(startPoint.x , startPoint.y + 35);   // entrée supérieure
    inputPoint2 = CPoint(startPoint.x, startPoint.y + 85);   // entrée inférieure
}




void OrGate::draw(CClientDC& dc)
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
    int inputArcLeft = startPoint.x - 18;
    int inputArcTop = startPoint.y;
    int inputArcRight = startPoint.x + 18;
    int inputArcBottom = startPoint.y + 88;

    // Points de début et fin pour l'arc d'entrée (MIROIR - inversés verticalement)
    CPoint inputArcTop_pt(startPoint.x, startPoint.y);
    CPoint inputArcBottom_pt(startPoint.x, startPoint.y + 88);

    // Dessiner l'arc d'entrée MIROIR (de bas en haut, convexe vers la DROITE)
    dc.Arc(inputArcLeft, inputArcTop, inputArcRight, inputArcBottom,
        inputArcBottom_pt.x, inputArcBottom_pt.y, inputArcTop_pt.x, inputArcTop_pt.y);

    // --- 2. Courbe supérieure ---
    POINT topCurve[4];
    topCurve[0] = CPoint(startPoint.x, startPoint.y);                // Départ (haut gauche)
    topCurve[1] = CPoint(startPoint.x + 36, startPoint.y - 18);      // Point de contrôle 1
    topCurve[2] = CPoint(startPoint.x + 69, startPoint.y + 9);       // Point de contrôle 2
    topCurve[3] = CPoint(startPoint.x + 95, startPoint.y + 44);      // Arrivée (sortie)
    dc.PolyBezier(topCurve, 4);

    // --- 3. Courbe inférieure ---
    POINT bottomCurve[4];
    bottomCurve[0] = CPoint(startPoint.x + 95, startPoint.y + 44);   // Départ (sortie)
    bottomCurve[1] = CPoint(startPoint.x + 69, startPoint.y + 79);   // Point de contrôle 1
    bottomCurve[2] = CPoint(startPoint.x + 36, startPoint.y + 106);  // Point de contrôle 2
    bottomCurve[3] = CPoint(startPoint.x, startPoint.y + 88);        // Arrivée (bas gauche)
    dc.PolyBezier(bottomCurve, 4);


    // --- 4. Point de sortie ---
    outputPoint = CPoint(startPoint.x + 95, startPoint.y + 44);


    CFont font;
    font.CreatePointFont(100, _T("Arial"));  // Taille de police ajustée
    CFont* oldFont = dc.SelectObject(&font);
    dc.SetBkMode(TRANSPARENT);


    CString input1(entre1 ? "1" : "0");
    dc.SetTextColor(entre1 ? APP_COLOR_HIGH : APP_COLOR_LOW);
    dc.TextOut(inputPoint1.x - 15, inputPoint1.y - 34, input1);

    // CORRECTION: Afficher entre2 (pas input1!)
    CString input2(entre2 ? "1" : "0");
    dc.SetTextColor(entre2 ? APP_COLOR_HIGH : APP_COLOR_LOW);
    dc.TextOut(inputPoint2.x - 15, inputPoint2.y - 42, input2);

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