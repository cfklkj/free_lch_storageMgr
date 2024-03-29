#pragma once

struct IMPORTINFO {
	std::string goodsGuid; //物品唯一标识
	int count;  //入库数量
	std::string data;  //入库日期
	std::string handleName;  //登记人
	std::string note;//备注
};
struct  OUTPORTINFO
{
	std::string goodsGuid;  //物品唯一标识
	int count;  //入库数量
	std::string data;  //入库日期
	std::string useName;  //领用人
	std::string handleName; //登记人 
	std::string note;//备注
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
	std::vector<IMPORTINFO> getSelectImportGoodsToStrorageInfo(IMPORTINFO info); 
	//出库
	bool outputGoodsFromStrorage(OUTPORTINFO info);
	std::vector<OUTPORTINFO>  getOutputGoodsFromStrorageInfo() { return m_vecOutport; };
	std::vector<OUTPORTINFO> getSelectOutputGoodsFromStrorageInfo(OUTPORTINFO info); 
	 

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
	//select
	bool isSelectImport(IMPORTINFO it, IMPORTINFO info);
	bool isSelectOutport(OUTPORTINFO it, OUTPORTINFO info);
	
};

