/***
*mbtoupr.c - Convert character to upper case (MBCS)
*
*       Copyright (c) Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Convert character to upper case (MBCS)
*
*******************************************************************************/
#ifndef _MBCS
    #error This file should only be compiled with _MBCS defined
#endif

#include <corecrt_internal_mbstring.h>
#include <locale.h>
#include "..\..\winapi_thunks.h"
#include <msvcrt_IAT.h>

/***
* _mbctoupper - Convert character to upper case (MBCS)
*
*Purpose:
*       If the given character is lower case, convert to upper case.
*       Handles MBCS chars correctly.
*
*       Note:  Use test against 0x00FF instead of _ISLEADBYTE
*       to ensure that we don't call SBCS routine with a two-byte
*       value.
*
*Entry:
*       unsigned int c = character to convert
*
*Exit:
*       Returns converted character
*
*Exceptions:
*
*******************************************************************************/

#ifdef _ATL_XP_TARGETING
extern "C" unsigned int __cdecl _mbctoupper_l_downlevel(
        unsigned int c,
        _locale_t plocinfo
        )
{
		if (!plocinfo)
			return _mbctoupper(c);

        unsigned char val[2];
        unsigned char ret[4];
        //_LocaleUpdate _loc_update(plocinfo);

        if (c > 0x00FF)
        {

            val[0] = (c >> 8) & 0xFF;
            val[1] = c & 0xFF;

            if ( !_ismbblead_l(val[0], plocinfo) )
                return c;


            if (__acrt_LCMapStringA(
                        plocinfo,
                        plocinfo->mbcinfo->mblcid,
                        LCMAP_UPPERCASE,
                        (const char *)val,
                        2,
                        (char *)ret,
                        2,
                        plocinfo->mbcinfo->mbcodepage,
                        TRUE ) == 0 )
                return c;

            c = ret[1];
            c += ret[0] << 8;

            return c;


        }
        else
            return (unsigned int)_mbbtoupper_l((int)c, plocinfo);
}

_LCRT_DEFINE_IAT_SYMBOL(_mbctoupper_l_downlevel);

#endif
/*unsigned int (__cdecl _mbctoupper)(
        unsigned int c
        )
{
    return _mbctoupper_l(c, nullptr);
}*/
