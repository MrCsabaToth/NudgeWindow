
// NudgeWindowDlg.h : header file
//

#pragma once


// CNudgeWindowDlg dialog
class CNudgeWindowDlg : public CDialog
{
// Construction
public:
	CNudgeWindowDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_NUDGEWINDOW_DIALOG };

	CEdit	m_wndEdit;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	HWND GetTargetWindowHandle();
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButtonDestroy();
};
