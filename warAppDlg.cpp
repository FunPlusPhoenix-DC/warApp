
// warAppDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "warApp.h"
#include "warAppDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include <iostream>
#include <xstring>
#include <WinUser.h>


#pragma warning (disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CwarAppDlg 对话框


IMPLEMENT_DYNAMIC(CwarAppDlg, CDialogEx);

CwarAppDlg::CwarAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WARAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = nullptr;
	p_PictureOfHero = new CWnd();
	iOriginCX = 0;
	iOriginCY = 0;
	iWidgetCount = 0;
	::memset(&m_WindowID, 0, sizeof(m_WindowID));
}

CwarAppDlg::~CwarAppDlg()
{
	// 如果该对话框有自动化代理，则
	//  此对话框的返回指针为 null，所以它知道
	//  此代理知道该对话框已被删除。
	if (m_pAutoProxy != nullptr)
		m_pAutoProxy->m_pDialog = nullptr;

	//delete target
	if (p_PictureOfHero != nullptr)
	{
		p_PictureOfHero->DestroyWindow();
		p_PictureOfHero = NULL;
	}
	
}

void CwarAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_HERO, showPicByguide);
}

BEGIN_MESSAGE_MAP(CwarAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CwarAppDlg::OnBnClickedButton1)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CwarAppDlg 消息处理程序

BOOL CwarAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	

	// TODO: 在此添加额外的初始化代码
	CWnd* wndTemp = GetWindow(GW_CHILD);
	m_WindowID[0] = wndTemp;
	m_WindowID[0]->GetWindowRect(&m_WidgetGroup[0]);
	ScreenToClient(&m_WidgetGroup[0]);
	iWidgetCount = 1;
	while (wndTemp = wndTemp->GetNextWindow())
	{
		m_WindowID[iWidgetCount] = wndTemp;
		m_WindowID[iWidgetCount]->GetWindowRect(&m_WidgetGroup[iWidgetCount]);
		ScreenToClient(&m_WidgetGroup[iWidgetCount]);
		++iWidgetCount;
	}
	::GetWindowRect(m_hWnd, m_DlgOriginRect);
	ScreenToClient(&m_DlgOriginRect);
	::GetWindowRect(GetDlgItem(IDOK)->m_hWnd, m_DlgOriginRectBTN_OK);
	ScreenToClient(&m_DlgOriginRectBTN_OK);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CwarAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CwarAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		//begin set parameter to target.
		p_PictureOfHero = GetDlgItem(IDC_PIC_HERO);
		//_T("C:\\Users\\37494\\Pictures\\Saved Pictures\\miku.jpg")
		CImage cimg_HeroPic;
		cimg_HeroPic.Load(_T("C:\\Users\\37494\\Pictures\\Saved Pictures\\miku.jpg"));
		RECT rec_IdcPicHero;
		p_PictureOfHero->GetWindowRect(&rec_IdcPicHero);
		CDC* pcdc_PictureOfHero = p_PictureOfHero->GetDC();
		pcdc_PictureOfHero->SetStretchBltMode(HALFTONE);	//保证拉伸后的图片不失真
		cimg_HeroPic.StretchBlt(pcdc_PictureOfHero->m_hDC, CRect(0, 0, 60, 19), 0); //实现图片大小
		cimg_HeroPic.Draw(pcdc_PictureOfHero->m_hDC,0,0,192,108);
		p_PictureOfHero->UpdateData();
		//end set parameter to target.
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CwarAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，如果控制器仍保持着它的某个
//  对象，则自动化服务器不应退出。  这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

void CwarAppDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CwarAppDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CwarAppDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CwarAppDlg::CanExit()
{
	// 如果代理对象仍保留在那里，则自动化
	//  控制器仍会保持此应用程序。
	//  使对话框保留在那里，但将其 UI 隐藏起来。
	if (m_pAutoProxy != nullptr)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}


void CwarAppDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD iRet = InitLogger("D:/WarDllLog");

	if (!iRet)
	{
		MessageBoxA(NULL, "Success to init", "iii", 0);
	}
	else
	{
		char szError[40]{ 0 };
		sprintf(szError, "GetlastError: %d", GetLastError());
		MessageBoxA(NULL, szError, "Warning", 0);
	}
	char szLog[50]{ 0 };

	sprintf(szLog, "%s", "This is english version");

	iRet = ExecuteLogger((LPVOID)szLog);

	if (iRet != 0)
	{
		char szError[40]{ 0 };
		sprintf(szError, "Last error code is :%d", iRet);
		MessageBoxA(NULL,szError, "GetLastError", 0);
	}

	HeroMain hm;

	RECT* picRect = new RECT; //原本用了CRECT，现在换回RECT看看结果。

	GetDlgItem(IDOK)->GetWindowRect(picRect);

	char szBuffer[256]{ 0 };

	sprintf(szBuffer, "left-top:%d-%d \n right-bottom:%d-%d",
		picRect->left,
		picRect->top,
		picRect->right,
		picRect->bottom);

	char szPosition[250]{ 0 };

	CRect buttonPosition;

	GetDlgItem(IDOK)->GetWindowRect(&buttonPosition);
	ScreenToClient(&buttonPosition);

	sprintf(szPosition, "position is below : \n "
		"(x,y)->(%d,%d)\n",
		buttonPosition.left,buttonPosition.top);

	MessageBoxA(NULL, szPosition, "position", 0);

	MessageBoxA(NULL, szBuffer, "OK's square", 0);

	delete picRect;

	picRect = NULL;

	hm.SetName("PathFinder");

	MessageBoxA(NULL, hm.GetName(), "Test", 0);
}


