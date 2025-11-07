// AndGate.h
#ifndef ANDGATE_H
#define ANDGATE_H

#include <afxwin.h>

class AndGate
{
private:
    bool entre1;
    bool entre2;
    bool sortie;
    CPoint startPoint;
    CPoint outputPoint;
    CPoint inputPoint1;
    CPoint inputPoint2;

    // NOUVEAUX: Pour stocker les portes connectées en entrée
    AndGate* inputGate1;
    AndGate* inputGate2;
    bool isInput1Variable;  // true si entrée 1 est une variable (X,Y,Z)
    bool isInput2Variable;  // true si entrée 2 est une variable (X,Y,Z)

public:
    AndGate();
    void setStartPoint(CPoint pt);
    void draw(CClientDC& dc, float scale);

    // Getters/Setters existants
    bool getEntre1() const;
    bool getEntre2() const;
    bool getSortie() const;
    void setEntre1(bool val);
    void setEntre2(bool val);

    CPoint getOutputPoint() const;
    CPoint getInputPoint1() const;
    CPoint getInputPoint2() const;

    // NOUVEAU: Méthode pour calculer le résultat
    void computeSortie();

    // NOUVEAU: Connecter des portes en entrée
    void connectInput1Gate(AndGate* gate);
    void connectInput2Gate(AndGate* gate);
    void setInput1AsVariable(bool val);
    void setInput2AsVariable(bool val);

    // NOUVEAU: Calculer récursivement
    bool evaluate();
};

#endif