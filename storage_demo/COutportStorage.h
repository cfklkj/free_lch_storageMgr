#pragma once


// COutportStorage 对话框

class COutportStorage : public CDialogEx
{
	DECLARE_DYNAMIC(COutportStorage)

public:
	COutportStorage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~COutportStorage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OutportStorage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
