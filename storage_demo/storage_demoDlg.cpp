
// storage_demoDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "storage_demo.h"
#include "storage_demoDlg.h"
#include "afxdialogex.h"

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

void CstoragedemoDlg::initTab()
{
	//为Tab Control增加两个页面
	m_tab.InsertItem(0, _T("物品信息"));
	m_tab.InsertItem(1, _T("入库信息"));
	m_tab.InsertItem(2, _T("出库信息"));
	setGoodsInfo();
}

void CstoragedemoDlg::setGoodsInfo()
{
	int tabSel = m_tab.GetCurSel();
	setListHead(tabSel);
	setListBody(tabSel);
}

void CstoragedemoDlg::setImportInfo()
{
	int tabSel = m_tab.GetCurSel();
	setListHead(tabSel);
	setListBody(tabSel);
}

void CstoragedemoDlg::setOutportInfo()
{
	int tabSel = m_tab.GetCurSel();
	setListHead(tabSel);
	setListBody(tabSel);
}

void CstoragedemoDlg::initList()
{
	// 为列表视图控件添加全行选中和栅格风格   
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
		const wchar_t* goodsInfo[] = { L"物品序号",L"物品类型", L"物品名称", L"余量" };
		int count = sizeof(goodsInfo);
		for (int i = 0; i < count; i++)
		{
			m_list.InsertColumn(i, goodsInfo[i], LVCFMT_CENTER, rect.Width() / count, i);
		}
		return;
	}
	if (tabSel == 1)
	{
		const wchar_t* goodsInfo[] = {L"入库日期", L"物品序号",L"入库数量", L"登记人" };
		int count = sizeof(goodsInfo);
		for (int i = 0; i < count; i++)
		{
			m_list.InsertColumn(i, goodsInfo[i], LVCFMT_CENTER, rect.Width() / count, i);
		}
		return;
	}
	if (tabSel == 2)
	{
		const wchar_t* goodsInfo[] = { L"出库日期", L"物品序号",L"出库数量", L"领用人", L"登记人" };
		int count = sizeof(goodsInfo);
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
		int row = 0;
		for (auto it : goodsGuids)
		{ 
			GOODSINFO info;
			if (GoodsInfo::instance()->getGoodsInfo(it, &info))
			{
				int col = 0;
				m_list.InsertItem(row, Fly_string::c2w(info.name.c_str()).c_str());
				m_list.SetItemText(row, col++, Fly_string::c2w(info.id.c_str()).c_str());
				m_list.SetItemText(row, col++, Fly_string::c2w(Fly_string::format("%d", info.type).c_str()).c_str());
			}
			row++;
		}
		return;
	}
	if (tabSel == 1)
	{
		auto info = StorageAct::instance()->getImportGoodsToStrorageInfo();
		int row = 0;
		for (auto it : info)
		{ 
			int col = 0;
			GOODSINFO info;
			if (!GoodsInfo::instance()->getGoodsInfo(it.goodsGuid, &info))
				continue;
			m_list.InsertItem(row, Fly_string::c2w(it.data.c_str() ).c_str());
			m_list.SetItemText(row, col++, Fly_string::c2w(info.guid.c_str()).c_str());
			m_list.SetItemText(row, col++, Fly_string::c2w(Fly_string::format("%d", it.count).c_str()).c_str());
			m_list.SetItemText(row, col++, Fly_string::c2w(it.handleName.c_str()).c_str());
			row++;
		}
		return;
	}
	if (tabSel == 2)
	{
		auto inf = StorageAct::instance()->getOutputGoodsFromStrorageInfo();
		int row = 0;
		for (auto it : inf)
		{
			int col = 0;
			GOODSINFO info;
			if (!GoodsInfo::instance()->getGoodsInfo(it.goodsGuid, &info))
				continue;
			m_list.InsertItem(row, Fly_string::c2w(it.data.c_str()).c_str());
			m_list.SetItemText(row, col++, Fly_string::c2w(info.guid.c_str()).c_str());
			m_list.SetItemText(row, col++, Fly_string::c2w(Fly_string::format("%d", it.count).c_str()).c_str());
			m_list.SetItemText(row, col++, Fly_string::c2w(it.useName.c_str()).c_str());
			m_list.SetItemText(row, col++, Fly_string::c2w(it.handleName.c_str()).c_str());
			row++;
		}
		return;
	}
}

void CstoragedemoDlg::addToListBody(int tabSel)
{
}

BEGIN_MESSAGE_MAP(CstoragedemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CstoragedemoDlg::OnSelchangeTab1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CstoragedemoDlg::OnLvnItemchangedList1)
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
	switch (m_tab.GetCurSel())
	{
	case 0:
		setGoodsInfo();
		break;
	case 1:
		setImportInfo();
		break;
	case 2:
		setOutportInfo();
		break;
	default:
		break;
	}
}


void CstoragedemoDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
