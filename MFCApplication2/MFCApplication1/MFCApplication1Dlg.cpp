
// MFCApplication1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "TipDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCApplication1Dlg 对话框



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


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
			{  //连接失败 
				printf("connect error !");
				closesocket(sclient);
			}
			//std::string savedata(CW2A(dSaveMoney.GetString()));
			//const char * sendData;
			//sendData = savedata.c_str();   //string转const char* 
			//char * sendData = "你好，TCP服务端，我是客户端\n";
	
			struct tm time_m;
			const time_t t = time(0);
			char tmpdate[64];
			localtime_s(&time_m, &t);
			strftime(tmpdate, sizeof(tmpdate), "%Y-%m-%d", &time_m);
			char tmptime[64];
			strftime(tmptime, sizeof(tmptime), "%H:%M:%S", &time_m);
			//报文格式：交易代码，取款人姓名，账户，日期，时间，ATM机器号，交易地址，币种，取款金额，银行支行行号，银行支行名称
			std::string savedata;
			savedata =
				trancode + "," + acctname + "," + acctno + ",活期," + tmpdate + "," + tmptime +
				",420111222,湖北省武汉市,人民币," + std::to_string(dSaveMoney) + ","
				"420010787," +
				"湖北省武汉建行分行," +
				"这是一个存款测试程序";

			//报文格式：交易代码，存款人姓名，账户，存款类型，日期，时间，ATM机器号，交易地址，币种，存款金额，银行支行行号，银行支行名称
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
				//send()用来将数据由指定的socket传给对方主机
				//int send(int s, const void * msg, int len, unsigned int flags)
				//s为已建立好连接的socket，msg指向数据内容，len则为数据长度，参数flags一般设0
				//成功则返回实际传送出去的字符数，失败返回-1，错误原因存于error 
	
			char recData[255];
			int ret = recv(sclient, recData, 255, 0);
			if (ret>0) {
				recData[ret] = 0x00;
				printf(recData);
			}
	
			closesocket(sclient);
	//	}
		MessageBoxA(NULL, UTF8ToGBK(recData).c_str(), "返回报文", MB_OK);
		//MessageBoxA(NULL, recData, "服务器返回", MB_OK);
	
		//delete[]pwBuf;
		//delete[]pBuf;
		WSACleanup();
		UpdateData(FALSE);
}


void CMFCApplication1Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
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
	//sendData = savedata.c_str();   //string转const char* 
	//char * sendData = "你好，TCP服务端，我是客户端\n";

	struct tm time_m;
	const time_t t = time(0);
	char tmpdate[64];
	localtime_s(&time_m, &t);
	strftime(tmpdate, sizeof(tmpdate), "%Y-%m-%d", &time_m);
	char tmptime[64];
	strftime(tmptime, sizeof(tmptime), "%H:%M:%S", &time_m);
	//报文格式：交易代码，取款人姓名，账户，日期，时间，ATM机器号，交易地址，币种，取款金额，银行支行行号，银行支行名称
	std::string savedata;
	savedata =
		trancode +","+ acctname + "," + acctno + "," + tmpdate + "," + tmptime + 
		",420111222,湖北省武汉市,人民币," + std::to_string(dGetMoney) + ","
		"420010787," +
		"湖北省武汉建行分行," +
		"这是一个取款测试程序";

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
	if (ret>0) {
		recData[ret] = 0x00;
		printf(recData);
	}

	closesocket(sclient);
	//	}
	MessageBoxA(NULL, UTF8ToGBK(recData).c_str(), "返回报文", MB_OK);
	//MessageBoxA(NULL, recData, "服务器返回", MB_OK);

	delete[]pwBuf;
	delete[]pBuf;
	WSACleanup();
	UpdateData(FALSE);
}


void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
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
	{  //连接失败 
		printf("connect error !");
		closesocket(sclient);
	}
	std::string savedata(CW2A(cName.GetString()));
	//const char * sendData;
	//sendData = savedata.c_str();   //string转const char* 
	//char * sendData = "你好，TCP服务端，我是客户端\n";

	//报文格式：交易代码，取款人姓名，账户，存款类型，日期，时间，ATM机器号，交易地址，币种，取款金额，银行支行行号，银行支行名称
	//std::string savedata;
	savedata = trancode + "," + savedata + ","+ acctno.c_str() +",这是一个查询余额测试程序";

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
	if (ret>0) {
		recData[ret] = 0x00;
		printf(recData);
	}

	closesocket(sclient);
	//	}
	MessageBoxA(NULL, UTF8ToGBK(recData).c_str(), "返回报文", MB_OK);

	//MessageBoxA(NULL, recData, "服务器返回", MB_OK);

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
	// TODO: 在此添加控件通知处理程序代码
	INT_PTR nRes;             // 用于保存DoModal函数的返回值   

	CTipDlg tipDlg;           // 构造对话框类CTipDlg的实例   
	nRes = tipDlg.DoModal();  // 弹出对话框   
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


void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CMFCApplication1Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication1Dlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
