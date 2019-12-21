#pragma once

#include "ChartCtrl\ChartCtrl.h"
#include "ChartCtrl\ChartTitle.h"  //����ͷ�ļ�
#include "ChartCtrl\ChartLineSerie.h"  //����ͷ�ļ�
#include "ChartCtrl\ChartPointsSerie.h"
#include "ChartCtrl\ChartMouseListener.h"  //�����Ӧͷ�ļ�

#include <vector>

#define MESSAGE_UPDATEPOS WM_USER+1001

// CModulateDlg �Ի���

class CModulateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModulateDlg)

public:
	CModulateDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModulateDlg();

	CChartCtrl m_ChartCtrl_Modulate;

// �Ի�������
	enum { IDD = IDD_DIALOG_MODULATE };

	// ���ɵ���Ϣӳ�亯��
	void drawPicture(std::vector<double>& vec);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnMessageUpdatepos(WPARAM wParam, LPARAM lParam);
};
