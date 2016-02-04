///        Copyright 2016 libo. All rights reserved
///   (Home at https://github.com/NingLeixueR/middleware/)

#include "middleware/middleware_base/socket_io/lpthread.hpp"

#include <boost/function.hpp>

#include <vector>


#define DEFAULT_MAX_THREAD  (128)

namespace middleware {
  namespace tools{

    /**
     * �����߳�
     */
    class workthread:
      public pthread
    {

      boost_sem m_sem;
      boost::function<void(void)> m_fun;

      virtual int run();
    public:

      workthread():
        m_sem(0)
      {
      }

      void push( boost::function<void(void)>& aifun )
      {
        m_fun = aifun;
        m_sem.post();
      }
    };

    class threadpool
    {
      static std::vector<workthread*> m_thread_list;
      static boost::mutex m_lock;
      static uint32_t m_threadsize;
      static uint32_t m_max_thread;
      static boost_sem m_sem;

      friend class workthread;

      /* workthread �ع� */
      static void push( workthread* aipthread )
      {
        boost::mutex::scoped_lock llock(m_lock);
        m_thread_list.push_back( aipthread );
        m_sem.post();
      }

      static bool task_workthread(boost::function<void(void)>& aifun)
      {
        /* boost::mutex::scoped_lock llock(m_lock); */
        m_lock.lock();
        if( m_thread_list.empty() )
        {
          if( m_max_thread == 0 || m_threadsize < m_max_thread )
          {
            ++m_threadsize;
          }
          else
          {
            m_lock.unlock();
            return false;
          }
          m_lock.unlock();
          workthread* lp = new workthread();
          lp->push( aifun );
        }
        else
        {
          ( *m_thread_list.rbegin() )->push( aifun );
          m_thread_list.pop_back();
          m_lock.unlock();
        }

        return true;
      }
    public:
      /**
       * ���û�п����߳��ҳ��������Ŀ����,��������
       */
      static bool asyn_thread( boost::function<void(void)> aifun)
      {
        return threadpool::task_workthread( aifun );
      }


      /**
       * ���ʧ��������  �ȴ� ֱ���п��е��߳�
       */
      static void syn_thread( boost::function<void(void)> aifun)
      {
        while( !threadpool::task_workthread( aifun ) )
        {
          m_sem.wait();
        }

      }

      /**
       *  ��ȡ�߳���Ŀ
       */
      static uint32_t thread_size()
      {
        return m_threadsize;
      }

      /**
       *  ��������߳�
       */
      static void set_maxthread( uint32_t ainum )
      {
        boost::mutex::scoped_lock llock(m_lock);
        if( m_max_thread < ainum)
        {
          m_max_thread = ainum;
        }
      }

	  /** 
	   * ��ȡ����߳���
	   */
	  static uint32_t get_maxthread()
	  {
		  return m_max_thread;
	  }

    };

  }  //namespace tools
}  //namespace middleware

/* vim: set expandtab ts=2 sw=2 sts=2 tw=100: */
