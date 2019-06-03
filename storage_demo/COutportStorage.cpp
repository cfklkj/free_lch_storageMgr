// COutportStorage.cpp: 实现文件
//

#include "stdafx.h"
#include "storage_demo.h"
#include "COutportStorage.h"
#include "afxdialogex.h"


// COutportStorage 对话框

IMPLEMENT_DYNAMIC(COutportStorage, CDialogEx)

COutportStorage::COutportStorage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OutportStorage, pParent)
{

}

COutportStorage::~COutportStorage()
{
}

void COutportStorage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COutportStorage, CDialogEx)
	ON_BN_CLICKED(IDOK, &COutportStorage::OnBnClickedOk)
END_MESSAGE_MAP()


// COutportStorage 消息处理程序


void COutportStorage::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpCtrl())
	{
		MessageBox(L"输入信息有误，请确保已录入物品基本信息，请修改后重试", L"提示！");
		return;
	}
	CDialogEx::OnOK();
}


bool COutportStorage::UpCtrl()
{
	OUTPORTINFO info;
	CEdit* goodsId = (CEdit*)this->GetDlgItem(IDC_goodsId);
	CEdit* goodsCount = (CEdit*)this->GetDlgItem(IDC_goodsCount);
	CEdit* handleName = (CEdit*)this->GetDlgItem(IDC_handleName);
	CEdit* useName = (CEdit*)this->GetDlgItem(IDC_useName);
	CString id;
	goodsId->GetWindowText(id);
	CString name;
	goodsCount->GetWindowText(name);
	CString uname;
	goodsCount->GetWindowText(uname);
	CString count;
	handleName->GetWindowText(count);
	if (id.IsEmpty() || name.IsEmpty() || count.IsEmpty() || uname.IsEmpty())
		return false;
	std::string tempGoodsGuid = GoodsInfo::instance()->getGoodsGuids(Fly_string::w2c(id));
	if (tempGoodsGuid.length() < 3)
		return false;
	info.goodsGuid = tempGoodsGuid;
	info.handleName = Fly_string::w2c(name);
	info.useName = Fly_string::w2c(uname);
	std::string countStr = Fly_string::w2c(count).c_str();
	info.count = atoi(countStr.c_str());
	if (info.count < 1 || info.count > 100000000)
		return false; 
	StorageAct::instance()->outputGoodsFromStrorage(info);
	return true;
}