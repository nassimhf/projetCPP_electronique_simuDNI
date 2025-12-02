

//La classe DFlipFlop représente une bascule D (D flip-flop) avec ses entrées D et CLK,
//et sa sortie Q. Elle gère l’état précédent de l’horloge pour détecter les fronts montants
//et met à jour la sortie en conséquence.
// La classe fournit des méthodes pour définir la position graphique de la bascule ,
// obtenir ou modifier ses entrées et sa sortie, et dessiner le symbole du flip-flop dans
// un contexte MFC via draw
// Elle inclut également des points pour connecter visuellement les entrées et la sortie dans
// un schéma.


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