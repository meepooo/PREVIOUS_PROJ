// Dialgl1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "Dialgl1.h"
#include "afxdialogex.h"
#include "MFCApplication1Dlg.h"
#include "TipDlg.h"

// CDialgl1 �Ի���

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


// CDialgl1 ��Ϣ�������


void CDialgl1::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	INT_PTR nRes;             // ���ڱ���DoModal�����ķ���ֵ   

	CMFCApplication1Dlg dlg;           // ����Ի�����CTipDlg��ʵ��   
	dlg.iPort = 8001;
	nRes = dlg.DoModal();  // �����Ի���   
	if (IDCANCEL == nRes)     // �ж϶Ի����˳��󷵻�ֵ�Ƿ�ΪIDCANCEL���������return�������������ִ��   
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CDialgl1::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CDialgl1::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	INT_PTR nRes;             // ���ڱ���DoModal�����ķ���ֵ   
	
	CMFCApplication1Dlg appdlg;           // ����Ի�����CTipDlg��ʵ��   
	CTipDlg tipdlg;
	tipdlg.iPort = 8000;
	nRes = tipdlg.DoModal();  // �����Ի���   
	if (IDCANCEL == nRes)     // �ж϶Ի����˳��󷵻�ֵ�Ƿ�ΪIDCANCEL���������return�������������ִ��   
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	INT_PTR nRes;             // ���ڱ���DoModal�����ķ���ֵ   

	CMFCApplication1Dlg dlg;           // ����Ի�����CTipDlg��ʵ��   
	dlg.iPort = 8002;
	nRes = dlg.DoModal();  // �����Ի���   
	if (IDCANCEL == nRes)     // �ж϶Ի����˳��󷵻�ֵ�Ƿ�ΪIDCANCEL���������return�������������ִ��   
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	INT_PTR nRes;             // ���ڱ���DoModal�����ķ���ֵ   

	CMFCApplication1Dlg dlg;           // ����Ի�����CTipDlg��ʵ��   
	dlg.iPort = 8003;
	nRes = dlg.DoModal();  // �����Ի���   
	if (IDCANCEL == nRes)     // �ж϶Ի����˳��󷵻�ֵ�Ƿ�ΪIDCANCEL���������return�������������ִ��   
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	INT_PTR nRes;             // ���ڱ���DoModal�����ķ���ֵ   

	CMFCApplication1Dlg dlg;           // ����Ի�����CTipDlg��ʵ��   
	dlg.iPort = 8004;
	nRes = dlg.DoModal();  // �����Ի���   
	if (IDCANCEL == nRes)     // �ж϶Ի����˳��󷵻�ֵ�Ƿ�ΪIDCANCEL���������return�������������ִ��   
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
