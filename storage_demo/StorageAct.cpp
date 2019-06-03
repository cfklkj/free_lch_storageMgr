#include "stdafx.h"
#include "StorageAct.h"

static StorageAct g_storage;
StorageAct::StorageAct()
{
	std::string path = Fly_file::Dir::getCurrentThisPath(NULL) + "data";
	Fly_file::Dir::createDirs(path);
	g_storageImportFilePath = path + "\\importStorage.data";
	g_storageOutportFilePath = path + "\\outportStorage.data";
}


StorageAct::~StorageAct()
{
}

StorageAct * StorageAct::instance()
{
	return &g_storage;
}
 
bool StorageAct::importGoodsToStrorage(IMPORTINFO info)
{ 
	if (GoodsInfo::instance()->getGoodsInfo(info.goodsGuid, NULL))
	{ 
		ErroInfo::instance()->setErroInfo("未找到物品id");
		return false;
	}
	info.data = Fly_Time::TIME::GetDateString();
	GoodsInfo::instance()->upGoodsCount(info.goodsGuid, info.count);
	addToImportStrorageFile(info);
	return false;
}

bool StorageAct::outputGoodsFromStrorage(OUTPORTINFO info)
{
	if (GoodsInfo::instance()->getGoodsInfo(info.goodsGuid, NULL))
	{
		ErroInfo::instance()->setErroInfo("未找到物品id");
		return false;
	}
	info.data = Fly_Time::TIME::GetDateString();
	GoodsInfo::instance()->upGoodsCount(info.goodsGuid, -info.count);
	addToOutportStrorageFile(info);
	return false;
}
 

bool StorageAct::addToImportStrorageFile(IMPORTINFO info)
{
	m_vecImport.push_back(info);

	FILE *stream;
	fopen_s(&stream, g_storageImportFilePath.c_str(), "w+");
	if (stream)
	{
		fprintf(stream, "{%s,%d,%s,%s\n", info.goodsGuid, info.count, info.data, info.handleName);
		fclose(stream);
	}
	return false;
}

bool StorageAct::addToOutportStrorageFile(OUTPORTINFO info)
{

	m_vecOutport.push_back(info);

	FILE *stream;
	fopen_s(&stream, g_storageOutportFilePath.c_str(), "w+");
	if (stream)
	{
		fprintf(stream, "{%s,%d,%s,%s,%s\n", info.goodsGuid, info.count, info.data, info.useName, info.handleName);
		fclose(stream);
	}
	return false;
}

void StorageAct::initVecImport()
{
	FILE *stream;
	fopen_s(&stream, g_storageImportFilePath.c_str(), "r");
	//  stream = _wfsopen(logPath, L"w", _SH_DENYNO);
	if (stream)
	{
		char buff[256];
		while (fgets(buff, 255, stream) != NULL);
		{
			IMPORTINFO info;
			info.goodsGuid = Fly_string::GetSubStr(buff, ",", 1);
			info.count = atoi(Fly_string::GetSubStr(buff, ",", 2).c_str());
			info.data = Fly_string::GetSubStr(buff, ",", 3);
			info.handleName = Fly_string::GetSubStr(buff, ",", 4);
			GoodsInfo::instance()->upGoodsCount(info.goodsGuid, info.count);
			m_vecImport.push_back(info);
		}
		fclose(stream);
	}

}

void StorageAct::initVecOutport()
{
	FILE *stream;
	fopen_s(&stream, g_storageOutportFilePath.c_str(), "r");
	//  stream = _wfsopen(logPath, L"w", _SH_DENYNO);
	if (stream)
	{
		char buff[256];
		while (fgets(buff, 255, stream) != NULL);
		{
			OUTPORTINFO info;
			info.goodsGuid = Fly_string::GetSubStr(buff, ",", 1);
			info.count = atoi(Fly_string::GetSubStr(buff, ",", 2).c_str());
			info.data = Fly_string::GetSubStr(buff, ",", 3);
			info.useName = Fly_string::GetSubStr(buff, ",", 4);
			info.handleName = Fly_string::GetSubStr(buff, ",", 5);
			GoodsInfo::instance()->upGoodsCount(info.goodsGuid, -info.count);
			m_vecOutport.push_back(info);
		}
		fclose(stream);
	}

}

 
