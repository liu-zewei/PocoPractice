#ifndef POCOLOGGER_H
#define POCOLOGGER_H

#include <string>
#include "Poco/LogStream.h"

using Poco::LogStream;

class PocoLogger
{
public:

	static PocoLogger* GetInstance();

	~PocoLogger();
	
	std::ostream &Information(std::string file, int line);

	std::ostream &Notice(std::string file, int line);

	std::ostream &Warning(std::string file, int line);

	std::ostream &Error(std::string file, int line);

	std::ostream &Critical(std::string file, int line);

	std::ostream &Fatal(std::string file, int line);

private:

	PocoLogger();

	void Init();

	void UnInit();

private:

	static PocoLogger instance_;

	LogStream *pLogStream_;

};

#define LOGI PocoLogger::GetInstance()->Information(__FILE__, __LINE__)
#define LOGN PocoLogger::GetInstance()->Notice(__FILE__, __LINE__)
#define LOGW PocoLogger::GetInstance()->Warning(__FILE__, __LINE__)
#define LOGE PocoLogger::GetInstance()->Error(__FILE__, __LINE__)
#define LOGC PocoLogger::GetInstance()->Critical(__FILE__, __LINE__)
#define LOGF PocoLogger::GetInstance()->Fatal(__FILE__, __LINE__)

class Tracer
{
public:

	Tracer(const std::string functionName) : function_(functionName)
	{
		LOGI << "Entering" << function_ << std::endl;
	}

	~Tracer()
	{
		LOGI << "Leaving" << function_ << std::endl;
	}

private:

	std::string function_;

};

#define TRACER Tracer tracer(__FUNCTION__);

#endif //POCOLOGGER_H