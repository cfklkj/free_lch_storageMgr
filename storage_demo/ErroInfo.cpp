#include "stdafx.h"
#include "ErroInfo.h"

static ErroInfo g_erroInfo;

ErroInfo::ErroInfo()
{
}


ErroInfo::~ErroInfo()
{
}

ErroInfo * ErroInfo::instance()
{
	return &g_erroInfo;
}

void ErroInfo::setErroInfo(std::string info)
{
	m_errorInfo = info;
}

std::string ErroInfo::getErroInfo()
{
	return m_errorInfo;
}
