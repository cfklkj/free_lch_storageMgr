#pragma once


struct GOODSINFO {
	std::string  guid;  // 物品唯一标识
	std::string  id; //物品序号
	int type; // 物品类型
	std::string name;  //物品名称
	int count; //余量
};

//物品信息
class GoodsInfo
{
public:
	GoodsInfo();
	~GoodsInfo();
	
	static GoodsInfo* instance();

public: 
	//添加
	bool addGoodsInfo(GOODSINFO info);
	//删除
	bool delGoodsInf(GOODSINFO info);
	//修改
	bool altGoodsInfo(GOODSINFO info);
	//获取 物品 guid
	std::vector<std::string> getGoodsGuids();
	//获取物品详细信息
	bool getGoodsInfo(std::string  goodsGuid, GOODSINFO *out_info);
	//更新余量
	void upGoodsCount(std::string goodsGuid, int offset);

private: //写文件
	std::string g_goodsFilePath; 
	std::map<std::string, GOODSINFO> m_mapGoods;  //物品guid  物品信息
	bool findGoods(GOODSINFO info);
	bool addToGoodsFile(GOODSINFO info);
	bool altToGoodsFile();
	void initMapGoods();

	 
};

