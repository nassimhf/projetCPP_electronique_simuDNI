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

    // Pour gérer les connexions entre portes
    DFlipFlop* inputGateD;
    DFlipFlop* inputGateCLK;
    bool isInputDVariable;
    bool isInputCLKVariable;

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
    void connectInputDGate(DFlipFlop* gate);
    void connectInputCLKGate(DFlipFlop* gate);
    void setInputDAsVariable(bool val);
    void setInputCLKAsVariable(bool val);

    // Calcul et évaluation
    void computeQ();
    bool evaluate();
};