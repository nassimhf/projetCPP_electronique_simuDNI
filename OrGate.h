#pragma once

class OrGate
{
public:
    bool entre1;       // premi�re entr�e
    bool entre2;       // deuxi�me entr�e
    bool sortie;       // sortie logique

    CPoint startPoint;  // point de d�part pour le dessin
    CPoint outputPoint; // point de sortie pour connexion
    CPoint inputPoint1; // entr�e 1
    CPoint inputPoint2; // entr�e 2

    OrGate* inputGate1;
    OrGate* inputGate2;
    bool isInput1Variable;  // true si entr�e 1 est une variable (X,Y,Z)
    bool isInput2Variable;  // true si entr�e 2 est une variable (X,Y,Z)
public:
    OrGate();
    void setStartPoint(CPoint pt);
    void draw(CClientDC& dc);

    // Getters/Setters existants
    bool getEntre1() const;
    bool getEntre2() const;
    bool getSortie() const;
    void setEntre1(bool val);
    void setEntre2(bool val);

    CPoint getOutputPoint() const;
    CPoint getInputPoint1() const;
    CPoint getInputPoint2() const;

    // NOUVEAU: M�thode pour calculer le r�sultat
    void computeSortie();

    // NOUVEAU: Connecter des portes en entr�e
    void connectInput1Gate(OrGate* gate);
    void connectInput2Gate(OrGate* gate);
    void setInput1AsVariable(bool val);
    void setInput2AsVariable(bool val);

    // NOUVEAU: Calculer r�cursivement
    bool evaluate();
};
