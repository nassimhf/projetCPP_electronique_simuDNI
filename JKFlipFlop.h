#pragma once
#include <afxwin.h>

class JKFlipFlop
{
private:
    bool J;              // Entrée J
    bool K;              // Entrée K
    bool CLK;            // Entrée Clock
    bool Q;              // Sortie
    bool previousCLK;    // État précédent de l'horloge pour détecter le front montant

    CPoint startPoint;
    CPoint inputPointJ;
    CPoint inputPointK;
    CPoint inputPointCLK;
    CPoint outputPointQ;

 

public:
    JKFlipFlop();

    void setStartPoint(CPoint pt);
    void draw(CClientDC& dc, float scale);

    // Getters/Setters
    bool getJ() const;
    bool getK() const;
    bool getCLK() const;
    bool getQ() const;
    void setJ(bool val);
    void setK(bool val);
    void setCLK(bool val);

    CPoint getOutputPointQ() const;
    CPoint getInputPointJ() const;
    CPoint getInputPointK() const;
    CPoint getInputPointCLK() const;

 
};