/***
*wcscoll.c - Collate wide-character locale strings
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Compare two wchar_t strings using the locale LC_COLLATE information.
*
*******************************************************************************/
#include <corecrt_internal.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include "..\..\winapi_thunks.h"
#include <msvcrt_IAT.h>


/***
*int wcscoll() - Collate wide-character locale strings
*
*Purpose:
*       Compare two wchar_t strings using the locale LC_COLLATE information.
*       In the C locale, wcscmp() is used to make the comparison.
*
*Entry:
*       const wchar_t *s1 = pointer to the first string
*       const wchar_t *s2 = pointer to the second string
*
*Exit:
*       -1 = first string less than second string
*        0 = strings are equal
*        1 = first string greater than second string
*       Returns _NLSCMPERROR is something went wrong
*       This range of return values may differ from other *cmp/*coll functions.
*
*Exceptions:
*       Input parameters are validated. Refer to the validation section of the function.
*
*******************************************************************************/

#ifdef _ATL_XP_TARGETING
extern "C" int __cdecl _wcscoll_l_downlevel (
        const wchar_t *_string1,
        const wchar_t *_string2,
        _locale_t plocinfo
        )
{
    int ret;
    //_LocaleUpdate _loc_update(plocinfo);

    /* validation section */
    _VALIDATE_RETURN(_string1 != nullptr, EINVAL, _NLSCMPERROR);
    _VALIDATE_RETURN(_string2 != nullptr, EINVAL, _NLSCMPERROR);

	auto _lc_collate = (plocinfo ? plocinfo->locinfo->lc_handle : ___lc_handle_func())[LC_COLLATE];

    if (_lc_collate == 0)
        return (wcscmp(_string1, _string2));

    if ( 0 == (ret = __acrt_CompareStringW(
                    _lc_collate,
                    SORT_STRINGSORT,
                    _string1,
                    -1,
                    _string2,
                    -1)) )
    {
        errno = EINVAL;
        return _NLSCMPERROR;
    }

    return (ret - 2);

}

_LCRT_DEFINE_IAT_SYMBOL(_wcscoll_l_downlevel);

#endif

#if 0
extern "C" int __cdecl wcscoll (
        const wchar_t *_string1,
        const wchar_t *_string2
        )
{
    if (!__acrt_locale_changed())
    {
        /* validation section */
        _VALIDATE_RETURN(_string1 != nullptr, EINVAL, _NLSCMPERROR);
        _VALIDATE_RETURN(_string2 != nullptr, EINVAL, _NLSCMPERROR);

        return (wcscmp(_string1, _string2));
    }
    else
    {
        return _wcscoll_l(_string1, _string2, nullptr);
    }
}
#endif
