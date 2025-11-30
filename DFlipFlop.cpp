#include <afxwin.h>
#include "pch.h"
#include "DFlipFlop.h"

#include "Colors.h"

DFlipFlop::DFlipFlop()
{
    D = false;
    CLK = false;
    Q = false;
    previousCLK = false;
    inputGateD = nullptr;
    inputGateCLK = nullptr;
    isInputDVariable = false;
    isInputCLKVariable = false;
}

void DFlipFlop::setStartPoint(CPoint pt)
{
    startPoint = pt;
}

void DFlipFlop::draw(CClientDC& dc, float scale)
{
    // DIMENSIONS GLOBALES POUR LA BASCULE D:
    // Largeur: 80 px
    // Hauteur: 100 px
    // Rectangle classique avec marque d'horloge triangulaire

    int width = int(80 * scale);
    int height = int(100 * scale);

    // --- 1. Dessiner le rectangle principal ---
    CPen pen(PS_SOLID, int(2 * scale), RGB(0, 0, 0));
    CPen* oldPen = dc.SelectObject(&pen);

    dc.Rectangle(startPoint.x, startPoint.y,
        startPoint.x + width, startPoint.y + height);

    // --- 2. Dessiner le triangle d'horloge (indique front montant) ---
    // Petit triangle sur l'entrée CLK
    int triangleSize = int(8 * scale);
    int clkY = startPoint.y + int(height * 0.65);

    POINT triangle[3];
    triangle[0] = CPoint(startPoint.x, clkY - triangleSize);
    triangle[1] = CPoint(startPoint.x, clkY + triangleSize);
    triangle[2] = CPoint(startPoint.x + triangleSize, clkY);
    dc.Polygon(triangle, 3);

    dc.SelectObject(oldPen);

    // --- 3. Points d'entrée et sortie ---
    inputPointD = CPoint(startPoint.x, startPoint.y + int(height * 0.30));
    inputPointCLK = CPoint(startPoint.x, clkY);
    outputPointQ = CPoint(startPoint.x + width, startPoint.y + int(height * 0.50));

    // --- 4. Labels sur la bascule ---
    CFont labelFont;
    labelFont.CreatePointFont(int(120 * scale), _T("Arial Bold"));
    CFont* oldFont = dc.SelectObject(&labelFont);
    dc.SetBkMode(TRANSPARENT);
    dc.SetTextColor(RGB(0, 0, 0));

    // Label "D"
    dc.TextOut(startPoint.x + int(10 * scale),
        startPoint.y + int(height * 0.25), _T("D"));

    // Label "CLK" (ou juste ">")
    dc.TextOut(startPoint.x + int(10 * scale),
        clkY - int(10 * scale), _T("CLK"));

    // Label "Q"
    dc.TextOut(startPoint.x + width - int(25 * scale),
        startPoint.y + int(height * 0.45), _T("Q"));

    dc.SelectObject(oldFont);

    // --- 5. Affichage des états logiques ---
    CFont stateFont;
    stateFont.CreatePointFont(int(100 * scale), _T("Arial"));
    oldFont = dc.SelectObject(&stateFont);

    // État de D
    CString inputD_str(D ? "1" : "0");
    dc.SetTextColor(D ? APP_COLOR_HIGH : APP_COLOR_LOW);
    dc.TextOut(inputPointD.x - int(20 * scale),
        inputPointD.y - int(10 * scale), inputD_str);

    // État de CLK
    CString inputCLK_str(CLK ? "1" : "0");
    dc.SetTextColor(CLK ? APP_COLOR_HIGH : APP_COLOR_LOW);
    dc.TextOut(inputPointCLK.x - int(20 * scale),
        inputPointCLK.y - int(10 * scale), inputCLK_str);

    // État de Q
    CString outputQ_str(Q ? "1" : "0");
    dc.SetTextColor(Q ? APP_COLOR_HIGH : APP_COLOR_LOW);
    dc.TextOut(outputPointQ.x + int(10 * scale),
        outputPointQ.y - int(10 * scale), outputQ_str);

    dc.SelectObject(oldFont);
}

// Getters/Setters
bool DFlipFlop::getD() const { return D; }
bool DFlipFlop::getCLK() const { return CLK; }
bool DFlipFlop::getQ() const { return Q; }
void DFlipFlop::setD(bool val) { D = val; }
void DFlipFlop::setCLK(bool val) { CLK = val; }
CPoint DFlipFlop::getOutputPointQ() const { return outputPointQ; }
CPoint DFlipFlop::getInputPointD() const { return inputPointD; }
CPoint DFlipFlop::getInputPointCLK() const { return inputPointCLK; }

// NOUVELLES MÉTHODES
void DFlipFlop::connectInputDGate(DFlipFlop* gate) {
    inputGateD = gate;
    isInputDVariable = false;
}

void DFlipFlop::connectInputCLKGate(DFlipFlop* gate) {
    inputGateCLK = gate;
    isInputCLKVariable = false;
}

void DFlipFlop::setInputDAsVariable(bool val) {
    isInputDVariable = true;
    D = val;
}

void DFlipFlop::setInputCLKAsVariable(bool val) {
    isInputCLKVariable = true;
    CLK = val;
}

void DFlipFlop::computeQ()
{
    // Détection du front montant (transition 0 -> 1)
    if (CLK && !previousCLK) {
        // Sur front montant, capturer la valeur de D
        Q = D;
    }
    // Sinon Q garde sa valeur

    // Mettre à jour l'état précédent de l'horloge
    previousCLK = CLK;
}

// ÉVALUATION RÉCURSIVE
bool DFlipFlop::evaluate()
{
    // Si entrée D n'est pas une variable, récupérer depuis la porte connectée
    if (!isInputDVariable && inputGateD != nullptr) {
        D = inputGateD->evaluate();
    }

    // Si entrée CLK n'est pas une variable, récupérer depuis la porte connectée
    if (!isInputCLKVariable && inputGateCLK != nullptr) {
        CLK = inputGateCLK->evaluate();
    }

    // Calculer la sortie Q
    computeQ();

    return Q;
}