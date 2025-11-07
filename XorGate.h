#pragma once

class XorGate
{
public:
    bool entre1;       // première entrée
    bool entre2;       // deuxième entrée
    bool sortie;       // sortie logique (XOR)

    CPoint startPoint;   // point de départ pour le dessin
    CPoint outputPoint;  // point de sortie
    CPoint inputPoint1;  // entrée 1
    CPoint inputPoint2;  // entrée 2
    // NOUVEAUX: Pour stocker les portes connectées en entrée
    XorGate* inputGate1;
    XorGate* inputGate2;
    bool isInput1Variable;  // true si entrée 1 est une variable (X,Y,Z)
    bool isInput2Variable;  // true si entrée 2 est une variable (X,Y,Z)
public:
    XorGate();

    void setStartPoint(CPoint pt);
    void draw(CClientDC& dc,float scale);
    

    
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
    void connectInput1Gate(XorGate* gate);
    void connectInput2Gate(XorGate* gate);
    void setInput1AsVariable(bool val);
    void setInput2AsVariable(bool val);

    // NOUVEAU: Calculer récursivement
    bool evaluate();
};
