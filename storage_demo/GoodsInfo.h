#pragma once


struct GOODSINFO {
	std::string  guid;  // ��ƷΨһ��ʶ
	std::string  id; //��Ʒ���
	int type; // ��Ʒ����
	std::string name;  //��Ʒ����
};

//��Ʒ��Ϣ
class GoodsInfo
{
public:
	GoodsInfo();
	~GoodsInfo();
	
	static GoodsInfo* instance();

public: 
	//����
	bool addGoodsInfo(GOODSINFO info);
	//ɾ��
	bool delGoodsInf(GOODSINFO info);
	//�޸�
	bool altGoodsInfo(GOODSINFO info);
	//��ȡ ��Ʒ guid
	std::vector<std::string> getGoodsGuids();
	//��ȡ��Ʒ��ϸ��Ϣ
	bool getGoodsInfo(std::string  goodsGuid, GOODSINFO *out_info);

private: //д�ļ�
	std::string g_goodsFilePath; 
	std::map<std::string, GOODSINFO> m_mapGoods;  //��Ʒguid  ��Ʒ��Ϣ
	bool findGoods(GOODSINFO info);
	bool addToGoodsFile(GOODSINFO info);
	bool altToGoodsFile();
	void initMapGoods();

	 
};
