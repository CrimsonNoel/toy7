
// toy7Dlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "vector"

using namespace std;
// ���� ����
class Student;
class StudentMale;
class StudentFemale;

// Ctoy7Dlg ��ȭ ����
class Ctoy7Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	Ctoy7Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOY7_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
	// List Control �����Դϴ�
	CListCtrl m_studentList;
	CListCtrl m_studentMale;
	CListCtrl m_studentFemale;
	// button �Լ� �Դϴ�
	afx_msg void OnBnClickedButtonload();
	afx_msg void OnBnClickedButtonsavefile();
	//
	void Category(char* str); // ī�װ� �з�
	void Average(vector<CString>& student,int categorySize); // ��ձ��ϱ�
	void ShowResult(vector<CString>& student, int size); // List ǥ��
	~Ctoy7Dlg(); // �Ҹ���
};

class Student
{
private:
	vector<CString> studentList;
	Ctoy7Dlg* pCtoy; // ������ ��ü ����
public:
	Student() {}; // �⺻ ������
	Student(Ctoy7Dlg* pParent); // ������ ��ü ������
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
