#pragma once


// CGoodsInfo 对话框

class CGoodsInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CGoodsInfo)

public:
	CGoodsInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGoodsInfo();

public:
	void InitCtl();
	bool UpCtrl();

	void setGoods(std::string goodsGuid) { m_goodsGuid = goodsGuid; };
	std::string getGoodsGuid() { return m_goodsGuid; };
private:
	std::string m_goodsGuid;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_addGoods };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
