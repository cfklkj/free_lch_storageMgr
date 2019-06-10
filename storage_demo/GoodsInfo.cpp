#include "stdafx.h"
#include "GoodsInfo.h"

static GoodsInfo g_addgoods; 

GoodsInfo::GoodsInfo()
{
	g_goodsFilePath = Fly_file::Dir::getCurrentThisPath(NULL) + "data";
	Fly_file::Dir::createDirs(g_goodsFilePath);
	g_goodsFilePath += "\\goodsInfo.data";
	initMapGoods();
}


GoodsInfo::~GoodsInfo()
{ 
}

GoodsInfo * GoodsInfo::instance()
{
	return &g_addgoods;
}
 
bool GoodsInfo::addGoodsInfo(GOODSINFO info)
{
	info.guid = Fly_string::makeStr::generateGuid();
	if (findGoods(info))
	{
		ErroInfo::instance()->setErroInfo("已存在物品id");
		return false;
	}
	addToGoodsFile(info);
	return true;
}

bool GoodsInfo::delGoodsInf(GOODSINFO info)
{  
	if (!findGoods(info))
	{
		ErroInfo::instance()->setErroInfo("不存在物品id");
		return false;
	}
	GOODSINFO delInfo;
	m_mapGoods[info.guid] = delInfo;
	altToGoodsFile();
	return true;
}

bool GoodsInfo::altGoodsInfo(GOODSINFO info)
{
	if (!findGoods(info))
	{
		ErroInfo::instance()->setErroInfo("不存在物品id");
		return false;
	}
	m_mapGoods[info.guid] = info;
	altToGoodsFile();
	return true;
}

std::vector<std::string> GoodsInfo::getGoodsGuids()
{
	std::vector<std::string> info;
	for (auto it : m_mapGoods)
	{
		info.push_back(it.first);
	}
	return info;
}

std::vector<std::string> GoodsInfo::getSelectGoodsGuids(GOODSINFO selectInfo)
{
	std::vector<std::string> info;
	for (auto it : m_mapGoods)
	{
		if (isSelectGoods(it.second, selectInfo))
		{
			info.push_back(it.first);
		}
	}
	return info;
}

std::string GoodsInfo::getGoodsGuids(std::string goodsId)
{
	for (auto it : m_mapGoods)
	{
		if(it.second.id == goodsId)
			return it.first;
	}
	return std::string();
}
 
 

bool GoodsInfo::getGoodsInfo(std::string goodsGuid, GOODSINFO *out_info)
{ 
	auto it = m_mapGoods.find(goodsGuid);
	if (it != m_mapGoods.end())
	{
		if (out_info)  //判断是否需要返回信息
		{ 
			*out_info = it->second;
		}		
		return true;
	}
	return false; 
}

void GoodsInfo::upGoodsCount(std::string goodsGuid, int offset)
{
	auto it = m_mapGoods.find(goodsGuid);
	if (it != m_mapGoods.end())
	{
		m_mapGoods[goodsGuid].count += offset;
	}
}

bool GoodsInfo::findGoods(GOODSINFO info)
{
	for (auto it : m_mapGoods)
	{
		if (it.second.id == info.id)
			return true;
	}
	return false;
}

bool GoodsInfo::addToGoodsFile(GOODSINFO info)
{
	m_mapGoods[info.guid] = info;

	FILE *stream;
	fopen_s(&stream, g_goodsFilePath.c_str(), "a+"); 
	if (stream)
	{ 
		fprintf(stream, "%s,%s,%s,%s\n", info.guid.c_str(), info.id.c_str(), info.type.c_str(), info.name.c_str());
		fclose(stream);
	}
	return false;
}

bool GoodsInfo::altToGoodsFile()
{
	FILE *stream;
	fopen_s(&stream, g_goodsFilePath.c_str(), "w+");
	if (stream)
	{
		for (auto it : m_mapGoods)
		{
			if (it.second.guid.length() < 3)
				continue;
			fprintf(stream, "%s,%s,%s,%s\n", it.second.guid.c_str(), it.second.id.c_str(), it.second.type.c_str(), it.second.name.c_str());
		}
		fclose(stream);
	}
	return false;
}

void GoodsInfo::initMapGoods()
{
	FILE *stream;
	fopen_s(&stream, g_goodsFilePath.c_str(), "r"); 
	if (stream)
	{
		char buff[256];
		while(fgets(buff, 255, stream) != NULL)
		{
			GOODSINFO info;
			info.guid = Fly_string::GetSubStr(buff, ",", 1);
			info.id = Fly_string::GetSubStr(buff, ",", 2);
			info.type = Fly_string::GetSubStr(buff, ",", 3);
			info.name = "\r\n" + Fly_string::GetSubStr(buff, ",", 4);
			if (info.guid.length() < 3)
				continue;
			info.name = Fly_string::delChar(info.name.c_str(), "\r\n", 0);
			m_mapGoods[info.guid] = info;
		} 
		fclose(stream); 
	}
}

bool GoodsInfo::isSelectGoods(GOODSINFO itInfo, GOODSINFO selectInfo)
{ 
	bool isSelect = false;
	if (selectInfo.guid.length() > 0 )
	{ 
		isSelect = selectInfo.guid == itInfo.guid;
		if (!isSelect)
			return false;
	}
	if (selectInfo.id.length() > 0)
	{ 
		isSelect = selectInfo.id == itInfo.id;
		if (!isSelect)
			return false;
	}
	if (selectInfo.name.length() > 0)
	{ 
		isSelect = selectInfo.name == itInfo.name;
		if (!isSelect)
			return false;
	}
	if (selectInfo.type.length() > 0)
	{ 
		isSelect = selectInfo.type == itInfo.type;
		if (!isSelect)
			return false;
	}
	return isSelect;
}
 