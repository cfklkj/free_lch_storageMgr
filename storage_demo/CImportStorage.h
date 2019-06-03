#pragma once


// CImportStorage 对话框

class CImportStorage : public CDialogEx
{
	DECLARE_DYNAMIC(CImportStorage)

public:
	CImportStorage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CImportStorage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ImportStorage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk(); 
	bool UpCtrl(); 
};
