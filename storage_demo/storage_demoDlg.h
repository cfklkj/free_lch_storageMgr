
// storage_demoDlg.h: 头文件
//

#pragma once


// CstoragedemoDlg 对话框
class CstoragedemoDlg : public CDialogEx
{
// 构造
public:
	CstoragedemoDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STORAGE_DEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	void addInfo();
	void altInfo();
	void delInfo();
private:
	void initTab();
	void setGoodsInfo();
	void setImportInfo();
	void setOutportInfo();

private:
	void initList();
	void setListHead(int tabSel);
	void setListBody(int tabSel);
	bool addGoodsInfoToListBody(int row, std::string goodsGuid); 
	bool addImportInfoToListBody(int row, IMPORTINFO info);
	bool addOutportInfoToListBody(int row, OUTPORTINFO info);
	 
	void setListSel(int cur) { m_listSel = cur; };
	int getListSel() { return m_listSel; }; 
private:
	int m_listSel = -1; 
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;
	afx_msg void OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_list;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	void PopMenu(int cursel, int row);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
};
