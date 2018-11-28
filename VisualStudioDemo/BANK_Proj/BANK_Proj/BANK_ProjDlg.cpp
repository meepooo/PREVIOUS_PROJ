
// BANK_ProjDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BANK_Proj.h"
#include "BANK_ProjDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBANK_ProjDlg �Ի���



CBANK_ProjDlg::CBANK_ProjDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BANK_PROJ_DIALOG, pParent)
	, saveMoney(_T(""))
	, getMoney(_T(""))
	, sumValue(_T(""))
	, cPort(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBANK_ProjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDIT3, Port);
	DDX_Text(pDX, IDC_EDIT5, saveMoney);
	DDX_Text(pDX, IDC_EDIT4, getMoney);
	DDX_Text(pDX, IDC_EDIT6, sumValue);
	DDX_Text(pDX, IDC_EDIT3, cPort);
}

BEGIN_MESSAGE_MAP(CBANK_ProjDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CBANK_ProjDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CBANK_ProjDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT3, &CBANK_ProjDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT5, &CBANK_ProjDlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT4, &CBANK_ProjDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT6, &CBANK_ProjDlg::OnEnChangeEdit6)
END_MESSAGE_MAP()


// CBANK_ProjDlg ��Ϣ�������

BOOL CBANK_ProjDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CBANK_ProjDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBANK_ProjDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBANK_ProjDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBANK_ProjDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//WORD sockVersion = MAKEWORD(2, 2);
	//WSADATA data;

	//if (WSAStartup(sockVersion, &data) != 0)
	//{
	//	printf("invalid socket!");
	//}

	//SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//if (sclient == INVALID_SOCKET)
	//{
	//	printf("invalid socket!");
	//}

	//std::string portdata(CW2A(cPort.GetString()));
	//int iPort = atoi(portdata.c_str());

	//sockaddr_in serAddr;
	//serAddr.sin_family = AF_INET;
	//serAddr.sin_port = htons(iPort);
	//serAddr.sin_addr.S_un.S_addr = inet_addr("123.56.223.8");
	//if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	//{  //����ʧ�� 
	//	printf("connect error !");
	//	closesocket(sclient);
	//}
	//std::string savedata(CW2A(getMoney.GetString()));
	//const char * sendData;
	//sendData = savedata.c_str();   //stringתconst char* 
	//							   //char * sendData = "��ã�TCP����ˣ����ǿͻ���\n";

	//							   //���ĸ�ʽ�����״��룬ȡ�����������˻������ڣ�ʱ�䣬ATM�����ţ����׵�ַ�����֣�ȡ�������֧���кţ�����֧������
	//savedata =
	//	"1001,����,6225111122228888,2018-08-25,10:01:02,420111222,����ʡ�人��,�����," + savedata + ","
	//	"420010787," +
	//	"����ʡ�人���з���," +
	//	"����һ�����Գ���";

	//int nwLen = 1024;
	//int nLen = 1024;

	//wchar_t * pwBuf = new wchar_t[nwLen + 1];
	//char * pBuf = new char[nLen + 1];

	//ZeroMemory(pwBuf, nwLen * 2 + 2);
	//MultiByteToWideChar(CP_ACP, 0, savedata.c_str(), savedata.length(), pwBuf, nwLen);
	//WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	//send(sclient, pBuf, strlen(pBuf), 0);

	//char recData[255];
	//int ret = recv(sclient, recData, 255, 0);
	//if (ret>0) {
	//	recData[ret] = 0x00;
	//	printf(recData);
	//}

	//closesocket(sclient);
	//MessageBoxA(NULL, recData, "hello", MB_OK);

	//delete[]pwBuf;
	//delete[]pBuf;
	//WSACleanup();
}


void CBANK_ProjDlg::OnBnClickedButton1()
{
	CAboutDlg cAboutDlg;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	cAboutDlg.DoModal();
	CBANK_ProjDlg cDlg;
	cDlg.DoModal();

//	WORD sockVersion = MAKEWORD(2, 2);
//	WSADATA data;
//
//	if (WSAStartup(sockVersion, &data) != 0)
//	{
//		printf("invalid socket!");
//	}
////	while (true) {
//		SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//		if (sclient == INVALID_SOCKET)
//		{
//			printf("invalid socket!");
//		}
//
//		//std::string portdata(CW2A(cPort.GetString()));
//		int iPort = 8000;// atoi(portdata.c_str());
//		
//		sockaddr_in serAddr;
//		serAddr.sin_family = AF_INET;
//		serAddr.sin_port = htons(iPort);
//		serAddr.sin_addr.S_un.S_addr = inet_addr("123.56.223.8");
//		if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
//		{  //����ʧ�� 
//			printf("connect error !");
//			closesocket(sclient);
//		}
//		std::string savedata(CW2A(saveMoney.GetString()));
//		const char * sendData;
//		sendData = savedata.c_str();   //stringתconst char* 
//		//char * sendData = "��ã�TCP����ˣ����ǿͻ���\n";
//
//		//���ĸ�ʽ�����״��룬������������˻���������ͣ����ڣ�ʱ�䣬ATM�����ţ����׵�ַ�����֣���������֧���кţ�����֧������
//		savedata = 
//			"1000,����,6225111122228888,����,2018-08-25,10:01:02,420111222,����ʡ�人��,�����," + savedata + ","
//			"420010787," +
//			"����ʡ�人���з���," +
//			"����һ�����Գ���";
//
//		int nwLen = 1024;
//		int nLen = 1024;
//
//		wchar_t * pwBuf = new wchar_t[nwLen + 1];
//		char * pBuf = new char[nLen + 1];
//
//		ZeroMemory(pwBuf, nwLen * 2 + 2);
//		MultiByteToWideChar(CP_ACP, 0, savedata.c_str(), savedata.length(), pwBuf, nwLen);
//		WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
//
//		send(sclient, pBuf, strlen(pBuf), 0);
//		//send(sclient, sendData, strlen(sendData), 0);
//			//send()������������ָ����socket�����Է�����
//			//int send(int s, const void * msg, int len, unsigned int flags)
//			//sΪ�ѽ��������ӵ�socket��msgָ���������ݣ�len��Ϊ���ݳ��ȣ�����flagsһ����0
//			//�ɹ��򷵻�ʵ�ʴ��ͳ�ȥ���ַ�����ʧ�ܷ���-1������ԭ�����error 
//
//		char recData[255];
//		int ret = recv(sclient, recData, 255, 0);
//		if (ret>0) {
//			recData[ret] = 0x00;
//			printf(recData);
//		}
//
//		closesocket(sclient);
////	}
//	MessageBoxA(NULL, recData, "hello", MB_OK);
//
//	delete[]pwBuf;
//	delete[]pBuf;
//	WSACleanup();
}


void CBANK_ProjDlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CBANK_ProjDlg::OnEnChangeEdit5()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CBANK_ProjDlg::OnEnChangeEdit4()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CBANK_ProjDlg::OnEnChangeEdit6()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
