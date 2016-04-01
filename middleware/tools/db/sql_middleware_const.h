#ifndef SQL_MIDDLEWARE_CONST_H

#include <iostream>
#include <string>
#include <cstdint>
#include <list>
#include <map>

#if WIN32
# include<winsock2.h>
# define snprintf  sprintf_s
#endif //WIN32

#include <mysql.h>

struct connect_db_arg
{
	uint32_t		m_port;				/** �˿� */
	std::string		m_ip;				/** ip */
	std::string     m_account;			/** �˺� */
	std::string     m_passworld;		/** ���� */
	std::string     m_dbname;			/** ���ݿ����� */
};





#endif //SQL_MIDDLEWARE_CONST_H