// CImportStorage.cpp: 实现文件
//

#include "stdafx.h"
#include "storage_demo.h"
#include "CImportStorage.h"
#include "afxdialogex.h"


// CImportStorage 对话框

IMPLEMENT_DYNAMIC(CImportStorage, CDialogEx)

CImportStorage::CImportStorage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ImportStorage, pParent)
{

}

CImportStorage::~CImportStorage()
{
}

void CImportStorage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CImportStorage, CDialogEx)
	ON_BN_CLICKED(IDOK, &CImportStorage::OnBnClickedOk)
END_MESSAGE_MAP()


// CImportStorage 消息处理程序


void CImportStorage::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpCtrl())
	{
		MessageBox(L"输入信息有误，请确保已录入物品基本信息，请修改后重试", L"提示！");
		return;
	}
	CDialogEx::OnOK();
} 

bool CImportStorage::UpCtrl()
{
	IMPORTINFO info;
	CEdit* goodsId = (CEdit*)this->GetDlgItem(IDC_goodsId);
	CEdit* goodsCount = (CEdit*)this->GetDlgItem(IDC_goodsCount);
	CEdit* handleName = (CEdit*)this->GetDlgItem(IDC_handleName);
	CEdit* note = (CEdit*)this->GetDlgItem(IDC_noteImport);
	CString id;
	goodsId->GetWindowText(id);
	CString name;
	handleName->GetWindowText(name);
	CString count;
	goodsCount->GetWindowText(count);
	CString noteStr;
	note->GetWindowText(noteStr);
	if (id.IsEmpty() || name.IsEmpty() || count.IsEmpty())
		return false;
	std::string tempGoodsGuid = GoodsInfo::instance()->getGoodsGuids(Fly_string::w2c(id));
	if (tempGoodsGuid.length() < 3)
		return false;
	info.goodsGuid = tempGoodsGuid;
	info.handleName = Fly_string::w2c(name);
	std::string countStr = Fly_string::w2c(count).c_str();
	info.count = atoi(countStr.c_str());
	info.note = Fly_string::w2c(noteStr);
	if (info.count < 1 || info.count > 100000000)
		return false;
	return StorageAct::instance()->importGoodsToStrorage(info);  
}