
// toy7.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// Ctoy7App:
// �� Ŭ������ ������ ���ؼ��� toy7.cpp�� �����Ͻʽÿ�.
//

class Ctoy7App : public CWinApp
{
public:
	Ctoy7App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern Ctoy7App theApp;