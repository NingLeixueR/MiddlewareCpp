///        Copyright 2016 libo. All rights reserved
///   (Home at https://github.com/NingLeixueR/middleware/)

#ifndef READCONFIG_KEY_VALUES
#define READCONFIG_KEY_VALUES

namespace middleware {
	namespace tools {

		/* csv �ļ���Ӧkey */
		enum CONFIG_KEY
		{
			E_TEST_CONFIG,					/* ���� */
		};


		/* �� */
		enum E_TEST_LIE
		{
			CFG_LIE_KEY,								/* �����ݵ�key */
			CFG_LIE_NAME,								/* ���� */
			CFG_LIE_VALUES,							/* ֵ */
			CFG_LIE_INTERPRETATION,			/* ���� */
		};

		/* �� */
		enum E_TEST_HANG
		{
			CFG_HANG_TCP_PORT,				/* TCP�˿� */
			CFG_HANG_UDP_PORT = 5,				/* UDP�˿� */
		};

	}  //namespace tools
}  //namespace middleware 

#endif  //READCONFIG_KEY_VALUES
/* vim: set expandtab ts=2 sw=2 sts=2 tw=100: */