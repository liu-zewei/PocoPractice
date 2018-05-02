#include <string>
#include "PocoLogger.h"
#include "Poco/AutoPtr.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/Logger.h"
#include "Poco/FileChannel.h"
#include "Poco/LocalDateTime.h"
#include "Poco/NumberFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/PatternFormatter.h"

using Poco::AutoPtr;
using Poco::Path;
using Poco::File;
using Poco::Logger;
using Poco::FileChannel;
using Poco::LocalDateTime;
using Poco::NumberFormatter;
using Poco::FormattingChannel;
using Poco::PatternFormatter;

PocoLogger PocoLogger::instance_;

PocoLogger* PocoLogger::GetInstance()
{
	return &instance_;
}

PocoLogger::PocoLogger()
{
	Init();
}

PocoLogger::~PocoLogger()
{
	UnInit();
}

std::ostream& PocoLogger::Information(std::string file, int line)
{
	return pLogStream_->information() << "[" << file << ":" << line << "]";
}

std::ostream& PocoLogger::Notice(std::string file, int line)
{
	return pLogStream_->notice() << "[" << file << ":" << line << "]";
}

std::ostream& PocoLogger::Warning(std::string file, int line)
{
	return pLogStream_->warning() << "[" << file << ":" << line << "]";
}

std::ostream& PocoLogger::Error(std::string file, int line)
{
	return pLogStream_->error() << "[" << file << ":" << line << "]";
}

std::ostream& PocoLogger::Critical(std::string file, int line)
{
	return pLogStream_->critical() << "[" << file << ":" << line << "]";
}

std::ostream& PocoLogger::Fatal(std::string file, int line)
{
	return pLogStream_->fatal() << "[" << file << ":" << line << "]";
}

void PocoLogger::Init()
{
	//设置日志存储路径
	File logDir = Path::current() + "log/";
	if (!logDir.exists())
	{
		logDir.createDirectory();
	}

	//设置日志文件名
    LocalDateTime now;
	std::string logFileName = logDir.path() + "/"
							+ NumberFormatter::format(now.year()) + "-"
							+ NumberFormatter::format(now.month()) + "-"
							+ NumberFormatter::format(now.day()) + "-"
							+ NumberFormatter::format(now.hour()) + "-"
							+ NumberFormatter::format(now.minute()) + "-"
							+ NumberFormatter::format(now.second()) + ".log";

	//新建文件通道并设置属性
	AutoPtr<FileChannel> pChannel(new FileChannel);
	pChannel->setProperty("path", logFileName);

	//新建格式模板
	AutoPtr<PatternFormatter> pPF(new PatternFormatter);
	pPF->setProperty("pattern", "%H:%M:%S %P %I %l %t");

	//新建格式通道
	AutoPtr<FormattingChannel> pFC(new FormattingChannel(pPF, pChannel));

	//将格式通道设置为根日志器的通道
	Logger::root().setChannel(pFC);

	Logger &logger = Logger::get("PocoLogger");
	
	pLogStream_ = new LogStream(logger);
}

void PocoLogger::UnInit()
{
	delete pLogStream_;
}