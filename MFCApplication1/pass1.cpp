// pass1.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "pass1.h"

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include"ahmain.h"
#include <json/json.h>
#include <fstream>


// pass1 对话框

IMPLEMENT_DYNAMIC(pass1, CDialogEx)

pass1::pass1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

pass1::~pass1()
{
}

void pass1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(pass1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &pass1::OnBnClickedButton1)
END_MESSAGE_MAP()


// pass1 消息处理程序
#include <afxinet.h>
CString pass1::UTF8ToUnicode2(char* UTF8)
{

	DWORD dwUnicodeLen;        //转换后Unicode的长度
	TCHAR* pwText;            //保存Unicode的指针
	CString strUnicode;        //返回值
	//获得转换后的长度，并分配内存
	dwUnicodeLen = MultiByteToWideChar(CP_UTF8, 0, UTF8, -1, NULL, 0);
	pwText = new TCHAR[dwUnicodeLen];
	if (!pwText)
	{
		return strUnicode;
	}
	//转为Unicode
	MultiByteToWideChar(CP_UTF8, 0, UTF8, -1, pwText, dwUnicodeLen);
	//转为CString
	strUnicode.Format(_T("%s"), pwText);
	//清除内存
	delete[]pwText;
	//返回转换好的Unicode字串
	return strUnicode;
}

void pass1::OnBnClickedButton1()
{
	int num2;
	// TODO: 在此添加控件通知处理程序代码
	CString tonken = _T("");
	GetDlgItem(IDC_EDIT180)->GetWindowText(tonken);
	CInternetSession session(_T("HttpClient"));
	TCHAR* url = _T("https://api.vvhan.com/api/qqsc?key=ca0f946cdda97a917cb23b2eddee28e1");
	CHttpFile* pfile = (CHttpFile*)session.OpenURL(url);
	DWORD dwStatusCode;
	pfile->QueryInfoStatusCode(dwStatusCode);
	if (dwStatusCode == HTTP_STATUS_OK)
	{
		CString content;
		CString data;
		while (pfile->ReadString(data))
		{
			content += data;
		}
		char* pch;
		pch = new char[content.GetLength() * sizeof(TCHAR) + 1];
		memcpy(pch, content, content.GetLength() * sizeof(TCHAR));
		content = UTF8ToUnicode2(pch);//转换编码，不然就乱码了
		//AfxMessageBox(content);
		//CString content2;
	//	content2 = content.Left(content.Find('r'));
	//	content2 = content2.Right(content.GetLength() - 1 - content.ReverseFind(':'));
		//CString contenta;
	//	contenta = content.Left(content.Find('a'));
		//contenta = content.Right(content.GetLength() - 1 - content.ReverseFind(':'));

		CString str = content;
		Json::Reader reader;
		Json::Value root;
		CString temp;
		CString temp2;
		CString temp3;
		CString temp4;
		CString temp5;
		CString temp6;
		USES_CONVERSION;
		char* cJson = T2A(str.GetBuffer(0));
		str.ReleaseBuffer();
		if (reader.parse(cJson, root)) {
			temp = root["text"].asCString();
			//temp2 = root["data"][0]["desc"].asCString();
		//	MessageBox(temp);
			num2 = _ttoi(temp);
		}

	}
	pfile->Close();
	delete pfile;
	session.Close();

	CString passw1 ;
	GetDlgItem(IDC_EDIT180)->GetWindowText(passw1);
	int num = _ttoi(passw1);
	if (num == num2) {
		//this->ShowWindow(SW_HIDE);
		ahmain dlg;
		dlg.DoModal();
	}
	else {
		MessageBox(_T("密码错误，请重新输入或寻求开发者帮助。"));
	}
}
