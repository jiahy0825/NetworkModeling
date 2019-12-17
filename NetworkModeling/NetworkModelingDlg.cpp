
// NetworkModelingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NetworkModeling.h"
#include "NetworkModelingDlg.h"
#include "afxdialogex.h"

#include "Huffman.h"
#include "ASCIICode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CNetworkModelingDlg �Ի���



CNetworkModelingDlg::CNetworkModelingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNetworkModelingDlg::IDD, pParent)
	, str_input(_T(""))
	, str_encode(_T(""))
	, str_decode(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetworkModelingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CODE, str_input);
	DDX_Text(pDX, IDC_EDIT_BINARY, str_encode);
	DDX_Text(pDX, IDC_EDIT_ENCODE, str_decode);
}

BEGIN_MESSAGE_MAP(CNetworkModelingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ENCODE, &CNetworkModelingDlg::OnBnClickedButtonEncode)
	ON_BN_CLICKED(IDC_BUTTON_DECODE, &CNetworkModelingDlg::OnBnClickedButtonDecode)
	ON_BN_CLICKED(IDC_BUTTON_ASCII_ENCODE, &CNetworkModelingDlg::OnBnClickedButtonAsciiEncode)
	ON_BN_CLICKED(IDC_BUTTON_ASCII_DECODE, &CNetworkModelingDlg::OnBnClickedButtonAsciiDecode)
END_MESSAGE_MAP()


// CNetworkModelingDlg ��Ϣ��������

BOOL CNetworkModelingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵������ӵ�ϵͳ�˵��С�

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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ����Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CNetworkModelingDlg::OnPaint()
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
HCURSOR CNetworkModelingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNetworkModelingDlg::OnBnClickedButtonEncode()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	UpdateData(TRUE);
	string str = CT2A(str_input.GetBuffer());
	str_encode = huffman.encode(str).c_str();

	// ���¶Ի����ֵ
	UpdateData(FALSE);
}


void CNetworkModelingDlg::OnBnClickedButtonDecode()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	UpdateData(TRUE);
	string str = CT2A(str_encode.GetBuffer());
	str_decode = huffman.decode(str).c_str();

	// ���¶Ի����ֵ
	UpdateData(FALSE);
}


void CNetworkModelingDlg::OnBnClickedButtonAsciiEncode()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	UpdateData(TRUE);
	string str = CT2A(str_input.GetBuffer());
	str_encode = asciiCode.encode(str).c_str();

	// ���¶Ի����ֵ
	UpdateData(FALSE);
}


void CNetworkModelingDlg::OnBnClickedButtonAsciiDecode()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	UpdateData(TRUE);
	string str = CT2A(str_encode.GetBuffer());
	str_decode = asciiCode.decode(str).c_str();

	// ���¶Ի����ֵ
	UpdateData(FALSE);
}