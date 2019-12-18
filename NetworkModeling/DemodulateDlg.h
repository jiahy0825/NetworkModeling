#pragma once

#include "ChartCtrl\ChartCtrl.h"
#include "ChartCtrl\ChartTitle.h"  //����ͷ�ļ�
#include "ChartCtrl\ChartLineSerie.h"  //����ͷ�ļ�
#include "ChartCtrl\ChartMouseListener.h"  //�����Ӧͷ�ļ�

#include <vector>

#define MESSAGE_UPDATEPOS_DEMODULATE WM_USER+1002

// CDemodulateDlg �Ի���

class CDemodulateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDemodulateDlg)

public:
	CDemodulateDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDemodulateDlg();

	// �Ի�������
	enum { IDD = IDD_DIALOG_DEMODULATE };

	// ���ɵ���Ϣӳ�亯��
	void drawPicture(std::vector<double>& vec);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnMessageUpdateposDemodulate(WPARAM wParam, LPARAM lParam);
};
