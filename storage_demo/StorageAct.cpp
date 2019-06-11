#include "stdafx.h"
#include "StorageAct.h"

static StorageAct g_storage;
StorageAct::StorageAct()
{
	std::string path = Fly_file::Dir::getCurrentThisPath(NULL) + "data";
	Fly_file::Dir::createDirs(path);
	g_storageImportFilePath = path + "\\importStorage.data";
	g_storageOutportFilePath = path + "\\outportStorage.data";
	initVecImport();
	initVecOutport();
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
	if (!GoodsInfo::instance()->getGoodsInfo(info.goodsGuid, NULL))
	{ 
		ErroInfo::instance()->setErroInfo("未找到物品id");
		return false;
	}
	info.data = Fly_Time::TIME::GetDateString();
	GoodsInfo::instance()->upGoodsCount(info.goodsGuid, info.count);
	addToImportStrorageFile(info);
	return true;
}

std::vector<IMPORTINFO> StorageAct::getSelectImportGoodsToStrorageInfo(IMPORTINFO info)
{
	std::vector<IMPORTINFO> rstInfo;
	for (auto it : m_vecImport)
	{
		if (isSelectImport(it, info))
			rstInfo.push_back(it);
	}
	return rstInfo;
}
 

bool StorageAct::outputGoodsFromStrorage(OUTPORTINFO info)
{
	if (!GoodsInfo::instance()->getGoodsInfo(info.goodsGuid, NULL))
	{
		ErroInfo::instance()->setErroInfo("未找到物品id");
		return false;
	}
	info.data = Fly_Time::TIME::GetDateString();
	GoodsInfo::instance()->upGoodsCount(info.goodsGuid, -info.count);
	addToOutportStrorageFile(info);
	return false;
}

std::vector<OUTPORTINFO> StorageAct::getSelectOutputGoodsFromStrorageInfo(OUTPORTINFO info)
{
	std::vector<OUTPORTINFO> rstInfo;
	for (auto it : m_vecOutport)
	{
		if (isSelectOutport(it, info))
			rstInfo.push_back(it);
	}
	return rstInfo;
}
 

bool StorageAct::addToImportStrorageFile(IMPORTINFO info)
{
	m_vecImport.push_back(info);

	FILE *stream;
	fopen_s(&stream, g_storageImportFilePath.c_str(), "a+");
	if (stream)
	{
		fprintf(stream, "%s,%d,%s,%s,%s\n", info.goodsGuid.c_str(), info.count, info.data.c_str(), info.handleName.c_str(), info.note.c_str());
		fclose(stream);
	}
	return false;
}

bool StorageAct::addToOutportStrorageFile(OUTPORTINFO info)
{

	m_vecOutport.push_back(info);

	FILE *stream;
	fopen_s(&stream, g_storageOutportFilePath.c_str(), "a+");
	if (stream)
	{
		fprintf(stream, "%s,%d,%s,%s,%s,%s\n", info.goodsGuid.c_str(), info.count, info.data.c_str(), info.useName.c_str(), info.handleName.c_str(), info.note.c_str());
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
		while (fgets(buff, 255, stream) != NULL)
		{
			IMPORTINFO info;
			info.goodsGuid = Fly_string::GetSubStr(buff, ",", 1);
			info.count = atoi(Fly_string::GetSubStr(buff, ",", 2).c_str());
			info.data = Fly_string::GetSubStr(buff, ",", 3);
			info.handleName = Fly_string::GetSubStr(buff, ",", 4);
			info.note = Fly_string::GetSubStr(buff, ",", 5); 
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
		while (fgets(buff, 255, stream) != NULL)
		{
			OUTPORTINFO info;
			info.goodsGuid = Fly_string::GetSubStr(buff, ",", 1);
			info.count = atoi(Fly_string::GetSubStr(buff, ",", 2).c_str());
			info.data = Fly_string::GetSubStr(buff, ",", 3);
			info.useName = Fly_string::GetSubStr(buff, ",", 4);
			info.handleName = Fly_string::GetSubStr(buff, ",", 5);
			info.note = Fly_string::GetSubStr(buff, ",", 6);
			GoodsInfo::instance()->upGoodsCount(info.goodsGuid, -info.count);
			m_vecOutport.push_back(info);
		}
		fclose(stream);
	}

}

bool StorageAct::isSelectImport(IMPORTINFO it, IMPORTINFO info)
{
	bool isSelect = false;
	if (info.data.length() > 0)
	{
		isSelect = it.data == info.data;
		if (!isSelect)
			return false;
	}
	if (info.goodsGuid.length() > 0 )
	{
		isSelect = it.goodsGuid == info.goodsGuid;
		if (!isSelect)
			return false;
	}
	if (info.handleName.length() > 0 )
	{
		isSelect = it.handleName == info.handleName;
		if (!isSelect)
			return false;
	} 
	return isSelect;
}

bool StorageAct::isSelectOutport(OUTPORTINFO it, OUTPORTINFO info)
{
	bool isSelect = false;
	if (info.data.length() > 0)
	{
		isSelect = it.data == info.data;
		if (!isSelect)
			return false;
	}
	if (info.goodsGuid.length() > 0)
	{
		isSelect = it.goodsGuid == info.goodsGuid;
		if (!isSelect)
			return false;
	}
	if (info.handleName.length() > 0)
	{
		isSelect = it.handleName == info.handleName;
		if (!isSelect)
			return false;
	}
	if (info.useName.length() > 0)
	{
		isSelect = it.useName == info.useName;
		if (!isSelect)
			return false;
	}
	return true;
}

 
