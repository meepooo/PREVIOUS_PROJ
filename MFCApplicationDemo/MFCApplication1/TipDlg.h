#pragma once

std::string GBKToUTF8(const std::string &strGBK);
std::string UTF8ToGBK(const std::string &strUTF8);
char * getFiled(char *value, const char *sBuf, int iNum, char *sSign);
#include <WS2tcpip.h>
// CTipDlg �Ի���

class CTipDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTipDlg)

public:
	CTipDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTipDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	// ��¼�û���
	CString user;
	// ��¼����
	CString passwd;
	int iPort;
	afx_msg void OnBnClickedOk();
};
