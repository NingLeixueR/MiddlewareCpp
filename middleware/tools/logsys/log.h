///        Copyright 2016 libo. All rights reserved
///   (Home at https://github.com/NingLeixueR/middleware/)

#ifndef LOG_HPP
#define LOG_HPP

#define FLUSH_TIME            (5)       /** ������ļ�ˢһ������ */
#define LOG_LEVE_WARN         (0)         /** ���� */
#define LOG_LEVE_INFO         (1)         /** ��� */
#define LOG_LEVE_ERROR        (2)         /** ���� */
#define LOG_LEVE_WARN_STR     "WARN"      /** ���� */
#define LOG_LEVE_INFO_STR     "INFO"      /** ��� */
#define LOG_LEVE_ERROR_STR    "ERROR"     /** ���� */

#ifndef __cplusplus
#define true   (1)
#define false  (0)
#endif
#define OPEN_LOGFILE_PRINTF       (true)         /** �Ƿ��ı���� */
#define OPEN_CONSOLE_PRINTF       (true)         /** �Ƿ�򿪿���̨���,����߳�������ܻ���,��Ϊ */
#define OPEN_LOG_ERROR            (1)            /** �Ƿ�ʼ��־Ϊ����Ĵ�ӡ */
#define OPEN_LOG_INFO             (0)            /** �Ƿ�����־Ϊ��ͨ�����Ϣ�Ĵ�ӡ */
#define OPEN_LOG_WARN             (1)            /** �Ƿ�����־Ϊ����Ĵ�ӡ */
#define CHECK_PRINTF_LOG( OPEN_LOG_TYPE )      ( ( OPEN_LOGFILE_PRINTF || OPEN_CONSOLE_PRINTF ) && OPEN_LOG_TYPE ) /** ����Ƿ��ӡ */

#define DEFAULT_SAVE_LOG_TIME           (12*60*60*60)  /** 12 hour */

#define LOG_SYS_BUFFER_SIZE             (2048)
#define LOG_SYS_EVERY_MAX_BUFFER_SIZE   (256)

#ifdef _MSC_VER
# ifndef snprintf
#  define snprintf _snprintf
# endif //snprintf
#endif //_MSC_VER

#ifdef __cplusplus
# define LOG_PRINTF( LOG_LEVEL, LOG_ID, LOG_NAME, FORMAT, ...)           \
	{                                                                      \
		char lch[256];                                                       \
		if( snprintf( lch, 256, FORMAT, __VA_ARGS__) > 0 )                   \
		{                                                                    \
			middleware::tools::WLOG( LOG_LEVEL, LOG_ID, LOG_NAME, lch);        \
		}                                                                    \
	}
#else
# define LOG_PRINTF( LOG_LEVEL, LOG_ID, LOG_NAME, FORMAT, ...)           \
	{                                                                      \
		char lch[256];                                                       \
		if( snprintf( lch, 256, FORMAT, __VA_ARGS__) > 0 )                   \
		{                                                                    \
			WLOG( LOG_LEVEL, &LOG_ID, LOG_NAME, lch);													 \
		}                                                                    \
	}
#endif //__cplusplus



/**
* ����һ����־�ļ�
*/
#ifdef __cplusplus
# define CREATE_LOG( LOG_ID, LOG_NAME )    middleware::tools::CLOG(LOG_ID,LOG_NAME);
#else
# define CREATE_LOG( LOG_ID, LOG_NAME )    CLOG(&LOG_ID,LOG_NAME);
#endif //__cplusplus
/**
*  ��ӡһ����־
*/
#define LOG_ERROR( LOG_ID, FORMAT, ...)  if(CHECK_PRINTF_LOG(LOG_LEVE_ERROR)) {LOG_PRINTF( LOG_LEVE_ERROR, LOG_ID, "", FORMAT, __VA_ARGS__)}
#define LOG_INFO( LOG_ID, FORMAT, ...)   if(CHECK_PRINTF_LOG(LOG_LEVE_INFO)) {LOG_PRINTF( LOG_LEVE_INFO, LOG_ID, "", FORMAT, __VA_ARGS__)}
#define LOG_WARN( LOG_ID, FORMAT, ...)   if(CHECK_PRINTF_LOG(LOG_LEVE_WARN)) {LOG_PRINTF( LOG_LEVE_WARN, LOG_ID, "", FORMAT, __VA_ARGS__)}


#ifdef __cplusplus
#define LOG_PLUSH( LOG_ID )    middleware::tools::WPLUSH(LOG_ID);
#else
#define LOG_PLUSH( LOG_ID )    WPLUSH(LOG_ID);
#endif //__cplusplus

#endif //LOG_HPP
