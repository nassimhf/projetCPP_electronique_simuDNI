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
	chrono.setPosition(100, 150);
	chrono.setHeight(60);
	chrono.setTimeScale(0.5f);  // 0.5 pixel par ms
	chrono.setStates(states, times);
}

BEGIN_MESSAGE_MAP(MainScreen, CDialogEx)
	ON_WM_PAINT()  // AJOUTER CETTE LIGNE - TRÈS IMPORTANT !
	ON_BN_CLICKED(IDC_RETOUR, &MainScreen::OnBnClickedRetour)
END_MESSAGE_MAP()

void MainScreen::OnPaint()
{
	
	CDialogEx::OnPaint();
	CClientDC dc(this); // Utilise CPaintDC pour OnPaint

	vector<InputDataVector> inputData;
	vector<bool> resultVector;
	vector<int> times;
	// Ou si tu veux vraiment CClientDC :
	// CClientDC dc(this);
	FileReader fileReader;
	fileReader.readFile(m_path);
	times = fileReader.getDelays();
	inputData = fileReader.getPoints();

	// Dessiner  schéma
	SchemaDrawer drawer(&dc);
	if (!m_expr.empty())
	{
		CClientDC dc(this);
		SchemaDrawer drawer(&dc);
		drawer.drawSchema(m_expr);
	}

	for (auto input : inputData)
	{
		bool result = drawer.evaluateSchema(m_expr, input);
		resultVector.push_back(result);
	}

	// Configurer et afficher
	Chronogram chrono(_T("CLK"), 100, 600);
	chrono.setTimeScale(0.8f);  // 0.5 pixel = 1ms
	chrono.setStates(resultVector, times);
	chrono.draw(&dc);
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
