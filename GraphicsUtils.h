#pragma once
#include <afxwin.h> // nécessaire pour CDC et CString

class GraphicsUtils
{
public:
    // Fonction statique : accessible depuis n'importe quelle classe
	static void DrawBinaryInput(CDC* dc, bool value, CPoint pos, int type = 0)
	{

		int fontSize = 90;
		// Déterminer le texte et la couleur
		char* text = !value ? "0" : "1";
		COLORREF color = !value ? RGB(0, 0, 207) : RGB(207, 0, 0); // bleu pour 0, rouge pour 1
		// Config police
		CFont font;
		font.CreatePointFont(fontSize, _T("Arial Bold"));
		CFont* oldFont = dc->SelectObject(&font);
		// Couleur + fond
		dc->SetTextColor(color);
		dc->SetBkMode(TRANSPARENT);
		// Affichage
		CString label(text);
		int x = 0;
		int y = 0;
		if (type == 1) {
			x = pos.x - 15;
			y = pos.y - 40;
		}
		else if (type == 2) {
			x = pos.x - 25;
			y = pos.y - 25;
		}
		else {
			x = pos.x - 15;
			y = pos.y - 25;
		}
		
		dc->TextOutW(x,y, label);
		// Restauration
		dc->SelectObject(oldFont);
	}
};
