///        Copyright 2016 libo. All rights reserved
///   (Home at https://github.com/NingLeixueR/middleware/)

#ifndef LOG_DEF_H
#define LOG_DEF_H


namespace middleware {

	/** ����ģ��洢id��ȫ�ֱ��� */
	extern int g_log_socked_io_id;

}//namespace middleware 


/** Ϊÿ��ʹ��logsysģ��Ķ���һ���� */
/** socket ioģ�� */
#define LOG_SOCKET_IO_ID   ( g_log_socked_io_id )
#define LOG_SOCKET_IO_STR  ( "socket_io"  )




#endif //LOG_DEF_H