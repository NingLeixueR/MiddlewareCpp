cmake_minimum_required(VERSION 2.6)

PROJECT (middleware)
SET(EXECUTABLE_OUTPUT_PATH "./bin") 
SET(LIBRARY_OUTPUT_PATH "./lib")
INCLUDE_DIRECTORIES(../)
ADD_DEFINITIONS(-DBOOST_ALL_NO_LIB)
ADD_DEFINITIONS(-DBOOST_HAS_WINTHREADS)
ADD_DEFINITIONS(-DBOOST_THREAD_BUILD_DLL)

AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../src/tools/logsys LOGSYS_SRC) 
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../src/tools/db SQL_MIDDLEWARE_SRC)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../src/tools/incidental READCONFIG_SRC)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../src/tools/serializecpp/public SERIALIZECPP_FUN_SRC)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../src/tools/serializecpp/public/endian SERIALIZECPP_FUN_ENDIAN_SRC)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../src/tools/threadpool THREADPOLL_SRC)

AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../src/middleware_base/socket_asio SOCKET_ASIO_SRC)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../src/middleware_base/socket_io SOCKET_IO_SRC)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../src/middleware_base/loop_array LOOPARRAY_SRC)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../src/middleware_base MIDDLEWARE_BASE_SRC)

AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../src/tools/compress_zlip COMPRESS_ZLIB_SRC)

set(MIDDLE_SRC ${LOGSYS_SRC} ${SQL_MIDDLEWARE_SRC} ${READCONFIG_SRC} ${SERIALIZECPP_FUN_SRC} ${SERIALIZECPP_FUN_ENDIAN_SRC} ${THREADPOLL_SRC} ${SOCKET_ASIO_SRC} ${SOCKET_IO_SRC} ${LOOPARRAY_SRC} ${MIDDLEWARE_BASE_SRC} ${COMPRESS_ZLIB_SRC})


#boost
INCLUDE_DIRECTORIES(../3part/boost/)
INCLUDE_DIRECTORIES(../3part/)
#LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../../3part/boost_lib1)
#LINK_DIRECTORIES(F:/git/3part/boost/lib)
#mysql
if(WIN32)
INCLUDE_DIRECTORIES(../3part/mysql/include/)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../3part/mysql/)
else()
FIND_EXTERBAL_LIB(Mysql mysql)
endif()

#zlib
INCLUDE_DIRECTORIES(../3part/zlib/include/)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../3part/zlib/)



#boost lib
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../3part/boost/libs/atomic/src boost_atomic_lib_src) 
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../3part/boost/libs/chrono/src boost_chrono_lib_src) 
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../3part/boost/libs/date_time/src/gregorian boost_date_time_lib_src1) 
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../3part/boost/libs/date_time/src/posix_time boost_date_time_lib_src2) 
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../3part/boost/libs/exception/src boost_exception_lib_src) 
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../3part/boost/libs/filesystem/src boost_filesystem_lib_src) 
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../3part/boost/libs/smart_ptr/src boost_smart_ptr_lib_src) 
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../3part/boost/libs/system/src boost_system_lib_src) 
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../3part/boost/libs/thread/src boost_thread_lib_src1)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/../3part/boost/libs/thread/src/win32 boost_thread_lib_src2)
set(BOOST_SRC ${boost_atomic_lib_src} ${boost_chrono_lib_src} ${boost_date_time_lib_src1} ${boost_date_time_lib_src2} ${boost_exception_lib_src} ${boost_filesystem_lib_src} ${boost_smart_ptr_lib_src} ${boost_system_lib_src} ${boost_thread_lib_src1}  ${boost_thread_lib_src2})
#set(BOOST_SRC ${boost_atomic_lib_src} ${boost_chrono_lib_src} ${boost_date_time_lib_src1} ${boost_date_time_lib_src2} ${boost_exception_lib_src} ${boost_filesystem_lib_src} ${boost_smart_ptr_lib_src} ${boost_system_lib_src} ${boost_thread_lib_src2})


#libmiddle
ADD_LIBRARY(middle STATIC ${BOOST_SRC} ${MIDDLE_SRC})
#ADD_LIBRARY(middle STATIC ${MIDDLE_SRC})

#libmiddle

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/Debug/)
SET(EXAMPLE_PATH ${PROJECT_SOURCE_DIR}/../example/)

ADD_EXECUTABLE(example_liblogsys ${EXAMPLE_PATH}/example_logsys.cpp)
TARGET_LINK_LIBRARIES(example_liblogsys middle)

ADD_EXECUTABLE(example_libsql_middleware ${EXAMPLE_PATH}/example_db.cpp)
TARGET_LINK_LIBRARIES(example_libsql_middleware middle libmysql clientlib)

ADD_EXECUTABLE(example_libreadconfig ${EXAMPLE_PATH}/example_logsys.cpp)
TARGET_LINK_LIBRARIES(example_libreadconfig middle)

ADD_EXECUTABLE(example_libserializecpp_fun ${EXAMPLE_PATH}/example_serializecpp.cpp)
TARGET_LINK_LIBRARIES(example_libserializecpp_fun middle)

ADD_EXECUTABLE(example_libthreadpool ${EXAMPLE_PATH}/example_threadpool.cpp)
TARGET_LINK_LIBRARIES(example_libthreadpool middle)

ADD_EXECUTABLE(example_compress_zlib ${EXAMPLE_PATH}/example_compress_zlib.cpp)
TARGET_LINK_LIBRARIES(example_compress_zlib middle)