#pragma once


struct GOODSINFO {
	std::string  guid="";  // ��ƷΨһ��ʶ
	std::string  id=""; //��Ʒ���
	int type=0; // ��Ʒ����
	std::string name="";  //��Ʒ����
	int count=0; //����
};

//��Ʒ��Ϣ
class GoodsInfo
{
public:
	GoodsInfo();
	~GoodsInfo();
	
	static GoodsInfo* instance();

public: 
	//���
	bool addGoodsInfo(GOODSINFO info);
	//ɾ��
	bool delGoodsInf(GOODSINFO info);
	//�޸�
	bool altGoodsInfo(GOODSINFO info);
	//��ȡ ��Ʒ guid
	std::vector<std::string> getGoodsGuids();
	std::string getGoodsGuids(std::string goodsId); 
	//��ȡ��Ʒ��ϸ��Ϣ
	bool getGoodsInfo(std::string  goodsGuid, GOODSINFO *out_info);
	//��������
	void upGoodsCount(std::string goodsGuid, int offset);

private: //д�ļ�
	std::string g_goodsFilePath; 
	std::map<std::string, GOODSINFO> m_mapGoods;  //��Ʒguid  ��Ʒ��Ϣ
	bool findGoods(GOODSINFO info);
	bool addToGoodsFile(GOODSINFO info);
	bool altToGoodsFile();
	void initMapGoods();

	 
};

