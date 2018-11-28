// TipDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "TipDlg.h"
#include "afxdialogex.h"
#include "MFCApplication1Dlg.h"
#include "string"


using namespace std;

// CTipDlg 对话框

IMPLEMENT_DYNAMIC(CTipDlg, CDialogEx)

CTipDlg::CTipDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, user(_T("账号/身份证号/姓名"))
	, passwd(_T(""))
{

}

CTipDlg::~CTipDlg()
{
}

void CTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, user);
	DDX_Text(pDX, IDC_EDIT2, passwd);
}


BEGIN_MESSAGE_MAP(CTipDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CTipDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CTipDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CTipDlg 消息处理程序


void CTipDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;

	if (WSAStartup(sockVersion, &data) != 0)
	{
		printf("invalid socket!");
	}
	//	while (true) {
	SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sclient == INVALID_SOCKET)
	{
		printf("invalid socket!");
	}

	//std::string portdata(CW2A(cPort.GetString()));
	//int iPort = atoi(portdata.c_str());

	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(iPort);
	//serAddr.sin_addr.S_un.S_addr = inet_addr("123.56.223.8");
	inet_pton(AF_INET, "123.56.223.8", (void *)&serAddr.sin_addr.S_un.S_addr);
	if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{  //连接失败 
		printf("connect error !");
		closesocket(sclient);
	}
	std::string userdata(CW2A(user.GetString()));
	std::string passwddata(CW2A(passwd.GetString()));
	//const char * sendData;
	//sendData = savedata.c_str();   //string转const char* 
	//char * sendData = "你好，TCP服务端，我是客户端\n";

	//报文格式：交易代码，存款人姓名，账户，存款类型，日期，时间，ATM机器号，交易地址，币种，存款金额，银行支行行号，银行支行名称
	std::string savedata;
	savedata =
		"1003," + userdata + "," +
		passwddata + ","
		"这是一个密码测试程序";

	int nwLen = 1024;
	int nLen = 1024;

	wchar_t * pwBuf = new wchar_t[nwLen + 1];
	char * pBuf = new char[nLen + 1];

	ZeroMemory(pwBuf, nwLen * 2 + 2);
	MultiByteToWideChar(CP_ACP, 0, savedata.c_str(), savedata.length(), pwBuf, nwLen);
	WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	send(sclient, pBuf, strlen(pBuf), 0);
	//send(sclient, sendData, strlen(sendData), 0);
	//send()用来将数据由指定的socket传给对方主机
	//int send(int s, const void * msg, int len, unsigned int flags)
	//s为已建立好连接的socket，msg指向数据内容，len则为数据长度，参数flags一般设0
	//成功则返回实际传送出去的字符数，失败返回-1，错误原因存于error 

	char recData[255];
	int ret = recv(sclient, recData, 255, 0);
	if (ret > 0) {
		recData[ret] = 0x00;
		printf(recData);
	}

	closesocket(sclient);
	//	}

	//ZeroMemory(pwBuf, nwLen * 2 + 2);
	//memset(pBuf, 0, sizeof(pBuf));
	//MultiByteToWideChar(CP_ACP, 0, recData, strlen(recData), pwBuf, nwLen);
	//WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string recvstr;
	recvstr = UTF8ToGBK(recData);
		
	MessageBoxA(NULL, recvstr.c_str(), "返回密码", MB_OK);

	delete[]pwBuf;
	delete[]pBuf;
	WSACleanup();
	
	if (!strncmp(recData, "000000", 6))
	{
		CMFCApplication1Dlg appdlg;
		appdlg.iPort = iPort;
		char tmpdata[100];
		memset(tmpdata, 0, sizeof(tmpdata));
		getFiled(tmpdata, recData, 2, ",");
		appdlg.acctno = tmpdata;
		
		memset(tmpdata, 0, sizeof(tmpdata));
		getFiled(tmpdata, recvstr.c_str(), 3, ",");
		appdlg.acctname = tmpdata;
		appdlg.cName = appdlg.acctname.c_str();

		memset(tmpdata, 0, sizeof(tmpdata));
		getFiled(tmpdata, recData, 4, ",");
		appdlg.certno = tmpdata;
		appdlg.DoModal();
	}

	UpdateData(FALSE);
}


void CTipDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

string GBKToUTF8(const string &strGBK)
{
	string strOutUTF8 = "";
	WCHAR *str1;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char *str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	strOutUTF8 = str2;
	delete[] str1;
	str1 = NULL;
	delete[] str2;
	str2 = NULL;
	return strOutUTF8;
}

string UTF8ToGBK(const string &strUTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
	WCHAR *wszGBK = new WCHAR[len + 1];
	memset(wszGBK, 0, (len + 1) * sizeof(WCHAR));
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)strUTF8.c_str(), -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	//strUTF8 = szGBK;
	string strTemp(szGBK);
	delete[] szGBK;
	szGBK = NULL;
	delete[] wszGBK;
	wszGBK = NULL;
	return strTemp;
}

char * getFiled(char *value, const char *sBuf, int iNum, char *sSign)
{
	const char *pf = NULL;
	const char *pb = NULL;
	int i = 0;
	int iLen = 0;

	pf = sBuf;
	pb = sBuf;

	iLen = strlen(sSign);

	for (i = 0; i<iNum; i++)
	{
		pb = strstr(pb, sSign);
		pb += iLen;
	}
	pf = strstr(pb, sSign);

	iLen = pf - pb;

	if (iLen == 0)
	{
		value[0] = 0;
		return value;
	}

	memcpy(value, pb, iLen);

	return value;
}