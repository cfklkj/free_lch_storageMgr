
// storage_demoDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "storage_demo.h"
#include "storage_demoDlg.h"
#include "afxdialogex.h"
#include "CGoodsInfo.h"
#include "CImportStorage.h"
#include "COutportStorage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CstoragedemoDlg 对话框



CstoragedemoDlg::CstoragedemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STORAGE_DEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CstoragedemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

void CstoragedemoDlg::addInfo()
{
	int cur = m_tab.GetCurSel();
	if (cur == 0)
	{
		CGoodsInfo dlg;
		if (dlg.DoModal() == IDOK)
		{
			setTabInfo();
		}
		return;
	}
	if (cur == 1)
	{
		CImportStorage dlg;
		if (dlg.DoModal() == IDOK)
		{
			setTabInfo();
		}
		return;
	}
	if (cur == 2)
	{
		COutportStorage dlg;
		if (dlg.DoModal() == IDOK)
		{
			setTabInfo();
		}
		return;
	}

}

void CstoragedemoDlg::altInfo()
{
	int cur = m_tab.GetCurSel();
	if (cur == 0)
	{
		CGoodsInfo dlg;
		int row = getListSel();
		std::string* goodsGuid = (std::string*)m_list.GetItemData(row);
		dlg.setGoods(*goodsGuid);
		if (dlg.DoModal() == IDOK)
		{ 
			GOODSINFO info;
			if (GoodsInfo::instance()->getGoodsInfo(*goodsGuid, &info))
			{
				int col = 0; 
				m_list.InsertItem(row, Fly_string::c2w(info.name.c_str()).c_str());
				m_list.SetItemText(row, col++, Fly_string::c2w(info.id.c_str()).c_str());
				m_list.SetItemText(row, col++, Fly_string::c2w(info.type.c_str()).c_str());
			} 
		}
		return;
	}	
}

void CstoragedemoDlg::delInfo()
{
	int cur = m_tab.GetCurSel();
	if (cur == 0)
	{
		int sel = getListSel();
		std::string goodsId = Fly_string::w2c(m_list.GetItemText(sel, 0));
		std::string goodsGuid = GoodsInfo::instance()->getGoodsGuids(goodsId);
		m_list.DeleteItem(sel);
		GOODSINFO info;
		if(GoodsInfo::instance()->getGoodsInfo(goodsGuid, &info))
			GoodsInfo::instance()->delGoodsInf(info);
	}
}

void CstoragedemoDlg::selectInfo()
{

	CEdit* select = (CEdit*)this->GetDlgItem(IDC_Where);
	CString whereStr;
	select->GetWindowText(whereStr); 
	if (setSelectTabInfo(whereStr))
	{
		selectTabInfo();
	}
	else
	{
		setTabInfo();
	} 
}

void CstoragedemoDlg::initTab()
{
	//为Tab Control增加两个页面
	m_tab.InsertItem(0, _T("物品信息"));
	m_tab.InsertItem(1, _T("入库信息"));
	m_tab.InsertItem(2, _T("出库信息")); 
	setTabInfo();
}

void CstoragedemoDlg::setTabInfo()
{
	int tabSel = m_tab.GetCurSel();
	setListHead(tabSel);
	setListBody(tabSel);
}
 
void CstoragedemoDlg::selectTabInfo()
{
	int tabSel = m_tab.GetCurSel();
	setListHead(tabSel);
	setSelectListBody(tabSel);
}

