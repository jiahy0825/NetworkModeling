// ModulateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NetworkModeling.h"
#include "ModulateDlg.h"
#include "afxdialogex.h"

#include "OOK.h"

#include <iostream>

double modulate_x;
double modulate_y;

// CModulateDlg �Ի���


void WriteLog(CString strLog, CString strType)
{
	CString strPath = CString("C:\\Users\\jiahy\\Desktop\\NetworkModeling\\Log.txt");		//log·��
	CString strTime = CTime::GetCurrentTime().Format(L"[%Y-%m-%d %H:%M:%S]");
	USES_CONVERSION;
	char szStr[MAX_PATH] = { 0 };
	strcpy_s(szStr, sizeof(szStr), W2A(strPath));
	char *sPath = szStr;
 
	CString strText;
	strText = L"[" + strType + L"]" + strTime + L" " + strLog + L"\r\n";
 
	FILE *fp = NULL;
	fopen_s(&fp, sPath, "at+");		//���ı���ʽ׷��
	if (NULL == fp)
	{
		return;
	}
 
	char Text[MAX_PATH] = { 0 };
	strcpy_s(Text, sizeof(Text), W2A(strText));
	fprintf(fp, "%s", Text);
	fflush(fp);						//����д����������Ҫ��������������������ݽ�������д��ʱ
	fclose(fp);
}

IMPLEMENT_DYNAMIC(CModulateDlg, CDialogEx)

CModulateDlg::CModulateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CModulateDlg::IDD, pParent)
{
	pAxis = NULL;
	m_index = 100;
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
void CModulateDlg::drawPicture(std::vector<double>& vec, bool dynamic){
	m_ChartCtrl_Modulate.EnableRefresh(false);
	// ��������
	pAxis = m_ChartCtrl_Modulate.CreateStandardAxis(CChartCtrl::BottomAxis);
	pAxis->SetAutomatic(true);
	pAxis = m_ChartCtrl_Modulate.CreateStandardAxis(CChartCtrl::LeftAxis);
	pAxis->SetAutomatic(true);

	WriteLog(CString("success"), CString("Print"));

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
	m_ChartCtrl_Modulate.SetZoomEnabled(true);
	m_ChartCtrl_Modulate.RemoveAllSeries();//�����
	pLineSerie = m_ChartCtrl_Modulate.CreateLineSerie();
	//pLineSerie2 = m_ChartCtrl_Modulate.CreatePointsSerie();
	pLineSerie->SetSeriesOrdering(poNoOrdering);//����Ϊ����
	//pLineSerie2->SetPoints(X1Values, Y1Values, vec.size());
	pLineSerie->AddPoints(X1Values, Y1Values, size);

	// �����������¼�
	CCustomCursorListener* m_pCursorListener;
	CChartCrossHairCursor* pCrossHair =
		m_ChartCtrl_Modulate.CreateCrossHairCursor();

	HWND hWnd = this->GetSafeHwnd();
	m_pCursorListener = new CCustomCursorListener;
	m_pCursorListener->GetHwnd(hWnd);
	pCrossHair->RegisterListener(m_pCursorListener);

	m_ChartCtrl_Modulate.EnableRefresh(true);

	if (dynamic){
		SetTimer(1, 0, NULL);
	}
}

void CModulateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM_MODULATE, m_ChartCtrl_Modulate);
}


BEGIN_MESSAGE_MAP(CModulateDlg, CDialogEx)
	ON_MESSAGE(MESSAGE_UPDATEPOS, &CModulateDlg::OnMessageUpdatepos)
	ON_WM_TIMER()
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



void CModulateDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	pLineSerie->AddPoint(m_index, m_vec[m_index]);
	m_index++;
	if (m_index >= m_vec.size()){
		KillTimer(1);
	}

	CDialogEx::OnTimer(nIDEvent);
}
