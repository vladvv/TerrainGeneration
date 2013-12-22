#pragma once

#include "resource.h"   

// Number_Input dialog

class Number_Input : public CDialog
{
	DECLARE_DYNAMIC(Number_Input)

public:
	Number_Input(CWnd* pParent = NULL);   // standard constructor
	virtual ~Number_Input();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString entered;
};