bool CstoragedemoDlg::setSelectTabInfo(CString selectStr)
{
	if (selectStr.IsEmpty())
		return false;

	std::string tmpRst= Fly_string::w2c(selectStr).c_str();
	const char* fullStr = tmpRst.c_str();
	int tabSel = m_tab.GetCurSel();
	bool isSelect = false;
	if (tabSel == 0)
	{

		const char* goodsInfo[] = { "物品序号=", "物品名称=", "物品类型=",  "余量=" };
		int i = 0;
		GOODSINFO tmpGoodsInfo;
		for (auto it : goodsInfo)
		{
			i++;
			if (i == 1 && tmpGoodsInfo.id.length() < 3 && Fly_string::FindSub(fullStr, it))
			{
				tmpGoodsInfo.id = Fly_string::pFindSub(fullStr, it);
				tmpGoodsInfo.id = Fly_string::GetSubStr(tmpGoodsInfo.id.c_str(), ",", 1);
				isSelect = true;
			}
			if (i == 2 && tmpGoodsInfo.name.length() < 3 && Fly_string::FindSub(fullStr, it))
			{
				tmpGoodsInfo.name = Fly_string::pFindSub(fullStr, it);
				tmpGoodsInfo.name = Fly_string::GetSubStr(tmpGoodsInfo.name.c_str(), ",", 1);
				isSelect = true;
			}
			if (i == 3 && tmpGoodsInfo.type.length() < 3 && Fly_string::FindSub(fullStr, it))
			{
				tmpGoodsInfo.type = Fly_string::pFindSub(fullStr, it);
				tmpGoodsInfo.type = Fly_string::GetSubStr(tmpGoodsInfo.type.c_str(), ",", 1);
				isSelect = true;
			} 
		}
		m_select.goodsInfo = tmpGoodsInfo;
		return isSelect;
	}
	if (tabSel == 1)
	{		 
		const char* goodsInfo[] = { "入库日期=", "物品序号=", "登记人=" };
		int i = 0;
		IMPORTINFO tmpImportInfo;
		for (auto it : goodsInfo)
		{
			i++; 
			if (i == 1 && tmpImportInfo.data.length() < 3 && Fly_string::FindSub(fullStr, it))
			{
				tmpImportInfo.data = Fly_string::pFindSub(fullStr, it);
				tmpImportInfo.data = Fly_string::GetSubStr(tmpImportInfo.data.c_str(), ",", 1);
				isSelect = true;
			}
			if (i == 2 && tmpImportInfo.goodsGuid.length() < 3 && Fly_string::FindSub(fullStr, it))
			{
				std::string id = Fly_string::pFindSub(fullStr, it);
				id = Fly_string::GetSubStr(id.c_str(), ",", 1);
				tmpImportInfo.goodsGuid  = GoodsInfo::instance()->getGoodsGuids(id);
				isSelect = true;
			}
			if (i == 3 && tmpImportInfo.handleName.length() < 3 && Fly_string::FindSub(fullStr, it))
			{
				tmpImportInfo.handleName = Fly_string::pFindSub(fullStr, it);
				tmpImportInfo.handleName = Fly_string::GetSubStr(tmpImportInfo.handleName.c_str(), ",", 1);
				isSelect = true;
			} 
		}
		m_select.importInfo = tmpImportInfo;
		return isSelect;
	}
	if (tabSel == 2)
	{
		 
		const char* goodsInfo[] = { "出库日期=", "物品序号=", "领用人=", "登记人=" };
		int i = 0;
		OUTPORTINFO outPortInfo;
		for (auto it : goodsInfo)
		{
			i++;
			if (i == 1 && outPortInfo.data.length() < 3 && Fly_string::FindSub(fullStr, it))
			{
				outPortInfo.data = Fly_string::pFindSub(fullStr, it);
				outPortInfo.data = Fly_string::GetSubStr(outPortInfo.data.c_str(), ",", 1);
				isSelect = true;
			}
			if (i == 2 && outPortInfo.goodsGuid.length() < 3 && Fly_string::FindSub(fullStr, it))
			{
				std::string id = Fly_string::pFindSub(fullStr, it);
				id = Fly_string::GetSubStr(id.c_str(), ",", 1);
				outPortInfo.goodsGuid = GoodsInfo::instance()->getGoodsGuids(id); 
				isSelect = true;
			}
			if (i == 3 && outPortInfo.useName.length() < 3 && Fly_string::FindSub(fullStr, it))
			{
				outPortInfo.useName = Fly_string::pFindSub(fullStr, it);
				outPortInfo.useName = Fly_string::GetSubStr(outPortInfo.useName.c_str(), ",", 1);
				isSelect = true;
			}
			if (i == 4 && outPortInfo.handleName.length() < 3 && Fly_string::FindSub(fullStr, it))
			{
				outPortInfo.handleName = Fly_string::pFindSub(fullStr, it);
				outPortInfo.handleName = Fly_string::GetSubStr(outPortInfo.handleName.c_str(), ",", 1);
				isSelect = true;
			}
		}
		m_select.outportInfo = outPortInfo;
		return isSelect;
	}
}

SELECTINFO CstoragedemoDlg::getSelectTabInfo()
{
	return m_select;
}
 
