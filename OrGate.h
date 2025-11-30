#pragma once

class OrGate
{
public:
    bool entre1;       // première entrée
    bool entre2;       // deuxième entrée
    bool sortie;       // sortie logique

    CPoint startPoint;  // point de départ pour le dessin
    CPoint outputPoint; // point de sortie pour connexion
    CPoint inputPoint1; // entrée 1
    CPoint inputPoint2; // entrée 2

 
public:
    OrGate();
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

};
