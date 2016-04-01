#ifndef SQL_MIDDLEWARE_H

#include "sql_middleware_const.h"

template <uint32_t BINART_SIZE>
struct SLECT_BINARY_DATA
{
	uint32_t m_id;
	char m_binarydata[BINART_SIZE];
	uint32_t m_update_time;
};


class sql_middleware
{
	
public:
	typedef uint32_t dbtype_u32_key;
	typedef std::map<dbtype_u32_key,MYSQL> dbtype_map_mysql;
	
	static MYSQL* key2db(dbtype_u32_key akey);
	
	static bool create_connect(dbtype_u32_key akey, std::string aitabname ,connect_db_arg& aicarg);


	/** ���� */
	bool insert(dbtype_u32_key akey, std::string aitabname,uint32_t aid, char* aibinary,uint32_t aisize);
	/** ��ѯ*/
	bool select(dbtype_u32_key akey, std::string aitabname,uint32_t aid, char* aibinary,uint32_t& aisize);
	
	template <uint32_t BINART_SIZE>
	bool select_id(
		dbtype_u32_key akey, 
		std::string aitabname,  
		vector<SLECT_BINARY_DATA<BINART_SIZE>>& aivec,
		uint32_t aigetsize,
		uint32_t order
		);

	template <uint32_t BINART_SIZE>
	bool select_update_time(
		dbtype_u32_key akey, 
		std::string aitabname,  
		vector<SLECT_BINARY_DATA<BINART_SIZE>>& aivec,
		uint32_t aigetsize,
		uint32_t order
		);

	/** ������ݿ��Ƿ����,���������Դ��� */
	static bool check_db(MYSQL *mysql,const char *db_name); 
	/** ������ݱ��Ƿ����,���������Դ��� */
	static bool check_tab(MYSQL* mysql,const char *tabname);  
private:
	static dbtype_map_mysql m_sql;

};






#endif //SQL_MIDDLEWARE_H