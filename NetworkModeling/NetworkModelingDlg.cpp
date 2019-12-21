
// NetworkModelingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NetworkModeling.h"
#include "NetworkModelingDlg.h"
#include "afxdialogex.h"

#include "Huffman.h"
#include "ASCIICode.h"
#include "Hamming.h"
#include "OOK.h"

#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNetworkModelingDlg 对话框



CNetworkModelingDlg::CNetworkModelingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNetworkModelingDlg::IDD, pParent)
	, str_input(_T(""))
	, str_encode(_T(""))
	, str_decode(_T(""))
	, str_module(_T(""))
	, sigma(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	for (int i = 0;i < 100;i++){
		m_ModulateDlg[i] = NULL;
		m_DemodulateDlg[i] = NULL;
	}
	m_ModulateDlg_index = 0;
	m_DemodulateDlg_index = 0;
}

void CNetworkModelingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CODE, str_input);
	DDX_Text(pDX, IDC_EDIT_BINARY, str_encode);
	DDX_Text(pDX, IDC_EDIT_ENCODE, str_decode);
	DDX_Text(pDX, IDC_EDIT_MODULE, str_module);
	DDX_Text(pDX, IDC_EDIT_SIGMA, sigma);
}

BEGIN_MESSAGE_MAP(CNetworkModelingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ENCODE, &CNetworkModelingDlg::OnBnClickedButtonEncode)
	ON_BN_CLICKED(IDC_BUTTON_DECODE, &CNetworkModelingDlg::OnBnClickedButtonDecode)
	ON_BN_CLICKED(IDC_BUTTON_ASCII_ENCODE, &CNetworkModelingDlg::OnBnClickedButtonAsciiEncode)
	ON_BN_CLICKED(IDC_BUTTON_ASCII_DECODE, &CNetworkModelingDlg::OnBnClickedButtonAsciiDecode)
	ON_BN_CLICKED(IDC_BUTTON_CORRECT, &CNetworkModelingDlg::OnBnClickedButtonCorrect)
	ON_BN_CLICKED(IDC_BUTTON_DETECT, &CNetworkModelingDlg::OnBnClickedButtonDetect)
	ON_BN_CLICKED(IDC_BUTTON_MODULE, &CNetworkModelingDlg::OnBnClickedButtonModule)
	ON_BN_CLICKED(IDC_BUTTON_DEMODULE, &CNetworkModelingDlg::OnBnClickedButtonDemodule)
	ON_BN_CLICKED(IDC_BUTTON_NOISE, &CNetworkModelingDlg::OnBnClickedButtonNoise)
END_MESSAGE_MAP()


// CNetworkModelingDlg 消息处理程序

BOOL CNetworkModelingDlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNetworkModelingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNetworkModelingDlg::OnPaint()
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
HCURSOR CNetworkModelingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNetworkModelingDlg::OnBnClickedButtonEncode()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string str = CT2A(str_input.GetBuffer());
	str_encode = huffman.encode(str).c_str();

	// 更新对话框的值
	UpdateData(FALSE);
}


void CNetworkModelingDlg::OnBnClickedButtonDecode()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string str = CT2A(str_encode.GetBuffer());
	str_decode = huffman.decode(str).c_str();

	// 更新对话框的值
	UpdateData(FALSE);
}


void CNetworkModelingDlg::OnBnClickedButtonAsciiEncode()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string str = CT2A(str_input.GetBuffer());
	str_encode = asciiCode.encode(str).c_str();

	// 更新对话框的值
	UpdateData(FALSE);
}


void CNetworkModelingDlg::OnBnClickedButtonAsciiDecode()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string str = CT2A(str_encode.GetBuffer());
	str_decode = asciiCode.decode(str).c_str();

	// 更新对话框的值
	UpdateData(FALSE);
}

// 011011011010有误
void CNetworkModelingDlg::OnBnClickedButtonCorrect()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string str = CT2A(str_input.GetBuffer());
	str = huffman.encode(str);
	str = hamming.encode(str);
	str_encode = str.c_str();

	// 更新对话框的值
	UpdateData(FALSE);
}


