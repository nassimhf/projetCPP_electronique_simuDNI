#pragma once
#include <afxwin.h>

// La classe JKFlipFlop représente une bascule JK avec ses entrées J, K et CLK,
// et sa sortie Q. Elle gère l’état précédent de l’horloge pour détecter les fronts montants
// et met à jour la sortie selon les règles de la bascule JK.
// La classe fournit des méthodes pour définir la position graphique de la bascule,
// obtenir ou modifier ses entrées et sa sortie, et dessiner le symbole du flip-flop
// dans un contexte MFC via draw.
// Elle inclut également des points pour connecter visuellement les entrées et la sortie
// dans un schéma.


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