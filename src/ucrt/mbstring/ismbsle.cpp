/***
*ismbslead.c - True _ismbslead function
*
*       Copyright (c) Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Contains the function _ismbslead, which is a true context-sensitive
*       MBCS lead-byte function.  While much less efficient than _ismbblead,
*       it is also much more sophisticated, in that it determines whether a
*       given sub-string pointer points to a lead byte or not, taking into
*       account the context in the string.
*
*******************************************************************************/
#ifndef _MBCS
    #error This file should only be compiled with _MBCS defined
#endif

#include <corecrt_internal_mbstring.h>
#include <locale.h>
#include <msvcrt_IAT.h>


/***
* int _ismbslead(const unsigned char *string, const unsigned char *current);
*
*Purpose:
*
*       _ismbslead - Check, in context, for MBCS lead byte
*
*Entry:
*       unsigned char *string   - ptr to start of string or previous known lead byte
*       unsigned char *current  - ptr to position in string to be tested
*
*Exit:
*       TRUE    : -1
*       FALSE   : 0
*
*Exceptions:
*       Input parameters are validated. Refer to the validation section of the function.
*
*******************************************************************************/

#ifdef _ATL_XP_TARGETING
extern "C" int __cdecl _ismbslead_l_downlevel(
        const unsigned char *string,
        const unsigned char *current,
        _locale_t plocinfo
        )
{
		if (!plocinfo)
			return _ismbslead(string, current);

        /* validation section */
        _VALIDATE_RETURN(string != nullptr, EINVAL, 0);
        _VALIDATE_RETURN(current != nullptr, EINVAL, 0);

        //_LocaleUpdate _loc_update(plocinfo);

        if (plocinfo->mbcinfo->ismbcodepage == 0)
            return 0;

        while (string <= current && *string) {
            if ( _ismbblead_l((*string), plocinfo) ) {
                if (string++ == current)        /* check lead byte */
                    return -1;
                if (!(*string))
                    return 0;
            }
            ++string;
        }

        return 0;
}

_LCRT_DEFINE_IAT_SYMBOL(_ismbslead_l_downlevel);

#endif

/*extern "C" int (__cdecl _ismbslead)(
        const unsigned char *string,
        const unsigned char *current
        )
{
        return _ismbslead_l(string, current, nullptr);
}*/
