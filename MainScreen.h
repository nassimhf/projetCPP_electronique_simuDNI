#pragma once
#include "afxdialogex.h"
#include <string>
#include "Chronogram.h"
#include <thread>
#include <atomic>
using namespace std;

// boîte de dialogue de MainScreen

class MainScreen : public CDialogEx
{
	DECLARE_DYNAMIC(MainScreen)

public:
	MainScreen(CWnd* pParent = nullptr);   // constructeur standard
	virtual BOOL OnInitDialog();
	virtual ~MainScreen();
	void SetChronogramData(vector<bool> states, vector<int> times);
	
	Chronogram chrono;
	string m_expr;
	string m_path;

// Données de boîte de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV
	afx_msg void OnPaint();  // Ajoutez cette ligne
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRestart();
	afx_msg void OnBnClickedRetour();



	afx_msg void OnBnClickedOk();
};
