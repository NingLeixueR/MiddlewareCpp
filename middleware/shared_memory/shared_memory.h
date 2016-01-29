///        Copyright 2016 libo. All rights reserved
///   (Home at https://github.com/NingLeixueR/middleware/)

#ifndef GETEWAY_SHARED_MEMORY_H
#define GETEWAY_SHARED_MEMORY_H


#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include <cstring>
#include <iostream>

using boost::interprocess::shared_memory_object;
using boost::interprocess::mapped_region;
using boost::interprocess::interprocess_exception;
using boost::interprocess::create_only;
using boost::interprocess::read_write;
using boost::interprocess::read_only;
using boost::interprocess::open_only;

namespace middleware {
  
  /* �����ڴ�ͷ */
  struct shared_memory_head;

  /**
   **  ���������ڴ�
   **/
  class gateway_shared_memory
  {
    shared_memory_object* mp_smobj;
    mapped_region* mp_mmap;
  public:
#if 0
    gateway_shared_memory(const char* aismname, uint64_t aibufsize)
    {
      shared_memory_object::remove(aismname);
      mp_smobj = new shared_memory_object(create_only, aismname, read_write);
      mp_smobj->truncate(aibufsize);
      mp_mmap = new mapped_region(*mp_smobj, read_write);
    }
#endif
    gateway_shared_memory() :
      mp_smobj(nullptr),
      mp_mmap(nullptr)
    {}

    ~gateway_shared_memory()
    {
      delete mp_mmap;
      mp_mmap = nullptr;
      delete mp_smobj;
      mp_smobj = nullptr;
    }

	/*
	 *   ���������ڴ�ͷ 
	 */
    void create_shared_memort_head(const char* aismname, uint64_t aibufsize)
    {
      shared_memory_object::remove(aismname);
      mp_smobj = new shared_memory_object(create_only, aismname, read_write);
      mp_smobj->truncate(aibufsize);
      mp_mmap = new mapped_region(*mp_smobj, read_write);
    }

	/*
	 *  �򿪹����ڴ�ͷ
	 */
    bool open_shared_memort_head(const char* aismname)
    {
      try
      {
        mp_smobj = new shared_memory_object(open_only, aismname, read_write);
        mp_mmap = new mapped_region(*mp_smobj, read_write);
        return true;
      }
      catch (interprocess_exception& e)
      {
        std::cout << e.what() << std::endl;
        return false;
      }
    }
#if 0
    gateway_shared_memory(const char* aismname)
    {
      try
      {
        mp_smobj = new shared_memory_object(open_only, aismname, read_write);
        mp_mmap = new mapped_region(*mp_smobj, read_write);
      }
      catch (interprocess_exception& e)
      {
        std::cout << e.what() << std::endl;
      }
    }
#endif //0

	/*
	 *  ��ȡ��ַ
	 */
    void* address()
    {
      return  mp_mmap->get_address();
    }

	/*
	 *  ��ȡ�ֽ���
	 */
    std::size_t size()
    {
      return  mp_mmap->get_size();
    }

  };

}

#endif
