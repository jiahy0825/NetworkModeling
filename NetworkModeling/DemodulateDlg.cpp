// DemodulateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NetworkModeling.h"
#include "DemodulateDlg.h"
#include "afxdialogex.h"


double demodulate_x;
double demodulate_y;

// CDemodulateDlg 对话框

IMPLEMENT_DYNAMIC(CDemodulateDlg, CDialogEx)

CDemodulateDlg::CDemodulateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDemodulateDlg::IDD, pParent)
{

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

// 对话框在此处画折线图
void CDemodulateDlg::drawPicture(std::vector<double>& vec){
	// 画坐标轴
	CChartAxis *pAxis = NULL;
	pAxis = m_ChartCtrl_Demodulate.CreateStandardAxis(CChartCtrl::BottomAxis);
	pAxis->SetAutomatic(true);
	pAxis = m_ChartCtrl_Demodulate.CreateStandardAxis(CChartCtrl::LeftAxis);
	pAxis->SetAutomatic(true);

	// 导入标题
	TChartString str1;
	str1 = _T("OOK 解调图像");
	m_ChartCtrl_Demodulate.GetTitle()->AddString(str1);

	// 更改外观
	m_ChartCtrl_Demodulate.GetTitle()->SetColor(RGB(255, 255, 255));   //标题字体白色
	m_ChartCtrl_Demodulate.GetLeftAxis()->SetTextColor(RGB(255, 255, 255));  //左坐标轴白色
	m_ChartCtrl_Demodulate.GetBottomAxis()->SetTextColor(RGB(255, 255, 255));  //底部坐标轴白色
	m_ChartCtrl_Demodulate.SetBorderColor(RGB(255, 255, 255));  //边框颜色白色
	m_ChartCtrl_Demodulate.SetBackColor(RGB(85, 85, 85));  //背景颜色深灰色

	double* X1Values = (double*)malloc(sizeof(double) * vec.size());
	double* Y1Values = (double*)malloc(sizeof(double) * vec.size());
	for (int i = 0; i < vec.size(); i++)
	{
		X1Values[i] = i + 1;
		Y1Values[i] = vec[i];
	}

	CChartLineSerie *pLineSerie2;
	// 开始绘画折线图
	m_ChartCtrl_Demodulate.SetZoomEnabled(true);
	m_ChartCtrl_Demodulate.RemoveAllSeries();//先清空
	pLineSerie2 = m_ChartCtrl_Demodulate.CreateLineSerie();
	pLineSerie2->SetSeriesOrdering(poNoOrdering);//设置为无序
	pLineSerie2->SetPoints(X1Values, Y1Values, vec.size());

	// 设置鼠标监听事件
	CCustomCursorListenerDemodulate* m_pCursorListener;
	CChartCrossHairCursor* pCrossHair =
		m_ChartCtrl_Demodulate.CreateCrossHairCursor();

	HWND hWnd = this->GetSafeHwnd();
	m_pCursorListener = new CCustomCursorListenerDemodulate;
	m_pCursorListener->GetHwnd(hWnd);
	pCrossHair->RegisterListener(m_pCursorListener);
}

void CDemodulateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM_DEMODULATE, m_ChartCtrl_Demodulate);
}


BEGIN_MESSAGE_MAP(CDemodulateDlg, CDialogEx)
	ON_MESSAGE(MESSAGE_UPDATEPOS_DEMODULATE, &CDemodulateDlg::OnMessageUpdateposDemodulate)
END_MESSAGE_MAP()


// CDemodulateDlg 消息处理程序


afx_msg LRESULT CDemodulateDlg::OnMessageUpdateposDemodulate(WPARAM wParam, LPARAM lParam)
{
	CString s;
	s.Format(_T("x = %.2f,y = %.2f"), demodulate_x, demodulate_y);
	CStatic* pStatic;
	pStatic = (CStatic*)GetDlgItem(IDC_STATIC_DEMODULATE);
	pStatic->SetWindowText(s);
	return 1;
}
