#include <iostream>
#include <Poco/Util/Application.h>

class MyApp : public Poco::Util::Application
{
public:
	MyApp();
	~MyApp();
	void initialize(Application& self);
	void uninitialize();
	int main(const std::vector<std::string>& args);
private:
	//~MyApp();
};

MyApp::MyApp()
{
}

MyApp::~MyApp()
{
}

void MyApp::initialize(Application& self)
{
	Poco::Util::Application::initialize(self);
	std::cout << "this is initialize" << std::endl;
}

void MyApp::uninitialize()
{
	Poco::Util::Application::uninitialize();
	std::cout << "this is uninitialize" << std::endl;
}

int MyApp::main(const std::vector<std::string>& args)
{
	std::cout << "this is main" << std::endl;
	return Application::EXIT_OK;
}

int main(int argc, char **agrv)
{
	MyApp app;
	app.run();
}

