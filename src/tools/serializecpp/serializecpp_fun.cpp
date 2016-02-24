///        Copyright 2016 libo. All rights reserved
///   (Home at https://github.com/NingLeixueR/middleware/)

#include "middleware/tools/serializecpp/public/serializecpp_fun.hpp"

#include <cstring>
#include <cstdio>

namespace middleware {
	namespace tools {

		int Binary2Cstr(unsigned char *pSrc, int nSrcLen, unsigned char *pDst, int nDstMaxLen)
		{
			if (pDst != NULL)
			{
				*pDst = 0;
			}

			if (pSrc == NULL || nSrcLen <= 0 || pDst == NULL || nDstMaxLen <= nSrcLen * 2)
			{
				return 0;
			}

			//0x0-0xf���ַ����ұ� 
			const char szTable[] = "0123456789ABCDEF";
			for (int i = 0; i<nSrcLen; i++)
			{
				//�����4λ   
				*pDst++ = szTable[pSrc[i] >> 4];
				// �����4λ   
				*pDst++ = szTable[pSrc[i] & 0x0f];
			}
			// ����ַ����Ӹ�������   
			*pDst = '\0';
			//����Ŀ���ַ�������   
			return  nSrcLen * 2;
		}

		int Cstr2Binary(unsigned char* szSrc, unsigned char* pDst, int nDstMaxLen)
		{
			if (szSrc == NULL)
			{
				return 0;
			}
			int iLen = strlen((char *)szSrc);
			if (iLen <= 0 || iLen % 2 != 0 || pDst == NULL || nDstMaxLen < iLen / 2)
			{
				return 0;
			}

			iLen /= 2;
			strupr((char *)szSrc);
			for (int i = 0; i<iLen; i++)
			{
				int iVal = 0;
				unsigned char *pSrcTemp = szSrc + i * 2;
				sscanf((char *)pSrcTemp, "%02x", &iVal);
				pDst[i] = (unsigned char)iVal;
			}
			return iLen;
		}

	} //namespace tools
}// namespace middleware

 /* vim: set expandtab ts=2 sw=2 sts=2 tw=100: */