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

   
};

#endif