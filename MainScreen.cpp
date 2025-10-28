// MainScreen.cpp : fichier d'implémentation
//

#include "pch.h"
#include "Projetcppsimu.h"
#include "afxdialogex.h"
#include "MainScreen.h"
#include "SchemaDrawer.h"
#include "FileReader.h"
#include "resource.h"


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


BEGIN_MESSAGE_MAP(MainScreen, CDialogEx)
	ON_WM_PAINT()  // AJOUTER CETTE LIGNE - TRÈS IMPORTANT !

END_MESSAGE_MAP()

void MainScreen::OnPaint()
{
	CDialogEx::OnPaint();

	CClientDC dc(this); // Utilise CPaintDC pour OnPaint

	// Ou si tu veux vraiment CClientDC :
	// CClientDC dc(this);

	// Dessiner ton schéma ici
	SchemaDrawer drawer(&dc);
	if (!m_expr.empty())
	{
		CClientDC dc(this);
		SchemaDrawer drawer(&dc);
		drawer.drawSchema(m_expr);
	}
	

}
// gestionnaires de messages de MainScreen

void MainScreen::OnBnClickedRestart()
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contrôle


}
