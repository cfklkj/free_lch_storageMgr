#pragma once
#include <string> 

namespace Fly_web {
	namespace RAW {
		//初始化环境
		bool IniSocket();
		//释放环境
		void UnInitSocket();
		//接收数据 
		std::string GetInfo(const int socket);
		//是否联网
		bool isLinkInternet();
		//从网址提取IP Port
		std::string GetIpPortfromUrl(const char* URl); 
		//从网址提取IP Port 如果存在:9080
		std::string GetIpPortfromUrl(const char* URl); 

	} 
	namespace Test {
		void Init();
	}

	namespace TCPs {
		namespace server {
			//创建服务套接字
			bool Init(int port);
			//等待客户端
			//等待客户端
			unsigned long WaitClientCome();
			//等待客户端数据
			std::string WaitClientInfo(const int clientID, char* rstBuff, int rstBuffLen);
			//发送数据
			bool SendInfo(const int clientID, const char* msg, int lenth);
		}
		namespace client {
			//创建客户端套接字
			bool Init(int port, char* IP);
			//接收数据
			std::string WaitServerMsg();
			//发送数据  parentID --调用init线程ID
			bool SendInfo(const int parentID, const char* msg, int lenth);
		}
	}
	namespace SETs {
		//是否是网络IP
		// LAN IP's
		// -------------------------------------------
		//	0.*								"This" Network
		//	10.0.0.0 - 10.255.255.255		Class A
		//	172.16.0.0 - 172.31.255.255		Class B
		//	192.168.0.0 - 192.168.255.255	Class C
		bool IsLANIP(unsigned int nIP);
		//启用或禁用网络
		//代替方案可用 cmd.exe /c ipconfig /release | /renew 
		bool LinkWeb(bool isDiskconnect);
		//获取网卡地址
		std::string GetMac();
	}
	namespace HTMLs {
		//Post
		std::string PosttUrlInfo(const char* Url);
		//获取网址内容
		std::string GetUrlInfo(const char* Url);
		//网址请求
		//body = "" 或 eg:id=12&ip=1234   --""  可判断 网址是否可用 ？
		std::string UrlRequest(const char * url, const char * body,const char * fun_type = "POST", const char * accept_type = "html/text", const char * connection_type = "Close");
		std::string UrlRequestV2(const char* url, const char* requestHead, const char* body);
	}
	namespace IOCPs {
		//注：---客户端使用 TCPs::lient  即可
		namespace server {
			//阻塞式   服务器可只做转发消息---转发消息到另外一个客户端去处理真正的逻辑
			bool createIOCPServer(int port);
		}
	}
}
 