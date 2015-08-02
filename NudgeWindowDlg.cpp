
// NudgeWindowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NudgeWindow.h"
#include "NudgeWindowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CNudgeWindowDlg dialog




CNudgeWindowDlg::CNudgeWindowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNudgeWindowDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNudgeWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HWND_EDIT, m_wndEdit);
}

BEGIN_MESSAGE_MAP(CNudgeWindowDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CNudgeWindowDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CNudgeWindowDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_DESTROY, &CNudgeWindowDlg::OnBnClickedButtonDestroy)
END_MESSAGE_MAP()


HWND CNudgeWindowDlg::GetTargetWindowHandle()
{
	CString text;
	//m_wndEdit.GetLine(0, text.GetBuffer(256), 256);
	m_wndEdit.GetWindowText(text);
	UINT hexNum = wcstoul((const WCHAR *)text, NULL, 16);
	if (hexNum == 0 ||
		hexNum == LONG_MIN ||
		hexNum == LONG_MAX)
	{
		AfxMessageBox(_T("hWnd doesn't seem to be a valid hexa number."));
	}
	else
	{
		HWND hWnd = (HWND)hexNum;
		if (IsWindow(hWnd) != FALSE)
		{
			return hWnd;
		}
		else
		{
			AfxMessageBox(_T("hWnd doesn't seem to be a valid window handle. Please specify it in hex format."));
		}
	}
	return NULL;
}


// CNudgeWindowDlg message handlers

BOOL CNudgeWindowDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNudgeWindowDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNudgeWindowDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNudgeWindowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CNudgeWindowDlg::OnBnClickedOk()
{
	HWND hWnd = GetTargetWindowHandle();
	if (hWnd != NULL) {
		LRESULT lRes = ::SendMessage(hWnd, DM_REPOSITION, 0, 0);
		BOOL retVal = ::BringWindowToTop(hWnd);
	}
	// do not close the dialog
	// OnOK();
}

void CNudgeWindowDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CNudgeWindowDlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CNudgeWindowDlg::OnBnClickedButtonDestroy()
{
	HWND hWnd = GetTargetWindowHandle();
	if (hWnd != NULL) {
		BOOL retVal = ::DestroyWindow(hWnd);
	}
}
