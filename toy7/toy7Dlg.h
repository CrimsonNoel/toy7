
// toy7Dlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "vector"

using namespace std;
// 전방 선언
class Student;
class StudentMale;
class StudentFemale;

// Ctoy7Dlg 대화 상자
class Ctoy7Dlg : public CDialogEx
{
// 생성입니다.
public:
	Ctoy7Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOY7_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	FILE* file;
	CString szFilter;
	vector<CString> category;
	Student* stu;
	StudentMale* sm;
	StudentFemale* sf;
public:
	// List Control 변수입니다
	CListCtrl m_studentList;
	CListCtrl m_studentMale;
	CListCtrl m_studentFemale;
	// button 함수 입니다
	afx_msg void OnBnClickedButtonload();
	afx_msg void OnBnClickedButtonsavefile();
	//
	void Category(char* str); // 카테고리 분류
	void Average(vector<CString>& student,int categorySize); // 평균구하기
	void ShowResult(vector<CString>& student, int size); // List 표시
	~Ctoy7Dlg(); // 소멸자
};

class Student
{
private:
	vector<CString> studentList;
	Ctoy7Dlg* pCtoy; // 포인터 객체 선언
public:
	Student() {}; // 기본 생성자
	Student(Ctoy7Dlg* pParent); // 포인터 객체 생성자
	virtual void GetStudentList(vector<CString>& studentList);
	virtual void SetStudentList(char* str,StudentMale* sm,StudentFemale* sf);
};

class StudentMale : public Student
{
private:
	vector<CString> studentMale;
	Ctoy7Dlg* pCtoy;
public:
	StudentMale(Ctoy7Dlg* pParent);
	void SetStudentList(CString& studentList);
	void GetStudentList(vector<CString>& studentList);
	void ShowResult2(vector<CString>& student);
};

class StudentFemale : public Student
{
private:
	vector<CString> studentFemale;
	Ctoy7Dlg* pCtoy;
public:
	StudentFemale(Ctoy7Dlg* pParent);
	void SetStudentList(CString& studentList);
	void GetStudentList(vector<CString>& studentList);
	void ShowResult3(vector<CString>& student);
};
