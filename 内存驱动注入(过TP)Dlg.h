
// 内存驱动注入(过TP)Dlg.h: 头文件
//

#pragma once


// C内存驱动注入过TPDlg 对话框
class C内存驱动注入过TPDlg : public CDialogEx
{
// 构造
public:
	C内存驱动注入过TPDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//鼠标按下，抬起和移动的响应函数
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CPoint m_ptMove;
	CPoint m_ptOffset;
	BOOL m_bIsLButtonDown;
	CImageList m_imgDrag;
	CStatic m_StaticTest;
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void GetCursorProcess(POINT point, OUT DWORD32* dwPid, OUT char* szFileName, int size);
	CStatic m_BitMap;
	DWORD m_dwPid;//保存最后一次拖拽的Pid;
	char* m_szFileName[1024];
};
