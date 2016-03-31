#ifndef SQL_MIDDLEWARE_CONST_H

#include <iostream>
#include <string>
#include <cstdint>
#include <list>
#include <map>

#include <mysql.h>


#ifdef WIN32
#define snprintf  sprintf_s
#endif //WIN32


struct connect_db_arg
{
	uint32_t		m_port;				/** �˿� */
	std::string		m_ip;				/** ip */
	std::string     m_account;			/** �˺� */
	std::string     m_passworld;		/** ���� */
	std::string     m_dbname;			/** ���ݿ����� */
};





#endif //SQL_MIDDLEWARE_CONST_H