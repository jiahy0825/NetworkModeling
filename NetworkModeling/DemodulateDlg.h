#pragma once

#include "ChartCtrl\ChartCtrl.h"
#include "ChartCtrl\ChartTitle.h"  //标题头文件
#include "ChartCtrl\ChartLineSerie.h"  //画线头文件
#include "ChartCtrl\ChartMouseListener.h"  //鼠标响应头文件

#include <vector>

#define MESSAGE_UPDATEPOS_DEMODULATE WM_USER+1002

// CDemodulateDlg 对话框

class CDemodulateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDemodulateDlg)

public:
	CDemodulateDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDemodulateDlg();

	// 对话框数据
	enum { IDD = IDD_DIALOG_DEMODULATE };

	// 生成的消息映射函数
	void drawPicture(std::vector<double>& vec);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnMessageUpdateposDemodulate(WPARAM wParam, LPARAM lParam);
};
