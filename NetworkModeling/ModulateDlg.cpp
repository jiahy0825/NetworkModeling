// ModulateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NetworkModeling.h"
#include "ModulateDlg.h"
#include "afxdialogex.h"

#include "OOK.h"


CChartCtrl m_ChartCtrl_Modulate;
double modulate_x;
double modulate_y;

// CModulateDlg �Ի���

IMPLEMENT_DYNAMIC(CModulateDlg, CDialogEx)

CModulateDlg::CModulateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CModulateDlg::IDD, pParent)
{

}

CModulateDlg::~CModulateDlg()
{
}

// �����������¼�
class CCustomCursorListener : public CChartCursorListener
{
public:
	void OnCursorMoved(CChartCursor *pCursor, double xValue, double yValue)
	{
		modulate_x = xValue;
		modulate_y = yValue;
		SendMessage(m_hwnd, MESSAGE_UPDATEPOS, 0, 0);
		// Do something with the string...
	}

	void GetHwnd(HWND hwnd)
	{
		m_hwnd = hwnd;
	}
	HWND m_hwnd;
};

// �Ի����ڴ˴�������ͼ
void CModulateDlg::drawPicture(std::vector<double>& vec){
	// ��������
	CChartAxis *pAxis = NULL;
	pAxis = m_ChartCtrl_Modulate.CreateStandardAxis(CChartCtrl::BottomAxis);
	pAxis->SetAutomatic(true);
	pAxis = m_ChartCtrl_Modulate.CreateStandardAxis(CChartCtrl::LeftAxis);
	pAxis->SetAutomatic(true);

	// �������
	TChartString str1;
	str1 = _T("OOK ����ͼ��");
	m_ChartCtrl_Modulate.GetTitle()->AddString(str1);

	// �������
	m_ChartCtrl_Modulate.GetTitle()->SetColor(RGB(255, 255, 255));   //���������ɫ
	m_ChartCtrl_Modulate.GetLeftAxis()->SetTextColor(RGB(255, 255, 255));  //���������ɫ
	m_ChartCtrl_Modulate.GetBottomAxis()->SetTextColor(RGB(255, 255, 255));  //�ײ��������ɫ
	m_ChartCtrl_Modulate.SetBorderColor(RGB(255, 255, 255));  //�߿���ɫ��ɫ
	m_ChartCtrl_Modulate.SetBackColor(RGB(85, 85, 85));  //������ɫ���ɫ

	double* X1Values = (double*)malloc(sizeof(double) * vec.size());
	double* Y1Values = (double*)malloc(sizeof(double) * vec.size());
	for (int i = 0; i < vec.size(); i++)
	{
		X1Values[i] = i + 1;
		Y1Values[i] = vec[i];
	}

	CChartLineSerie *pLineSerie2;
	// ��ʼ�滭����ͼ
	m_ChartCtrl_Modulate.SetZoomEnabled(true);
	m_ChartCtrl_Modulate.RemoveAllSeries();//�����
	pLineSerie2 = m_ChartCtrl_Modulate.CreateLineSerie();
	pLineSerie2->SetSeriesOrdering(poNoOrdering);//����Ϊ����
	pLineSerie2->SetPoints(X1Values, Y1Values, vec.size());

	// �����������¼�
	CCustomCursorListener* m_pCursorListener;
	CChartCrossHairCursor* pCrossHair =
		m_ChartCtrl_Modulate.CreateCrossHairCursor();

	HWND hWnd = this->GetSafeHwnd();
	m_pCursorListener = new CCustomCursorListener;
	m_pCursorListener->GetHwnd(hWnd);
	pCrossHair->RegisterListener(m_pCursorListener);
}

void CModulateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM_MODULATE, m_ChartCtrl_Modulate);
}


BEGIN_MESSAGE_MAP(CModulateDlg, CDialogEx)
	ON_MESSAGE(MESSAGE_UPDATEPOS, &CModulateDlg::OnMessageUpdatepos)
END_MESSAGE_MAP()


// CModulateDlg ��Ϣ�������


afx_msg LRESULT CModulateDlg::OnMessageUpdatepos(WPARAM wParam, LPARAM lParam)
{
	CString s;
	s.Format(_T("x = %.2f,y = %.2f"), modulate_x, modulate_y);
	CStatic* pStatic;
	pStatic = (CStatic*)GetDlgItem(IDC_STATIC_MODULATE);
	pStatic->SetWindowText(s);
	return 1;
}

