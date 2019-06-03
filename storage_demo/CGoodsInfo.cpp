// CGoodsInfo.cpp: 实现文件
//

#include "stdafx.h"
#include "storage_demo.h"
#include "CGoodsInfo.h"
#include "afxdialogex.h"


// CGoodsInfo 对话框

IMPLEMENT_DYNAMIC(CGoodsInfo, CDialogEx)

CGoodsInfo::CGoodsInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_addGoods, pParent)
{

}

CGoodsInfo::~CGoodsInfo()
{
}

void CGoodsInfo::InitCtl()
{
	std::string goodsGuid = getGoodsGuid();
	if (goodsGuid.length() < 3)
		return;
	GOODSINFO info;
	if (!GoodsInfo::instance()->getGoodsInfo(goodsGuid, &info))
		return;
	CEdit* goodsId = (CEdit*)this->GetDlgItem(IDC_goodsId);
	CEdit* goodsName = (CEdit*)this->GetDlgItem(IDC_goodsName);
	CEdit* goodsType = (CEdit*)this->GetDlgItem(IDC_goodsType);

	goodsId->SetWindowText((LPCTSTR)info.id.c_str());
	goodsName->SetWindowText((LPCTSTR)info.name.c_str());
	std::string goodsTypeStr = Fly_string::format("%d", info.type);
	goodsType->SetWindowText((LPCTSTR)goodsTypeStr.c_str());
}

bool CGoodsInfo::UpCtrl()
{
	GOODSINFO info;
	CEdit* goodsId = (CEdit*)this->GetDlgItem(IDC_goodsId);
	CEdit* goodsName = (CEdit*)this->GetDlgItem(IDC_goodsName);
	CEdit* goodsType = (CEdit*)this->GetDlgItem(IDC_goodsType);
	CString id;
	goodsId->GetWindowText(id);
	CString name;
	goodsName->GetWindowText(name);
	CString type;
	goodsType->GetWindowText(type);
	if (id.IsEmpty() || name.IsEmpty() || type.IsEmpty())
		return false;
	info.id = Fly_string::w2c(id);
	info.name = Fly_string::w2c(name);
	info.type = atoi(Fly_string::format("%d", Fly_string::w2c(type).c_str()).c_str());
	std::string goodsGuid = getGoodsGuid();
	if (goodsGuid.length() < 3)
	{
		GoodsInfo::instance()->addGoodsInfo(info);
	}
	else
	{
		GoodsInfo::instance()->altGoodsInfo(info);
	}
	return true;
}

void CGoodsInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGoodsInfo, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGoodsInfo::OnBnClickedOk)
END_MESSAGE_MAP()


// CGoodsInfo 消息处理程序


void CGoodsInfo::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpCtrl())
	{
		MessageBox(L"输入信息有误，请重试", L"提示");
		return;
	}
	CDialogEx::OnOK();
}
