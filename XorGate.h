#pragma once

// Cette classe permet de dessiner une porte logique XOR grace a la fonction draw()
// la fonction setStartPoint() permet de définir la position (x,y) de la porte


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

};
