#ifndef SERIALIZACPP_JSON_HPP
#define SERIALIZACPP_JSON_HPP

#include "middleware/tools/serializecpp/public/xml_json/xmljson_serializecpp.hpp"

#include <cstdint>

namespace middleware{
	namespace tools {

		/**
		 * json���л�
		 */
		typedef serialize_stand<serializecpp_jsonbuffer> serializecpp_json;


	} //namespace tools
}  //namespace middleware

#endif //SERIALIZACPP_JSON_HPP

/* vim: set expandtab ts=2 sw=2 sts=2 tw=100: */
