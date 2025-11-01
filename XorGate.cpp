#include "pch.h"
#include "XorGate.h"
#include "GraphicsUtils.h"
#include "Colors.h"
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

    // --- Sortie (après l'ellipse) ---
    outputPoint = CPoint(startPoint.x + gateWidth, startPoint.y + 44);

    // --- Entrées (touchant l'arc d'entrée principal) ---
    // Les entrées doivent toucher l'arc à mi-hauteur de chaque moitié
    // Arc d'entrée va de y à y+88
    // Point haut : ~25% de la hauteur (y + 22)
    // Point bas : ~75% de la hauteur (y + 66)

    inputPoint1 = CPoint(startPoint.x, startPoint.y + 22);  // entrée supérieure sur l'arc
    inputPoint2 = CPoint(startPoint.x, startPoint.y + 66);  // entrée inférieure sur l'arc



}

void XorGate::draw(CClientDC& dc)
{
    // DIMENSIONS GLOBALES POUR LA PORTE XOR:
    // Largeur totale: ~95 px (identique à OR gate)
    // Hauteur totale: 88 px (identique à OR gate)
    // La porte XOR est une porte OR avec:
    // 1. Un arc d'entrée supplémentaire (décalé vers la gauche)
    // 2. Une ellipse à la sortie

    // --- 0. Dessiner l'arc d'entrée SUPPLÉMENTAIRE (caractéristique du XOR) ---
    // Arc décalé de ~10px vers la gauche - PLUS COURBÉ
    int extraArcLeft = startPoint.x - 32;  // Augmenté pour plus de courbure
    int extraArcTop = startPoint.y;
    int extraArcRight = startPoint.x - 4;   // Augmenté pour plus de courbure
    int extraArcBottom = startPoint.y + 88;

    CPoint extraArcTop_pt(startPoint.x - 10, startPoint.y);
    CPoint extraArcBottom_pt(startPoint.x - 10, startPoint.y + 88);

    // Dessiner l'arc supplémentaire (de bas en haut, convexe vers la DROITE)
    dc.Arc(extraArcLeft, extraArcTop, extraArcRight, extraArcBottom,
        extraArcBottom_pt.x, extraArcBottom_pt.y, extraArcTop_pt.x, extraArcTop_pt.y);

    // --- 1. Dessiner la courbe d'entrée principale (côté gauche) ---
    int inputArcLeft = startPoint.x - 18;
    int inputArcTop = startPoint.y;
    int inputArcRight = startPoint.x + 18;
    int inputArcBottom = startPoint.y + 88;

    CPoint inputArcTop_pt(startPoint.x, startPoint.y);
    CPoint inputArcBottom_pt(startPoint.x, startPoint.y + 88);

    // Dessiner l'arc d'entrée principal
    dc.Arc(inputArcLeft, inputArcTop, inputArcRight, inputArcBottom,
        inputArcBottom_pt.x, inputArcBottom_pt.y, inputArcTop_pt.x, inputArcTop_pt.y);

    // --- 2. Courbe supérieure ---
    POINT topCurve[4];
    topCurve[0] = CPoint(startPoint.x, startPoint.y);
    topCurve[1] = CPoint(startPoint.x + 36, startPoint.y - 18);
    topCurve[2] = CPoint(startPoint.x + 69, startPoint.y + 9);
    topCurve[3] = CPoint(startPoint.x + 95, startPoint.y + 44);
    dc.PolyBezier(topCurve, 4);

    // --- 3. Courbe inférieure ---
    POINT bottomCurve[4];
    bottomCurve[0] = CPoint(startPoint.x + 95, startPoint.y + 44);
    bottomCurve[1] = CPoint(startPoint.x + 69, startPoint.y + 79);
    bottomCurve[2] = CPoint(startPoint.x + 36, startPoint.y + 106);
    bottomCurve[3] = CPoint(startPoint.x, startPoint.y + 88);
    dc.PolyBezier(bottomCurve, 4);

    

    //entres 1
    

    //CORRECTION: Afficher entre1
    
  
    CFont font;
    font.CreatePointFont(100, _T("Arial"));  // Taille de police ajustée
    CFont* oldFont = dc.SelectObject(&font);
    dc.SetBkMode(TRANSPARENT);

    
    CString input1(entre1 ? "1" : "0");
    dc.TextOut(inputPoint1.x - 26, inputPoint1.y - 20, input1);

    // CORRECTION: Afficher entre2 (pas input1!)
    CString input2(entre2 ? "1" : "0");
    dc.TextOut(inputPoint2.x - 26, inputPoint2.y - 20, input2);

    dc.SelectObject(oldFont);


   

    // --- 5. Point de sortie (après l'ellipse) ---
    outputPoint = CPoint(startPoint.x + 95, startPoint.y + 44);



   
   
	

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

// NOUVELLES MÉTHODES
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

// ÉVALUATION RÉCURSIVE
bool XorGate::evaluate()
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