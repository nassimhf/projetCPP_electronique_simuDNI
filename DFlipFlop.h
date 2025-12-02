#pragma once
#include <afxwin.h>

class DFlipFlop
{
private:
    bool D;              // Entrée Data
    bool CLK;            // Entrée Clock
    bool Q;              // Sortie
    bool previousCLK;    // État précédent de l'horloge pour détecter le front montant

    CPoint startPoint;
    CPoint inputPointD;
    CPoint inputPointCLK;
    CPoint outputPointQ;

   

public:
    DFlipFlop();

    void setStartPoint(CPoint pt);
    void draw(CClientDC& dc, float scale);

    // Getters/Setters
    bool getD() const;
    bool getCLK() const;
    bool getQ() const;
    void setD(bool val);
    void setCLK(bool val);
    
    CPoint getOutputPointQ() const;
    CPoint getInputPointD() const;
    CPoint getInputPointCLK() const;

    // Méthodes de connexion
    
 
};