
// NetworkModelingDlg.h : 头文件
//

#pragma once

#include "Huffman.h"
#include "ASCIICode.h"
#include "Hamming.h"
#include "OOK.h"

#include "ModulateDlg.h"

// CNetworkModelingDlg 对话框
class CNetworkModelingDlg : public CDialogEx
{
// 构造
public:
	CNetworkModelingDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_NETWORKMODELING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString str_input;
	CString str_encode;
	CString str_decode;
	CString str_module;

	Huffman huffman;
	ASCIICode asciiCode;
	Hamming hamming;
	OOK ook;

	CModulateDlg* m_ModulateDlg;

	afx_msg void OnBnClickedButtonEncode();
	afx_msg void OnBnClickedButtonDecode();
	afx_msg void OnBnClickedButtonAsciiEncode();
	afx_msg void OnBnClickedButtonAsciiDecode();
	afx_msg void OnBnClickedButtonCorrect();
	afx_msg void OnBnClickedButtonDetect();
	afx_msg void OnBnClickedButtonModule();
	afx_msg void OnBnClickedButtonDemodule();
};
