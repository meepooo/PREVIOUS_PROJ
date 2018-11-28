// Dialgl1.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "Dialgl1.h"
#include "afxdialogex.h"
#include "MFCApplication1Dlg.h"
#include "TipDlg.h"

// CDialgl1 对话框

IMPLEMENT_DYNAMIC(CDialgl1, CDialogEx)

CDialgl1::CDialgl1(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG1, pParent)
{

}

CDialgl1::~CDialgl1()
{
}

void CDialgl1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialgl1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialgl1::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CDialgl1::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialgl1::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON6, &CDialgl1::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialgl1::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDialgl1::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CDialgl1::OnBnClickedButton5)
END_MESSAGE_MAP()


// CDialgl1 消息处理程序


void CDialgl1::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	INT_PTR nRes;             // 用于保存DoModal函数的返回值   

	CMFCApplication1Dlg dlg;           // 构造对话框类CTipDlg的实例   
	dlg.iPort = 8001;
	nRes = dlg.DoModal();  // 弹出对话框   
	if (IDCANCEL == nRes)     // 判断对话框退出后返回值是否为IDCANCEL，如果是则return，否则继续向下执行   
		return;

	if (nRes == IDOK)
	{
//		MessageBoxA(NULL, "OKOK", "press ok", MB_OK);
	}
	else if (nRes == IDCANCEL)
	{
//		MessageBoxA(NULL, "CANCEL", "press cancel", MB_OK);
	}
}


void CDialgl1::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CDialgl1::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CDialgl1::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	INT_PTR nRes;             // 用于保存DoModal函数的返回值   
	
	CMFCApplication1Dlg appdlg;           // 构造对话框类CTipDlg的实例   
	CTipDlg tipdlg;
	tipdlg.iPort = 8000;
	nRes = tipdlg.DoModal();  // 弹出对话框   
	if (IDCANCEL == nRes)     // 判断对话框退出后返回值是否为IDCANCEL，如果是则return，否则继续向下执行   
		return;

	if (nRes == IDOK)
	{
//		MessageBoxA(NULL, "OKOK", "press ok", MB_OK);
	}
	else if (nRes == IDCANCEL)
	{
//		MessageBoxA(NULL, "CANCEL", "press cancel", MB_OK);
	}
}


void CDialgl1::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	INT_PTR nRes;             // 用于保存DoModal函数的返回值   

	CMFCApplication1Dlg dlg;           // 构造对话框类CTipDlg的实例   
	dlg.iPort = 8002;
	nRes = dlg.DoModal();  // 弹出对话框   
	if (IDCANCEL == nRes)     // 判断对话框退出后返回值是否为IDCANCEL，如果是则return，否则继续向下执行   
		return;

	if (nRes == IDOK)
	{
//		MessageBoxA(NULL, "OKOK", "press ok", MB_OK);
	}
	else if (nRes == IDCANCEL)
	{
//		MessageBoxA(NULL, "CANCEL", "press cancel", MB_OK);
	}
}


void CDialgl1::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	INT_PTR nRes;             // 用于保存DoModal函数的返回值   

	CMFCApplication1Dlg dlg;           // 构造对话框类CTipDlg的实例   
	dlg.iPort = 8003;
	nRes = dlg.DoModal();  // 弹出对话框   
	if (IDCANCEL == nRes)     // 判断对话框退出后返回值是否为IDCANCEL，如果是则return，否则继续向下执行   
		return;

	if (nRes == IDOK)
	{
//		MessageBoxA(NULL, "OKOK", "press ok", MB_OK);
	}
	else if (nRes == IDCANCEL)
	{
//		MessageBoxA(NULL, "CANCEL", "press cancel", MB_OK);
	}
}


void CDialgl1::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	INT_PTR nRes;             // 用于保存DoModal函数的返回值   

	CMFCApplication1Dlg dlg;           // 构造对话框类CTipDlg的实例   
	dlg.iPort = 8004;
	nRes = dlg.DoModal();  // 弹出对话框   
	if (IDCANCEL == nRes)     // 判断对话框退出后返回值是否为IDCANCEL，如果是则return，否则继续向下执行   
		return;

	if (nRes == IDOK)
	{
//		MessageBoxA(NULL, "OKOK", "press ok", MB_OK);
	}
	else if (nRes == IDCANCEL)
	{
//		MessageBoxA(NULL, "CANCEL", "press cancel", MB_OK);
	}
}
