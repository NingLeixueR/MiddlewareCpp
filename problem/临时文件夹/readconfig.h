#ifndef READ_CONFIG_H
#define READ_CONFIG_H

#include <cstdint>
#include <unordered_map>
#include <map>
#include <fstream>
#include <function.hpp>
#include "ethrow_num.h"
#include "lpthread.h"


/*
	��ȡcsv�ļ�
*/


#define CSV_SEGMENTATION_CHAR			( ',' )				/* csv�ָ��ַ� */


class table
{
	uint32_t milen;
	uint32_t mikey;
	std::vector<char*> modata_vec;
	static char m_segmentation;

	bool copy_to_vec(char* aiData , uint32_t aiitemsize )
	{
		modata_vec.push_back(aiData);
		sscanf( aiData , "%d" , &mikey );
		milen = strlen(aiData);
		for(uint32_t i = 0;i<milen;i++)
		{
			if (aiData[i] == m_segmentation)
			{
				aiData[i] = '\0';
				modata_vec.push_back(&(aiData[i+1]));
				--aiitemsize;
			}
		}

		if( aiitemsize != 0 )
		{
			modata_vec.clear();
			return false;
		}
		else
		{
			return true;
		}
	}

public:
	table()
	{
	}

	table(int aikey):mikey(aikey)
	{

	}

	void set_segmentation( const char aisegm )
	{
		m_segmentation = aisegm;
	}

	uint32_t set_data(char* aiData , uint32_t aiitemsize)
	{
		if( NULL != aiData)
		{
			if( copy_to_vec(aiData , aiitemsize) )
			{
				return mikey ;	
			}
			else
			{
				return (uint32_t)(-1);
			}
		}
		else
		{
			throw THROW__DATA_NULL;
		}
	}

	const char* operator[](unsigned int arr) const
	{
		if(arr < modata_vec.size() && arr >= 0)
		{
			return modata_vec[arr];
		}
		else
		{
			return NULL;
		}
	}

	bool operator<(const table& r)const 
	{
		return mikey < r.mikey;
	}

	bool operator==(const table& r)const 
	{
		return mikey == r.mikey;
	}

	void clear()
	{
		modata_vec.clear();
		milen = 0;
		mikey = 0;
	}

	~table(){};
};


/*
	csv��ʽ
	ǰ���б��� ϵͳʹ��   ��������
	һ.��һ��ָ��һϵ��������Ϣ   
		1.��һ���� csv�����õķָ����  Ĭ��ʹ��','  �ָ���Ų��ܳ�����������
	��.�ڶ��� �������ݱ�ʾ�ĺ��� 
*/
class tabkey_config;

typedef std::unordered_map< uint32_t , table* > ump_tabkey;
typedef std::unordered_map< uint32_t , tabkey_config* > ump_fkey;

#define TAB_ITEM_SIZE  2  /* �������������ָ��� */
class tabkey_config
{
	void open_file(const char* aifilename)
	{
		m_readfile.open(aifilename);
		if(!m_readfile.is_open())
		{
			m_readfile.close();
			throw THROW__OPENFILE_ERR;
		}
	}
	void close_file()
	{
		m_readfile.close();
	}

	void read_file()
	{
		//��ȡ�ļ���С 
		m_readfile.seekg(0,std::ios::end);
		size_t lisize = (size_t)(m_readfile.tellg());
		m_readfile.seekg(std::ios::beg);
		char* lcbuf = new char[lisize+1];
		m_p = lcbuf;
		memset(lcbuf,0x0,lisize);
		
		m_readfile.read(lcbuf,lisize);
		lcbuf[lisize] = '\n';

		table* litab = NULL;
		char* p = lcbuf;
		uint32_t temp_key = 0;
		bool lbo = false;
		for(size_t i = 0; i <= lisize;++i)
		{
			if( lcbuf[i] == '\n' || i == lisize)
			{
				lcbuf[i] = 0;

				

				
				/*if( i == lisize )
				{
				break;
				}*/
				if( *p == 0 )//���˿���
				{
					p = &(lcbuf[i+1]);
					continue;
				}


				if( !lbo )/* ���˱�ͷ */
				{
					lbo = true;
					p = &(lcbuf[i+1]);
					continue;
				}




				if( litab == NULL )
				{
					litab = new table();
				}


				temp_key = litab->set_data( p , TAB_ITEM_SIZE );
				if( temp_key == (uint32_t)(-1) )
				{
					p = &(lcbuf[i+1]);
					continue;
				}
				else
				{
					m_tabkey.insert( std::make_pair( temp_key ,litab ) );
					litab = NULL;
				}



				p = &(lcbuf[i+1]);

			}
		}

		if( litab != NULL )
		{
			delete litab;
		}



	}
	ump_tabkey m_tabkey;
	static std::ifstream m_readfile;
	static boost::mutex m_lock;
	char* m_p;
public:
	tabkey_config( const char* apfkey ):
		m_p(NULL)
	{
		m_lock.lock();
		try
		{
			open_file( apfkey );
			read_file();
			m_readfile.close();
		}
		catch(...)
		{
			std::cout<< " tabkey_config(const char*) error " << std::endl;
		}
		

		m_lock.unlock();
	}


	table& operator[]( uint32_t aikey )
	{
		auto itor = m_tabkey.find( aikey );
		if( itor != m_tabkey.end() )
		{
			return *( itor->second );
		}
		else
		{
			throw THROW__NOT_FIND_KEY;
		}
	}


	void for_each( boost::function< void(std::pair< const uint32_t , table* >) > aifun )
	{
		for( auto itor = m_tabkey.begin() ; itor != m_tabkey.end() ; ++itor )
		{
			aifun(*itor);
		}
	}
	~tabkey_config()
	{
		if( m_p == NULL )
		{
			delete m_p;
		}
		
		for (auto itor = m_tabkey.begin(); itor != m_tabkey.end() ; ++itor )
		{
			delete itor->second;
		}

		m_tabkey.clear();
	}
};


class fkey_config
{
	
	
	ump_fkey m_fkey;
public:


	/* 
		ͨ��apfkey ��ȡ�����ļ���  ����uint32_t key
	*/
	void push( const char* apfile , uint32_t aikey )
	{
		auto itor = m_fkey.find( aikey );
		if( itor != m_fkey.end() )
		{
			return ;
		}
		
		tabkey_config* p = new tabkey_config( apfile );
		m_fkey.insert( std::make_pair( aikey , p )  );
		return ;
	}




	tabkey_config& operator []( uint32_t afkey )
	{
		auto itor = m_fkey.find( afkey );
		if( itor != m_fkey.end() )
		{
			return *( itor->second );
		}
		else
		{
			throw THROW__NOT_FIND_KEY;
		}
	}

	void for_each( boost::function< void(std::pair< const uint32_t , tabkey_config* >) > aifun )
	{
		for( auto itor = m_fkey.begin() ; itor != m_fkey.end() ; ++itor )
		{
			aifun(*itor);
		}
	}

};





#endif