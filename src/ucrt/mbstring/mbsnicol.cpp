/***
*mbsnicol.c - Collate n characters of strings, ignoring case (MBCS)
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Collate n characters of strings, ignoring case (MBCS)
*
*******************************************************************************/
#ifndef _MBCS
    #error This file should only be compiled with _MBCS defined
#endif

#include <corecrt_internal_mbstring.h>
#include <limits.h>
#include <locale.h>
#include <string.h>
#include "..\..\winapi_thunks.h"
#include <msvcrt_IAT.h>


/***
* _mbsnicoll - Collate n characters of strings, ignoring case (MBCS)
*
*Purpose:
*       Collates up to n charcters of two strings for lexical order.
*       Strings are collated on a character basis, not a byte basis.
*       Case of characters is not considered.
*
*Entry:
*       unsigned char *s1, *s2 = strings to collate
*       size_t n = maximum number of characters to collate
*
*Exit:
*       Returns <0 if s1 < s2
*       Returns  0 if s1 == s2
*       Returns >0 if s1 > s2
*       Returns _NLSCMPERROR is something went wrong
*
*Exceptions:
*       Input parameters are validated. Refer to the validation section of the function.
*
*******************************************************************************/

#ifdef _ATL_XP_TARGETING
extern "C" int __cdecl _mbsnicoll_l_downlevel(
        const unsigned char *s1,
        const unsigned char *s2,
        size_t n,
        _locale_t plocinfo
        )
{
		if (!plocinfo)
			return _mbsnicoll(s1, s2, n);

        int ret;
        size_t bcnt1, bcnt2;
        //_LocaleUpdate _loc_update(plocinfo);

        if (n == 0)
            return 0;

        /* validation section */
        _VALIDATE_RETURN(s1 != nullptr, EINVAL, _NLSCMPERROR);
        _VALIDATE_RETURN(s2 != nullptr, EINVAL, _NLSCMPERROR);
        _VALIDATE_RETURN(n <= INT_MAX, EINVAL, _NLSCMPERROR);

        if (plocinfo->mbcinfo->ismbcodepage == 0)
            return _strnicoll_l((const char *)s1, (const char *)s2, n, plocinfo);

        bcnt1 = _mbsnbcnt_l(s1, n, plocinfo);
        bcnt2 = _mbsnbcnt_l(s2, n, plocinfo);

        if ( 0 == (ret = __acrt_CompareStringA(
                        plocinfo,
                        plocinfo->mbcinfo->mblcid,
                        SORT_STRINGSORT | NORM_IGNORECASE,
                        (const char *)s1,
                        (int)bcnt1,
                        (char *)s2,
                        (int)bcnt2,
                        plocinfo->mbcinfo->mbcodepage )) )
        {
            errno = EINVAL;
            return _NLSCMPERROR;
        }

        return ret - 2;

}

_LCRT_DEFINE_IAT_SYMBOL(_mbsnicoll_l_downlevel);

#endif

/*extern "C" int (__cdecl _mbsnicoll)(
        const unsigned char *s1,
        const unsigned char *s2,
        size_t n
        )
{
    return _mbsnicoll_l(s1, s2, n, nullptr);
}*/
