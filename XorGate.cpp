#include "pch.h"
#include "XorGate.h"

#include "Colors.h"
XorGate::XorGate()
{
    entre1 = false;
    entre2 = false;
    
}

void XorGate::setStartPoint(CPoint pt)
{
    startPoint = pt;

    // Dimensions de la porte XOR
    int gateHeight = 88;
    int gateWidth = 107;

    // --- Sortie (après l'ellipse) ---
    outputPoint = CPoint(startPoint.x + gateWidth, startPoint.y + 44);

    // --- Entrées (touchant l'arc d'entrée principal) ---
    // Les entrées doivent toucher l'arc à mi-hauteur de chaque moitié
    // Arc d'entrée va de y à y+88
    // Point haut : ~25% de la hauteur (y + 22)
    // Point bas : ~75% de la hauteur (y + 66)

  



}

void XorGate::draw(CClientDC& dc,float scale)
{
    // --- Dimensions de base ---
    const int baseWidth = 95;
    const int baseHeight = 88;
    

    // --- 0. Arc supplémentaire (spécifique au XOR) ---
    int extraArcLeft = startPoint.x - int(32 * scale);
    int extraArcTop = startPoint.y;
    int extraArcRight = startPoint.x - int(4 * scale);
    int extraArcBottom = startPoint.y + int(baseHeight * scale);

    CPoint extraArcTop_pt(startPoint.x - int(10 * scale), startPoint.y);
    CPoint extraArcBottom_pt(startPoint.x - int(10 * scale), startPoint.y + int(baseHeight * scale));

    dc.Arc(extraArcLeft, extraArcTop, extraArcRight, extraArcBottom,
        extraArcBottom_pt.x, extraArcBottom_pt.y,
        extraArcTop_pt.x, extraArcTop_pt.y);

    // --- 1. Arc principal (entrée gauche) ---
    int inputArcLeft = startPoint.x - int(18 * scale);
    int inputArcTop = startPoint.y;
    int inputArcRight = startPoint.x + int(18 * scale);
    int inputArcBottom = startPoint.y + int(baseHeight * scale);

    CPoint inputArcTop_pt(startPoint.x, startPoint.y);
    CPoint inputArcBottom_pt(startPoint.x, startPoint.y + int(baseHeight * scale));

    dc.Arc(inputArcLeft, inputArcTop, inputArcRight, inputArcBottom,
        inputArcBottom_pt.x, inputArcBottom_pt.y,
        inputArcTop_pt.x, inputArcTop_pt.y);

    // --- 2. Courbe supérieure ---
    POINT topCurve[4];
    topCurve[0] = CPoint(startPoint.x, startPoint.y);
    topCurve[1] = CPoint(startPoint.x + int(36 * scale), startPoint.y - int(18 * scale));
    topCurve[2] = CPoint(startPoint.x + int(69 * scale), startPoint.y + int(9 * scale));
    topCurve[3] = CPoint(startPoint.x + int(95 * scale), startPoint.y + int(44 * scale));
    dc.PolyBezier(topCurve, 4);

    // --- 3. Courbe inférieure ---
    POINT bottomCurve[4];
    bottomCurve[0] = CPoint(startPoint.x + int(95 * scale), startPoint.y + int(44 * scale));
    bottomCurve[1] = CPoint(startPoint.x + int(69 * scale), startPoint.y + int(79 * scale));
    bottomCurve[2] = CPoint(startPoint.x + int(36 * scale), startPoint.y + int(106 * scale));
    bottomCurve[3] = CPoint(startPoint.x, startPoint.y + int(88 * scale));
    dc.PolyBezier(bottomCurve, 4);

    // --- 4. Points d'entrée et de sortie (mis à l’échelle) ---
    int gateWidth = int(baseWidth * scale);

    inputPoint1 = CPoint(startPoint.x, startPoint.y + int(baseHeight * 0.25 * scale)); // 25% depuis le haut
    inputPoint2 = CPoint(startPoint.x, startPoint.y + int(baseHeight * 0.75 * scale)); // 75% depuis le haut
    outputPoint = CPoint(startPoint.x + gateWidth, startPoint.y + int(44 * scale)); // sortie

    // --- 5. Affichage des entrées (1 / 0) ---
    CFont font;
    font.CreatePointFont(int(100 * scale), _T("Arial"));
    CFont* oldFont = dc.SelectObject(&font);
    dc.SetBkMode(TRANSPARENT);

    CString input1(entre1 ? "1" : "0");
    dc.SetTextColor(entre1 ? APP_COLOR_HIGH : APP_COLOR_LOW);
    dc.TextOut(inputPoint1.x - int(26 * scale), inputPoint1.y - int(20 * scale), input1);

    CString input2(entre2 ? "1" : "0");
    dc.SetTextColor(entre2 ? APP_COLOR_HIGH : APP_COLOR_LOW);
    dc.TextOut(inputPoint2.x - int(26 * scale), inputPoint2.y - int(20 * scale), input2);

    dc.SelectObject(oldFont);
    // Tu peux l'utiliser ensuite pour connecter des fils, par exemple :
    // dc.MoveTo(outputPoint);
    // dc.LineTo(outputPoint.x + 20, outputPoint.y);
}
	

// Getters/Setters
bool XorGate::getEntre1() const { return entre1; }
bool XorGate::getEntre2() const { return entre2; }
bool XorGate::getSortie() const { return sortie; }
void XorGate::setEntre1(bool val) { entre1 = val; }
void XorGate::setEntre2(bool val) { entre2 = val; }
CPoint XorGate::getOutputPoint() const { return outputPoint; }
CPoint XorGate::getInputPoint1() const { return inputPoint1; }
CPoint XorGate::getInputPoint2() const { return inputPoint2; }

