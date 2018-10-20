
// MFCApplication1Dlg.h : 头文件
//

#pragma once
#include <time.h>

// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
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
	// 端口号
	int iPort;
	// 存款金额
	double dSaveMoney;
	// 取款金额
	double dGetMoney;
	// 姓名
	CString cName;
	std::string acctno;
	std::string acctname;
	std::string certno;
	std::string trancode;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	// 余额
	double dQueryBal;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
};