void CstoragedemoDlg::initList()
{
	// 为列表视图控件添加全行选中和栅格风格    
	LONG lStyle;
	lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);//获取当前窗口style 
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位 
	lStyle |= LVS_REPORT; //设置style 
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle);//设置style
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); 
}

void CstoragedemoDlg::setListHead(int tabSel)
{

	// 为列表视图控件添加三列   
	CRect rect; 
	// 获取编程语言列表视图控件的位置和大小   
	m_list.GetClientRect(&rect);
	//清理
	while (m_list.DeleteColumn(0)); 
	m_list.DeleteAllItems();

	if (tabSel == 0)
	{
		const wchar_t* goodsInfo[] = { L"物品序号", L"物品名称", L"物品类型",  L"余量" };
		int count = sizeof(goodsInfo)/4;
		for (int i = 0; i < count; i++)
		{
			m_list.InsertColumn(i, goodsInfo[i], LVCFMT_CENTER, rect.Width() / count, i); 
		}
		return;
	}
	if (tabSel == 1)
	{
		const wchar_t* goodsInfo[] = {L"入库日期", L"物品序号",L"入库数量", L"登记人" };
		int count = sizeof(goodsInfo) / 4;
		for (int i = 0; i < count; i++)
		{
			m_list.InsertColumn(i, goodsInfo[i], LVCFMT_CENTER, rect.Width() / count, i);
		}
		return;
	}
	if (tabSel == 2)
	{
		const wchar_t* goodsInfo[] = { L"出库日期", L"物品序号",L"出库数量", L"领用人", L"登记人" };
		int count = sizeof(goodsInfo) / 4;
		for (int i = 0; i < count; i++)
		{
			m_list.InsertColumn(i, goodsInfo[i], LVCFMT_CENTER, rect.Width() / count, i);
		}
		return;
	}
}

void CstoragedemoDlg::setListBody(int tabSel)
{
	if (tabSel == 0)
	{
		auto goodsGuids = GoodsInfo::instance()->getGoodsGuids();
		int row = m_list.GetItemCount();
		for (auto it : goodsGuids)
		{ 
			if(addGoodsInfoToListBody(row, it))
				row++;
		}
		return;
	}
	if (tabSel == 1)
	{
		auto info = StorageAct::instance()->getImportGoodsToStrorageInfo();
		int row = m_list.GetItemCount();
		for (auto it : info)
		{ 
			if(addImportInfoToListBody(row, it))
				row++;
		}
		return;
	}
	if (tabSel == 2)
	{
		auto inf = StorageAct::instance()->getOutputGoodsFromStrorageInfo();
		int row = m_list.GetItemCount();
		for (auto it : inf)
		{
			if(addOutportInfoToListBody(row, it))
				row++;
		}
		return;
	}
}

void CstoragedemoDlg::setSelectListBody(int tabSel)
{
	auto it = getSelectTabInfo();
	if (tabSel == 0)
	{
		auto goodsGuids = GoodsInfo::instance()->getSelectGoodsGuids(it.goodsInfo);
		int row = m_list.GetItemCount();
		for (auto it : goodsGuids)
		{
			if (addGoodsInfoToListBody(row, it))
				row++;
		}
		return;
	}
	if (tabSel == 1)
	{
		auto info = StorageAct::instance()->getSelectImportGoodsToStrorageInfo(it.importInfo);
		int row = m_list.GetItemCount();
		for (auto it : info)
		{
			if (addImportInfoToListBody(row, it))
				row++;
		}
		return;
	}
	if (tabSel == 2)
	{
		auto inf = StorageAct::instance()->getSelectOutputGoodsFromStrorageInfo(it.outportInfo);
		int row = m_list.GetItemCount();
		for (auto it : inf)
		{
			if (addOutportInfoToListBody(row, it))
				row++;
		}
		return;
	}
}

bool CstoragedemoDlg::addGoodsInfoToListBody(int row, std::string goodsGuid)
{
	GOODSINFO info;
	if (GoodsInfo::instance()->getGoodsInfo(goodsGuid, &info))
	{
		if (info.id.length() < 3)
			return false;
		int col = 1;  
		m_list.InsertItem(row, Fly_string::c2w(info.id.c_str()).c_str());
		m_list.SetItemText(row, col, Fly_string::c2w(info.name.c_str()).c_str());
		col++;
		m_list.SetItemText(row, col, Fly_string::c2w(info.type.c_str()).c_str());
		col++;
		m_list.SetItemText(row, col, Fly_string::c2w(Fly_string::format("%d", info.count).c_str()).c_str());
		return true;
	}
	return false;
}
 
