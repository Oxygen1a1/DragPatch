
// 内存驱动注入(过TP)Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "内存驱动注入(过TP).h"
#include "内存驱动注入(过TP)Dlg.h"
#include "afxdialogex.h"
#include <Psapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DRAGTIMER 0x123456
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


// C内存驱动注入过TPDlg 对话框



C内存驱动注入过TPDlg::C内存驱动注入过TPDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C内存驱动注入过TPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_asd, m_StaticTest);

	DDX_Control(pDX, IDC_BITMAP, m_BitMap);
}


BEGIN_MESSAGE_MAP(C内存驱动注入过TPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C内存驱动注入过TPDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	//鼠标左键按下，抬起，移动响应消息 
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// C内存驱动注入过TPDlg 消息处理程序

BOOL C内存驱动注入过TPDlg::OnInitDialog()
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

	HBITMAP hBitMap2 = (HBITMAP)::LoadImage(NULL, _T("res\\123.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_BitMap.SetBitmap(hBitMap2);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C内存驱动注入过TPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C内存驱动注入过TPDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C内存驱动注入过TPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C内存驱动注入过TPDlg::OnBnClickedOk()
{
#define TIMER_ID 1
	SetTimer(TIMER_ID, 100, 0);
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void C内存驱动注入过TPDlg::OnTimer(UINT_PTR nIDEvent)
{

	switch (nIDEvent) {
	case DRAGTIMER: {
		POINT point;
		GetCursorPos(&point);
		DWORD32 dwPid;
		char* szFileName = (char*)malloc(0x1000);
		GetCursorProcess(point, &dwPid, szFileName, 0x1000);
		CString csTest;
		csTest.Format("%d %s", dwPid, szFileName);
		m_StaticTest.SetWindowTextA(csTest);
		m_dwPid = dwPid;
		memcpy(m_szFileName, szFileName, strlen(szFileName));
		break;
	}
	}
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
}

void C内存驱动注入过TPDlg::GetCursorProcess(POINT point, OUT DWORD32* dwPid, OUT char* szFileName, int size)
{
	HWND hWnd = ::WindowFromPoint(point);
	DWORD _dwPid;
	GetWindowThreadProcessId(hWnd, &_dwPid);
	*dwPid = _dwPid;
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, _dwPid);
	::GetProcessImageFileName(hProcess, szFileName, size);

}

void C内存驱动注入过TPDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CRect   rectPic;

	POINT   ptPut = point;


	//获取图像控件对象边框
	GetDlgItem(IDC_BITMAP)->GetWindowRect(rectPic);

	ClientToScreen(&ptPut);//转换成x y 全局屏幕坐标

	if (rectPic.PtInRect(ptPut))//如果在控件围成的矩形中

	{
		SetTimer(DRAGTIMER, 50, 0);
		CBitmap     bitmapTemp, * pOldBitmap;

		//获取DC
		CDC* pDC = GetDlgItem(IDC_BITMAP)->GetDC(),

			* pMemDC = new CDC;

		//创建位图内存   

		bitmapTemp.CreateCompatibleBitmap(pDC, rectPic.Width(), rectPic.Height());

		pMemDC->CreateCompatibleDC(pDC);

		pOldBitmap = pMemDC->SelectObject(&bitmapTemp);

		pMemDC->BitBlt(0, 0, rectPic.Width(), rectPic.Height(), pDC, 0, 0, SRCCOPY);

		pMemDC->SelectObject(pOldBitmap);

		delete  pMemDC;

		ReleaseDC(pDC);

		m_bIsLButtonDown = TRUE;

		m_ptOffset.x = ptPut.x - rectPic.left;

		m_ptOffset.y = ptPut.y - rectPic.top;

		m_imgDrag.DeleteImageList();

		m_imgDrag.Create(rectPic.Width(), rectPic.Height(), ILC_COLOR32 | ILC_MASK, 0, 1);

		m_imgDrag.Add(&bitmapTemp, RGB(0, 0, 0));

		m_imgDrag.BeginDrag(0, m_ptOffset);


		m_imgDrag.DragEnter(NULL, ptPut);

		SetCapture();

	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void C内存驱动注入过TPDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CRect rect;
	GetClientRect(&rect);

	if (m_bIsLButtonDown)

	{

		CRect   rectPic;

		CWnd* pPic = GetDlgItem(IDC_BITMAP);

		ScreenToClient(&m_ptMove);

		pPic->GetWindowRect(rectPic);

		//pPic->MoveWindow(m_ptMove.x - m_ptOffset.x, m_ptMove.y - m_ptOffset.y, rectPic.Width(), rectPic.Height());

		m_bIsLButtonDown = FALSE;

		CImageList::DragLeave(this);

		CImageList::EndDrag();

		ReleaseCapture();

		pPic->Invalidate();
		
		KillTimer(DRAGTIMER);

		char* szInfo = (char*)malloc(0x1000);
		szInfo[0] = '\0';

		sprintf_s(szInfo,0x1000,"ProcessId:%d\nFileName:%s", m_dwPid, m_szFileName);

		MessageBox(szInfo, "Tips", MB_OK| MB_ICONINFORMATION);
	}


	CDialogEx::OnLButtonUp(nFlags, point);
}


void C内存驱动注入过TPDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if (m_bIsLButtonDown)

	{

		CRect       rtClient, rtPicture;
		CPoint tempPoint;
		GetClientRect(rtClient);

		m_ptMove = point;

		GetDlgItem(IDC_BITMAP)->GetWindowRect(rtPicture);

		ClientToScreen(&rtClient);

		ClientToScreen(&m_ptMove);

		//if (rtClient.left > m_ptMove.x - m_ptOffset.x)
		//	m_ptMove.x = rtClient.left + m_ptOffset.x;

		//if (rtClient.top > m_ptMove.y - m_ptOffset.y)
		//	m_ptMove.y = rtClient.top + m_ptOffset.y;

		//if ((rtClient.right - rtPicture.Width()) < (m_ptMove.x - m_ptOffset.x))
		//	m_ptMove.x = rtClient.right - rtPicture.Width() + m_ptOffset.x;

		//if (rtClient.bottom - rtPicture.Height() < (m_ptMove.y - m_ptOffset.y))
		//	m_ptMove.y = rtClient.bottom - rtPicture.Height() + m_ptOffset.y;

		CImageList::DragMove(m_ptMove);

	}

	CDialogEx::OnMouseMove(nFlags, point);
}