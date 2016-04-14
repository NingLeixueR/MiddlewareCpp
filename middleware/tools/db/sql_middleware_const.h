#ifndef SQL_MIDDLEWARE_CONST_H
#define SQL_MIDDLEWARE_CONST_H

#include <iostream>
#include <string>
#include <cstdint>
#include <list>
#include <map>
#include <vector>

#if WIN32
# include<winsock2.h>
# define snprintf  sprintf_s
#endif //WIN32

#include <mysql.h>

namespace middleware{
	namespace tools{
		struct connect_db_arg
		{
			uint32_t		m_port;				/** �˿� */
			std::string		m_ip;				/** ip */
			std::string     m_account;			/** �˺� */
			std::string     m_passworld;		/** ���� */
			std::string     m_dbname;			/** ���ݿ����� */
		};


#ifdef _DEBUG
# define DBG_OUT(...)  \
	printf(__VA_ARGS__);
#else
# define DBG_OUT(...)
#endif //DEBUG



		/** ����ֶθ����ֶ� */
		enum ENUM_SQLFIELD
		{
			E_SQLID,			//ID
			E_SQLGROUPID,			//��id
			E_SQLBINARY,		//����������
			E_SQLTIME,			//������ʱ��
			E_FIELD_SIZE,		//�ֶε���Ŀ
		};


		/** ����ķ�ʽ */
		enum ENUM_SORT
		{
			E_SORT_MIN,
			E_SORT_MAX,
			E_SORT_RAND,
			E_SORT_SIZE,
		};

#define TAB_MIN_VALUES  (0x0)
#define TAB_MAX_VALUES  (0x7fffffff)

	} //namespace tools
} //namespace middleware

#endif //SQL_MIDDLEWARE_CONST_H