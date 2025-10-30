
// ProjetcppsimuDlg.cpp : fichier d'implémentation
//

#include "pch.h"
#include "framework.h"
#include "Projetcppsimu.h"
#include "ProjetcppsimuDlg.h"
#include "afxdialogex.h"
#include <string>
#include <iostream>
#include "MainScreen.h"
#include "Colors.h"
#include <atlimage.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif








class CAboutDlg : public CDialogEx
{
	
public:
	CAboutDlg();
	
// Données de boîte de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

// Implémentation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}





void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// boîte de dialogue de CProjetcppsimuDlg



CProjetcppsimuDlg::CProjetcppsimuDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJETCPPSIMU_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProjetcppsimuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_EQ, m_editZone);

	DDX_Control(pDX, IDC_EDIT_PATH, m_path_text);
}

BEGIN_MESSAGE_MAP(CProjetcppsimuDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_B, &CProjetcppsimuDlg::OnBnClickedButtonB)
	ON_BN_CLICKED(IDC_BUTTON_A2, &CProjetcppsimuDlg::OnBnClickedButtonA2)

	
	ON_WM_DRAWITEM()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_C, &CProjetcppsimuDlg::OnBnClickedButtonC)
	ON_EN_CHANGE(IDC_EDIT_EQ, &CProjetcppsimuDlg::OnEnChangeEditEq)
	ON_BN_CLICKED(IDC_BUTTON_OR, &CProjetcppsimuDlg::OnBnClickedButtonOr)
	ON_BN_CLICKED(IDC_BUTTON_AND, &CProjetcppsimuDlg::OnBnClickedButtonAnd)
	ON_BN_CLICKED(IDC_BUTTON_XOR, &CProjetcppsimuDlg::OnBnClickedButtonXor)
	ON_BN_CLICKED(IDC_BUTTON_NOT, &CProjetcppsimuDlg::OnBnClickedButtonNot)
	ON_BN_CLICKED(IDC_BUTTON_OP, &CProjetcppsimuDlg::OnBnClickedButtonOp)
	ON_BN_CLICKED(IDC_BUTTON_CP, &CProjetcppsimuDlg::OnBnClickedButtonCp)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CProjetcppsimuDlg::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CProjetcppsimuDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDOK, &CProjetcppsimuDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CProjetcppsimuDlg::OnBnClickedButtonSave)
	
	ON_BN_CLICKED(IDC_BUTTON_PATH, &CProjetcppsimuDlg::OnBnClickedButtonPath)
	ON_EN_CHANGE(IDC_EDIT_PATH, &CProjetcppsimuDlg::OnEnChangeEditPath)
	ON_BN_CLICKED(IDCANCEL, &CProjetcppsimuDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// gestionnaires de messages de CProjetcppsimuDlg

BOOL CProjetcppsimuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Ajouter l'élément de menu "À propos de..." au menu Système.
	SetBackgroundColor(APP_COLOR_LIGHT);





	int buttonIDs[] = { IDC_BUTTON1,IDC_BUTTON_DEL,IDCANCEL, IDC_BUTTON_A2, IDC_BUTTON_AND,IDC_BUTTON_B,IDC_BUTTON_C,IDC_BUTTON_CLEAR,IDC_BUTTON_XOR,IDC_BUTTON_NOT,IDC_BUTTON_SAVE,IDC_BUTTON13,IDC_BUTTON_OR,IDC_BUTTON_OP,IDC_BUTTON_CP};
	for (int id : buttonIDs)
	{
		CButton* pBtn = (CButton*)GetDlgItem(id);
		if (pBtn)
			pBtn->ModifyStyle(0, BS_OWNERDRAW);
	}




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
	SetIcon(m_hIcon, TRUE);			// Définir une grande icône
	SetIcon(m_hIcon, FALSE);		// Définir une petite icône

	// TODO: ajoutez ici une initialisation supplémentaire

	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

HBRUSH CProjetcppsimuDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_EDIT_EQ) // Remplace par ton ID
	{
		pDC->SetTextColor(RGB(50, 50, 50));       // couleur du texte
		pDC->SetBkColor(RGB(230, 230, 230));      // couleur du fond
		static CBrush brush(RGB(230, 230, 230));  // brosse pour le fond
		return brush;
	}

	return hbr;
}

void CProjetcppsimuDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	CRect rect = lpDrawItemStruct->rcItem;

	bool isPressed = (lpDrawItemStruct->itemState & ODS_SELECTED);
	bool isFocused = (lpDrawItemStruct->itemState & ODS_FOCUS);

	// --- Définir les couleurs ---
	COLORREF bgColor = RGB(245, 247, 250);  // fond par défaut clair
	COLORREF borderColor = RGB(200, 200, 200);
	COLORREF textColor = APP_COLOR_TEXT_PRIMARY;

	if (isPressed)
	{
		bgColor = APP_COLOR_PRIMARY;      // fond bleu foncé
		textColor = APP_COLOR_WHITE;
	}
	else if (isFocused)
	{
		bgColor = RGB(225, 235, 245);     // léger bleu clair
		borderColor = APP_COLOR_SECONDARY;
	}

	// --- Ombre subtile (effet relief) ---
	CRect shadowRect = rect;
	shadowRect.OffsetRect(2, 2);
	dc.FillSolidRect(shadowRect, RGB(220, 220, 220)); // ombre grise douce

	// --- Fond du bouton ---
	dc.FillSolidRect(rect, bgColor);

	// --- Bordure arrondie très fine ---
	CPen borderPen(PS_SOLID, 1, borderColor);
	dc.SelectObject(&borderPen);
	dc.RoundRect(rect, CPoint(8, 8));

	// --- Texte centré ---
	CString text;
	GetDlgItem(nIDCtl)->GetWindowText(text);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(textColor);
	dc.SelectObject(GetFont());
	dc.DrawText(text, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	dc.Detach();
}




void CProjetcppsimuDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Si vous ajoutez un bouton Réduire à votre boîte de dialogue, vous devez utiliser le code ci-dessous
//  pour dessiner l'icône.  Pour les applications MFC utilisant le modèle Document/Vue,
//  cela est fait automatiquement par l'infrastructure.

