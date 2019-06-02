#pragma once
class ErroInfo
{
public:
	ErroInfo();
	~ErroInfo();
	static ErroInfo * instance();

public:
	//¥ÌŒÛ–≈œ¢
	void setErroInfo(std::string info);

	std::string getErroInfo();
private:
	std::string m_errorInfo;
};