void CwarAppDlg::RePaint(UINT ID, double cx , double cy)
{
	CRect rect;

	//CWnd* p_wnd = NULL;

	//p_wnd = GetDlgItem(ID);

	/*if (p_wnd == NULL)
	{
		MessageBox(_T("No selected ID"), NULL, 0);
		return;
	}*/

	//p_wnd->GetWindowRect(&rect);

	//ScreenToClient(&rect);

		double ivalueX = cx * 1.0 / iOriginCX;
		double ivalueY = cy * 1.0 / iOriginCY;
		TRACE(_T("aaaiOriginCX:%lf\n"), iOriginCX);
		TRACE(_T("aaaiOriginCY:%lf\n"), iOriginCY);
		NEWPOS data{ 0 };

		if (ivalueX != 0)
		{
			data.lleftX = long((double)ivalueX * rect.left);
			data.bSet = true;
			rect.left = (long)((double)ivalueX * m_WidgetGroup[ID].left);//m_DlgOriginRectBTN_OK.left;
			rect.right = (long)((double)ivalueX * m_WidgetGroup[ID].right);//m_DlgOriginRectBTN_OK.right;
			TRACE(_T("m_WidgetGroup[ID].left:%d\n"), m_WidgetGroup[ID].left);
		}
		if (ivalueY != 0)
		{
			data.ltopY = long((double)ivalueY * rect.top);
			rect.top = (long)((double)ivalueY * m_WidgetGroup[ID].top);
			rect.bottom = (long)((double)ivalueY * m_WidgetGroup[ID].bottom);
			data.bSet = true;
			//rect.bottom = long((double)(ivalueY / iOriginCY) * rect.bottom);
		}
		TRACE(_T("ivaluex:%lf\n"), ivalueX);
		TRACE(_T("ivalueY:%lf\n"), ivalueY);
		//bool bMove = ::MoveWindow(p_wnd->GetSafeHwnd(), rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 1);
		if (data.bSet)
		{
			//p_wnd->SetWindowPos(&wndTop, data.lleftX, data.ltopY  , 88, 25, SWP_SHOWWINDOW | SWP_NOSIZE);
			//p_wnd->MoveWindow(&rect);
			m_WindowID[ID]->MoveWindow(&rect);
		}
		/*if (bMove)
		{
			MessageBoxA(NULL, "Move!", NULL, 0);
		}*/
	
}//精度有问题，客户区有问题

void CwarAppDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_DlgOriginRect.left == 0 && m_DlgOriginRect.right == 0
		&& m_DlgOriginRect.top == 0 && m_DlgOriginRect.bottom == 0)
	{
		goto FINAL;
	}
	else
	{
		if (cx == 0 && cy == 0)
		{
			return;
		}
		//test begin
		
		CRect picRect;
		GetDlgItem(IDOK)->GetWindowRect(picRect);
		TRACE(_T("m_DlgOriginRect.right:%d\n"), iOriginCX);
		TRACE(_T("m_DlgOriginRect.left:%d\n"), iOriginCX);
		iOriginCX = m_DlgOriginRect.right - m_DlgOriginRect.left;
		iOriginCY = m_DlgOriginRect.bottom - m_DlgOriginRect.top;
		//test end
		CRect recDlgChangeSize;
		this->GetClientRect(&recDlgChangeSize);
		ScreenToClient(&recDlgChangeSize);
		double lfValueCX = recDlgChangeSize.right - recDlgChangeSize.left;
		double lfValueCY = recDlgChangeSize.bottom - recDlgChangeSize.top;
		for (int i = 0; i < 32; i++)
		{
			if (m_WindowID[i] == nullptr)
				break;
			RePaint(i, lfValueCX, lfValueCY);
		}
		CDialogEx::OnPaint();
		return;
	}

	FINAL:
	this->GetWindowRect(&m_DlgOriginRect);
	//UpdateWindow();
	CDialogEx::OnPaint();
}
