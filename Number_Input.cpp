// Number_Input.cpp : implementation file
//

#include "stdafx.h"
#include "Number_Input.h"
#include "afxdialogex.h"
//#include "resource.h"   


// Number_Input dialog

IMPLEMENT_DYNAMIC(Number_Input, CDialog)

Number_Input::Number_Input(CWnd* pParent /*=NULL*/)
	: CDialog(Number_Input::IDD, pParent)
	, entered(_T(""))
{

}

Number_Input::~Number_Input()
{
}

void Number_Input::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, entered);
}


BEGIN_MESSAGE_MAP(Number_Input, CDialog)
END_MESSAGE_MAP()


// Number_Input message handlers
