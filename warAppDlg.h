
// warAppDlg.h: 头文件
//

#pragma once

class CwarAppDlgAutoProxy;


typedef struct newPos {
	long lleftX;
	long ltopY;
	long lwidth;
	long lheight;
	bool bSet;
}NEWPOS, * LPNEWPOS;

// CwarAppDlg 对话框
class CwarAppDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CwarAppDlg);
	friend class CwarAppDlgAutoProxy;

// 构造
public:
	CwarAppDlg(CWnd* pParent = nullptr);	// 标准构造函数
	virtual ~CwarAppDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WARAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CwarAppDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

public:
	CWnd* p_PictureOfHero; //Hero picture in main.

	HeroMain structHeroState; //Set hero properties struct.
	
	CStatic showPicByguide;

	CRect m_DlgOriginRect;
	CRect m_DlgOriginRectBTN_OK;

	int iOriginCX;

	int iOriginCY;

	void RePaint(UINT ID, double cx, double cy);
	
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
