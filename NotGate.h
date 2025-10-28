#ifndef NOTGATE_H
#define NOTGATE_H

#include <afxwin.h>

class NotGate
{
private:
    bool entree;
    bool sortie;
    CPoint startPoint;
    CPoint outputPoint;
    CPoint inputPoint;

    // NOUVEAUX: Pour stocker la porte connect�e en entr�e
    void* inputGate;  // Peut �tre AndGate, OrGate, XorGate, ou NotGate
    bool isInputVariable;  // true si entr�e est une variable (X,Y,Z)

public:
    NotGate();
    void setStartPoint(CPoint pt);
    void draw(CClientDC& dc);

    // Getters/Setters
    bool getEntree() const;
    bool getSortie() const;
    void setEntree(bool val);

    CPoint getOutputPoint() const;
    CPoint getInputPoint() const;

    // Calcul du r�sultat
    void computeSortie();

    // Connexion des portes
    void connectInputGate(void* gate);
    void setInputAsVariable(bool val);

    // �valuation r�cursive
    bool evaluate();
};

#endif