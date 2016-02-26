///        Copyright 2016 libo. All rights reserved
///   (Home at https://github.com/NingLeixueR/middleware/)

#ifndef PROTOCOL_COUT
#define PROTOCOL_COUT

#include "middleware/tools/protocol/protocol_base.hpp"
#include "middleware/tools/protocol/protocol/test_protocol/protocol_test_num.hpp"

#include <string>

namespace middleware {
	namespace tools {
		class protocol_test_0 :
			public tools::protocol_base<spack_head::protocol_head, spack_head::protocol_head >
		{
			std::string mpop_ls;
		public:
			protocol_test_0() :
				tools::protocol_base<spack_head::protocol_head, spack_head::protocol_head >(E_TEST_0)
			{}

			virtual bool task(uint32_t aikey)
			{
				return 0;
			}
			virtual void serialization()
			{

			}
			virtual void unserialization()
			{
				m_premote2local->pop(mpop_ls);
			}
			virtual tools::protocol_base<spack_head::protocol_head, spack_head::protocol_head>* new_own()
			{
				return new protocol_test_0();
			}
		};

	} //namespace tools
}//namespace middleware
#endif //PROTOCOL_COUT

 /* vim: set expandtab ts=2 sw=2 sts=2 tw=100: */