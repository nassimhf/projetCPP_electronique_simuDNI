
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
	CEdit m_path_text;
	CFont m_fontStatic;
	

	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);

// Données de boîte de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJETCPPSIMU_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV


// Implémentation
protected:
	HICON m_hIcon;
		
	
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonB();
	afx_msg void OnBnClickedButtonA2();

	afx_msg void OnBnClickedButtonC();
	afx_msg void OnEnChangeEditEq();
	afx_msg void OnBnClickedButtonOr();

	afx_msg void OnBnClickedButtonAnd();
	afx_msg void OnBnClickedButtonXor();
	afx_msg void OnBnClickedButtonNot();
	afx_msg void OnBnClickedButtonOp();
	afx_msg void OnBnClickedButtonCp();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonSave();
	
	
	afx_msg void OnBnClickedButtonPath();
	afx_msg void OnEnChangeEditPath();
	afx_msg void OnBnClickedCancel();

	

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
