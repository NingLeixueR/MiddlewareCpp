#ifndef SQL_MIDDLEWARE_H

#include "sql_middleware_const.h"



/** ����ʽ */
extern char* g_field_sort[E_SORT_SIZE];
/** tab�ֶ� */
extern char* g_field[E_FIELD_SIZE];

template <typename T_BINARY>
struct SLECT_BINARY_DATA
{
	uint32_t m_id;
	time_t m_update_time;
	T_BINARY m_binarydata;
};




class sql_middleware
{
	
public:
	typedef uint32_t dbtype_u32_key;
	typedef std::map<dbtype_u32_key,MYSQL> dbtype_map_mysql;
private:
	bool _select(
		dbtype_u32_key akey,			//key
		std::string& aitabname,			//tabname
		uint32_t aid,					//sqlid
		MYSQL_ROW& aibinary,			//binary data
		uint32_t& aisize			//T_BINARY��ָ�������С
		);

	bool _insert(dbtype_u32_key akey, std::string aitabname,uint32_t aid, void* aibinary,uint32_t aisize);
public:
	static MYSQL* key2db(dbtype_u32_key akey);
	
	static bool create_connect(dbtype_u32_key akey, std::string aitabname ,connect_db_arg& aicarg);


	/** ���� */
	//template <typedef T_BINARY>
	template <typename T_BINARY>
	bool insert(dbtype_u32_key akey, std::string aitabname,uint32_t aid, std::vector<T_BINARY>& aibinary)
	{
		return _insert( akey, aitabname, aid, aibinary.data(), aibinary.size()*sizeof(T_BINARY));
	}
	
	template <typename T_BINARY>
	bool insert(dbtype_u32_key akey, std::string aitabname,uint32_t aid, T_BINARY* aibinary, uint32_t aisize)
	{
		return _insert( akey, aitabname, aid, aibinary, aisize*sizeof(T_BINARY));
	}

	/** ��ѯ */
	template <typename T_BINARY>
	bool select(
		dbtype_u32_key akey,			//key
		std::string& aitabname,			//tabname
		uint32_t aid,					//sqlid
		SLECT_BINARY_DATA<T_BINARY>& aibinary,			//binary data
		uint32_t& aisize					//T_BINARY��ָ�������С
		)
	{
		MYSQL_ROW lvoid;
		if( _select(akey,aitabname,aid,lvoid,aisize) )
		{
			uint32_t lsize = (aisize >= sizeof(T_BINARY) ? sizeof(T_BINARY) : aisize);
			DBG_OUT("select [%s,%s]\n",lvoid[E_SQLID],lvoid[E_SQLTIME]);
			aibinary.m_id = aid;
			aibinary.m_update_time = atoi(lvoid[E_SQLTIME]);
			memset(&aibinary.m_binarydata, 0x0, sizeof(T_BINARY));
			memcpy( &aibinary.m_binarydata, lvoid[E_SQLBINARY], lsize);
			
			return true;
		}
		else
		{
			DBG_OUT("SQL FAIL = [_select() == false]\n");
			return false;
		}
		
		
		
		return true;
	}

	bool _select(
		dbtype_u32_key akey,			//key
		std::string aitabname,			//tabname
		ENUM_SQLFIELD aiwhere,			//���ĸ��ֶ���Ϊ��������
		ENUM_SORT aisort,				//����ʽ
		uint32_t aisize,				//ѡȡ��Ŀ��
		std::vector<MYSQL_ROW>& aidata,
		std::vector<uint32_t>& aibinarybytes
		);
	/** ����������ѯ */
	template <typename T_BINARY>
	bool select(
		dbtype_u32_key akey,			//key
		std::string aitabname,			//tabname
		ENUM_SQLFIELD aiwhere,			//���ĸ��ֶ���Ϊ��������
		ENUM_SORT aisort,				//����ʽ
		uint32_t aisize,				//ѡȡ��Ŀ��
		std::vector<SLECT_BINARY_DATA<T_BINARY> >& aibinary	//binary data ָ��
		)
	{
		std::vector<MYSQL_ROW>& aidata;
		std::vector<uint32_t>& aibinarybytes;
		_select(akey,aitabname,aiwhere,aisort,aisize,aidata,aibinarybytes);
		uint32_t lsize = aidata.size();
		aibinary.resize(lsize);
		uint32_t lbinarysize = 0;
		for (uint32_t i = 0;i<lsize;++i)
		{
			aibinary[i].m_id = atoi(aidata[E_SQLID]);
			aibinary[i].m_update_time = atoi(aidata[E_SQLTIME]);
			lbinarysize = (aibinarybytes[i] >= sizeof(T_BINARY) ? sizeof(T_BINARY) : aisize);
			memcpy( &aibinary[i].m_binarydata, aidata[E_SQLBINARY],lbinarysize);
		}
		return true;
	}

	/** ������ݿ��Ƿ����,���������Դ��� */
	static bool check_db(MYSQL *mysql,const char *db_name); 
	/** ������ݱ��Ƿ����,���������Դ��� */
	static bool check_tab(MYSQL* mysql,const char *tabname);  
private:
	static dbtype_map_mysql m_sql;

};









#endif //SQL_MIDDLEWARE_H