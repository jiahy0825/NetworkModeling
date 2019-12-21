// DemodulateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NetworkModeling.h"
#include "DemodulateDlg.h"
#include "afxdialogex.h"


double demodulate_x;
double demodulate_y;

// CDemodulateDlg �Ի���

IMPLEMENT_DYNAMIC(CDemodulateDlg, CDialogEx)

CDemodulateDlg::CDemodulateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDemodulateDlg::IDD, pParent)
{
	pAxis = NULL;
	m_index = 100;
}

CDemodulateDlg::~CDemodulateDlg()
{
}

class CCustomCursorListenerDemodulate : public CChartCursorListener
{
public:
	void OnCursorMoved(CChartCursor *pCursor, double xValue, double yValue)
	{
		demodulate_x = xValue;
		demodulate_y = yValue;
		SendMessage(m_hwnd, MESSAGE_UPDATEPOS_DEMODULATE, 0, 0);
		// Do something with the string...
	}

	void GetHwnd(HWND hwnd)
	{
		m_hwnd = hwnd;
	}
	HWND m_hwnd;
};

// �Ի����ڴ˴�������ͼ
void CDemodulateDlg::drawPicture(std::vector<double>& vec, bool dynamic){
	m_ChartCtrl_Demodulate.EnableRefresh(false);
	// ��������
	pAxis = m_ChartCtrl_Demodulate.CreateStandardAxis(CChartCtrl::BottomAxis);
	pAxis->SetAutomatic(true);
	pAxis = m_ChartCtrl_Demodulate.CreateStandardAxis(CChartCtrl::LeftAxis);
	pAxis->SetAutomatic(true);

	// �������
	TChartString str1;
	str1 = _T("OOK ���ͼ��");
	m_ChartCtrl_Demodulate.GetTitle()->AddString(str1);

	// �������
	m_ChartCtrl_Demodulate.GetTitle()->SetColor(RGB(255, 255, 255));   //���������ɫ
	m_ChartCtrl_Demodulate.GetLeftAxis()->SetTextColor(RGB(255, 255, 255));  //���������ɫ
	m_ChartCtrl_Demodulate.GetBottomAxis()->SetTextColor(RGB(255, 255, 255));  //�ײ��������ɫ
	m_ChartCtrl_Demodulate.SetBorderColor(RGB(255, 255, 255));  //�߿���ɫ��ɫ
	m_ChartCtrl_Demodulate.SetBackColor(RGB(85, 85, 85));  //������ɫ���ɫ

	int size = 0;
	if (dynamic){
		m_vec = vec;
		m_index = 100;
		size = min(100, vec.size());
	}else{
		size = vec.size();
	}

	double* X1Values = (double*)malloc(sizeof(double) * size);
	double* Y1Values = (double*)malloc(sizeof(double) * size);
	for (int i = 0; i < size; i++)
	{
		X1Values[i] = i + 1;
		Y1Values[i] = vec[i];
	}

	// ��ʼ�滭����ͼ
	m_ChartCtrl_Demodulate.SetZoomEnabled(true);
	m_ChartCtrl_Demodulate.RemoveAllSeries();//�����
	pLineSerie = m_ChartCtrl_Demodulate.CreateLineSerie();
	pLineSerie->SetSeriesOrdering(poNoOrdering);//����Ϊ����
	pLineSerie->AddPoints(X1Values, Y1Values, size);

	// �����������¼�
	CCustomCursorListenerDemodulate* m_pCursorListener;
	CChartCrossHairCursor* pCrossHair =
		m_ChartCtrl_Demodulate.CreateCrossHairCursor();

	HWND hWnd = this->GetSafeHwnd();
	m_pCursorListener = new CCustomCursorListenerDemodulate;
	m_pCursorListener->GetHwnd(hWnd);
	pCrossHair->RegisterListener(m_pCursorListener);

	m_ChartCtrl_Demodulate.EnableRefresh(true);

	if (dynamic){
		SetTimer(1, 0, NULL);
	}
}

void CDemodulateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM_DEMODULATE, m_ChartCtrl_Demodulate);
}


BEGIN_MESSAGE_MAP(CDemodulateDlg, CDialogEx)
	ON_MESSAGE(MESSAGE_UPDATEPOS_DEMODULATE, &CDemodulateDlg::OnMessageUpdateposDemodulate)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDemodulateDlg ��Ϣ�������


afx_msg LRESULT CDemodulateDlg::OnMessageUpdateposDemodulate(WPARAM wParam, LPARAM lParam)
{
	CString s;
	s.Format(_T("x = %.2f,y = %.2f"), demodulate_x, demodulate_y);
	CStatic* pStatic;
	pStatic = (CStatic*)GetDlgItem(IDC_STATIC_DEMODULATE);
	pStatic->SetWindowText(s);
	return 1;
}


void CDemodulateDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	pLineSerie->AddPoint(m_index, m_vec[m_index]);
	m_index++;
	if (m_index >= m_vec.size()){
		KillTimer(1);
	}

	CDialogEx::OnTimer(nIDEvent);
}
