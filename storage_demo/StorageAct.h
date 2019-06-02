#pragma once

struct IMPORTINFO {
	std::string id; //物品序号
	int count;  //入库数量
	std::string data;  //入库日期
	std::string handleName;  //登记人
};
struct  OUTPORTINFO
{
	std::string id;  //物品序号
	int count;  //入库数量
	std::string data;  //入库日期
	std::string useName;  //领用人
	std::string handleName; //登记人

};
class StorageAct
{
public:
	StorageAct();
	~StorageAct();
	
	static StorageAct* instance();
public: 

	//入库
	bool importGoodsToStrorage(IMPORTINFO info);
	std::vector<IMPORTINFO> getImportGoodsToStrorageInfo() { return m_vecImport; };
	//出库
	bool outputGoodsFromStrorage(OUTPORTINFO info);
	std::vector<OUTPORTINFO>  getOutputGoodsFromStrorageInfo() { return m_vecOutport; };
	 

private:
	//写文件
	std::string g_storageImportFilePath;
	std::string g_storageOutportFilePath;
	std::vector<IMPORTINFO> m_vecImport;
	std::vector<OUTPORTINFO> m_vecOutport;
	bool addToImportStrorageFile(IMPORTINFO info);
	bool addToOutportStrorageFile(OUTPORTINFO info);
	void initVecImport();
	void initVecOutport();
	
};

