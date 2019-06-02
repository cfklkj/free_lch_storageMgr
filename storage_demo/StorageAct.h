#pragma once

struct IMPORTINFO {
	std::string id; //��Ʒ���
	int count;  //�������
	std::string data;  //�������
	std::string handleName;  //�Ǽ���
};
struct  OUTPORTINFO
{
	std::string id;  //��Ʒ���
	int count;  //�������
	std::string data;  //�������
	std::string useName;  //������
	std::string handleName; //�Ǽ���

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
	//����
	bool outputGoodsFromStrorage(OUTPORTINFO info);
	std::vector<OUTPORTINFO>  getOutputGoodsFromStrorageInfo() { return m_vecOutport; };
	 

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
	
};

