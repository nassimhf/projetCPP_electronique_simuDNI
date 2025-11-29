// MainScreen.cpp : fichier d'implémentation
//

#include "pch.h"
#include "Projetcppsimu.h"
#include "afxdialogex.h"
#include "MainScreen.h"
#include "SchemaDrawer.h"
#include "FileReader.h"
#include "resource.h"
#include "Colors.h"


// boîte de dialogue de MainScreen

IMPLEMENT_DYNAMIC(MainScreen, CDialogEx)

MainScreen::MainScreen(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	
}

void DrawSeparatorWithLabel(CDC* dc, int y, int width, CString label) {
	// Ligne de séparation
	CPen pen(PS_SOLID, 2, RGB(70, 130, 180)); // Bleu acier
	CPen* oldPen = dc->SelectObject(&pen);

	// Mesurer le texte
	CFont font;
	font.CreatePointFont(100, _T("Arial"));
	CFont* oldFont = dc->SelectObject(&font);

	CSize textSize = dc->GetTextExtent(label);
	int textX =   100;

	// Ligne gauche
	dc->MoveTo(10, y);
	dc->LineTo(textX - 10, y);

	// Texte au centre
	dc->SetBkMode(TRANSPARENT);
	dc->SetTextColor(RGB(70, 130, 180));
	dc->TextOut(textX, y - textSize.cy / 2, label);

	// Ligne droite
	dc->MoveTo(textX + textSize.cx + 10, y);
	dc->LineTo(width - 10, y);

	dc->SelectObject(oldFont);
	dc->SelectObject(oldPen);
}



BOOL MainScreen::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Ajouter l'élément de menu "À propos de..." au menu Système.
	SetBackgroundColor(APP_COLOR_LIGHT);
	// IDM_ABOUTBOX doit se trouver dans la plage des commandes système.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// Définir l'icône de cette boîte de dialogue.  L'infrastructure effectue cela automatiquement
	//  lorsque la fenêtre principale de l'application n'est pas une boîte de dialogue
	
	// TODO: ajoutez ici une initialisation supplémentaire

	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

MainScreen::~MainScreen()
{
}

void MainScreen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
void MainScreen::SetChronogramData(vector<bool> states, vector<int> times)
{
	chrono.setSignalName(_T("Signal A"));
	chrono.setHeight(60);
	chrono.setStates(states, times);
}

BEGIN_MESSAGE_MAP(MainScreen, CDialogEx)
	ON_WM_PAINT()  // AJOUTER CETTE LIGNE - TRÈS IMPORTANT !
	ON_BN_CLICKED(IDC_RETOUR, &MainScreen::OnBnClickedRetour)
	ON_BN_CLICKED(IDOK, &MainScreen::OnBnClickedOk)
END_MESSAGE_MAP()

void MainScreen::OnPaint()
{
	
	CDialogEx::OnPaint();
	CClientDC dc(this); // Utilise CPaintDC pour OnPaint
	CRect rect;
	GetClientRect(&rect);

	
	SchemaDrawer drawer(&dc);


	vector<InputDataVector> inputData;
	vector<bool> resultVector;

	vector<bool> resultVectorCurrent;
	vector<int> times;
	// Ou si tu veux vraiment CClientDC :
	// CClientDC dc(this);
	FileReader fileReader;
	fileReader.readFile(m_path);
	times = fileReader.getDelays();
	inputData = fileReader.getPoints();


	float width = rect.Width() - 200;
	// Configurer et afficher
	Chronogram chrono(_T("S"), 100, rect.Height() - 130);
	int totaltime = 0;
	for (int i : times) totaltime += i;

	float timeScale = (width) / (float)totaltime;
	chrono.setTimeScale(timeScale);  // 0.5 pixel = 1ms


	//CString msg;
	//msg.Format(_T("gateScale = %f"), drawer.calculateGateScale());  // %d convertit true → 1, false → 0

	//AfxMessageBox(msg);


	chrono.setStates(resultVector, times);
	chrono.draw(&dc);
	
	int separatorY = rect.Height() - 160;
	int separatorY2 = 20;

	if (!m_expr.empty())
	{
		for (auto input : inputData)
			{
				bool result = drawer.evaluateSchema(m_expr, input);
				resultVector.push_back(result);
			}

		for (int i = 0; i < inputData.size();i++) {

			resultVectorCurrent.push_back(resultVector[i]);
			drawer.inputData = inputData[i];
			drawer.Clear(&dc);
			drawer.drawSchema(m_expr);
			chrono.setStates(resultVectorCurrent, times);
			chrono.draw(&dc);
			DrawSeparatorWithLabel(&dc, separatorY2, rect.Width() - 20, _T("SCHEMA"));

			DrawSeparatorWithLabel(&dc, separatorY, rect.Width() - 20, _T("CHRONOGRAMME"));


			Sleep(times[i]* multiplicateur);
		}

	
	}


}
// gestionnaires de messages de MainScreen
void MainScreen::OnBnClickedRestart()
{

	EndDialog(IDCANCEL); // ou EndDialog(ID_RETOUR);
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contrôle
}
void MainScreen::OnBnClickedRetour()
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contrôle
	EndDialog(IDCANCEL); // ou EndDialog(ID_RETOUR);
}

void MainScreen::OnBnClickedOk()
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contrôle
	CDialogEx::OnOK();
}
