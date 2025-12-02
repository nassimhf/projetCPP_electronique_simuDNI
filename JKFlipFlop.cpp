#include <afxwin.h>
#include "pch.h"
#include "JKFlipFlop.h"

#include "Colors.h"

JKFlipFlop::JKFlipFlop()
{
    J = false;
    K = false;
    CLK = false;
    Q = false;
    previousCLK = false;
 
}

void JKFlipFlop::setStartPoint(CPoint pt)
{
    startPoint = pt;
}

void JKFlipFlop::draw(CClientDC& dc, float scale)
{
    // DIMENSIONS GLOBALES POUR LA BASCULE JK:
    // Largeur: 80 px
    // Hauteur: 120 px (plus haute que la bascule D pour 3 entrées)
    // Rectangle classique avec marque d'horloge triangulaire

    int width = int(80 * scale);
    int height = int(120 * scale);

    // --- 1. Dessiner le rectangle principal ---
    CPen pen(PS_SOLID, int(2 * scale), RGB(0, 0, 0));
    CBrush nullBrush;
    nullBrush.CreateStockObject(NULL_BRUSH); // crée un brush stock qui vit tant que nullBrush existe

    // sélectionner et garder les anciens objets renvoyés
    CPen* pOldPen = dc.SelectObject(&pen);
    CBrush* pOldBrush = (CBrush*)dc.SelectObject(&nullBrush);

    // dessin
    dc.Rectangle(startPoint.x, startPoint.y,
        startPoint.x + width, startPoint.y + height);

    // restaurer les anciens objets (vérifier non-null avant)
    if (pOldBrush) dc.SelectObject(pOldBrush);
    if (pOldPen)  dc.SelectObject(pOldPen);


    CPen* oldPen = dc.SelectObject(&pen);

    // --- 2. Dessiner le triangle d'horloge (indique front montant) ---
    // Petit triangle sur l'entrée CLK
    int triangleSize = int(8 * scale);
    int clkY = startPoint.y + int(height * 0.50); // CLK au milieu

    POINT triangle[3];
    triangle[0] = CPoint(startPoint.x, clkY - triangleSize);
    triangle[1] = CPoint(startPoint.x, clkY + triangleSize);
    triangle[2] = CPoint(startPoint.x + triangleSize, clkY);
    dc.Polygon(triangle, 3);

    dc.SelectObject(oldPen);

    // --- 3. Points d'entrée et sortie ---
    inputPointJ = CPoint(startPoint.x, startPoint.y + int(height * 0.20));   // J en haut
    inputPointCLK = CPoint(startPoint.x, clkY);                               // CLK au milieu
    inputPointK = CPoint(startPoint.x, startPoint.y + int(height * 0.80));   // K en bas
    outputPointQ = CPoint(startPoint.x + width, startPoint.y + int(height * 0.50));

    // --- 4. Labels sur la bascule ---
    CFont labelFont;
    labelFont.CreatePointFont(int(120 * scale), _T("Arial Bold"));
    CFont* oldFont = dc.SelectObject(&labelFont);
    dc.SetBkMode(TRANSPARENT);
    dc.SetTextColor(RGB(0, 0, 0));

    // Label "J"
    dc.TextOut(startPoint.x + int(10 * scale),
        startPoint.y + int(height * 0.15), _T("J"));

    // Label "CLK" (ou juste ">")
    dc.TextOut(startPoint.x + int(10 * scale),
        clkY - int(10 * scale), _T("CLK"));

    // Label "K"
    dc.TextOut(startPoint.x + int(10 * scale),
        startPoint.y + int(height * 0.75), _T("K"));

    // Label "Q"
    dc.TextOut(startPoint.x + width - int(25 * scale),
        startPoint.y + int(height * 0.45), _T("Q"));

    dc.SelectObject(oldFont);

    // --- 5. Affichage des états logiques ---
    CFont stateFont;
    stateFont.CreatePointFont(int(100 * scale), _T("Arial"));
    oldFont = dc.SelectObject(&stateFont);

    // État de J
    CString inputJ_str(J ? "1" : "0");
    dc.SetTextColor(J ? APP_COLOR_HIGH : APP_COLOR_LOW);
    dc.TextOut(inputPointJ.x - int(20 * scale),
        inputPointJ.y - int(20 * scale), inputJ_str);

    // État de CLK
    CString inputCLK_str(CLK ? "1" : "0");
    dc.SetTextColor(CLK ? APP_COLOR_HIGH : APP_COLOR_LOW);
    dc.TextOut(inputPointCLK.x - int(20 * scale),
        inputPointCLK.y - int(20 * scale), inputCLK_str);

    // État de K
    CString inputK_str(K ? "1" : "0");
    dc.SetTextColor(K ? APP_COLOR_HIGH : APP_COLOR_LOW);
    dc.TextOut(inputPointK.x - int(20 * scale),
        inputPointK.y - int(20 * scale), inputK_str);

    // État de Q
    CString outputQ_str(Q ? "1" : "0");
    dc.SetTextColor(Q ? APP_COLOR_HIGH : APP_COLOR_LOW);
    dc.TextOut(outputPointQ.x + int(10 * scale),
        outputPointQ.y - int(20 * scale), outputQ_str);

    dc.SelectObject(oldFont);
}

// Getters/Setters
bool JKFlipFlop::getJ() const { return J; }
bool JKFlipFlop::getK() const { return K; }
bool JKFlipFlop::getCLK() const { return CLK; }
bool JKFlipFlop::getQ() const { return Q; }
void JKFlipFlop::setJ(bool val) { J = val; }
void JKFlipFlop::setK(bool val) { K = val; }
void JKFlipFlop::setCLK(bool val) { CLK = val; }
CPoint JKFlipFlop::getOutputPointQ() const { return outputPointQ; }
CPoint JKFlipFlop::getInputPointJ() const { return inputPointJ; }
CPoint JKFlipFlop::getInputPointK() const { return inputPointK; }
CPoint JKFlipFlop::getInputPointCLK() const { return inputPointCLK; }

