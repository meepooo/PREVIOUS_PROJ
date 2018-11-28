#pragma once

std::string GBKToUTF8(const std::string &strGBK);
std::string UTF8ToGBK(const std::string &strUTF8);
char * getFiled(char *value, const char *sBuf, int iNum, char *sSign);
#include <WS2tcpip.h>
// CTipDlg 对话框

class CTipDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTipDlg)

public:
	CTipDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTipDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	// 登录用户名
	CString user;
	// 登录密码
	CString passwd;
	int iPort;
	afx_msg void OnBnClickedOk();
};
