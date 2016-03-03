#ifndef LOG_SYS_H
#define LOG_SYS_H

#include "middleware/tools/logsys/log.h"
#include "OtherLanguages/c/logsys/logdef.h"

#include <inttypes.h>


#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus
	/**
	*  ������־
	*/
	uint32_t CLOG(int* LOG_ID, const char* LOG_NAME);

	/**
	*  д��־
	*/
	uint32_t WLOG(uint32_t LOG_LEVEL, int* LOG_ID, const char* LOG_NAME, const char* ap);

	/**
	*  ����־ˢ������
	*/
	uint32_t WPLUSH(int LOG_ID);
#ifdef __cplusplus
}
#endif //__cplusplus


#endif //LOG_SYS_H
