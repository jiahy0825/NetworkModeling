// ModulateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NetworkModeling.h"
#include "ModulateDlg.h"
#include "afxdialogex.h"

#include "OOK.h"


CChartCtrl m_ChartCtrl_Modulate;
double modulate_x;
double modulate_y;

// CModulateDlg 对话框

IMPLEMENT_DYNAMIC(CModulateDlg, CDialogEx)

CModulateDlg::CModulateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CModulateDlg::IDD, pParent)
{

}

CModulateDlg::~CModulateDlg()
{
}

// 设置鼠标监听事件
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

// 对话框在此处画折线图
void CModulateDlg::drawPicture(std::vector<double>& vec){
	// 画坐标轴
	CChartAxis *pAxis = NULL;
	pAxis = m_ChartCtrl_Modulate.CreateStandardAxis(CChartCtrl::BottomAxis);
	pAxis->SetAutomatic(true);
	pAxis = m_ChartCtrl_Modulate.CreateStandardAxis(CChartCtrl::LeftAxis);
	pAxis->SetAutomatic(true);

	// 导入标题
	TChartString str1;
	str1 = _T("OOK 调制图像");
	m_ChartCtrl_Modulate.GetTitle()->AddString(str1);

	// 更改外观
	m_ChartCtrl_Modulate.GetTitle()->SetColor(RGB(255, 255, 255));   //标题字体白色
	m_ChartCtrl_Modulate.GetLeftAxis()->SetTextColor(RGB(255, 255, 255));  //左坐标轴白色
	m_ChartCtrl_Modulate.GetBottomAxis()->SetTextColor(RGB(255, 255, 255));  //底部坐标轴白色
	m_ChartCtrl_Modulate.SetBorderColor(RGB(255, 255, 255));  //边框颜色白色
	m_ChartCtrl_Modulate.SetBackColor(RGB(85, 85, 85));  //背景颜色深灰色

	double* X1Values = (double*)malloc(sizeof(double) * vec.size());
	double* Y1Values = (double*)malloc(sizeof(double) * vec.size());
	for (int i = 0; i < vec.size(); i++)
	{
		X1Values[i] = i + 1;
		Y1Values[i] = vec[i];
	}

	CChartLineSerie *pLineSerie2;
	// 开始绘画折线图
	m_ChartCtrl_Modulate.SetZoomEnabled(true);
	m_ChartCtrl_Modulate.RemoveAllSeries();//先清空
	pLineSerie2 = m_ChartCtrl_Modulate.CreateLineSerie();
	pLineSerie2->SetSeriesOrdering(poNoOrdering);//设置为无序
	pLineSerie2->SetPoints(X1Values, Y1Values, vec.size());

	// 设置鼠标监听事件
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


// CModulateDlg 消息处理程序


afx_msg LRESULT CModulateDlg::OnMessageUpdatepos(WPARAM wParam, LPARAM lParam)
{
	CString s;
	s.Format(_T("x = %.2f,y = %.2f"), modulate_x, modulate_y);
	CStatic* pStatic;
	pStatic = (CStatic*)GetDlgItem(IDC_STATIC_MODULATE);
	pStatic->SetWindowText(s);
	return 1;
}

