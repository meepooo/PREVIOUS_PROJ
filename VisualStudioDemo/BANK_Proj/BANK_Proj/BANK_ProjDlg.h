
// BANK_ProjDlg.h : ͷ�ļ�
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

// CBANK_ProjDlg �Ի���
class CBANK_ProjDlg : public CDialogEx
{
// ����
public:
	CBANK_ProjDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BANK_PROJ_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	// ������
	CEdit SaveMoney;
	afx_msg void OnEnChangeEdit3();
	// �˿ں�
	CEdit Port;
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit4();
	// �����
	CString saveMoney;
	// ȡ����
	CString getMoney;
	afx_msg void OnEnChangeEdit6();
	CString sumValue;
	CString cPort;
};
