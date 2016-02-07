///        Copyright 2016 libo. All rights reserved
///   (Home at https://github.com/NingLeixueR/middleware/)

#include "middleware/middleware_base/cmiddleware_base.h"

#include <stdio.h>
#include <string.h>

bool callback_printf(const char* ap, uint32_t aplen)
{
	printf(ap);
	return 1;
};

void test_middleware_sm_server()
{
  void* lserver = init_middleware_sm_server( "kk", 1024, 1024, 128, callback_printf );
  uint32_t lnum = 900;
  char cbuf[128];
  uint32_t litemp;
  while (lnum)
  {
    litemp = sprintf(cbuf, "server2client %d", lnum--);
    send_middleware_sm( lserver, cbuf, litemp + 1);
  }
}


void test_middleware_sm_client()
{
  void* lclient = init_middleware_sm_client("kk", 1024, 1024, 128, callback_printf);
  uint32_t lnum = 0;
  char cbuf[128];
  uint32_t litemp;
  while (lnum != 900)
  {
    litemp = sprintf(cbuf, "client2server %d", lnum++);
     send_middleware_sm( lclient, cbuf, litemp + 1);
  }
}

void test_middleware_la_server()
{
	void* lclient = init_middleware_la_server("kk", 1024, 128, callback_printf, false, true);
	uint32_t lnum = 10000;
	char cbuf[128];
	uint32_t litemp;
	while (lnum != 0)
	{
		litemp = sprintf(cbuf, "client2server %d", lnum--);
		send_middleware_la(lclient,cbuf, litemp + 1);
	}
}
void test_middleware_la_client()
{
	void* lclient = init_middleware_la_client("kk", 1024, 1024, callback_printf, false, false);

	uint32_t lnum = 0;
	char cbuf[128];
	uint32_t litemp;
	while (lnum != 900)
	{
		litemp = sprintf(cbuf, "client2server %d", lnum++);
		send_middleware_la(lclient,cbuf, litemp + 1);
	}
}



/** recv call back */
bool rcb(uint32_t aikey, const char* ap, uint32_t aplen)
{
	printf(ap);
	return true;
};

/** send failure call back*/
bool sfcb(const char* ap, uint32_t aplen)
{
	printf( "send err" );
	aplen = 0;
	return true;
};

void test_middleware_soio_server()
{

	void* lserver = init_middleware_soio_server(13140, rcb, 10240, 1024, sfcb);
	while (1)
	{
		send_middleware_soio_server( lserver, 0, "helloworld",sizeof("helloworld") );
	}
	return;
}


void test_middleware_soio_client(uint32_t aikey)
{
	void* lclient = init_middleware_soio_client(rcb, 10240, 1024);
	create_connect_client( lclient,aikey,"127.0.0.1", 13140, sfcb);
	while (1)
	{
		send_middleware_soio_server( lclient, 0, "very much.",sizeof("very much.") );
	}
	return;
}

int main(int argc, char *argv[])
{
	if (argc >= 3)
	{
		printf( argv[1]);
		printf( "\n" );
		printf( argv[2]);
		printf("\n%d",memcmp(argv[1], "-soio", sizeof("-soio")-1));
		if (memcmp(argv[1], "-sm", sizeof("-sm")-1) == 0)/** 共享内存测试 */
		{
			if (memcmp(argv[2], "-c", sizeof("-c")-1) == 0)
			{
				test_middleware_sm_client();
			}
			else if (memcmp(argv[2], "-s", sizeof("-s")-1) == 0)
			{
				test_middleware_sm_server();
			}
		}
		else if (memcmp(argv[1], "-la", sizeof("-la")-1) == 0)
		{
			test_thread(test_middleware_la_server);
			test_thread(test_middleware_la_client);
		}
		else if (memcmp(argv[1], "-soio", sizeof("-soio")-1) == 0)
		{
			if (memcmp(argv[2], "-c", sizeof("-c")-1) == 0)
			{
				int lkey;
				scanf( &( argv[2][sizeof("-c")]),"%d",&lkey);
				test_middleware_soio_client( lkey);
			}
			else if (memcmp(argv[2], "-s", sizeof("-s")-1) == 0)
			{
				test_middleware_soio_server();
			}
		}
		else
		{
			goto PRINT_MESSAGE;
		}
		getchar();
		return 0;

	}

PRINT_MESSAGE:
	printf(  "/** \n" );
	printf(  " *  THIS.EXE -TYPE  -CLIENT OR SERVER \n" );
	printf(  " *  -TYPE      sm   共享内存\n" );
	printf(  " *             la   循环数组\n" );
	printf(  " *\n" );
	printf(  " *\n" );
	printf(  " *  -CLIENT OR SERVER\n" );
	printf(  "example:\n" );
	printf(  " *          THIS.EXE -sm -c \n" );
	printf(  " *\n" );
	printf(  " */\n" );

	return 0;
}



 /* vim: set expandtab ts=2 sw=2 sts=2 tw=100: */