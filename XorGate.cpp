#include "pch.h"
#include "XorGate.h"
#include "GraphicsUtils.h"
XorGate::XorGate()
{
    entre1 = false;
    entre2 = false;
    inputGate1 = nullptr;
    inputGate2 = nullptr;
    isInput1Variable = false;
    isInput2Variable = false;
}

void XorGate::setStartPoint(CPoint pt)
{
    startPoint = pt;

    // Dimensions de la porte XOR
    int gateHeight = 88;
    int gateWidth = 107;

    // --- Sortie (apr�s l'ellipse) ---
    outputPoint = CPoint(startPoint.x + gateWidth, startPoint.y + 44);

    // --- Entr�es (touchant l'arc d'entr�e principal) ---
    // Les entr�es doivent toucher l'arc � mi-hauteur de chaque moiti�
    // Arc d'entr�e va de y � y+88
    // Point haut : ~25% de la hauteur (y + 22)
    // Point bas : ~75% de la hauteur (y + 66)

    inputPoint1 = CPoint(startPoint.x, startPoint.y + 22);  // entr�e sup�rieure sur l'arc
    inputPoint2 = CPoint(startPoint.x, startPoint.y + 66);  // entr�e inf�rieure sur l'arc



}

void XorGate::draw(CClientDC& dc)
{
    // DIMENSIONS GLOBALES POUR LA PORTE XOR:
    // Largeur totale: ~95 px (identique � OR gate)
    // Hauteur totale: 88 px (identique � OR gate)
    // La porte XOR est une porte OR avec:
    // 1. Un arc d'entr�e suppl�mentaire (d�cal� vers la gauche)
    // 2. Une ellipse � la sortie

    // --- 0. Dessiner l'arc d'entr�e SUPPL�MENTAIRE (caract�ristique du XOR) ---
    // Arc d�cal� de ~10px vers la gauche - PLUS COURB�
    int extraArcLeft = startPoint.x - 32;  // Augment� pour plus de courbure
    int extraArcTop = startPoint.y;
    int extraArcRight = startPoint.x - 4;   // Augment� pour plus de courbure
    int extraArcBottom = startPoint.y + 88;

    CPoint extraArcTop_pt(startPoint.x - 10, startPoint.y);
    CPoint extraArcBottom_pt(startPoint.x - 10, startPoint.y + 88);

    // Dessiner l'arc suppl�mentaire (de bas en haut, convexe vers la DROITE)
    dc.Arc(extraArcLeft, extraArcTop, extraArcRight, extraArcBottom,
        extraArcBottom_pt.x, extraArcBottom_pt.y, extraArcTop_pt.x, extraArcTop_pt.y);

    // --- 1. Dessiner la courbe d'entr�e principale (c�t� gauche) ---
    int inputArcLeft = startPoint.x - 18;
    int inputArcTop = startPoint.y;
    int inputArcRight = startPoint.x + 18;
    int inputArcBottom = startPoint.y + 88;

    CPoint inputArcTop_pt(startPoint.x, startPoint.y);
    CPoint inputArcBottom_pt(startPoint.x, startPoint.y + 88);

    // Dessiner l'arc d'entr�e principal
    dc.Arc(inputArcLeft, inputArcTop, inputArcRight, inputArcBottom,
        inputArcBottom_pt.x, inputArcBottom_pt.y, inputArcTop_pt.x, inputArcTop_pt.y);

    // --- 2. Courbe sup�rieure ---
    POINT topCurve[4];
    topCurve[0] = CPoint(startPoint.x, startPoint.y);
    topCurve[1] = CPoint(startPoint.x + 36, startPoint.y - 18);
    topCurve[2] = CPoint(startPoint.x + 69, startPoint.y + 9);
    topCurve[3] = CPoint(startPoint.x + 95, startPoint.y + 44);
    dc.PolyBezier(topCurve, 4);

    // --- 3. Courbe inf�rieure ---
    POINT bottomCurve[4];
    bottomCurve[0] = CPoint(startPoint.x + 95, startPoint.y + 44);
    bottomCurve[1] = CPoint(startPoint.x + 69, startPoint.y + 79);
    bottomCurve[2] = CPoint(startPoint.x + 36, startPoint.y + 106);
    bottomCurve[3] = CPoint(startPoint.x, startPoint.y + 88);
    dc.PolyBezier(bottomCurve, 4);

    // --- 4. Ellipse de sortie (caract�ristique du XOR) ---
    // Petite ellipse � la sortie (diam�tre ~12px)
    int ellipseLeft = startPoint.x + 95;
    int ellipseTop = startPoint.y + 38;
    int ellipseRight = startPoint.x + 107;
    int ellipseBottom = startPoint.y + 50;

    dc.Ellipse(ellipseLeft, ellipseTop, ellipseRight, ellipseBottom);

    // --- 5. Point de sortie (apr�s l'ellipse) ---
    outputPoint = CPoint(startPoint.x + 107, startPoint.y + 44);


   
	

}
// Getters/Setters
bool XorGate::getEntre1() const { return entre1; }
bool XorGate::getEntre2() const { return entre2; }
bool XorGate::getSortie() const { return sortie; }
void XorGate::setEntre1(bool val) { entre1 = val; }
void XorGate::setEntre2(bool val) { entre2 = val; }
CPoint XorGate::getOutputPoint() const { return outputPoint; }
CPoint XorGate::getInputPoint1() const { return inputPoint1; }
CPoint XorGate::getInputPoint2() const { return inputPoint2; }

// NOUVELLES M�THODES
void XorGate::connectInput1Gate(XorGate* gate) {
    inputGate1 = gate;
    isInput1Variable = false;
}

void XorGate::connectInput2Gate(XorGate* gate) {
    inputGate2 = gate;
    isInput2Variable = false;
}

void XorGate::setInput1AsVariable(bool val) {
    isInput1Variable = true;
    entre1 = val;
}

void XorGate::setInput2AsVariable(bool val) {
    isInput2Variable = true;
    entre2 = val;
}

void XorGate::computeSortie()
{
    sortie = entre1 ^ entre2;
}

// �VALUATION R�CURSIVE
bool XorGate::evaluate()
{
    // Si entr�e 1 n'est pas une variable, r�cup�rer depuis la porte connect�e
    if (!isInput1Variable && inputGate1 != nullptr) {
        entre1 = inputGate1->evaluate();
    }

    // Si entr�e 2 n'est pas une variable, r�cup�rer depuis la porte connect�e
    if (!isInput2Variable && inputGate2 != nullptr) {
        entre2 = inputGate2->evaluate();
    }

    // Calculer la sortie
    computeSortie();

    return sortie;
}