
// NetworkModelingDlg.h : ͷ�ļ�
//

#pragma once

#include "Huffman.h"
#include "ASCIICode.h"
#include "Hamming.h"
#include "OOK.h"

#include "ModulateDlg.h"
#include "DemodulateDlg.h"


// CNetworkModelingDlg �Ի���
class CNetworkModelingDlg : public CDialogEx
{
// ����
public:
	CNetworkModelingDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_NETWORKMODELING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString str_input;
	CString str_encode;
	CString str_module;
	CString str_decode;
	CString str_output;
	
	double sigma;
	int m_period;

	Huffman huffman;
	ASCIICode asciiCode;
	Hamming hamming;
	OOK ook;

	CModulateDlg* m_ModulateDlg[100];
	int m_ModulateDlg_index;
	CDemodulateDlg* m_DemodulateDlg[100];
	int m_DemodulateDlg_index;

	afx_msg void OnBnClickedButtonEncode();
	afx_msg void OnBnClickedButtonDecode();
	afx_msg void OnBnClickedButtonAsciiEncode();
	afx_msg void OnBnClickedButtonAsciiDecode();
	afx_msg void OnBnClickedButtonCorrect();
	afx_msg void OnBnClickedButtonDetect();
	afx_msg void OnBnClickedButtonModule();
	afx_msg void OnBnClickedButtonDemodule();
	afx_msg void OnBnClickedButtonNoise();
};
