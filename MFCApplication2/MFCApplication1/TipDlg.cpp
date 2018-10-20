// TipDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "TipDlg.h"
#include "afxdialogex.h"
#include "MFCApplication1Dlg.h"
#include "string"


using namespace std;

// CTipDlg �Ի���

IMPLEMENT_DYNAMIC(CTipDlg, CDialogEx)

CTipDlg::CTipDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, user(_T("�˺�/���֤��/����"))
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


// CTipDlg ��Ϣ�������


void CTipDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	{  //����ʧ�� 
		printf("connect error !");
		closesocket(sclient);
	}
	std::string userdata(CW2A(user.GetString()));
	std::string passwddata(CW2A(passwd.GetString()));
	//const char * sendData;
	//sendData = savedata.c_str();   //stringתconst char* 
	//char * sendData = "��ã�TCP����ˣ����ǿͻ���\n";

	//���ĸ�ʽ�����״��룬������������˻���������ͣ����ڣ�ʱ�䣬ATM�����ţ����׵�ַ�����֣���������֧���кţ�����֧������
	std::string savedata;
	savedata =
		"1003," + userdata + "," +
		passwddata + ","
		"����һ��������Գ���";

	int nwLen = 1024;
	int nLen = 1024;

	wchar_t * pwBuf = new wchar_t[nwLen + 1];
	char * pBuf = new char[nLen + 1];

	ZeroMemory(pwBuf, nwLen * 2 + 2);
	MultiByteToWideChar(CP_ACP, 0, savedata.c_str(), savedata.length(), pwBuf, nwLen);
	WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	send(sclient, pBuf, strlen(pBuf), 0);
	//send(sclient, sendData, strlen(sendData), 0);
	//send()������������ָ����socket�����Է�����
	//int send(int s, const void * msg, int len, unsigned int flags)
	//sΪ�ѽ��������ӵ�socket��msgָ���������ݣ�len��Ϊ���ݳ��ȣ�����flagsһ����0
	//�ɹ��򷵻�ʵ�ʴ��ͳ�ȥ���ַ�����ʧ�ܷ���-1������ԭ�����error 

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
		
	MessageBoxA(NULL, recvstr.c_str(), "��������", MB_OK);

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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