void CNetworkModelingDlg::OnBnClickedButtonDetect()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string str = CT2A(str_encode.GetBuffer());
	str = hamming.decode(str);
	str = huffman.decode(str);
	str_decode = str.c_str();

	// 更新对话框的值
	UpdateData(FALSE);
}


void CNetworkModelingDlg::OnBnClickedButtonModule()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	bool selected = IsDlgButtonChecked(IDC_CHECK_SLIDE);

	string str = CT2A(str_input.GetBuffer());
	str = huffman.encode(str);
	str = hamming.encode(str);
	str_encode = str.c_str();

	vector<double> modulePoints = ook.modulate(str, 16);
	str = ook.encode(modulePoints);
	str_module = str.c_str();

	//显示 m_ModulateDlg 对话框
	if (NULL == m_ModulateDlg[m_ModulateDlg_index]){   
        // 创建非模态对话框
        m_ModulateDlg[m_ModulateDlg_index] = new CModulateDlg();   
        m_ModulateDlg[m_ModulateDlg_index]->Create(IDD_DIALOG_MODULATE, this);
	}   
	// 显示非模态对话框
	m_ModulateDlg[m_ModulateDlg_index]->ShowWindow(SW_SHOW);   
	m_ModulateDlg[m_ModulateDlg_index]->drawPicture(modulePoints, selected);
	m_ModulateDlg_index++;

	// 更新对话框的值
	UpdateData(FALSE);
}


void CNetworkModelingDlg::OnBnClickedButtonDemodule()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	bool selected = IsDlgButtonChecked(IDC_CHECK_SLIDE);

	int period = 16;
	int idx = period / 2;
	string str = CT2A(str_module.GetBuffer());
	vector<double> modulePoints = ook.demodulate(ook.decode(str), period);

	str = "";
	while (idx < modulePoints.size()){
		if (modulePoints[idx] > 0.25){
			str += "1";
		}else{
			str += "0";
		}
		idx += period;
	}

	string binary = hamming.decode(str);
	if (binary != "Hamming Decode error"){
		str = huffman.decode(binary);
	}
	//str = huffman.decode(str);
	str = str + "\r\n" + binary;
	str_decode = str.c_str();
	
	//显示 m_ModulateDlg 对话框
	if (NULL == m_DemodulateDlg[m_DemodulateDlg_index]){   
        // 创建非模态对话框
        m_DemodulateDlg[m_DemodulateDlg_index] = new CDemodulateDlg();   
        m_DemodulateDlg[m_DemodulateDlg_index]->Create(IDD_DIALOG_DEMODULATE, this);
	}   
	// 显示非模态对话框
	m_DemodulateDlg[m_DemodulateDlg_index]->ShowWindow(SW_SHOW);
	m_DemodulateDlg[m_DemodulateDlg_index]->drawPicture(modulePoints, selected);
	m_DemodulateDlg_index++;

	// 更新对话框的值
	UpdateData(FALSE);
}


void CNetworkModelingDlg::OnBnClickedButtonNoise()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	
	bool selected = IsDlgButtonChecked(IDC_CHECK_SLIDE);

	int period = 16;
	string str = CT2A(str_module.GetBuffer());
	vector<double> modulePoints = ook.demodulate(ook.decode(str), period);
	modulePoints = ook.addNoise(modulePoints, sigma);

	str = ook.encode(modulePoints);
	str_module = str.c_str();

		//显示 m_ModulateDlg 对话框
	if (NULL == m_ModulateDlg[m_ModulateDlg_index]){   
        // 创建非模态对话框
        m_ModulateDlg[m_ModulateDlg_index] = new CModulateDlg();   
        m_ModulateDlg[m_ModulateDlg_index]->Create(IDD_DIALOG_MODULATE, this);
	}   
	// 显示非模态对话框
	m_ModulateDlg[m_ModulateDlg_index]->ShowWindow(SW_SHOW);   
	m_ModulateDlg[m_ModulateDlg_index]->drawPicture(modulePoints, selected);
	m_ModulateDlg_index++;

	UpdateData(FALSE);
}
