// AndGate.h


// Cette classe permet de dessiner une porte logique AND grace a la fonction draw()
// la fonction setStartPoint() permet de définir la position (x,y) de la porte
//
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

  

  

   
};

#endif