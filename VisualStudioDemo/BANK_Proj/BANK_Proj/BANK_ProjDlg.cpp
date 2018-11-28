
// BANK_ProjDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BANK_Proj.h"
#include "BANK_ProjDlg.h"
#include "afxdialogex.h"

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


// CBANK_ProjDlg 对话框



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


// CBANK_ProjDlg 消息处理程序

BOOL CBANK_ProjDlg::OnInitDialog()
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBANK_ProjDlg::OnPaint()
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
HCURSOR CBANK_ProjDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBANK_ProjDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
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
	//{  //连接失败 
	//	printf("connect error !");
	//	closesocket(sclient);
	//}
	//std::string savedata(CW2A(getMoney.GetString()));
	//const char * sendData;
	//sendData = savedata.c_str();   //string转const char* 
	//							   //char * sendData = "你好，TCP服务端，我是客户端\n";

	//							   //报文格式：交易代码，取款人姓名，账户，日期，时间，ATM机器号，交易地址，币种，取款金额，银行支行行号，银行支行名称
	//savedata =
	//	"1001,程琪,6225111122228888,2018-08-25,10:01:02,420111222,湖北省武汉市,人民币," + savedata + ","
	//	"420010787," +
	//	"湖北省武汉建行分行," +
	//	"这是一个测试程序";

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
	// TODO: 在此添加控件通知处理程序代码
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
//		{  //连接失败 
//			printf("connect error !");
//			closesocket(sclient);
//		}
//		std::string savedata(CW2A(saveMoney.GetString()));
//		const char * sendData;
//		sendData = savedata.c_str();   //string转const char* 
//		//char * sendData = "你好，TCP服务端，我是客户端\n";
//
//		//报文格式：交易代码，存款人姓名，账户，存款类型，日期，时间，ATM机器号，交易地址，币种，存款金额，银行支行行号，银行支行名称
//		savedata = 
//			"1000,程琪,6225111122228888,活期,2018-08-25,10:01:02,420111222,湖北省武汉市,人民币," + savedata + ","
//			"420010787," +
//			"湖北省武汉建行分行," +
//			"这是一个测试程序";
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
//			//send()用来将数据由指定的socket传给对方主机
//			//int send(int s, const void * msg, int len, unsigned int flags)
//			//s为已建立好连接的socket，msg指向数据内容，len则为数据长度，参数flags一般设0
//			//成功则返回实际传送出去的字符数，失败返回-1，错误原因存于error 
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
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CBANK_ProjDlg::OnEnChangeEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CBANK_ProjDlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CBANK_ProjDlg::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
