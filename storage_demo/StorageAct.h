#pragma once

struct IMPORTINFO {
	std::string goodsGuid; //��ƷΨһ��ʶ
	int count;  //�������
	std::string data;  //�������
	std::string handleName;  //�Ǽ���
	std::string note;//��ע
};
struct  OUTPORTINFO
{
	std::string goodsGuid;  //��ƷΨһ��ʶ
	int count;  //�������
	std::string data;  //�������
	std::string useName;  //������
	std::string handleName; //�Ǽ��� 
	std::string note;//��ע
};
class StorageAct
{
public:
	StorageAct();
	~StorageAct();
	
	static StorageAct* instance();
public: 

	//���
	bool importGoodsToStrorage(IMPORTINFO info);
	std::vector<IMPORTINFO> getImportGoodsToStrorageInfo() { return m_vecImport; };
	std::vector<IMPORTINFO> getSelectImportGoodsToStrorageInfo(IMPORTINFO info); 
	//����
	bool outputGoodsFromStrorage(OUTPORTINFO info);
	std::vector<OUTPORTINFO>  getOutputGoodsFromStrorageInfo() { return m_vecOutport; };
	std::vector<OUTPORTINFO> getSelectOutputGoodsFromStrorageInfo(OUTPORTINFO info); 
	 

private:
	//д�ļ�
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