void CProjetcppsimuDlg::OnPaint()
{


	CPaintDC dc(this);
	
	if (IsIconic())
	{
	
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrer l'icône dans le rectangle client
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dessiner l'icône
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Le système appelle cette fonction pour obtenir le curseur à afficher lorsque l'utilisateur fait glisser
//  la fenêtre réduite.
HCURSOR CProjetcppsimuDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CProjetcppsimuDlg::OnBnClickedButtonB() ////////////
{
	CString currentText;
	m_editZone.GetWindowText(currentText);   // récupère le texte actuel
	currentText += _T("Y");                  // ajoute "A" à la suite
	m_editZone.SetWindowText(currentText);
}

void CProjetcppsimuDlg::OnBnClickedButtonA2() ////////////
{
	CString currentText;
	m_editZone.GetWindowText(currentText);   // récupère le texte actuel
	currentText += _T("X");                  // ajoute "A" à la suite
	m_editZone.SetWindowText(currentText);
	
	
}





void CProjetcppsimuDlg::OnBnClickedButtonC() /////////////
{
	CString currentText;
	m_editZone.GetWindowText(currentText);   // récupère le texte actuel
	currentText += _T("Z");                  // ajoute "A" à la suite
	m_editZone.SetWindowText(currentText);
}

void CProjetcppsimuDlg::OnEnChangeEditEq() ////////////////
{

	
	// TODO:  S'il s'agit d'un contrôle RICHEDIT, le contrôle ne
	// envoyez cette notification sauf si vous substituez CDialogEx::OnInitDialog()
	// fonction et appelle CRichEditCtrl().SetEventMask()
	// avec l'indicateur ENM_CHANGE ajouté au masque grâce à l'opérateur OR.

	// TODO:  Ajoutez ici le code de votre gestionnaire de notification de contrôle
}




void CProjetcppsimuDlg::OnBnClickedButtonOr()
{
	CString currentText;
	m_editZone.GetWindowText(currentText);   // récupère le texte actuel
	currentText += _T(" OR ");                  // ajoute "A" à la suite
	m_editZone.SetWindowText(currentText);
}


void CProjetcppsimuDlg::OnBnClickedButtonAnd()
{
	CString currentText;
	m_editZone.GetWindowText(currentText);   // récupère le texte actuel
	currentText += _T(" AND ");                  // ajoute "A" à la suite
	m_editZone.SetWindowText(currentText);
}

void CProjetcppsimuDlg::OnBnClickedButtonXor()
{
	CString currentText;
	m_editZone.GetWindowText(currentText);   // récupère le texte actuel
	currentText += _T(" XOR ");                  // ajoute "A" à la suite
	m_editZone.SetWindowText(currentText);
}

void CProjetcppsimuDlg::OnBnClickedButtonNot()
{
	CString currentText;
	m_editZone.GetWindowText(currentText);   // récupère le texte actuel
	currentText += _T(" NOT");                  // ajoute "A" à la suite
	m_editZone.SetWindowText(currentText);
}

void CProjetcppsimuDlg::OnBnClickedButtonOp()
{
	CString currentText;
	m_editZone.GetWindowText(currentText);   // récupère le texte actuel
	currentText += _T("(");                  // ajoute "A" à la suite
	m_editZone.SetWindowText(currentText);
}

void CProjetcppsimuDlg::OnBnClickedButtonCp()
{
	CString currentText;
	m_editZone.GetWindowText(currentText);   // récupère le texte actuel
	currentText += _T(")");                  // ajoute "A" à la suite
	m_editZone.SetWindowText(currentText);
}


void CProjetcppsimuDlg::OnBnClickedButtonDel()
{
	CString currentText;
	m_editZone.GetWindowText(currentText);   // récupère le texte actuel

	int len = currentText.GetLength();
	if (len > 0)
	{
		currentText.Delete(len - 1, 1);      // supprime le dernier caractère
		m_editZone.SetWindowText(currentText); // remet le texte modifié
	}
}

void CProjetcppsimuDlg::OnBnClickedButtonClear()
{
	m_editZone.SetWindowText(_T(""));
}

void CProjetcppsimuDlg::OnBnClickedOk()
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contrôle
	CDialogEx::OnOK();
}

void CProjetcppsimuDlg::OnBnClickedButtonSave()
{
		CString expression;
		m_editZone.GetWindowText(expression);
		CT2CA exprConverted(expression);
		std::string EXP_str(exprConverted);

		CString file_path;
		m_path_text.GetWindowText(file_path);
		CT2CA filePathConverted(file_path);
		std::string FILE_str(filePathConverted);

		// Masquer au lieu de fermer
		ShowWindow(SW_HIDE);

		MainScreen mainScreen;
		mainScreen.m_expr = EXP_str;
		mainScreen.m_path = FILE_str;

		INT_PTR result = mainScreen.DoModal();

		// Quand le 2ème dialogue se ferme
		if (result == IDCANCEL || result == IDC_Restart)// ID_RETOUR = valeur personnalisée
		{
			ShowWindow(SW_SHOW); // Réafficher le 1er dialogue
		}
		else
		{
			EndDialog(IDOK); // Fermer complètement si terminé
		}

}



void CProjetcppsimuDlg::OnBnClickedButtonPath()
{
	// Créer une boîte de dialogue de fichier pour ouvrir un fichier
	CFileDialog fileDlg(
		TRUE,                       // TRUE = Open dialog, FALSE = Save dialog
		_T("txt"),                  // Default file extension
		NULL,                       // Default file name
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		_T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||") // Filter
	);

	// Display the dialog
	if (fileDlg.DoModal() == IDOK)
	{
		CString filePath = fileDlg.GetPathName();  // Full path of the chosen file
		m_path_text.SetWindowText(filePath);  // Set the path in the edit control
		
		// Example: show the selected file path 
	}
}

void CProjetcppsimuDlg::OnEnChangeEditPath()
{
	// TODO:  S'il s'agit d'un contrôle RICHEDIT, le contrôle ne
	// envoyez cette notification sauf si vous substituez CDialogEx::OnInitDialog()
	// fonction et appelle CRichEditCtrl().SetEventMask()
	// avec l'indicateur ENM_CHANGE ajouté au masque grâce à l'opérateur OR.

	// TODO:  Ajoutez ici le code de votre gestionnaire de notification de contrôle
}

void CProjetcppsimuDlg::OnBnClickedCancel()
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contrôle
	CDialogEx::OnCancel();
}