bool CstoragedemoDlg::addImportInfoToListBody(int row, IMPORTINFO info)
{
	GOODSINFO goodsInfo;
	if (!GoodsInfo::instance()->getGoodsInfo(info.goodsGuid, &goodsInfo))
		return false;
	if (goodsInfo.id.length() < 3)
		return false;
	int col = 1;
	m_list.InsertItem(row, Fly_string::c2w(info.data.c_str()).c_str());
	m_list.SetItemText(row, col, Fly_string::c2w(goodsInfo.id.c_str()).c_str());
	col++;
	m_list.SetItemText(row, col, Fly_string::c2w(Fly_string::format("%d", info.count).c_str()).c_str());
	col++;
	m_list.SetItemText(row, col, Fly_string::c2w(info.handleName.c_str()).c_str());
	return true;
}

bool CstoragedemoDlg::addOutportInfoToListBody(int row, OUTPORTINFO info)
{
	int col = 1;
	GOODSINFO goodsInfo;
	if (!GoodsInfo::instance()->getGoodsInfo(info.goodsGuid, &goodsInfo))
		return false;
	if (goodsInfo.id.length() < 3)
		return false;
	m_list.InsertItem(row, Fly_string::c2w(info.data.c_str()).c_str());
	m_list.SetItemText(row, col, Fly_string::c2w(goodsInfo.id.c_str()).c_str());
	col++;
	m_list.SetItemText(row, col, Fly_string::c2w(Fly_string::format("%d", info.count).c_str()).c_str());
	col++;
	m_list.SetItemText(row, col, Fly_string::c2w(info.useName.c_str()).c_str());
	col++;
	m_list.SetItemText(row, col, Fly_string::c2w(info.handleName.c_str()).c_str());
	return true;
}
 
 

BEGIN_MESSAGE_MAP(CstoragedemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CstoragedemoDlg::OnSelchangeTab1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CstoragedemoDlg::OnLvnItemchangedList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CstoragedemoDlg::OnRclickList1)
	ON_BN_CLICKED(IDC_Select, &CstoragedemoDlg::OnBnClickedSelect)
END_MESSAGE_MAP()


// CstoragedemoDlg 消息处理程序

BOOL CstoragedemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	initTab();
	initList();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CstoragedemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CstoragedemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CstoragedemoDlg::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	setTabInfo();
}


void CstoragedemoDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CstoragedemoDlg::OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int cur = m_tab.GetCurSel();
	int row = pNMItemActivate->iItem;    //item (行)
	setListSel(row);
	PopMenu(cur, row);
}

void CstoragedemoDlg::PopMenu(int cursel, int row)
{
	CPoint p;
	GetCursorPos(&p);//鼠标点的屏幕坐标
	CMenu m_Menu;
	m_Menu.LoadMenu(IDR_MENU1);//编辑好的菜单资源
	if (cursel > 0)
	{
		CMenu *m_SubMenu = m_Menu.GetSubMenu(0);
		m_SubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, p.x, p.y, this);
		return;
	}

	if (row > -1)
	{
		CMenu *m_SubMenu = m_Menu.GetSubMenu(1);
		m_SubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, p.x, p.y, this);
	}
	else
	{
		CMenu *m_SubMenu = m_Menu.GetSubMenu(0);
		m_SubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, p.x, p.y, this);
	}
}


BOOL CstoragedemoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return 1;
	if (pMsg->message == WM_COMMAND && pMsg->wParam == ID_ADD) //添加
	{
		addInfo();
		return 1;
	}
	if (pMsg->message == WM_COMMAND && pMsg->wParam == ID_ALT) //修改
	{
		altInfo();
		return 1;
	}
	if (pMsg->message == WM_COMMAND && pMsg->wParam == ID_DEL) //删除
	{
		delInfo();
		return 1;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CstoragedemoDlg::OnBnClickedSelect()
{
	// TODO: 在此添加控件通知处理程序代码
	selectInfo();
}
