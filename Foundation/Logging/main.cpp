#include "PocoLogger.h"

int main()
{
	TRACER
	//PocoLogger logger;
	LOGI << "hello world!" << std::endl;
	LOGN << "oiaefioaw" << std::endl;
	LOGW << "hioweo" << std::endl;
	LOGE << "lkdwoo " << std::endl;
	LOGC << "iwoeiaowe" << std::endl;
	LOGF << "weoioowie" << std::endl;
	return 0;
}