#include "pch.h"
#include "NotGate.h"

NotGate::NotGate()
{
    entree = false;
    sortie = true; 
    
}

void NotGate::setStartPoint(CPoint pt)
{
    startPoint = pt;


}

void NotGate::draw(CClientDC& dc)
{
    int gateWidth = 35;
    int gateHeight = 26;
    int circleRadius = 6;

    // --- Dessiner le triangle ---
    POINT triangle[4];
    triangle[0] = CPoint(startPoint.x, startPoint.y);                           // Coin haut-gauche
    triangle[1] = CPoint(startPoint.x, startPoint.y + gateHeight);             // Coin bas-gauche
    triangle[2] = CPoint(startPoint.x + gateWidth, startPoint.y + gateHeight / 2); // Pointe droite
    triangle[3] = triangle[0];  // Fermer le triangle

    dc.Polyline(triangle, 4);

    // --- Dessiner le petit cercle de négation ---
    int circleLeft = startPoint.x + gateWidth;
    int circleTop = startPoint.y + (gateHeight / 2) - circleRadius;
    int circleRight = startPoint.x + gateWidth + (circleRadius * 2);
    int circleBottom = startPoint.y + (gateHeight / 2) + circleRadius;

    dc.Ellipse(circleLeft, circleTop, circleRight, circleBottom);


    //mise a jour des I/O
        // Point de sortie (après le cercle)
    outputPoint = CPoint(startPoint.x + gateWidth + circleRadius * 2, startPoint.y + gateHeight / 2);

    // Point d'entrée (à gauche du triangle)
    inputPoint = CPoint(startPoint.x, startPoint.y + gateHeight / 2);

    CFont font;
    font.CreatePointFont(100, _T("Arial"));  // Taille de police ajustée
    CFont* oldFont = dc.SelectObject(&font);
    dc.SetBkMode(TRANSPARENT);


    CString input1(entree ? "1" : "0");
    dc.TextOut(inputPoint.x - 26, inputPoint.y - 20, input1);

  

    dc.SelectObject(oldFont);

}

// Getters/Setters
bool NotGate::getEntree() const {
    return entree;
}

bool NotGate::getSortie() const {
    return sortie;
}

void NotGate::setEntree(bool val) {
    entree = val;

}

CPoint NotGate::getOutputPoint() const {
    return outputPoint;
}

CPoint NotGate::getInputPoint() const {
    return inputPoint;
}

