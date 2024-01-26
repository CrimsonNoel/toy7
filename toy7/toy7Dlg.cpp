
// toy7Dlg.cpp : 구현 파일
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

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// Ctoy7Dlg 대화 상자

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


// Ctoy7Dlg 메시지 처리기

BOOL Ctoy7Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// 확장자 관리
	szFilter = "텍스트 파일(*.txt, *.csv) | *.txt;*.csv; |모든파일(*.*)|*.*||";
	// 각 클래스 초기화
	stu = new Student(this);
	sm = new StudentMale(this);
	sf = new StudentFemale(this);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void Ctoy7Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.

HCURSOR Ctoy7Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
// 파일 로드
void Ctoy7Dlg::OnBnClickedButtonload()
{
	// 버튼을 눌러 csv파일 로드합니다.
	// 로드후 studentList에 등록되고 전체 평균값을 구합니다. 남학생/여학생 클래스에 따로 저장하고
	// 각 성별 클래스에 저장후 성별마다 창에 자동 업로드됩니다. 이때 각 성별의 국어,수학 값의 평균을 구합니다
	CFileDialog dlg(TRUE, "", "", OFN_HIDEREADONLY, szFilter);
	if (IDOK == dlg.DoModal())
	{
		CString pathName = dlg.GetPathName(); // 경로
		errno_t fileOpen = fopen_s(&file, pathName, "rt");
		if (fileOpen == 0)
		{
			int cnt = 0;
			char str[100];
			while (fgets(str, sizeof(str), file) != NULL)
			{
				if (str[strlen(str) - 1] == '\n')
					str[strlen(str) - 1] = '\0';
				if (cnt == 0) //카테고리 분류
				{
					Category(str);
				}
				else
				{
					stu->SetStudentList(str, sm, sf);
				}
				cnt++;
			}
			vector<CString> nStudentList; // 전체학생 리스트 받아올 벡터
			vector<CString> nStudentMaleList; // 남학생 ''
			vector<CString> nStudentFemaleList; // 여학생 ''
			size_t categorySize = category.size();// 카테고리 갯수
			stu->GetStudentList(nStudentList); // 전체학생 리스트
			ShowResult(nStudentList, categorySize); // 결과창 표시

			sm->GetStudentList(nStudentMaleList); // 남학생 리스트
			sm->ShowResult2(nStudentMaleList); // 표시
			sf->GetStudentList(nStudentFemaleList); // 여학생 리스트
			sf->ShowResult3(nStudentFemaleList); // 표시
			
			//평균 구하기
			Average(nStudentList, categorySize);//전체학생 평균 구하기
			Average(nStudentMaleList, categorySize);//남학생 평균 구하기
			Average(nStudentFemaleList, categorySize);//여학생 평균 구하기
			
			fclose(file); // 파일 닫기
		}
		else
		{	// 파일이 안 열렸을 경우
			char errormsg[100];
			strerror_s(errormsg, sizeof(errormsg) + 1, fileOpen);
			printf("오류코드: %d, 오류내용: %s", fileOpen, errormsg);
		}
	}
}
// 결과 출력
void Ctoy7Dlg::OnBnClickedButtonsavefile()
{
	CFileDialog dlg(FALSE, "", "", OFN_HIDEREADONLY, "텍스트파일(*.txt)|*.txt;||");
	CString pathName = dlg.GetPathName();
	if (IDOK == dlg.DoModal())
	{
		pathName = dlg.GetPathName(); // 경로저장
		errno_t fileOpen = fopen_s(&file, pathName, "wt");
		if (fileOpen == 0)
		{
			CString result;
			GetDlgItemText(IDC_EDIT_studentListAverage, result);
			fprintf(file, "전체 학생 평균값: %s", result.GetString());
			GetDlgItemText(IDC_EDIT_maleAverage, result);
			fprintf(file, "\n남학생 평균값: %s", result.GetString());
			GetDlgItemText(IDC_EDIT_femaleAverage, result);
			fprintf(file, "\n여학생 평균값: %s", result.GetString());
			fclose(file); // 파일닫기
		}

	}
}
// 생성자. 포인터로 서로 연결 되었음
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
{// 첫줄은 카테고리로서 분류하고 각 List 창에 뿌림
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
{	// 저장할 데이터와 저장할 곳의 포인터를 받음.
	// Student 클래스의 StudentList에 저장
	CString nstr = str;
	char* context = NULL;
	char* c = strtok_s(str, ",", &context);
	while (c != NULL)
	{
		studentList.push_back(c);
		c = strtok_s(NULL, ",", &context);
		if (c != NULL && strcmp(c, "남") == 0)
		{
			sm->SetStudentList(nstr);
		}
		else if (c != NULL && strcmp(c, "여") == 0)
		{
			sf->SetStudentList(nstr);
		}
	}
}
void Ctoy7Dlg::ShowResult(vector<CString>& studentList, int size)
{	// 전체 학생 정보 표시
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
{	// 저장된 여학생 정보 가져와서 csv형태 데이터 정리후 List에 표시
	// 저장된 정보로 저장
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
{	// 저장된 여학생 정보 가져와서 csv형태 데이터 정리후 List에 표시
	// 저장된 정보로 저장
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
{	// 남학생 정보 저장
	studentMale.push_back(studentList);
}
void StudentFemale::SetStudentList(CString& studentList)
{	// 여학생 정보 저장
	studentFemale.push_back(studentList);
}
void Student::GetStudentList(vector<CString>& nStudentList)
{	// 저장된 남학생 정보 가져오기
	for (int i = 0; i < studentList.size(); i++)
	{
		nStudentList.push_back(studentList[i]);
	}
}
void StudentMale::GetStudentList(vector<CString>& studentMaleList)
{	// 저장된 여학생 정보 가져오기
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
// 함수 구하는 식
void Ctoy7Dlg::Average(vector<CString>& student, int categorySize)
{
	int male = 0;
	int female = 0;
	for (int i = 0; i < student.size(); i++)
	{
		if (student[i] == "남")
			male++;
		if (student[i] == "여")
			female++;
	}
	// 남학생 평균
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
	// 여학생 평균
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
	// 전체 평균
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
// 소멸자
Ctoy7Dlg::~Ctoy7Dlg()
{
	delete stu;
	delete sm;
	delete sf;
}