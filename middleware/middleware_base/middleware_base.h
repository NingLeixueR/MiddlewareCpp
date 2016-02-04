///        Copyright 2016 libo. All rights reserved
///   (Home at https://github.com/NingLeixueR/middleware/)


#include "middleware/middleware_base/shared_memory/mgt_shared_memory.hpp"
#include "middleware/middleware_base/loop_array/loop_array_middleware.hpp"
#include "middleware/middleware_base/socket_io/gateway_client.hpp"
#include "middleware/middleware_base/socket_io/gateway_server.hpp"

#include <cstdint>

namespace middleware {
	
	/**
	*  �м��
	*  �ù��캯��
	*  ����
	*  ѭ������,
	*  �����ڴ�,
	*  socket
	*/
	class middleware_base
	{
	public:
		virtual bool send(char* apdata, uint32_t aiwlen) = 0;
		virtual bool close() = 0;
	};
	
 /**
  *  �����ڴ�ͻ���
  */
  class middleware_sm_server :
		public middleware_base
	{
		communicate_module m_sms;
	public:
		middleware_sm_server(const char* aismname, uint64_t  ai_client_byte_sum, uint64_t ai_server_byte_sum, uint32_t aieveryonemaxsize, boost::function<bool(char*, uint32_t&)> logic_fun) :
			m_sms(aismname, ai_client_byte_sum, ai_server_byte_sum, aieveryonemaxsize, logic_fun, true)
		{}

		virtual bool send(char* apdata, uint32_t aiwlen)
		{
			memcpy(m_sms.wget_start(), apdata, aiwlen);
			m_sms.wget_finish(aiwlen);
			return true;
		}

		virtual bool close()
		{
			/** δʵ��*/
			return true;
		}
	};

  /**
   *  �����ڴ�ͻ���
   *  shared memory client
   */
  class middleware_sm_client :
    public middleware_base
  {
    communicate_module m_smc;
  public:
    middleware_sm_client(const char* aismname, uint64_t  ai_client_byte_sum, uint64_t ai_server_byte_sum, uint32_t aieveryonemaxsize, boost::function<bool(char*, uint32_t&)> logic_fun) :
      m_smc(aismname, ai_client_byte_sum, ai_server_byte_sum, aieveryonemaxsize, logic_fun, false)
    {
    }

    virtual bool send(char* apdata, uint32_t aiwlen)
    {
      memcpy(m_smc.wget_start(), apdata, aiwlen);
      m_smc.wget_finish(aiwlen);
      return true;
    }

    virtual bool close()
    {
      /** δʵ�� */
      return true;
    }
  };


  /**
   *  ѭ�����������
   */
  class middleware_la_server :
		public middleware_base
	{
		middleware_looparray m_las;
	public:
		middleware_la_server( const char* ainame,
			uint32_t apbuffersize,
			uint32_t aieverymaxsize,
			FUN_READ_CALLBACK aireadfun,
			bool apstartthread,
			bool apisclient) :
		m_las(ainame, apbuffersize, aieverymaxsize, aireadfun, apstartthread, apisclient)
		{}

		virtual bool send(char* apdata, uint32_t aiwlen)
		{
			 return m_las.send(apdata, aiwlen);
		}

		virtual bool close()
		{
			return m_las.close();
		}
	};

  /**
   *  ѭ������ͻ���
   */
  class middleware_la_client :
	  public middleware_base
  {
	  middleware_looparray m_las;
  public:
	  middleware_la_client( const char* ainame,
		  uint32_t apbuffersize,
		  uint32_t aieverymaxsize,
		  FUN_READ_CALLBACK aireadfun,
		  bool apstartthread,
		  bool apisclient) :
	  m_las(ainame, apbuffersize, aieverymaxsize, aireadfun, apstartthread, apisclient)
	  {}

	  virtual bool send(char* apdata, uint32_t aiwlen)
	  {
		  return m_las.send(apdata, aiwlen);
	  }

	  virtual bool close()
	  {
		  return m_las.close();
	  }
  };



	/**
	*  һ�Զ��м��
	*  ������ͨ��key��ͻ�����ϵ  
	*  �ù��캯��
	*  ����
	*  socket io
	*  socket asio
	*/
	class multi_middleware_base
	{
	public:
		virtual bool send(uint32_t aikey, char* apdata, uint32_t aiwlen) = 0;
		virtual bool close(uint32_t aikey) = 0;
	};


  /**
   *  socket io ������
   */
  class middleware_soio_server :
		public multi_middleware_base
	{
		gateway_socket_server_con m_asi;
	public:
		middleware_soio_server( uint32_t aiport,
			boost::function<bool(uint32_t, const char*, uint32_t)> logic_recv_callback,
			uint32_t aimaxsize,
			uint32_t aievery_once_max_size,
			boost::function<bool(const char*, uint32_t)> aisendfailure
			):
			m_asi(aiport, logic_recv_callback, aimaxsize, aievery_once_max_size, aisendfailure)
		{}

		virtual bool send(uint32_t aikey, char* apdata, uint32_t aiwlen)
		{
			 return m_asi.send( aikey, apdata, aiwlen);
		}

		virtual bool close(uint32_t aikey)
		{
			return m_asi.close( aikey);
		}
	};

  /**
   *  socket io �ͻ���
   */
  class middleware_soio_client :
	  public multi_middleware_base
  {
	  gateway_socket_client_con m_asi;
  public:
	  middleware_soio_client(  
		  boost::function<bool(uint32_t ,const char*, uint32_t)> logic_recv_callback,
		uint32_t aimaxsize,
      uint32_t aievery_once_max_size
	  ) :
	  m_asi(logic_recv_callback, aimaxsize, aievery_once_max_size)
	  {}

	  virtual bool send(uint32_t aikey, char* apdata, uint32_t aiwlen)
	  {
		  return m_asi.send(aikey, apdata, aiwlen);
	  }

	  virtual bool close(uint32_t aikey)
	  {
		  return m_asi.close(aikey);
	  }
  };

}

