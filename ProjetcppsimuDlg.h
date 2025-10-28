
// ProjetcppsimuDlg.h : fichier d'en-tête
//

#pragma once


// boîte de dialogue de CProjetcppsimuDlg
class CProjetcppsimuDlg : public CDialogEx
{
// Construction
public:
	CProjetcppsimuDlg(CWnd* pParent = nullptr);	// constructeur standard
	CEdit m_editZone;
	

// Données de boîte de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJETCPPSIMU_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV


// Implémentation
protected:
	HICON m_hIcon;
		
	// Fonctions générées de la table des messages
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonB();
	afx_msg void OnBnClickedButtonA2();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButtonC();
	afx_msg void OnEnChangeEditEq();
	afx_msg void OnBnClickedButtonOr();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButtonAnd();
	afx_msg void OnBnClickedButtonXor();
	afx_msg void OnBnClickedButtonNot();
	afx_msg void OnBnClickedButtonOp();
	afx_msg void OnBnClickedButtonCp();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonSave();
	
};
