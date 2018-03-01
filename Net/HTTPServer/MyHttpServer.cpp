#include <iostream>
#include <string>
#include <vector>

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

using namespace Poco;
using namespace Poco::Net;
using namespace Poco::Util;

class MyRequestHandler : public HTTPRequestHandler
{
public:
	virtual void handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp)
	{
		resp.setStatus(HTTPResponse::HTTP_OK);
		resp.setContentType("text/html");

		std::ostream & out = resp.send();

		out << "<h1>Hello World!</h1>";
	}
};

class MyRequestHandlerFactory : public HTTPRequestHandlerFactory
{
public:
	virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest &)
	{
		return new MyRequestHandler;
	}
};

class MyHttpServer : public ServerApplication
{
protected:
	int main(const std::vector<std::string> &)
	{
		HTTPServer s(new MyRequestHandlerFactory, ServerSocket(8080), new HTTPServerParams);

		s.start();
		std::cout << std::endl << "Server started" << std::endl;

		waitForTerminationRequest();

		std::cout << std::endl << "Shutting down..." << std::endl;
		s.stop();
		return Application::EXIT_OK;
	}
};

int main(int argc, char **argv)
{
	MyHttpServer app;
	return app.run(argc, argv);
}
