
// toy7Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "toy7.h"
#include "toy7Dlg.h"
#include "afxdialogex.h"
#include "vector"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Ctoy7Dlg ��ȭ ����

Ctoy7Dlg::Ctoy7Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TOY7_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctoy7Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_studentList, m_studentList);
	DDX_Control(pDX, IDC_LIST_male, m_studentMale);
	DDX_Control(pDX, IDC_LIST_female, m_studentFemale);
}

BEGIN_MESSAGE_MAP(Ctoy7Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_load, &Ctoy7Dlg::OnBnClickedButtonload)
	ON_BN_CLICKED(IDC_BUTTON_saveFile, &Ctoy7Dlg::OnBnClickedButtonsavefile)
END_MESSAGE_MAP()


// Ctoy7Dlg �޽��� ó����

BOOL Ctoy7Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	// Ȯ���� ����
	szFilter = "�ؽ�Ʈ ����(*.txt, *.csv) | *.txt;*.csv; |�������(*.*)|*.*||";
	// �� Ŭ���� �ʱ�ȭ
	stu = new Student(this);
	sm = new StudentMale(this);
	sf = new StudentFemale(this);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}
void Ctoy7Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void Ctoy7Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.

HCURSOR Ctoy7Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
// ���� �ε�
void Ctoy7Dlg::OnBnClickedButtonload()
{
	// ��ư�� ���� csv���� �ε��մϴ�.
	// �ε��� studentList�� ��ϵǰ� ��ü ��հ��� ���մϴ�. ���л�/���л� Ŭ������ ���� �����ϰ�
	// �� ���� Ŭ������ ������ �������� â�� �ڵ� ���ε�˴ϴ�. �̶� �� ������ ����,���� ���� ����� ���մϴ�
	CFileDialog dlg(TRUE, "", "", OFN_HIDEREADONLY, szFilter);
	if (IDOK == dlg.DoModal())
	{
		CString pathName = dlg.GetPathName(); // ���
		errno_t fileOpen = fopen_s(&file, pathName, "rt");
		if (fileOpen == 0)
		{
			int cnt = 0;
			char str[100];
			while (fgets(str, sizeof(str), file) != NULL)
			{
				if (str[strlen(str) - 1] == '\n')
					str[strlen(str) - 1] = '\0';
				if (cnt == 0) //ī�װ� �з�
				{
					Category(str);
				}
				else
				{
					stu->SetStudentList(str, sm, sf);
				}
				cnt++;
			}
			vector<CString> nStudentList; // ��ü�л� ����Ʈ �޾ƿ� ����
			vector<CString> nStudentMaleList; // ���л� ''
			vector<CString> nStudentFemaleList; // ���л� ''
			size_t categorySize = category.size();// ī�װ� ����
			stu->GetStudentList(nStudentList); // ��ü�л� ����Ʈ
			ShowResult(nStudentList, categorySize); // ���â ǥ��

			sm->GetStudentList(nStudentMaleList); // ���л� ����Ʈ
			sm->ShowResult2(nStudentMaleList); // ǥ��
			sf->GetStudentList(nStudentFemaleList); // ���л� ����Ʈ
			sf->ShowResult3(nStudentFemaleList); // ǥ��
			
			//��� ���ϱ�
			Average(nStudentList, categorySize);//��ü�л� ��� ���ϱ�
			Average(nStudentMaleList, categorySize);//���л� ��� ���ϱ�
			Average(nStudentFemaleList, categorySize);//���л� ��� ���ϱ�
			
			fclose(file); // ���� �ݱ�
		}
		else
		{	// ������ �� ������ ���
			char errormsg[100];
			strerror_s(errormsg, sizeof(errormsg) + 1, fileOpen);
			printf("�����ڵ�: %d, ��������: %s", fileOpen, errormsg);
		}
	}
}
// ��� ���
void Ctoy7Dlg::OnBnClickedButtonsavefile()
{
	CFileDialog dlg(FALSE, "", "", OFN_HIDEREADONLY, "�ؽ�Ʈ����(*.txt)|*.txt;||");
	CString pathName = dlg.GetPathName();
	if (IDOK == dlg.DoModal())
	{
		pathName = dlg.GetPathName(); // �������
		errno_t fileOpen = fopen_s(&file, pathName, "wt");
		if (fileOpen == 0)
		{
			CString result;
			GetDlgItemText(IDC_EDIT_studentListAverage, result);
			fprintf(file, "��ü �л� ��հ�: %s", result.GetString());
			GetDlgItemText(IDC_EDIT_maleAverage, result);
			fprintf(file, "\n���л� ��հ�: %s", result.GetString());
			GetDlgItemText(IDC_EDIT_femaleAverage, result);
			fprintf(file, "\n���л� ��հ�: %s", result.GetString());
			fclose(file); // ���ϴݱ�
		}

	}
}
// ������. �����ͷ� ���� ���� �Ǿ���
Student::Student(Ctoy7Dlg* pParent)
{
	pCtoy = pParent;
}
StudentMale::StudentMale(Ctoy7Dlg* pParent)
{
	pCtoy = pParent;
}
StudentFemale::StudentFemale(Ctoy7Dlg* pParent)
{
	pCtoy = pParent;
}
void Ctoy7Dlg::Category(char* str)
{// ù���� ī�װ��μ� �з��ϰ� �� List â�� �Ѹ�
	char* context = NULL;
	char* c = strtok_s(str, ",", &context);
	while (c != NULL)
	{
		category.push_back(c);
		c = strtok_s(NULL, ",", &context);
	}
	for (int i = 0; i < category.size(); i++)
	{
		m_studentList.InsertColumn(i, category[i], LVCFMT_LEFT, 100);
		m_studentMale.InsertColumn(i, category[i], LVCFMT_LEFT, 100);
		m_studentFemale.InsertColumn(i, category[i], LVCFMT_LEFT, 100);
	}
}
void Student::SetStudentList(char* str, StudentMale* sm, StudentFemale* sf)
{	// ������ �����Ϳ� ������ ���� �����͸� ����.
	// Student Ŭ������ StudentList�� ����
	CString nstr = str;
	char* context = NULL;
	char* c = strtok_s(str, ",", &context);
	while (c != NULL)
	{
		studentList.push_back(c);
		c = strtok_s(NULL, ",", &context);
		if (c != NULL && strcmp(c, "��") == 0)
		{
			sm->SetStudentList(nstr);
		}
		else if (c != NULL && strcmp(c, "��") == 0)
		{
			sf->SetStudentList(nstr);
		}
	}
}
void Ctoy7Dlg::ShowResult(vector<CString>& studentList, int size)
{	// ��ü �л� ���� ǥ��
	for (int i = 0; i < studentList.size() / size; i++)
	{
		int index = i * size;
		m_studentList.InsertItem(i, studentList[index]);
		for (int j = 1; j < size; j++)
		{
			m_studentList.SetItemText(i, j, studentList[index + j]);
		}
	}
}
void StudentMale::ShowResult2(vector<CString>& studentList)
{	// ����� ���л� ���� �����ͼ� csv���� ������ ������ List�� ǥ��
	// ����� ������ ����
	vector<CString> ShowRes;
	int comma = 0;
	if (comma == 0)
	{
		if (studentList.size() != 0)
		{
			CString commaNum = studentList[0];
			comma = commaNum.Remove(',');
			comma++;
		}
	}
	for (int i = 0; i < studentList.size(); i++)
	{
		char* str1 = new char[studentList[i].GetLength() + 1];
		strcpy_s(str1, studentList[i].GetLength() + 1, studentList[i]);
		char* context = NULL;
		char* c = strtok_s(str1, ",", &context);
		while (c != NULL)
		{
			ShowRes.push_back(c);
			c = strtok_s(NULL, ",", &context);
		}
		delete[] str1;
	}
	for (int i = 0; i < ShowRes.size() / comma; i++)
	{
		int index = i * comma;
		pCtoy->m_studentMale.InsertItem(i, ShowRes[index]);
		for (int j = 1; j < comma; j++)
		{
			pCtoy->m_studentMale.SetItemText(i, j, ShowRes[index + j]);
		}
	}
	studentList = ShowRes;
}
void StudentFemale::ShowResult3(vector<CString>& studentList)
{	// ����� ���л� ���� �����ͼ� csv���� ������ ������ List�� ǥ��
	// ����� ������ ����
	vector<CString> ShowRes;
	int comma = 0;
	if (comma == 0)
	{
		if (studentList.size() != 0)
		{
			CString commaNum = studentList[0];
			comma = commaNum.Remove(',');
			comma++;
		}
	}
	for (int i = 0; i < studentList.size(); i++)
	{
		char* str1 = new char[studentList[i].GetLength() + 1];
		strcpy_s(str1, studentList[i].GetLength() + 1, studentList[i]);
		char* context = NULL;
		char* c = strtok_s(str1, ",", &context);
		while (c != NULL)
		{
			ShowRes.push_back(c);
			c = strtok_s(NULL, ",", &context);
		}
		delete[] str1;
	}

	for (int i = 0; i < ShowRes.size() / comma; i++)
	{
		int index = i * comma;
		pCtoy->m_studentFemale.InsertItem(i, ShowRes[index]);
		for (int j = 1; j < comma; j++)
		{
			pCtoy->m_studentFemale.SetItemText(i, j, ShowRes[index + j]);
		}
	}
	studentList = ShowRes;
}
void StudentMale::SetStudentList(CString& studentList)
{	// ���л� ���� ����
	studentMale.push_back(studentList);
}
void StudentFemale::SetStudentList(CString& studentList)
{	// ���л� ���� ����
	studentFemale.push_back(studentList);
}
void Student::GetStudentList(vector<CString>& nStudentList)
{	// ����� ���л� ���� ��������
	for (int i = 0; i < studentList.size(); i++)
	{
		nStudentList.push_back(studentList[i]);
	}
}
void StudentMale::GetStudentList(vector<CString>& studentMaleList)
{	// ����� ���л� ���� ��������
	for (int i = 0; i < studentMale.size(); i++)
	{
		studentMaleList.push_back(studentMale[i]);
	}
}
void StudentFemale::GetStudentList(vector<CString>& studentFemaleList)
{
	for (int i = 0; i < studentFemale.size(); i++)
	{
		studentFemaleList.push_back(studentFemale[i]);
	}
}
// �Լ� ���ϴ� ��
void Ctoy7Dlg::Average(vector<CString>& student, int categorySize)
{
	int male = 0;
	int female = 0;
	for (int i = 0; i < student.size(); i++)
	{
		if (student[i] == "��")
			male++;
		if (student[i] == "��")
			female++;
	}
	// ���л� ���
	if (male > 0 && female == 0)
	{
		double sum = 0;
		for (int i = 0; i < student.size() / categorySize; i++)
		{
			sum += atoi(student[(i * categorySize) + 3]);
			sum += atoi(student[(i * categorySize) + 4]);
		}
		CString average;
		sum = sum / ((student.size() / categorySize) * 2);
		average.Format("%.2f", sum);
		SetDlgItemText(IDC_EDIT_maleAverage, average);
	}
	// ���л� ���
	else if (male == 0 && female > 0)
	{
		double sum = 0;
		for (int i = 0; i < student.size() / categorySize; i++)
		{
			sum += atoi(student[(i * categorySize) + 3]);
			sum += atoi(student[(i * categorySize) + 4]);
		}
		CString average;
		sum = sum / ((student.size() / categorySize) * 2);
		average.Format("%.2f", sum);
		SetDlgItemText(IDC_EDIT_femaleAverage, average);
	}
	// ��ü ���
	else
	{
		double sum = 0;
		for (int i = 0; i < student.size() / categorySize; i++)
		{
			sum += atoi(student[(i * categorySize) + 3]);
			sum += atoi(student[(i * categorySize) + 4]);
		}
		CString average;
		sum = sum / ((student.size() / categorySize) * 2);
		average.Format("%.2f", sum);
		SetDlgItemText(IDC_EDIT_studentListAverage, average);
	}

}
// �Ҹ���
Ctoy7Dlg::~Ctoy7Dlg()
{
	delete stu;
	delete sm;
	delete sf;
}