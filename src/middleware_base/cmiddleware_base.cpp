///        Copyright 2016 libo. All rights reserved
///   (Home at https://github.com/NingLeixueR/middleware/)

#include "middleware/middleware_base/cmiddleware_base.h"
#include "middleware/middleware_base/middleware_base.hpp"
#include "middleware/middleware_base/socket_asio/socket_asio_server_arg.hpp"

extern "C" {


void* init_middleware_sm_server(
	uint32_t aiconfigtype,
	const char* aiconfigpath,
	callbackfun logic_fun
  )
{
  return new middleware::middleware_sm_server(
		aiconfigtype, aiconfigpath, logic_fun
    );
}

void* init_middleware_sm_server2(
	uint32_t aiconfigtype,
	const char* apconfigtxt,
	uint32_t apconfigtxtlen,
	callbackfun logic_fun
	)
{
	return new middleware::middleware_sm_server(
		aiconfigtype, apconfigtxt, apconfigtxtlen, logic_fun
		);
}


void* init_middleware_sm_client(
	uint32_t aiconfigtype,
	const char* aiconfigpath,
	callbackfun logic_fun)
{
  return new middleware::middleware_sm_client(
		aiconfigtype, aiconfigpath, logic_fun
    );
}

void* init_middleware_sm_client2(
	int32_t aiconfigtype,
	const char* apconfigtxt,
	uint32_t apconfigtxtlen,
	callbackfun logic_fun)
{
	return new middleware::middleware_sm_client(
		aiconfigtype, apconfigtxt, apconfigtxtlen, logic_fun
		);
}



bool send_middleware(void* ap, char* apdata, uint32_t aiwlen)
{
  return static_cast<middleware::middleware_base*>(ap)->send( apdata, aiwlen );
}

bool close_middleware(void* ap)
{
  return static_cast<middleware::middleware_base*>(ap)->close( );
}



void* init_middleware_la_server(
	uint32_t aiconfigtype,
	const char* aiconfigpath,
	callbackfun logic_fun)
{
  return new middleware::middleware_la_server(
		aiconfigtype, aiconfigpath, logic_fun);
}

void* init_middleware_la_server2(
	uint32_t aiconfigtype,
	const char* apconfigtxt,
	uint32_t apconfigtxtlen,
	callbackfun logic_fun)
{
	return new middleware::middleware_la_server(
		aiconfigtype, apconfigtxt, apconfigtxtlen, logic_fun);
}

void* init_middleware_la_client(
	uint32_t aiconfigtype,
	const char* aiconfigpath,
	callbackfun logic_fun)
{
  return new middleware::middleware_la_client(
		aiconfigtype, aiconfigpath, logic_fun);
}

void* init_middleware_la_client2(
	uint32_t aiconfigtype,
	const char* apconfigtxt,
	uint32_t apconfigtxtlen,
	callbackfun logic_fun)
{
	return new middleware::middleware_la_client(
		aiconfigtype, apconfigtxt, apconfigtxtlen, logic_fun);
}




void* init_middleware_soio_server(
	uint32_t aiconfigtype,
	const char* aiconfigpath,
	multi_recv_fun logic_recv_callback,
	sendfailure_fun aisendfailure
	)
{
  return new middleware::middleware_soio_server(
		aiconfigtype, aiconfigpath, logic_recv_callback, aisendfailure);
}

void* init_middleware_soio_server2(
	uint32_t aiconfigtype,
	const char* apconfigtxt,
	uint32_t apconfigtxtlen,
	multi_recv_fun logic_recv_callback,
	sendfailure_fun aisendfailure
	)
{
	return new middleware::middleware_soio_server(
		aiconfigtype, apconfigtxt, apconfigtxtlen, logic_recv_callback, aisendfailure);
}

void* init_middleware_soio_client(
	uint32_t aiconfigtype,
	const char* aiconfigpath,
	multi_recv_fun logic_recv_callback
	)
{
  return new middleware::middleware_soio_client(
		aiconfigtype, aiconfigpath, logic_recv_callback);
}

void* init_middleware_soio_client(
	uint32_t aiconfigtype,
	const char* apconfigtxt,
	uint32_t apconfigtxtlen,
	multi_recv_fun logic_recv_callback
	)
{
	return new middleware::middleware_soio_client(
		aiconfigtype, apconfigtxt, apconfigtxtlen, logic_recv_callback);
}

bool create_connkey(
	void* ap,
	uint32_t aiconfigtype,
	const char* aiconfigpath,
	sendfailure_fun aisendfailure
	)
{
  return static_cast<middleware::middleware_soio_client*>(ap)->create_connkey(
		aiconfigtype, aiconfigpath, aisendfailure);
}

bool create_connkey2(
	void* ap,
	uint32_t aiconfigtype,
	const char* apconfigtxt,
	uint32_t apconfigtxtlen,
	sendfailure_fun aisendfailure
	)
{
	return static_cast<middleware::middleware_soio_client*>(ap)->create_connkey(
		aiconfigtype, apconfigtxt, apconfigtxtlen, aisendfailure);
}

bool create_connect(uint32_t aikey,
	void* ap,
	uint32_t aiconfigtype,
	const char* aiconfigpath,
	sendfailure_fun aisendfailure
	)
{
	return static_cast<middleware::middleware_soio_client*>(ap)->create_connect(
		aiconfigtype, aiconfigpath, aisendfailure);
}

bool create_connect2(uint32_t aikey,
	void* ap,
	uint32_t aiconfigtype,
	const char* apconfigtxt,
	uint32_t apconfigtxtlen,
	sendfailure_fun aisendfailure
	)
{
	return static_cast<middleware::middleware_soio_client*>(ap)->create_connect(
		aiconfigtype, apconfigtxt, apconfigtxtlen, aisendfailure);
}

bool send_middleware_soio(void* ap, uint32_t aikey, char* apdata, uint32_t aiwlen)
{
  return static_cast<middleware::socket_middleware_base*>(ap)->send(aikey, apdata, aiwlen);
}

bool close_middleware_soio(void* ap, uint32_t aikey)
{
  return static_cast<middleware::socket_middleware_base*>(ap)->close(aikey);
}


void* init_middleware_asio_server(
	casio_arg* aparg
	)
{
	std::vector<boost::function<bool(const char*, uint32_t)> > lrecv;
	lrecv.resize(aparg->m_threadmaxsize);
	for (uint32_t i = 0; i < aparg->m_threadmaxsize;++i)
	{
		lrecv[i] = aparg->m_callbackfun[i];
	}

	middleware::socket_asio_arg larg(aparg->m_threadmaxsize, lrecv);

	larg.m_timeout								= aparg->m_timeout;                                         /** �����޻�Ĵ��ʱ�� ��λ�� */
	larg.m_port										= aparg->m_port;                                            /** �˿ں� */
	larg.m_recvpack_maxsize				= aparg->m_recvpack_maxsize;                                /** ��󵥸�����С */
	larg.m_session_num						= aparg->m_session_num;                                     /** Ҳ������������� */
	larg.m_loopbuffermaxsize			= aparg->m_loopbuffermaxsize;                               /** �������黺���С */
	larg.m_everyoncemaxsize				= aparg->m_everyoncemaxsize;                                /** ������������С */
	larg.m_extern_loopbuffermaxsize	= aparg->m_extern_loopbuffermaxsize;                      /** �ش����ⲿ�м���Ļ������黺���С */
	larg.m_extern_everyoncemaxsize	= aparg->m_extern_everyoncemaxsize;                       /** �ش����ⲿ�м���ĵ�����������С */
	larg.m_activ									= aparg->m_activ;                                           /** �Ƿ����ұ�֤���ݻ��� */
	larg.m_extern_activ						= aparg->m_extern_activ;
	larg.m_persecond_recvdatatbyte_num = aparg->m_persecond_recvdatatbyte_num;                /** ÿ���ӽ��յ��ֽ��� */
	larg.m_s2s										= aparg->m_s2s;                                             /** ������������������ӶϿ��Ƿ�֪ͨ�ϲ�(�˴������������ֱ���:1.����,2.��Ⱥ�е�ĳ�������ڵ�(��1�е����־��ǲ���time out����)) */
	larg.m_s2c										= aparg->m_s2c;                                             /** ��������ͻ��˵����ӶϿ��Ƿ�֪ͨ�ϲ� */
	larg.m_heartbeat_num					= aparg->m_heartbeat_num;                                   /** ����Э���,�յ�������time outʱ�䣬Ȼ���� */

	return new middleware::middleware_asio_server(larg);
}



void test_thread( test_fun fun)
{
  boost::thread( boost::function<void()>(fun) );
}

void boost_sleep(uint32_t ainum)
{
  boost::this_thread::sleep(boost::posix_time::milliseconds(ainum));
}


}
/* vim: set expandtab ts=2 sw=2 sts=2 tw=100: */
