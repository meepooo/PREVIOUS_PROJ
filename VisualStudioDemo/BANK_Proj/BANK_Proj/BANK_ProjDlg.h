
// BANK_ProjDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#define MAXLINE 4096  
#define IPADDR "127.0.0.1"

#include<WINSOCK2.H>
#include<STDIO.H>
#include<iostream>
#include<cstring>
#pragma comment(lib, "ws2_32.lib")
//#define _WINSOCK_DEPRECATED_NO_WARNINGS 0

// CBANK_ProjDlg 对话框
class CBANK_ProjDlg : public CDialogEx
{
// 构造
public:
	CBANK_ProjDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BANK_PROJ_DIALOG };
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
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	// 存入金额
	CEdit SaveMoney;
	afx_msg void OnEnChangeEdit3();
	// 端口号
	CEdit Port;
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit4();
	// 存款金额
	CString saveMoney;
	// 取款金额
	CString getMoney;
	afx_msg void OnEnChangeEdit6();
	CString sumValue;
	CString cPort;
};
