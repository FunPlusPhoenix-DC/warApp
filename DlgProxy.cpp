
// DlgProxy.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "warApp.h"
#include "DlgProxy.h"
#include "warAppDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CwarAppDlgAutoProxy

IMPLEMENT_DYNCREATE(CwarAppDlgAutoProxy, CCmdTarget)

CwarAppDlgAutoProxy::CwarAppDlgAutoProxy()
{
	EnableAutomation();

	// 为使应用程序在自动化对象处于活动状态时一直保持
	//	运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序的主窗口指针
	//  来访问对话框。  设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CwarAppDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CwarAppDlg)))
		{
			m_pDialog = reinterpret_cast<CwarAppDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CwarAppDlgAutoProxy::~CwarAppDlgAutoProxy()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	//	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != nullptr)
		m_pDialog->m_pAutoProxy = nullptr;
	AfxOleUnlockApp();
}

void CwarAppDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CwarAppDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CwarAppDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_IwarApp 的支持来支持类型安全绑定
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {65174735-235b-461f-9600-df46259b7341}
static const IID IID_IwarApp =
{0x65174735,0x235b,0x461f,{0x96,0x00,0xdf,0x46,0x25,0x9b,0x73,0x41}};

BEGIN_INTERFACE_MAP(CwarAppDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CwarAppDlgAutoProxy, IID_IwarApp, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏是在此项目的 pch.h 中定义的
// {775ba55b-5ad4-472b-bdbd-36160b27ca4f}
IMPLEMENT_OLECREATE2(CwarAppDlgAutoProxy, "warApp.Application", 0x775ba55b,0x5ad4,0x472b,0xbd,0xbd,0x36,0x16,0x0b,0x27,0xca,0x4f)


// CwarAppDlgAutoProxy 消息处理程序
