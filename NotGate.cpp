#include "pch.h"
#include "GraphicsUtils.h"
#include "NotGate.h"

NotGate::NotGate()
{
    entree = false;
    sortie = true;  // NOT de false = true
    inputGate = nullptr;
    isInputVariable = false;
}

void NotGate::setStartPoint(CPoint pt)
{
    startPoint = pt;

    // Dimensions de la porte NOT
    int gateWidth = 60;   // Largeur du triangle
    int gateHeight = 40;  // Hauteur du triangle
    int circleRadius = 8; // Rayon du petit cercle de négation

    // Point de sortie (après le cercle)
    outputPoint = CPoint(startPoint.x + gateWidth + circleRadius * 2, startPoint.y + gateHeight / 2);

    // Point d'entrée (à gauche du triangle)
    inputPoint = CPoint(startPoint.x, startPoint.y + gateHeight / 2);
}

void NotGate::draw(CClientDC& dc)
{
    int gateWidth = 60;
    int gateHeight = 40;
    int circleRadius = 8;

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
    computeSortie();  // Recalculer automatiquement
}

CPoint NotGate::getOutputPoint() const {
    return outputPoint;
}

CPoint NotGate::getInputPoint() const {
    return inputPoint;
}

// Connexion des portes
void NotGate::connectInputGate(void* gate) {
    inputGate = gate;
    isInputVariable = false;
}

void NotGate::setInputAsVariable(bool val) {
    isInputVariable = true;
    entree = val;
}

// Calcul de la sortie
void NotGate::computeSortie()
{
    sortie = !entree;  // Logique NOT
}

// Évaluation récursive
bool NotGate::evaluate()
{
    // Si l'entrée n'est pas une variable, récupérer depuis la porte connectée
    if (!isInputVariable && inputGate != nullptr) {
        // On doit caster selon le type de porte
        // Pour simplifier, on suppose que toutes les portes ont une méthode evaluate()
        // Tu pourrais utiliser un polymorphisme avec une classe de base Gate

        // SOLUTION TEMPORAIRE: Cast vers AndGate (tu devras améliorer ça)
        // Mieux: créer une classe de base abstraite Gate avec evaluate()
        entree = ((NotGate*)inputGate)->evaluate();
    }

    // Calculer la sortie NOT
    computeSortie();

    return sortie;
}