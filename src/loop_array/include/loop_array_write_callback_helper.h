#ifndef LOOP_ARRAY_WRITE_CALLBACK_HELPER_H
#define LOOP_ARRAY_WRITE_CALLBACK_HELPER_H

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <interprocess/sync/interprocess_semaphore.hpp>
#include <thread.hpp>
#include <function.hpp>
typedef boost::interprocess::interprocess_semaphore boost_sem;

#define _DLL_SAMPLE
#ifdef _DLL_SAMPLE
#define DLL_SAMPLE_API __declspec(dllexport)
#else
#define DLL_SAMPLE_API __declspec(dllimport)
#endif


#define DEFAULT_BUFFER_SIZE   10240

/*
new_loop_array
�������
�Ƿ�������õ���new_loop_array���߳�  ���Ǽ������� �����ᴴ�������߳� write��read ���� ����ֻ����һ�� ��һ�����õ����߳̽���
aiwritefun  д�ص�
aireadfun	���ص�
apbuffersize ָ��������buffer�ĳ���
aieverymaxsize ����������󳤶�,����ĵ���ָ����
�������ݰ��� bodysize �� body  write����һ��д�����������ĵ�������,��������д�벻�����ĵ�������
ֻ��Ҫ�´μ���д��ʱ��֤˳�򼴿�
*/

class loop_array;


/* д�ص� */
typedef boost::function<bool(char*, uint32_t&)> FUN_WRITE_CALLBACK;

/* ���ص� */
typedef boost::function<bool(const char*, uint32_t)>   FUN_READ_CALLBACK;

DLL_SAMPLE_API loop_array* new_loop_array(uint32_t apbuffersize, uint32_t aieverymaxsize, FUN_READ_CALLBACK aireadfun, FUN_WRITE_CALLBACK aiwritefun);

DLL_SAMPLE_API loop_array* new_loop_array(char* aibuffer, uint32_t apbuffersize, uint32_t aieverymaxsize, FUN_READ_CALLBACK aireadfun, FUN_WRITE_CALLBACK aiwritefun);


DLL_SAMPLE_API void start_run(loop_array*, bool aibool);

DLL_SAMPLE_API void delete_loop_array(loop_array* ap);

/* ���� */
//DLL_SAMPLE_API loop_array* new_loop_array( bool aibool , uint32_t apbuffersize, uint32_t aieverymaxsize , FUN_READ_CALLBACK aireadfun  );

DLL_SAMPLE_API char* loop_write_start(uint32_t& ailen);

DLL_SAMPLE_API void write_finish(uint32_t ailen);


/* ����looparray write call back  */
/* ����push_write_once
�����ָ���ǲ����ٵڶ��γɹ�����ǰ�޸������ݵ�
��Ϊ��ֻ�����Ǳ�����ָ��  �����Ŀ��������߳�����е�*/

class loop_array_write_callback_helper
{
	/* send_run_fun ����˽�б���*/
	bool write_once____the_first;
	uint32_t write_once____ltemp;
	uint32_t write_once____ltemp2;
	uint16_t write_once____lsize;
	bool write_once____is_push_head_size;

	boost_sem m_ready_sem1;
	boost_sem m_ready_sem2;
	char* sendbuffer;
	uint16_t sendbuffersize;
	boost::mutex  m_mutex;

public:
	loop_array_write_callback_helper() :
		m_ready_sem1(0),
		m_ready_sem2(0),
		sendbuffer(NULL),
		sendbuffersize(0),
		write_once____the_first(true)
	{}



	bool write_once(char* ap, uint32_t& aplen)
	{
		while (sendbuffer == NULL || sendbuffersize == 0)
		{
			m_ready_sem1.wait();
		}

		if (write_once____the_first)
		{
			write_once____ltemp = sizeof(uint16_t);
			write_once____ltemp2 = 0;
			write_once____lsize = sendbuffersize;
			write_once____is_push_head_size = true;
			write_once____the_first = false;
		}

		if (write_once____is_push_head_size)
		{
			if (aplen < write_once____ltemp)
			{
				/* δд��size */
				ap[0] = ((char*)(&write_once____lsize))[write_once____ltemp2];
				++write_once____ltemp2;
				if (write_once____ltemp == sizeof(uint16_t))
				{
					--write_once____ltemp;
					return true;
				}
				else
				{
					write_once____ltemp = 1;
					write_once____is_push_head_size = false;
					ap += write_once____ltemp;
				}

			}
			else
			{
				if (write_once____ltemp == 1)
				{
					ap[0] = ((char*)(&write_once____lsize))[1];
					write_once____ltemp = 1;
				}
				else
				{
					*((uint16_t*)(ap)) = write_once____lsize;
					write_once____ltemp = 2;
				}
				write_once____is_push_head_size = false;
				ap += write_once____ltemp;
			}

		}



		if (sendbuffersize > (aplen - write_once____ltemp))
		{

			memcpy(ap, (sendbuffer), (aplen - write_once____ltemp));
			/* ���� */
			sendbuffersize -= (aplen - write_once____ltemp);
			sendbuffer += (aplen - write_once____ltemp);
			write_once____ltemp = 0;
		}
		else
		{
			memcpy(ap, sendbuffer, sendbuffersize);
			aplen = sendbuffersize + write_once____ltemp;
			write_once____the_first = true;
			sendbuffer = NULL;
			sendbuffersize = 0;
			m_ready_sem2.post();
		}

		return true;

	}


	/* ���Ա����̵߳��� */
	bool push_write_once(char* ap, uint32_t aplen)
	{

		boost::mutex::scoped_lock llock(m_mutex);
		while (1)
		{
			if (sendbuffer == NULL && sendbuffersize == 0)
			{
				sendbuffer = ap;
				sendbuffersize = aplen;
				m_ready_sem1.post();
				return true;
			}
			else
			{
				m_ready_sem2.wait();
			}
		}
	}



};


#endif //LOOP_ARRAY_WRITE_CALLBACK_HELPER_H