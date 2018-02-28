#pragma once

#include <Poco/Util/ServerApplication.h>
#include <Poco/Net/HTTPServer.h>



class MySvrApp : public Poco::Util::ServerApplication
{
public:
	MySvrApp();
protected:
	virtual ~MySvrApp();

	Poco::Net::HTTPServer* httpServer_;
};
