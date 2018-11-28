
// MFCApplication1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "TipDlg.h"

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


// CMFCApplication1Dlg �Ի���



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
	, iPort(1)
	, dSaveMoney(0.00)
	, dGetMoney(0.00)
	, cName(_T(""))
	, dQueryBal(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, iPort);
	DDV_MinMaxInt(pDX, iPort, 1, 65535);
	DDX_Text(pDX, IDC_EDIT2, dSaveMoney);
	DDX_Text(pDX, IDC_EDIT3, dGetMoney);
	DDX_Text(pDX, IDC_EDIT4, cName);
	DDX_Text(pDX, IDC_EDIT5, dQueryBal);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication1Dlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplication1Dlg::OnEnChangeEdit2)
END_MESSAGE_MAP()


// CMFCApplication1Dlg ��Ϣ�������

BOOL CMFCApplication1Dlg::OnInitDialog()
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

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1Dlg::OnPaint()
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication1Dlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;

	trancode = "1000";

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
			//std::string savedata(CW2A(dSaveMoney.GetString()));
			//const char * sendData;
			//sendData = savedata.c_str();   //stringתconst char* 
			//char * sendData = "��ã�TCP����ˣ����ǿͻ���\n";
	
			struct tm time_m;
			const time_t t = time(0);
			char tmpdate[64];
			localtime_s(&time_m, &t);
			strftime(tmpdate, sizeof(tmpdate), "%Y-%m-%d", &time_m);
			char tmptime[64];
			strftime(tmptime, sizeof(tmptime), "%H:%M:%S", &time_m);
			//���ĸ�ʽ�����״��룬ȡ�����������˻������ڣ�ʱ�䣬ATM�����ţ����׵�ַ�����֣�ȡ�������֧���кţ�����֧������
			std::string savedata;
			savedata =
				trancode + "," + acctname + "," + acctno + ",����," + tmpdate + "," + tmptime +
				",420111222,����ʡ�人��,�����," + std::to_string(dSaveMoney) + ","
				"420010787," +
				"����ʡ�人���з���," +
				"����һ�������Գ���";

			//���ĸ�ʽ�����״��룬������������˻���������ͣ����ڣ�ʱ�䣬ATM�����ţ����׵�ַ�����֣���������֧���кţ�����֧������
			send(sclient, savedata.c_str(), savedata.length(), 0);

			//int nwLen = 1024;
			//int nLen = 1024;
	
			//wchar_t * pwBuf = new wchar_t[nwLen + 1];
			//char * pBuf = new char[nLen + 1];
	
			//ZeroMemory(pwBuf, nwLen * 2 + 2);
			//MultiByteToWideChar(CP_ACP, 0, savedata.c_str(), savedata.length(), pwBuf, nwLen);
			//WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
	
			//send(sclient, pBuf, strlen(pBuf), 0);
			//send(sclient, sendData, strlen(sendData), 0);
				//send()������������ָ����socket�����Է�����
				//int send(int s, const void * msg, int len, unsigned int flags)
				//sΪ�ѽ��������ӵ�socket��msgָ���������ݣ�len��Ϊ���ݳ��ȣ�����flagsһ����0
				//�ɹ��򷵻�ʵ�ʴ��ͳ�ȥ���ַ�����ʧ�ܷ���-1������ԭ�����error 
	
			char recData[255];
			int ret = recv(sclient, recData, 255, 0);
			if (ret>0) {
				recData[ret] = 0x00;
				printf(recData);
			}
	
			closesocket(sclient);
	//	}
		MessageBoxA(NULL, UTF8ToGBK(recData).c_str(), "���ر���", MB_OK);
		//MessageBoxA(NULL, recData, "����������", MB_OK);
	
		//delete[]pwBuf;
		//delete[]pBuf;
		WSACleanup();
		UpdateData(FALSE);
}


void CMFCApplication1Dlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;

	trancode = "1001";

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
	{
		printf("connect error !");
		closesocket(sclient);
	}
	//std::string savedata(CW2A(dSaveMoney.GetString()));
	//const char * sendData;
	//sendData = savedata.c_str();   //stringתconst char* 
	//char * sendData = "��ã�TCP����ˣ����ǿͻ���\n";

	struct tm time_m;
	const time_t t = time(0);
	char tmpdate[64];
	localtime_s(&time_m, &t);
	strftime(tmpdate, sizeof(tmpdate), "%Y-%m-%d", &time_m);
	char tmptime[64];
	strftime(tmptime, sizeof(tmptime), "%H:%M:%S", &time_m);
	//���ĸ�ʽ�����״��룬ȡ�����������˻������ڣ�ʱ�䣬ATM�����ţ����׵�ַ�����֣�ȡ�������֧���кţ�����֧������
	std::string savedata;
	savedata =
		trancode +","+ acctname + "," + acctno + "," + tmpdate + "," + tmptime + 
		",420111222,����ʡ�人��,�����," + std::to_string(dGetMoney) + ","
		"420010787," +
		"����ʡ�人���з���," +
		"����һ��ȡ����Գ���";

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
	if (ret>0) {
		recData[ret] = 0x00;
		printf(recData);
	}

	closesocket(sclient);
	//	}
	MessageBoxA(NULL, UTF8ToGBK(recData).c_str(), "���ر���", MB_OK);
	//MessageBoxA(NULL, recData, "����������", MB_OK);

	delete[]pwBuf;
	delete[]pBuf;
	WSACleanup();
	UpdateData(FALSE);
}


void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;

	trancode = "1002";
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
	std::string savedata(CW2A(cName.GetString()));
	//const char * sendData;
	//sendData = savedata.c_str();   //stringתconst char* 
	//char * sendData = "��ã�TCP����ˣ����ǿͻ���\n";

	//���ĸ�ʽ�����״��룬ȡ�����������˻���������ͣ����ڣ�ʱ�䣬ATM�����ţ����׵�ַ�����֣�ȡ�������֧���кţ�����֧������
	//std::string savedata;
	savedata = trancode + "," + savedata + ","+ acctno.c_str() +",����һ����ѯ�����Գ���";

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
	if (ret>0) {
		recData[ret] = 0x00;
		printf(recData);
	}

	closesocket(sclient);
	//	}
	MessageBoxA(NULL, UTF8ToGBK(recData).c_str(), "���ر���", MB_OK);

	//MessageBoxA(NULL, recData, "����������", MB_OK);

	delete[]pwBuf;
	delete[]pBuf;
	WSACleanup();

	char recBal[255];
	getFiled(recBal, recData, 2, ",");
//	char *p = strstr(recData, ",");
//	recData[p - recData] = 0;
//	dQueryBal = atof(recData);
	dQueryBal = atof(recBal);
	UpdateData(FALSE);
}


void CMFCApplication1Dlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	INT_PTR nRes;             // ���ڱ���DoModal�����ķ���ֵ   

	CTipDlg tipDlg;           // ����Ի�����CTipDlg��ʵ��   
	nRes = tipDlg.DoModal();  // �����Ի���   
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


void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CMFCApplication1Dlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication1Dlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
