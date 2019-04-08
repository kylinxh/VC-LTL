//
// winapi_thunks.cpp
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// Definitions of wrappers for Windows API functions that cannot be called
// directly because they are not available on all supported operating systems.
//

#include <corecrt_internal.h>
#include <appmodel.h>
#include <roapi.h>
#include "..\..\src\winapi_thunks.h"
#include <internal_shared.h>

#ifdef _ATL_XP_TARGETING
	//XP��2003������Ҫ����Ȼ����Ӳ����ʱ������ʧ��
	#pragma comment(linker, "/defaultlib:advapi32.lib")
#endif

// Define this locally because including ntstatus.h conflicts with headers above
#define STATUS_NOT_FOUND                 ((LONG)0xC0000225L)

// Prototype for NT OS API defined locally to avoid conflicts with NT headers
extern "C" NTSYSAPI LONG NTAPI RtlQueryPackageClaims(
    _In_ PVOID TokenObject,
    _Out_writes_bytes_to_opt_(*PackageSize, *PackageSize) PWSTR PackageFullName,
    _Inout_opt_ PSIZE_T PackageSize,
    _Out_writes_bytes_to_opt_(*AppIdSize, *AppIdSize) PWSTR AppId,
    _Inout_opt_ PSIZE_T AppIdSize,
    _Out_opt_ LPGUID DynamicId,
    _Out_opt_ PVOID /* PPS_PKG_CLAIM */ PkgClaim,
    _Out_opt_ PULONG64 AttributesPresent
    );

// SystemFunction036 is RtlGenRandom.  We declare it ourselves because the
// declaration in ntsecapi.h lacks an explicit calling convention.
extern "C" BOOLEAN WINAPI SystemFunction036(
    _Out_writes_bytes_(buffer_count) PVOID buffer,
    _In_                             ULONG buffer_count
    );

// The XState APIs are declared by the Windows headers only when building for
// x86 and x64.  We declare them here unconditionally so that we can share the
// same code for all architectures (we simply avoid use of these functions on
// other architectures).
extern "C" WINBASEAPI DWORD64 WINAPI GetEnabledXStateFeatures();

_Must_inspect_result_
extern "C" WINBASEAPI BOOL WINAPI GetXStateFeaturesMask(
    _In_  PCONTEXT context,
    _Out_ PDWORD64 feature_mask
    );

_Success_(return != NULL)
extern "C" WINBASEAPI PVOID WINAPI LocateXStateFeature(
    _In_      PCONTEXT context,
    _In_      DWORD    feature_id,
    _Out_opt_ PDWORD   length
    );

#ifndef _NONE_

#define _NO_APPLY(a,b)

//_NO_APPLY_2003 ��2003�Լ�����ƽ̨��Ӧ��
#if defined _ATL_XP_TARGETING && defined _X86_
#define _NO_APPLY_2003 _APPLY
#else
#define _NO_APPLY_2003(a,b)
#endif


//_NO_APPLY_Vista ��Vista�Լ�����ƽ̨��Ӧ��
#ifdef _ATL_XP_TARGETING
#define _NO_APPLY_Vista _APPLY
#else
#define _NO_APPLY_Vista(a,b)
#endif


#define _ACRT_APPLY_TO_LATE_BOUND_MODULES(_APPLY)                                                        \
    _APPLY(api_ms_win_core_datetime_l1_1_1,              "api-ms-win-core-datetime-l1-1-1"             ) \
    _APPLY(api_ms_win_core_fibers_l1_1_1,                "api-ms-win-core-fibers-l1-1-1"               ) \
    _APPLY(api_ms_win_core_file_l1_2_2,                  "api-ms-win-core-file-l1-2-2"                 ) \
    _APPLY(api_ms_win_core_localization_l1_2_1,          "api-ms-win-core-localization-l1-2-1"         ) \
    _APPLY(api_ms_win_core_localization_obsolete_l1_2_0, "api-ms-win-core-localization-obsolete-l1-2-0") \
    _APPLY(api_ms_win_core_processthreads_l1_1_2,        "api-ms-win-core-processthreads-l1-1-2"       ) \
    _APPLY(api_ms_win_core_string_l1_1_0,                "api-ms-win-core-string-l1-1-0"               ) \
    _APPLY(api_ms_win_core_synch_l1_2_0,                 "api-ms-win-core-synch-l1-2-0"                ) \
    _APPLY(api_ms_win_core_sysinfo_l1_2_1,               "api-ms-win-core-sysinfo-l1-2-1"              ) \
    _APPLY(api_ms_win_core_winrt_l1_1_0,                 "api-ms-win-core-winrt-l1-1-0"                ) \
    _APPLY(api_ms_win_core_xstate_l2_1_0,                "api-ms-win-core-xstate-l2-1-0"               ) \
    _APPLY(api_ms_win_rtcore_ntuser_window_l1_1_0,       "api-ms-win-rtcore-ntuser-window-l1-1-0"      ) \
    _APPLY(api_ms_win_security_systemfunctions_l1_1_0,   "api-ms-win-security-systemfunctions-l1-1-0"  ) \
    _APPLY(ext_ms_win_ntuser_dialogbox_l1_1_0,           "ext-ms-win-ntuser-dialogbox-l1-1-0"          ) \
    _APPLY(ext_ms_win_ntuser_windowstation_l1_1_0,       "ext-ms-win-ntuser-windowstation-l1-1-0"      ) \
    _APPLY(advapi32,                                     "advapi32"                                    ) \
    _APPLY(kernel32,                                     "kernel32"                                    ) \
    _APPLY(ntdll,                                        "ntdll"                                       ) \
    _APPLY(api_ms_win_appmodel_runtime_l1_1_2,           "api-ms-win-appmodel-runtime-l1-1-2"          ) \
    _APPLY(user32,                                       "user32"                                      )



#define _ACRT_APPLY_TO_LATE_BOUND_FUNCTIONS(_APPLY)                                                                                                     \
    _NO_APPLY(AreFileApisANSI,                             ({ /* api_ms_win_core_file_l1_2_2, */            kernel32                                   })) \
    _NO_APPLY(CompareStringEx,                             ({ api_ms_win_core_string_l1_1_0,                kernel32                                   })) \
    _NO_APPLY(EnumSystemLocalesEx,                         ({ api_ms_win_core_localization_l1_2_1,          kernel32                                   })) \
    _NO_APPLY(FlsAlloc,                                    ({ api_ms_win_core_fibers_l1_1_1,                kernel32                                   })) \
    _NO_APPLY(FlsFree,                                     ({ api_ms_win_core_fibers_l1_1_1,                kernel32                                   })) \
    _NO_APPLY(FlsGetValue,                                 ({ api_ms_win_core_fibers_l1_1_1,                kernel32                                   })) \
    _NO_APPLY(FlsSetValue,                                 ({ api_ms_win_core_fibers_l1_1_1,                kernel32                                   })) \
    _NO_APPLY(GetActiveWindow,                             ({ api_ms_win_rtcore_ntuser_window_l1_1_0,       user32                                     })) \
    _NO_APPLY(GetDateFormatEx,                             ({ api_ms_win_core_datetime_l1_1_1,              kernel32                                   })) \
    _NO_APPLY(GetEnabledXStateFeatures,                    ({ api_ms_win_core_xstate_l2_1_0,                kernel32                                   })) \
    _NO_APPLY(GetLastActivePopup,                          ({ ext_ms_win_ntuser_dialogbox_l1_1_0,           user32                                     })) \
    _NO_APPLY(GetLocaleInfoEx,                             ({ api_ms_win_core_localization_l1_2_1,          kernel32                                   })) \
    _NO_APPLY(GetProcessWindowStation,                     ({ ext_ms_win_ntuser_windowstation_l1_1_0,       user32                                     })) \
    _APPLY(GetSystemTimePreciseAsFileTime,                 ({ api_ms_win_core_sysinfo_l1_2_1                                                           })) \
    _NO_APPLY(GetTimeFormatEx,                             ({ api_ms_win_core_datetime_l1_1_1,              kernel32                                   })) \
    _NO_APPLY(GetUserDefaultLocaleName,                    ({ api_ms_win_core_localization_l1_2_1,          kernel32                                   })) \
    _NO_APPLY(GetUserObjectInformationW,                   ({ ext_ms_win_ntuser_windowstation_l1_1_0,       user32                                     })) \
    _NO_APPLY(GetXStateFeaturesMask,                       ({ api_ms_win_core_xstate_l2_1_0,                kernel32                                   })) \
    _NO_APPLY(InitializeCriticalSectionEx,                 ({ api_ms_win_core_synch_l1_2_0,                 kernel32                                   })) \
    _NO_APPLY(IsValidLocaleName,                           ({ api_ms_win_core_localization_l1_2_1,          kernel32                                   })) \
    _NO_APPLY(LCMapStringEx,                               ({ api_ms_win_core_localization_l1_2_1,          kernel32                                   })) \
    _NO_APPLY_Vista(LCIDToLocaleName,                      ({ api_ms_win_core_localization_obsolete_l1_2_0, kernel32                                   })) \
    _NO_APPLY_Vista(LocaleNameToLCID,                      ({ api_ms_win_core_localization_l1_2_1,          kernel32                                   })) \
    _NO_APPLY(LocateXStateFeature,                         ({ api_ms_win_core_xstate_l2_1_0,                kernel32                                   })) \
    _NO_APPLY(MessageBoxA,                                 ({ ext_ms_win_ntuser_dialogbox_l1_1_0,           user32                                     })) \
    _NO_APPLY(MessageBoxW,                                 ({ ext_ms_win_ntuser_dialogbox_l1_1_0,           user32                                     })) \
    _NO_APPLY(RoInitialize,                                ({ api_ms_win_core_winrt_l1_1_0                                                             })) \
    _NO_APPLY(RoUninitialize,                              ({ api_ms_win_core_winrt_l1_1_0                                                             })) \
    _NO_APPLY(AppPolicyGetProcessTerminationMethod,        ({ api_ms_win_appmodel_runtime_l1_1_2                                                       })) \
    _NO_APPLY(AppPolicyGetThreadInitializationType,        ({ api_ms_win_appmodel_runtime_l1_1_2                                                       })) \
    _NO_APPLY(AppPolicyGetShowDeveloperDiagnostic,         ({ api_ms_win_appmodel_runtime_l1_1_2                                                       })) \
    _NO_APPLY(AppPolicyGetWindowingModel,                  ({ api_ms_win_appmodel_runtime_l1_1_2                                                       })) \
    _NO_APPLY(SetThreadStackGuarantee,                     ({ api_ms_win_core_processthreads_l1_1_2,        kernel32                                   })) \
    _NO_APPLY(SystemFunction036,                           ({ api_ms_win_security_systemfunctions_l1_1_0,   advapi32                                   })) \
    _NO_APPLY_Vista(InitOnceExecuteOnce,                   ({ /*api_ms_win_core_synch_l1_1_0,*/             kernel32                                   })) \
    _NO_APPLY_Vista(InitializeConditionVariable,           ({ /*api_ms_win_core_synch_l1_1_0,*/             kernel32                                   })) \
    _NO_APPLY_Vista(SleepConditionVariableCS,              ({ /*api_ms_win_core_synch_l1_1_0,*/             kernel32                                   })) \
    _APPLY(WakeConditionVariable,                          ({ /*api_ms_win_core_synch_l1_2_0,*/             kernel32                                   })) \
    _APPLY(WakeAllConditionVariable,                       ({ /*api_ms_win_core_synch_l1_2_0,*/             kernel32                                   })) \
    _NO_APPLY_Vista(InitializeSRWLock,                     ({ /*api_ms_win_core_synch_l1_1_0,*/             kernel32                                   })) \
    _NO_APPLY_Vista(AcquireSRWLockExclusive,               ({ /*api_ms_win_core_synch_l1_1_0,*/             kernel32                                   })) \
    _APPLY(TryAcquireSRWLockExclusive,                     ({ /*api_ms_win_core_synch_l1_1_0,*/             kernel32                                   })) \
    _NO_APPLY_Vista(ReleaseSRWLockExclusive,               ({ /*api_ms_win_core_synch_l1_1_0,*/             kernel32                                   })) \
    _NO_APPLY_Vista(SleepConditionVariableSRW,             ({ /*api_ms_win_core_synch_l1_2_0,*/             kernel32                                   })) \
    _NO_APPLY_Vista(CreateThreadpoolWork,                  ({ /*api_ms_win_core_synch_l1_2_0,*/             kernel32                                   })) \
    _NO_APPLY_Vista(FreeLibraryWhenCallbackReturns,        ({ /*api_ms_win_core_synch_l1_2_0,*/             kernel32                                   })) \
    _NO_APPLY_Vista(SubmitThreadpoolWork,                  ({ /*api_ms_win_core_synch_l1_2_0,*/             kernel32                                   })) \
    _NO_APPLY_Vista(CloseThreadpoolWork,                   ({ /*api_ms_win_core_synch_l1_2_0,*/             kernel32                                   })) \
    _NO_APPLY_Vista(SetThreadpoolTimer,                    ({ /*api_ms_win_core_synch_l1_2_0,*/             kernel32                                   })) \
    _NO_APPLY_2003(GetCurrentProcessorNumber,              ({ /*api_ms_win_core_synch_l1_2_0,*/             kernel32                                   })) \
    _NO_APPLY_Vista(FlushProcessWriteBuffers,              ({ /*api_ms_win_core_synch_l1_2_0,*/             kernel32                                   })) \
    _NO_APPLY_Vista(GetTickCount64,                        ({ /*api_ms_win_core_synch_l1_2_0,*/             kernel32                                   })) \
    _NO_APPLY_Vista(SetThreadpoolWait,                     ({ /*api_ms_win_core_synch_l1_2_0,*/             kernel32                                   })) \
    _NO_APPLY_Vista(CloseThreadpoolWait,                   ({ /*api_ms_win_core_synch_l1_2_0,*/             kernel32                                   })) \
    _NO_APPLY_Vista(WaitForThreadpoolTimerCallbacks,       ({ /*api_ms_win_core_synch_l1_2_0,*/             kernel32                                   })) \
    _NO_APPLY_Vista(CreateThreadpoolWait,                  ({ /*api_ms_win_core_synch_l1_2_0,*/             kernel32                                   })) \
    _NO_APPLY_Vista(CloseThreadpoolTimer,                  ({ /*api_ms_win_core_synch_l1_2_0,*/             kernel32                                   })) \
    _NO_APPLY_Vista(CreateThreadpoolTimer,                 ({ /*api_ms_win_core_synch_l1_2_0,*/             kernel32                                   })) \
    _NO_APPLY_2003(GetLogicalProcessorInformation,         ({ /*api_ms_win_core_synch_l1_2_0,*/             kernel32                                   })) \
    _NO_APPLY_2003(GetNumaHighestNodeNumber,               ({ /*api_ms_win_core_synch_l1_2_0,*/             kernel32                                   }))

namespace
{
    // Generate enumerators for each of the modules:
    enum module_id : unsigned
    {
        #define _APPLY(_SYMBOL, _NAME) _SYMBOL,
        _ACRT_APPLY_TO_LATE_BOUND_MODULES(_APPLY)
        #undef _APPLY

        module_id_count
    };

    // Generate a table of module names that can be indexed by the module_id
    // enumerators:
    static wchar_t const* const module_names[module_id_count] =
    {
        #define _APPLY(_SYMBOL, _NAME) _CRT_WIDE(_NAME),
        _ACRT_APPLY_TO_LATE_BOUND_MODULES(_APPLY)
        #undef _APPLY
    };

    // Generate enumerators for each of the functions:
    enum function_id : unsigned
    {
        #define _APPLY(_FUNCTION, _MODULES) _CRT_CONCATENATE(_FUNCTION, _id),
        _ACRT_APPLY_TO_LATE_BOUND_FUNCTIONS(_APPLY)
        #undef _APPLY

        function_id_count
    };

    // Generate a typedef for each function of the form function_pft.
    #define _APPLY(_FUNCTION, _MODULES) \
        using _CRT_CONCATENATE(_FUNCTION, _pft) = decltype(_FUNCTION)*;
    _ACRT_APPLY_TO_LATE_BOUND_FUNCTIONS(_APPLY)
    #undef _APPLY
}



// This table stores the module handles that we have obtained via LoadLibrary.
// If a handle is null, we have not yet attempted to load that module.  If a
// handle is -1 (INVALID_HANDLE_VALUE), we have attempted to load the module
// but the attempt failed.
static HMODULE module_handles[module_id_count];

// This table stores the function pointers that we have loaded dynamically.  The
// function pointers are stored in encoded form via __crt_fast_encode_ponter.  If
// a function pointer is an encoded null pointer, we have not yet attempted to
// get that function pointer.  If a function pointer is an encoded -1, we have
// attempted to get that function pointer but the attempt failed.
static void* encoded_function_pointers[function_id_count];



extern "C" bool __cdecl __acrt_initialize_winapi_thunks()
{
    void* const encoded_nullptr = __crt_fast_encode_pointer(nullptr);

    for (void*& p : encoded_function_pointers)
    {
        p = encoded_nullptr;
    }

    return true;
}

extern "C" bool __cdecl __acrt_uninitialize_winapi_thunks(bool const terminating)
{
    // If the process is terminating, there's no need to free any module handles
    if (terminating)
    {
        return true;
    }

    for (HMODULE& module : module_handles)
    {
        if (module)
        {
            if (module != INVALID_HANDLE_VALUE)
            {
                FreeLibrary(module);
            }

            module = nullptr;
        }
    }

    return true;
}



static __forceinline void* __cdecl invalid_function_sentinel() throw()
{
    return reinterpret_cast<void*>(static_cast<uintptr_t>(-1));
}



static HMODULE __cdecl try_load_library_from_system_directory(wchar_t const* const name) throw()
{
    HMODULE const handle = LoadLibraryExW(name, nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (handle)
    {
        return handle;
    }

    // LOAD_LIBRARY_SEARCH_SYSTEM32 is only supported by Windows 7 and above; if
    // the OS does not support this flag, try again without it.  On these OSes,
    // all APISets will be forwarders.  To prevent DLL hijacking, do not attempt
    // to load the APISet forwarders dynamically.  This will cause our caller to
    // fall back to the real DLL (e.g. kernel32).  All of those are known DLLs.
    if (GetLastError() == ERROR_INVALID_PARAMETER &&
        wcsncmp(name, L"api-ms-", 7) != 0 &&
        wcsncmp(name, L"ext-ms-", 7) != 0)
    {
        return LoadLibraryExW(name, nullptr, 0);
    }

    return nullptr;
}



static HMODULE __cdecl try_get_module(module_id const id) throw()
{
    // First check to see if we've cached the module handle:
    if (HMODULE const cached_handle = __crt_interlocked_read_pointer(module_handles + id))
    {
        if (cached_handle == INVALID_HANDLE_VALUE)
        {
            return nullptr;
        }

        return cached_handle;
    }

    // If we haven't yet cached the module handle, try to load the library.  If
    // this fails, cache the sentinel handle value INVALID_HANDLE_VALUE so that
    // we don't attempt to load the module again:
    HMODULE const new_handle = try_load_library_from_system_directory(module_names[id]);
    if (!new_handle)
    {
        if (HMODULE const cached_handle = __crt_interlocked_exchange_pointer(module_handles + id, INVALID_HANDLE_VALUE))
        {
            _ASSERTE(cached_handle == INVALID_HANDLE_VALUE);
        }

        return nullptr;
    }

    // Swap the new handle into the cache.  If the cache no longer contained a
    // null handle, then some other thread loaded the module and cached the
    // handle while we were doing the same.  In that case, we free the handle
    // once to maintain the reference count:
    if (HMODULE const cached_handle = __crt_interlocked_exchange_pointer(module_handles + id, new_handle))
    {
        _ASSERTE(cached_handle == new_handle);
        FreeLibrary(new_handle);
    }

    return new_handle;
}



static HMODULE __cdecl try_get_first_available_module(
    module_id const* const first,
    module_id const* const last
    ) throw()
{
    for (module_id const* it = first; it != last; ++it)
    {
        HMODULE const handle = try_get_module(*it);
        if (handle)
        {
            return handle;
        }
    }

    return nullptr;
}



static __forceinline void* __cdecl try_get_proc_address_from_first_available_module(
    char      const* const name,
    module_id const* const first_module_id,
    module_id const* const last_module_id
    ) throw()
{
    HMODULE const module_handle = try_get_first_available_module(first_module_id, last_module_id);
    if (!module_handle)
    {
        return nullptr;
    }

    return reinterpret_cast<void*>(GetProcAddress(module_handle, name));
}



static void* __cdecl try_get_function(
    function_id      const id,
    char      const* const name,
    module_id const* const first_module_id,
    module_id const* const last_module_id
    ) throw()
{
    // First check to see if we've cached the function pointer:
    {
        void* const cached_fp = __crt_fast_decode_pointer(
            __crt_interlocked_read_pointer(encoded_function_pointers + id));

        if (cached_fp == invalid_function_sentinel())
        {
            return nullptr;
        }

        if (cached_fp)
        {
            return cached_fp;
        }
    }

    // If we haven't yet cached the function pointer, try to import it from any
    // of the modules in which it might be defined.  If this fails, cache the
    // sentinel pointer so that we don't attempt to load this function again:
    void* const new_fp = try_get_proc_address_from_first_available_module(name, first_module_id, last_module_id);
    if (!new_fp)
    {
        void* const cached_fp = __crt_fast_decode_pointer(
            __crt_interlocked_exchange_pointer(
                encoded_function_pointers + id,
                __crt_fast_encode_pointer(invalid_function_sentinel())));

        if (cached_fp)
        {
            _ASSERTE(cached_fp == invalid_function_sentinel());
        }

        return nullptr;
    }

    // Swap the newly obtained function pointer into the cache.  The cache may
    // no longer contain an encoded null pointer if another thread obtained the
    // function address while we were doing the same (both threads should have
    // gotten the same function pointer):
    {
        void* const cached_fp = __crt_fast_decode_pointer(
            __crt_interlocked_exchange_pointer(
                encoded_function_pointers + id,
                __crt_fast_encode_pointer(new_fp)));

        if (cached_fp)
        {
            _ASSERTE(cached_fp == new_fp);
        }
    }

    return new_fp;
}



// Generate accessors that wrap the general try_get_function for each function,
// passing the correct set of candidate modules and returning a function pointer
// of the correct type:
#define _APPLY(_FUNCTION, _MODULES)                                                                   \
    static _CRT_CONCATENATE(_FUNCTION, _pft) __cdecl _CRT_CONCATENATE(try_get_, _FUNCTION)() throw()  \
    {                                                                                                 \
        static module_id const candidate_modules[] = _CRT_UNPARENTHESIZE(_MODULES);                   \
                                                                                                      \
        return reinterpret_cast<_CRT_CONCATENATE(_FUNCTION, _pft)>(try_get_function(                  \
            _CRT_CONCATENATE(_FUNCTION, _id),                                                         \
            _CRT_STRINGIZE(_FUNCTION),                                                                \
            candidate_modules,                                                                        \
            candidate_modules + _countof(candidate_modules)));                                        \
    }
_ACRT_APPLY_TO_LATE_BOUND_FUNCTIONS(_APPLY)
#undef _APPLY

#endif

//extern "C" BOOL WINAPI __acrt_AreFileApisANSI()
//{
	//return AreFileApisANSI();
	//if (auto const are_file_apis_ansi = try_get_AreFileApisANSI())
	//{
	//	return are_file_apis_ansi();
	//}

	//// If we were unable to get the AreFileApisANSI function, we can safely
	//// assume that the file APIs are, in fact, ANSI:
	//return TRUE;
//}

#if 0
extern "C" int WINAPI __acrt_CompareStringEx(
    LPCWSTR          const locale_name,
    DWORD            const flags,
    LPCWCH           const string1,
    int              const string1_count,
    LPCWCH           const string2,
    int              const string2_count,
    LPNLSVERSIONINFO const version,
    LPVOID           const reserved,
    LPARAM           const param
    )
{

	/*if (auto const compare_string_ex = try_get_CompareStringEx())
	{
		return compare_string_ex(locale_name, flags, string1, string1_count, string2, string2_count, version, reserved, param);
	}*/

	return CompareStringW(__acrt_LocaleNameToLCID(locale_name, 0), flags, string1, string1_count, string2, string2_count);
}
#endif

// This has been split into its own function to work around a bug in the Dev12
// C++ compiler where nested captureless lambdas are not convertible to the
// required function pointer type.
static BOOL enum_system_locales_ex_nolock(
    LOCALE_ENUMPROCEX const enum_proc
    ) throw()
{
    static LOCALE_ENUMPROCEX static_enum_proc;

    static_enum_proc = __crt_fast_encode_pointer(enum_proc);
    BOOL const result = EnumSystemLocalesW(
        [](LPWSTR locale_string) { return __crt_fast_decode_pointer(static_enum_proc)(locale_string, 0, 0); },
        LCID_INSTALLED);
    static_enum_proc = __crt_fast_encode_pointer(nullptr);

    return result;
}

__if_exists(try_get_EnumSystemLocalesEx)
{
	extern "C" BOOL WINAPI __acrt_EnumSystemLocalesEx(
		LOCALE_ENUMPROCEX const enum_proc,
		DWORD             const flags,
		LPARAM            const param,
		LPVOID            const reserved
	)
	{
		if (auto const enum_system_locales_ex = try_get_EnumSystemLocalesEx())
		{
			return enum_system_locales_ex(enum_proc, flags, param, reserved);
		}

		return __acrt_lock_and_call(__acrt_locale_lock, [&]() -> BOOL
		{
			return enum_system_locales_ex_nolock(enum_proc);
		});
	}
}

__if_exists(try_get_FlsAlloc)
{
	extern "C" DWORD WINAPI __acrt_FlsAlloc(PFLS_CALLBACK_FUNCTION const callback)
	{
		if (auto const fls_alloc = try_get_FlsAlloc())
		{
			return fls_alloc(callback);
		}

		return TlsAlloc();
	}
}

__if_exists(try_get_FlsFree)
{
	extern "C" BOOL WINAPI __acrt_FlsFree(DWORD const fls_index)
	{
		if (auto const fls_free = try_get_FlsFree())
		{
			return fls_free(fls_index);
		}

		return TlsFree(fls_index);
	}
}

__if_exists(try_get_FlsGetValue)
{
	extern "C" PVOID WINAPI __acrt_FlsGetValue(DWORD const fls_index)
	{
		if (auto const fls_get_value = try_get_FlsGetValue())
		{
			return fls_get_value(fls_index);
		}

		return TlsGetValue(fls_index);
	}
}

__if_exists(try_get_FlsSetValue)
{
	extern "C" BOOL WINAPI __acrt_FlsSetValue(DWORD const fls_index, PVOID const fls_data)
	{
		if (auto const fls_set_value = try_get_FlsSetValue())
		{
			return fls_set_value(fls_index, fls_data);
		}

		return TlsSetValue(fls_index, fls_data);
	}
}

__if_exists(try_get_GetDateFormatEx)
{
	extern "C" int WINAPI __acrt_GetDateFormatEx(
		LPCWSTR           const locale_name,
		DWORD             const flags,
		SYSTEMTIME CONST* const date,
		LPCWSTR           const format,
		LPWSTR            const buffer,
		int               const buffer_count,
		LPCWSTR           const calendar
	)
	{
		if (auto const get_date_format_ex = try_get_GetDateFormatEx())
		{
			return get_date_format_ex(locale_name, flags, date, format, buffer, buffer_count, calendar);
		}

		return GetDateFormatW(__acrt_LocaleNameToLCID(locale_name, 0), flags, date, format, buffer, buffer_count);
	}
}

__if_exists(try_get_GetEnabledXStateFeatures)
{
	extern "C" DWORD64 WINAPI __acrt_GetEnabledXStateFeatures()
	{
		if (auto const get_enabled_xstate_features = try_get_GetEnabledXStateFeatures())
		{
			return get_enabled_xstate_features();
		}

		abort(); // No fallback; callers should check availablility before calling
	}
}

#if 0
extern "C" int WINAPI __acrt_GetLocaleInfoEx(
	LPCWSTR const locale_name,
	LCTYPE  const lc_type,
	LPWSTR  const data,
	int     const data_count
)
{
	/*if (auto const get_locale_info_ex = try_get_GetLocaleInfoEx())
	{
		return get_locale_info_ex(locale_name, lc_type, data, data_count);
	}*/

	return GetLocaleInfoW(__acrt_LocaleNameToLCID(locale_name, 0), lc_type, data, data_count);
}
#endif

#if _CRT_NTDDI_MIN < NTDDI_WIN7
extern "C" VOID WINAPI __acrt_GetSystemTimePreciseAsFileTime_advanced(LPFILETIME const system_time)
{
	if (auto const get_system_time_precise_as_file_time = try_get_GetSystemTimePreciseAsFileTime())
	{
		return get_system_time_precise_as_file_time(system_time);
	}

	return GetSystemTimeAsFileTime(system_time);
}
#endif

#if 0
extern "C" int WINAPI __acrt_GetTimeFormatEx(
    LPCWSTR           const locale_name,
    DWORD             const flags,
    SYSTEMTIME CONST* const time,
    LPCWSTR           const format,
    LPWSTR            const buffer,
    int               const buffer_count
    )
{

   /* if (auto const get_time_format_ex = try_get_GetTimeFormatEx())
    {
        return get_time_format_ex(locale_name, flags, time, format, buffer, buffer_count);
    }*/

    return GetTimeFormatW(__acrt_LocaleNameToLCID(locale_name, 0), flags, time, format, buffer, buffer_count);
}
#endif

__if_exists(try_get_GetUserDefaultLocaleName)
{
	extern "C" int WINAPI __acrt_GetUserDefaultLocaleName(
		LPWSTR const locale_name,
		int    const locale_name_count
	)
	{
		if (auto const get_user_default_locale_name = try_get_GetUserDefaultLocaleName())
		{
			return get_user_default_locale_name(locale_name, locale_name_count);
		}

		return __acrt_LCIDToLocaleName(GetUserDefaultLCID(), locale_name, locale_name_count, 0);
	}
}

__if_exists(try_get_GetXStateFeaturesMask)
{
	extern "C" BOOL WINAPI __acrt_GetXStateFeaturesMask(
		PCONTEXT const context,
		PDWORD64 const feature_mask
	)
	{
		if (auto const get_xstate_features_mask = try_get_GetXStateFeaturesMask())
		{
			return get_xstate_features_mask(context, feature_mask);
		}

		abort(); // No fallback; callers should check availablility before calling
	}
}

__if_exists(try_get_InitializeCriticalSectionEx)
{
	extern "C" BOOL WINAPI __acrt_InitializeCriticalSectionEx(
		LPCRITICAL_SECTION const critical_section,
		DWORD              const spin_count,
		DWORD              const flags
	)
	{
		if (auto const initialize_critical_section_ex = try_get_InitializeCriticalSectionEx())
		{
			return initialize_critical_section_ex(critical_section, spin_count, flags);
		}

		return InitializeCriticalSectionAndSpinCount(critical_section, spin_count);
	}
}

#if 0
extern "C" BOOL WINAPI __acrt_IsValidLocaleName(LPCWSTR const locale_name)
{

   /* if (auto const is_valid_locale_name = try_get_IsValidLocaleName())
    {
        return is_valid_locale_name(locale_name);
    }*/

    return IsValidLocale(__acrt_LocaleNameToLCID(locale_name, 0), LCID_INSTALLED);
}
#endif

#if 0
extern "C" int WINAPI __acrt_LCMapStringEx(
    LPCWSTR          const locale_name,
    DWORD            const flags,
    LPCWSTR          const source,
    int              const source_count,
    LPWSTR           const destination,
    int              const destination_count,
    LPNLSVERSIONINFO const version,
    LPVOID           const reserved,
    LPARAM           const sort_handle
    )
{
    //if (auto const lc_map_string_ex = try_get_LCMapStringEx())
    //{
    //    return lc_map_string_ex(locale_name, flags, source, source_count, destination, destination_count, version, reserved, sort_handle);
    //}
//#pragma warning(disable:__WARNING_PRECONDITION_NULLTERMINATION_VIOLATION) // 26035 LCMapStringW annotation is presently incorrect 11/26/2014 Jaykrell
    return LCMapStringW(__acrt_LocaleNameToLCID(locale_name, 0), flags, source, source_count, destination, destination_count);
}
#endif

#if 0
extern "C" int WINAPI __acrt_LCIDToLocaleName(
	LCID   const locale,
	LPWSTR const name,
	int    const name_count,
	DWORD  const flags
)
{
	if (auto const lcid_to_locale_name = try_get_LCIDToLocaleName())
	{
		return lcid_to_locale_name(locale, name, name_count, flags);
	}

	return __acrt_DownlevelLCIDToLocaleName(locale, name, name_count);
}
#endif

#if 0
extern "C" LCID WINAPI __acrt_LocaleNameToLCID(
	LPCWSTR const name,
	DWORD   const flags
)
{
	if (auto const locale_name_to_lcid = try_get_LocaleNameToLCID())
	{
		return locale_name_to_lcid(name, flags);
	}

	return __acrt_DownlevelLocaleNameToLCID(name);
}
#endif

__if_exists(try_get_LocateXStateFeature)
{
	extern "C" PVOID WINAPI __acrt_LocateXStateFeature(
		PCONTEXT const content,
		DWORD    const feature_id,
		PDWORD   const length
	)
	{
		if (auto const locate_xstate_feature = try_get_LocateXStateFeature())
		{
			return locate_xstate_feature(content, feature_id, length);
		}

		abort(); // No fallback; callers should check availablility before calling
	}
}

__if_exists(try_get_MessageBoxA)
{
	extern "C" int WINAPI __acrt_MessageBoxA(
		HWND   const hwnd,
		LPCSTR const text,
		LPCSTR const caption,
		UINT   const type
	)
	{
		if (auto const message_box_a = try_get_MessageBoxA())
		{
			return message_box_a(hwnd, text, caption, type);
		}

		abort(); // No fallback; callers should check availablility before calling
	}
}

__if_exists(try_get_MessageBoxW)
{
	extern "C" int WINAPI __acrt_MessageBoxW(
		HWND    const hwnd,
		LPCWSTR const text,
		LPCWSTR const caption,
		UINT    const type
	)
	{
		if (auto const message_box_w = try_get_MessageBoxW())
		{
			return message_box_w(hwnd, text, caption, type);
		}

		abort(); // No fallback; callers should check availablility before calling
	}
}

__if_exists(try_get_SystemFunction036)
{
	extern "C" BOOLEAN WINAPI __acrt_RtlGenRandom(
		PVOID const buffer,
		ULONG const buffer_count
	)
	{
		if (auto const rtl_gen_random = try_get_SystemFunction036())
		{
			return rtl_gen_random(buffer, buffer_count);
		}

		abort(); // No fallback (this function should exist)
	}
}

__if_exists(try_get_RoInitialize)
{
	extern "C" HRESULT WINAPI __acrt_RoInitialize(RO_INIT_TYPE const init_type)
	{
		if (auto const ro_initialize = try_get_RoInitialize())
		{
			return ro_initialize(init_type);
		}

		return S_OK; // No fallback (this is a best-effort wrapper)
	}
}

__if_exists(try_get_RoUninitialize)
{
	extern "C" void WINAPI __acrt_RoUninitialize()
	{
		if (auto const ro_uninitialize = try_get_RoUninitialize())
		{
			return ro_uninitialize();
		}

		// No fallback (this is a best-effort wrapper)
	}
}

__if_exists(try_get_AppPolicyGetProcessTerminationMethod)
{
	extern "C" LONG WINAPI __acrt_AppPolicyGetProcessTerminationMethodInternal(_Out_ AppPolicyProcessTerminationMethod* policy)
	{
		if (auto const app_policy_get_process_terminaton_method_claims = try_get_AppPolicyGetProcessTerminationMethod())
		{
			return app_policy_get_process_terminaton_method_claims(GetCurrentThreadEffectiveToken(), policy);
		}

		return STATUS_NOT_FOUND;
	}
}

__if_exists(try_get_AppPolicyGetThreadInitializationType)
{
	extern "C" LONG WINAPI __acrt_AppPolicyGetThreadInitializationTypeInternal(_Out_ AppPolicyThreadInitializationType* policy)
	{
		if (auto const app_policy_get_thread_initialization_type_claims = try_get_AppPolicyGetThreadInitializationType())
		{
			return app_policy_get_thread_initialization_type_claims(GetCurrentThreadEffectiveToken(), policy);
		}

		return STATUS_NOT_FOUND;
	}
}

__if_exists(try_get_AppPolicyGetShowDeveloperDiagnostic)
{
	extern "C" LONG WINAPI __acrt_AppPolicyGetShowDeveloperDiagnosticInternal(_Out_ AppPolicyShowDeveloperDiagnostic* policy)
	{
		if (auto const app_policy_get_show_developer_diagnostic_claims = try_get_AppPolicyGetShowDeveloperDiagnostic())
		{
			return app_policy_get_show_developer_diagnostic_claims(GetCurrentThreadEffectiveToken(), policy);
		}

		return STATUS_NOT_FOUND;
	}
}

__if_exists(try_get_AppPolicyGetWindowingModel)
{
	extern "C" LONG WINAPI __acrt_AppPolicyGetWindowingModelInternal(_Out_ AppPolicyWindowingModel* policy)
	{
		if (auto const app_policy_get_windowing_model_claims = try_get_AppPolicyGetWindowingModel())
		{
			return app_policy_get_windowing_model_claims(GetCurrentThreadEffectiveToken(), policy);
		}

		return STATUS_NOT_FOUND;
	}
}

__if_exists(try_get_SetThreadStackGuarantee)
{
	extern "C" BOOL WINAPI __acrt_SetThreadStackGuarantee(PULONG const stack_size_in_bytes)
	{
		if (auto const set_thread_stack_guarantee = try_get_SetThreadStackGuarantee())
		{
			return set_thread_stack_guarantee(stack_size_in_bytes);
		}

		return FALSE;
	}
}



//extern "C" bool __cdecl __acrt_can_show_message_box()
//{
//    bool can_show_message_box = false;
//    if (__acrt_get_windowing_model_policy() == windowing_model_policy_hwnd
//        && try_get_MessageBoxA() != nullptr
//        && try_get_MessageBoxW() != nullptr)
//    {
//        can_show_message_box = true;
//    }
//    return can_show_message_box;
//}

//extern "C" bool __cdecl __acrt_can_use_vista_locale_apis()
//{
//    return try_get_CompareStringEx() != nullptr;
//}

// This function simply attempts to get each of the locale-related APIs.  This
// allows a caller to "pre-load" the modules in which these APIs are hosted.  We
// use this in the _wsetlocale implementation to avoid calls to LoadLibrary while
// the locale lock is held.
extern "C" void __cdecl __acrt_eagerly_load_locale_apis()
{
	__if_exists(try_get_AreFileApisANSI)
	{
		try_get_AreFileApisANSI();
	}

	__if_exists(try_get_CompareStringEx)
	{
		try_get_CompareStringEx();
	}

	__if_exists(try_get_EnumSystemLocalesEx)
	{
		try_get_EnumSystemLocalesEx();
	}

	__if_exists(try_get_GetDateFormatEx)
	{
		try_get_GetDateFormatEx();
	}

	__if_exists(try_get_GetLocaleInfoEx)
	{
		try_get_GetLocaleInfoEx();
	}

	__if_exists(try_get_GetTimeFormatEx)
	{
		try_get_GetTimeFormatEx();
	}

	__if_exists(try_get_GetUserDefaultLocaleName)
	{
		try_get_GetUserDefaultLocaleName();
	}

	__if_exists(try_get_IsValidLocaleName)
	{
		try_get_IsValidLocaleName();
	}

	__if_exists(try_get_LCMapStringEx)
	{
		try_get_LCMapStringEx();
	}

	__if_exists(try_get_LCIDToLocaleName)
	{
		try_get_LCIDToLocaleName();
	}

	__if_exists(try_get_LocaleNameToLCID)
	{
		try_get_LocaleNameToLCID();
	}
}

__if_exists(try_get_LocateXStateFeature)
{
	extern "C" bool __cdecl __acrt_can_use_xstate_apis()
	{
		return try_get_LocateXStateFeature() != nullptr;
	}
}

__if_exists(try_get_GetActiveWindow)
{
	extern "C" HWND __cdecl __acrt_get_parent_window()
	{
		auto const get_active_window = try_get_GetActiveWindow();
		if (!get_active_window)
		{
			return nullptr;
		}

		HWND const active_window = get_active_window();
		if (!active_window)
		{
			return nullptr;
		}

		auto const get_last_active_popup = try_get_GetLastActivePopup();
		if (!get_last_active_popup)
		{
			return active_window;
		}

		return get_last_active_popup(active_window);
	}
}

__if_exists(try_get_GetProcessWindowStation)
{
	extern "C" bool __cdecl __acrt_is_interactive()
	{
		auto const get_process_window_station = try_get_GetProcessWindowStation();
		if (!get_process_window_station)
		{
			return true;
		}

		auto const get_user_object_information = try_get_GetUserObjectInformationW();
		if (!get_user_object_information)
		{
			return true;
		}

		HWINSTA const hwinsta = get_process_window_station();
		if (!hwinsta)
		{
			return false;
		}

		USEROBJECTFLAGS uof{};
		if (!get_user_object_information(hwinsta, UOI_FLAGS, &uof, sizeof(uof), nullptr))
		{
			return false;
		}

		if ((uof.dwFlags & WSF_VISIBLE) == 0)
		{
			return false;
		}

		return true;
	}
}


#ifdef _ATL_XP_TARGETING
EXTERN_C BOOL WINAPI __crtInitOnceExecuteOnce(
	_Inout_     PINIT_ONCE    InitOnce,
	_In_        PINIT_ONCE_FN InitFn,
	_Inout_opt_ PVOID         Parameter,
	_Out_opt_   LPVOID        *Context
)
{
	if(auto const pInitOnceExecuteOnce = try_get_InitOnceExecuteOnce())
	{
		return pInitOnceExecuteOnce(InitOnce, InitFn, Parameter, Context);
	}


	//Ŀ��ϵͳ��֧�֣��л���XP����ģʽ
	for (;;)
	{
		switch (InterlockedCompareExchange((volatile size_t*)InitOnce, 1, 0))
		{
		case 2:
			//ͬ����ɣ����������߳��Ѿ������ɹ�
			return TRUE;
			break;
		case 1:
			//��δ��ɣ������ȴ�
			Sleep(0);
			break;
		case 0:
			//ͬ����ɣ�ȷ���Ǵ�������ָ������
			{
			BOOL bRet = InitFn(InitOnce, Parameter, Context) == TRUE;
				//�����������

			if (InterlockedExchange((volatile size_t*)InitOnce, bRet ? 2 : 0)==1)
			{
				return bRet;
			}

			}
		default:
			//ͬ����ɣ����Ƿ�������
			goto __Error;
			break;
		}
	}

__Error:

	SetLastError(ERROR_INVALID_DATA);
	return FALSE;
}
#endif

#ifdef _ATL_XP_TARGETING
EXTERN_C VOID WINAPI __crtInitializeConditionVariable(
	_Out_ PCONDITION_VARIABLE ConditionVariable
)
{
	if (auto const pInitializeConditionVariable = try_get_InitializeConditionVariable())
	{
		return pInitializeConditionVariable(ConditionVariable);
	}
	else
	{
		//�жϳ���
		__debugbreak();

		//ǿ���˳�
		abort();
	}
}
#endif

#ifdef _ATL_XP_TARGETING
EXTERN_C BOOL WINAPI __crtSleepConditionVariableCS(
	_Inout_ PCONDITION_VARIABLE ConditionVariable,
	_Inout_ PCRITICAL_SECTION   CriticalSection,
	_In_    DWORD               dwMilliseconds
)
{
	if (auto const pSleepConditionVariableCS = try_get_SleepConditionVariableCS())
	{
		return pSleepConditionVariableCS(ConditionVariable, CriticalSection, dwMilliseconds);
	}
	else
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}
}
#endif

#ifdef _ATL_XP_TARGETING
EXTERN_C void WINAPI __crtWakeConditionVariable(
	_Inout_ PCONDITION_VARIABLE ConditionVariable
)
{
	if (auto const pWakeConditionVariable = try_get_WakeConditionVariable())
	{
		return pWakeConditionVariable(ConditionVariable);
	}
	else
	{
		//�жϳ���
		__debugbreak();

		//ǿ���˳�
		abort();
	}
}
#endif

#ifdef _ATL_XP_TARGETING
EXTERN_C VOID __crtWakeAllConditionVariable(
	_Inout_ PCONDITION_VARIABLE ConditionVariable
)
{
	if (auto const pWakeAllConditionVariable = try_get_WakeAllConditionVariable())
	{
		return pWakeAllConditionVariable(ConditionVariable);
	}
	else
	{
		//�жϳ���
		__debugbreak();

		//ǿ���˳�
		abort();
	}
}
#endif

#ifdef _ATL_XP_TARGETING
EXTERN_C VOID WINAPI __crtInitializeSRWLock(
	_Out_ PSRWLOCK SRWLock
)
{
	if (auto const pInitializeSRWLock = try_get_InitializeSRWLock())
	{
		return pInitializeSRWLock(SRWLock);
	}
	else
	{
		//�жϳ���
		__debugbreak();

		//ǿ���˳�
		abort();
	}
}
#endif

#ifdef _ATL_XP_TARGETING
EXTERN_C VOID WINAPI __crtAcquireSRWLockExclusive(
	_Inout_ PSRWLOCK SRWLock
)
{
	if (auto const pAcquireSRWLockExclusive = try_get_AcquireSRWLockExclusive())
	{
		return pAcquireSRWLockExclusive(SRWLock);
	}
	else
	{
		//�жϳ���
		__debugbreak();

		//ǿ���˳�
		abort();
	}
}
#endif

#if _CRT_NTDDI_MIN < NTDDI_WIN7
EXTERN_C BOOLEAN WINAPI __crtTryAcquireSRWLockExclusive(
	_Inout_ PSRWLOCK SRWLock
)
{
	if (auto const pTryAcquireSRWLockExclusive = try_get_TryAcquireSRWLockExclusive())
	{
		return pTryAcquireSRWLockExclusive(SRWLock);
	}
	else
	{
		//�жϳ���
		__debugbreak();

		//ǿ���˳�
		abort();
	}
}
#endif

#ifdef _ATL_XP_TARGETING
EXTERN_C VOID WINAPI __crtReleaseSRWLockExclusive(
	_Inout_ PSRWLOCK SRWLock
)
{
	if (auto const pReleaseSRWLockExclusive = try_get_ReleaseSRWLockExclusive())
	{
		return pReleaseSRWLockExclusive(SRWLock);
	}
	else
	{
		//�жϳ���
		__debugbreak();

		//ǿ���˳�
		abort();
	}
}
#endif


#ifdef _ATL_XP_TARGETING
EXTERN_C BOOL WINAPI __crtSleepConditionVariableSRW(
	_Inout_ PCONDITION_VARIABLE ConditionVariable,
	_Inout_ PSRWLOCK            SRWLock,
	_In_    DWORD               dwMilliseconds,
	_In_    ULONG               Flags
)
{
	if (auto const pSleepConditionVariableSRW = try_get_SleepConditionVariableSRW())
	{
		return pSleepConditionVariableSRW(ConditionVariable, SRWLock, dwMilliseconds, Flags);
	}
	else
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}
}
#endif

#if _CRT_NTDDI_MIN < NTDDI_WIN7
EXTERN_C BOOLEAN __cdecl __crt_are_win7_sync_apis_available()
{

	// TryAcquireSRWLockExclusive ONLY available on Win7+
	//DYNAMICGETCACHEDFUNCTION(KERNEL32, PFNTRYACQUIRESRWLOCKEXCLUSIVE, TryAcquireSRWLockExclusive, pfTryAcquireSRWLockExclusive);
	return try_get_TryAcquireSRWLockExclusive() != nullptr;
}
#endif

#ifdef _ATL_XP_TARGETING
EXTERN_C BOOLEAN __cdecl __crt_are_vista_sync_apis_available()
{
	// InitializeConditionVariable ONLY available on Vista+
	//DYNAMICGETCACHEDFUNCTION(KERNEL32, PFNINITIALIZECONDITIONVARIABLE, InitializeConditionVariable, pfInitializeConditionVariable);
	return try_get_InitializeConditionVariable() != nullptr;
}
#endif


#ifdef _ATL_XP_TARGETING
EXTERN_C BOOLEAN __cdecl __crt__Is_vista_threadpool_supported()
{
	return try_get_CreateThreadpoolWork() != nullptr;
}
#endif

__if_exists(try_get_FreeLibraryWhenCallbackReturns)
{
	EXTERN_C VOID WINAPI __crtFreeLibraryWhenCallbackReturns(
			_Inout_ PTP_CALLBACK_INSTANCE pci,
			_In_ HMODULE mod
		)
	{
		if (auto pFreeLibraryWhenCallbackReturns = try_get_FreeLibraryWhenCallbackReturns())
		{
			pFreeLibraryWhenCallbackReturns(pci, mod);
		}
		else
		{
			//�жϳ���
			__debugbreak();

			//ǿ���˳�
			abort();
		}
	}
}

__if_exists(try_get_CloseThreadpoolWork)
{
	EXTERN_C VOID WINAPI __crtCloseThreadpoolWork(
			_Inout_ PTP_WORK pwk
		)
	{
		if (auto pCloseThreadpoolWork = try_get_CloseThreadpoolWork())
		{
			pCloseThreadpoolWork(pwk);
		}
		else
		{
			//�жϳ���
			__debugbreak();

			//ǿ���˳�
			abort();
		}
	}
}

__if_exists(try_get_SubmitThreadpoolWork)
{
	EXTERN_C VOID WINAPI __crtSubmitThreadpoolWork(
			_Inout_ PTP_WORK pwk
		)
	{
		if (auto pSubmitThreadpoolWork = try_get_SubmitThreadpoolWork())
		{
			pSubmitThreadpoolWork(pwk);
		}
		else
		{
			//�жϳ���
			__debugbreak();

			//ǿ���˳�
			abort();
		}
	}
}

__if_exists(try_get_CreateThreadpoolWork)
{
	EXTERN_C PTP_WORK WINAPI
		__crtCreateThreadpoolWork(
			_In_ PTP_WORK_CALLBACK pfnwk,
			_Inout_opt_ PVOID pv,
			_In_opt_ PTP_CALLBACK_ENVIRON pcbe
		)
	{
		if (auto pCreateThreadpoolWork = try_get_CreateThreadpoolWork())
		{
			return pCreateThreadpoolWork(pfnwk, pv, pcbe);
		}
		else
		{
			SetLastError(ERROR_INVALID_PARAMETER);
			return nullptr;
		}
	}
}


#if defined _ATL_XP_TARGETING && defined _X86_

EXTERN_C DWORD WINAPI __crtGetCurrentProcessorNumber(void)
{
	if (auto pGetCurrentProcessorNumber = try_get_GetCurrentProcessorNumber())
	{
		return pGetCurrentProcessorNumber();
	}
	else
	{
		//�����֧�ִ˽ӿڣ���ô�ٶ��ǵ���
		return 0;
	}
}

#endif

#ifdef _ATL_XP_TARGETING
EXTERN_C VOID WINAPI __crtFlushProcessWriteBuffers(void)
{
	if (auto pFlushProcessWriteBuffers = try_get_FlushProcessWriteBuffers())
	{
		return pFlushProcessWriteBuffers();
	}
	else
	{
		//�жϳ���
		__debugbreak();

		//ǿ���˳�
		abort();
	}
}
#endif

#ifdef _ATL_XP_TARGETING
EXTERN_C ULONGLONG WINAPI __crtGetTickCount64(VOID)
{
	if (auto pGetTickCount64 = try_get_GetTickCount64())
	{
		return pGetTickCount64();
	}
	else
	{
		return GetTickCount();
	}
}
#endif

#ifdef _ATL_XP_TARGETING
EXTERN_C VOID WINAPI __crtSetThreadpoolTimer(
	_Inout_ PTP_TIMER pti,
	_In_opt_ PFILETIME pftDueTime,
	_In_ DWORD msPeriod,
	_In_opt_ DWORD msWindowLength
)
{
	if (auto pSetThreadpoolTimer = try_get_SetThreadpoolTimer())
	{
		return pSetThreadpoolTimer(pti, pftDueTime, msPeriod, msWindowLength);
	}
	else
	{
		//�жϳ���
		__debugbreak();

		//ǿ���˳�
		abort();
	}
}


EXTERN_C VOID WINAPI __crtSetThreadpoolWait(
	_Inout_ PTP_WAIT pwa,
	_In_opt_ HANDLE h,
	_In_opt_ PFILETIME pftTimeout
)
{
	if (auto pSetThreadpoolWait = try_get_SetThreadpoolWait())
	{
		return pSetThreadpoolWait(pwa, h, pftTimeout);
	}
	else
	{
		//�жϳ���
		__debugbreak();

		//ǿ���˳�
		abort();
	}
}

EXTERN_C VOID WINAPI __crtCloseThreadpoolWait(
	_Inout_ PTP_WAIT pwa
)
{
	if (auto pCloseThreadpoolWait = try_get_CloseThreadpoolWait())
	{
		return pCloseThreadpoolWait(pwa);
	}
	else
	{
		//�жϳ���
		__debugbreak();

		//ǿ���˳�
		abort();
	}
}

EXTERN_C VOID WINAPI __crtWaitForThreadpoolTimerCallbacks(
	_Inout_ PTP_TIMER pti,
	_In_ BOOL fCancelPendingCallbacks
)
{
	if (auto pWaitForThreadpoolTimerCallbacks = try_get_WaitForThreadpoolTimerCallbacks())
	{
		return pWaitForThreadpoolTimerCallbacks(pti, fCancelPendingCallbacks);
	}
	else
	{
		//�жϳ���
		__debugbreak();

		//ǿ���˳�
		abort();
	}
}

EXTERN_C PTP_WAIT WINAPI __crtCreateThreadpoolWait(
	_In_ PTP_WAIT_CALLBACK pfnwa,
	_Inout_opt_ PVOID pv,
	_In_opt_ PTP_CALLBACK_ENVIRON pcbe
)
{
	if (auto pCreateThreadpoolWait = try_get_CreateThreadpoolWait())
	{
		return pCreateThreadpoolWait(pfnwa, pv, pcbe);
	}
	else
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return nullptr;
	}
}


EXTERN_C VOID WINAPI __crtCloseThreadpoolTimer(
	_Inout_ PTP_TIMER pti
	)
{
	if (auto pCloseThreadpoolTimer = try_get_CloseThreadpoolTimer())
	{
		return pCloseThreadpoolTimer(pti);
	}
	else
	{
		//�жϳ���
		__debugbreak();

		//ǿ���˳�
		abort();
	}
}

EXTERN_C PTP_TIMER WINAPI __crtCreateThreadpoolTimer(
	_In_ PTP_TIMER_CALLBACK pfnti,
	_Inout_opt_ PVOID pv,
	_In_opt_ PTP_CALLBACK_ENVIRON pcbe
	)
{
	if (auto pCreateThreadpoolTimer = try_get_CreateThreadpoolTimer())
	{
		return pCreateThreadpoolTimer(pfnti, pv, pcbe);
	}
	else
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return nullptr;
	}
}

#endif

#if _CRT_NTDDI_MIN < 0x05020000
EXTERN_C BOOL
WINAPI
__ltlGetLogicalProcessorInformation(
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION Buffer,
	PDWORD ReturnedLength
    )
{
	if (auto pGetLogicalProcessorInformation = try_get_GetLogicalProcessorInformation())
	{
		return pGetLogicalProcessorInformation(Buffer, ReturnedLength);
	}
	else
	{
		SetLastError(ERROR_INVALID_FUNCTION);
		return FALSE;
	}
}
#endif

#if _CRT_NTDDI_MIN < 0x05020000
EXTERN_C BOOL
WINAPI
__ltlGetNumaHighestNodeNumber(
    _Out_ PULONG HighestNodeNumber
    )
{
	if (auto pGetNumaHighestNodeNumber = try_get_GetNumaHighestNodeNumber())
	{
		return pGetNumaHighestNodeNumber(HighestNodeNumber);
	}
	else
	{
		//��֧��ʱʼ�ռٶ�ֻ��һ��NUMA�ڵ�
		*HighestNodeNumber = 0;

		return TRUE;
	}
}
#endif

namespace
{
	typedef struct _UNICODE_STRING {
		USHORT Length;
		USHORT MaximumLength;
		PWSTR  Buffer;
	} UNICODE_STRING, *PUNICODE_STRING;
	typedef const UNICODE_STRING *PCUNICODE_STRING;

	typedef struct _PEB_LDR_DATA * PPEB_LDR_DATA;
	typedef struct _RTL_USER_PROCESS_PARAMETERS * PRTL_USER_PROCESS_PARAMETERS;


	typedef struct _PEB
	{
		BOOLEAN InheritedAddressSpace;
		BOOLEAN ReadImageFileExecOptions;
		BOOLEAN BeingDebugged;
		union
		{
			BOOLEAN BitField;
			struct
			{
				BOOLEAN ImageUsesLargePages : 1;
				BOOLEAN IsProtectedProcess : 1;
				BOOLEAN IsImageDynamicallyRelocated : 1;
				BOOLEAN SkipPatchingUser32Forwarders : 1;
				BOOLEAN IsPackagedProcess : 1;
				BOOLEAN IsAppContainer : 1;
				BOOLEAN IsProtectedProcessLight : 1;
				BOOLEAN IsLongPathAwareProcess : 1;
			};
		};

		HANDLE Mutant;

		PVOID ImageBaseAddress;
		PPEB_LDR_DATA Ldr;
		PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
		PVOID SubSystemData;
		PVOID ProcessHeap;
		PRTL_CRITICAL_SECTION FastPebLock;
		PVOID AtlThunkSListPtr;
		PVOID IFEOKey;
		union
		{
			ULONG CrossProcessFlags;
			struct
			{
				ULONG ProcessInJob : 1;
				ULONG ProcessInitializing : 1;
				ULONG ProcessUsingVEH : 1;
				ULONG ProcessUsingVCH : 1;
				ULONG ProcessUsingFTH : 1;
				ULONG ReservedBits0 : 27;
			};
		};
		union
		{
			PVOID KernelCallbackTable;
			PVOID UserSharedInfoPtr;
		};
		ULONG SystemReserved[1];
		ULONG AtlThunkSListPtr32;
		PVOID ApiSetMap;
		ULONG TlsExpansionCounter;
		PVOID TlsBitmap;
		ULONG TlsBitmapBits[2];
		PVOID ReadOnlySharedMemoryBase;
		PVOID HotpatchInformation;
		PVOID *ReadOnlyStaticServerData;
		PVOID AnsiCodePageData;
		PVOID OemCodePageData;
		PVOID UnicodeCaseTableData;

		ULONG NumberOfProcessors;
		ULONG NtGlobalFlag;

		LARGE_INTEGER CriticalSectionTimeout;
		SIZE_T HeapSegmentReserve;
		SIZE_T HeapSegmentCommit;
		SIZE_T HeapDeCommitTotalFreeThreshold;
		SIZE_T HeapDeCommitFreeBlockThreshold;

		ULONG NumberOfHeaps;
		ULONG MaximumNumberOfHeaps;
		PVOID *ProcessHeaps;

		PVOID GdiSharedHandleTable;
		PVOID ProcessStarterHelper;
		ULONG GdiDCAttributeList;

		PRTL_CRITICAL_SECTION LoaderLock;

		ULONG OSMajorVersion;
		ULONG OSMinorVersion;
		USHORT OSBuildNumber;
		USHORT OSCSDVersion;
		ULONG OSPlatformId;
		ULONG ImageSubsystem;
		ULONG ImageSubsystemMajorVersion;
		ULONG ImageSubsystemMinorVersion;
		ULONG_PTR ActiveProcessAffinityMask;
#ifdef _AMD64_
		ULONG GdiHandleBuffer[60];
#else
		ULONG GdiHandleBuffer[34];
#endif
		PVOID PostProcessInitRoutine;

		PVOID TlsExpansionBitmap;
		ULONG TlsExpansionBitmapBits[32];

		ULONG SessionId;

		ULARGE_INTEGER AppCompatFlags;
		ULARGE_INTEGER AppCompatFlagsUser;
		PVOID pShimData;
		PVOID AppCompatInfo;

		UNICODE_STRING CSDVersion;

		PVOID ActivationContextData;
		PVOID ProcessAssemblyStorageMap;
		PVOID SystemDefaultActivationContextData;
		PVOID SystemAssemblyStorageMap;

		SIZE_T MinimumStackCommit;

		PVOID *FlsCallback;
		LIST_ENTRY FlsListHead;
		PVOID FlsBitmap;
		ULONG FlsBitmapBits[FLS_MAXIMUM_AVAILABLE / (sizeof(ULONG) * 8)];
		ULONG FlsHighIndex;

		PVOID WerRegistrationData;
		PVOID WerShipAssertPtr;
		PVOID pContextData;
		PVOID pImageHeaderHash;
		union
		{
			ULONG TracingFlags;
			struct
			{
				ULONG HeapTracingEnabled : 1;
				ULONG CritSecTracingEnabled : 1;
				ULONG LibLoaderTracingEnabled : 1;
				ULONG SpareTracingBits : 29;
			};
		};
		ULONGLONG CsrServerReadOnlySharedMemoryBase;
		PVOID TppWorkerpListLock;
		LIST_ENTRY TppWorkerpList;
		PVOID WaitOnAddressHashTable[128];
	} PEB, *PPEB;

	typedef struct _TEB_ACTIVE_FRAME *PTEB_ACTIVE_FRAME;

	typedef struct _CLIENT_ID {
		HANDLE UniqueProcess;
		HANDLE UniqueThread;
	} CLIENT_ID, *PCLIENT_ID;

	typedef struct _GDI_TEB_BATCH
	{
		ULONG Offset;
		HDC hdc;
		ULONG buffer[310];
	} GDI_TEB_BATCH;


	typedef struct _TEB
	{
		NT_TIB NtTib;

		PVOID EnvironmentPointer;
		CLIENT_ID ClientId;
		PVOID ActiveRpcHandle;
		PVOID ThreadLocalStoragePointer;
		PPEB ProcessEnvironmentBlock;

		ULONG LastErrorValue;
		ULONG CountOfOwnedCriticalSections;
		PVOID CsrClientThread;
		PVOID Win32ThreadInfo;
		ULONG User32Reserved[26];
		ULONG UserReserved[5];
		PVOID WOW32Reserved;
		LCID CurrentLocale;
		ULONG FpSoftwareStatusRegister;
		PVOID ReservedForDebuggerInstrumentation[16];
		PVOID SystemReserved1[37];
		UCHAR WorkingOnBehalfTicket[8];
		NTSTATUS ExceptionCode;

		PVOID ActivationContextStackPointer;
		ULONG_PTR InstrumentationCallbackSp;
		ULONG_PTR InstrumentationCallbackPreviousPc;
		ULONG_PTR InstrumentationCallbackPreviousSp;
		ULONG TxFsContext;

		BOOLEAN InstrumentationCallbackDisabled;
		GDI_TEB_BATCH GdiTebBatch;
		CLIENT_ID RealClientId;
		HANDLE GdiCachedProcessHandle;
		ULONG GdiClientPID;
		ULONG GdiClientTID;
		PVOID GdiThreadLocalInfo;
		ULONG_PTR Win32ClientInfo[62];
		PVOID glDispatchTable[233];
		ULONG_PTR glReserved1[29];
		PVOID glReserved2;
		PVOID glSectionInfo;
		PVOID glSection;
		PVOID glTable;
		PVOID glCurrentRC;
		PVOID glContext;

		NTSTATUS LastStatusValue;
		UNICODE_STRING StaticUnicodeString;
		WCHAR StaticUnicodeBuffer[261];

		PVOID DeallocationStack;
		PVOID TlsSlots[64];
		LIST_ENTRY TlsLinks;

		PVOID Vdm;
		PVOID ReservedForNtRpc;
		PVOID DbgSsReserved[2];

		ULONG HardErrorMode;
#ifdef _WIN64
		PVOID Instrumentation[11];
#else
		PVOID Instrumentation[9];
#endif
		GUID ActivityId;

		PVOID SubProcessTag;
		PVOID PerflibData;
		PVOID EtwTraceData;
		PVOID WinSockData;
		ULONG GdiBatchCount;

		union
		{
			PROCESSOR_NUMBER CurrentIdealProcessor;
			ULONG IdealProcessorValue;
			struct
			{
				UCHAR ReservedPad0;
				UCHAR ReservedPad1;
				UCHAR ReservedPad2;
				UCHAR IdealProcessor;
			};
		};

		ULONG GuaranteedStackBytes;
		PVOID ReservedForPerf;
		PVOID ReservedForOle;
		ULONG WaitingOnLoaderLock;
		PVOID SavedPriorityState;
		ULONG_PTR ReservedForCodeCoverage;
		PVOID ThreadPoolData;
		PVOID *TlsExpansionSlots;
#ifdef _WIN64
		PVOID DeallocationBStore;
		PVOID BStoreLimit;
#endif
		ULONG MuiGeneration;
		ULONG IsImpersonating;
		PVOID NlsCache;
		PVOID pShimData;
		USHORT HeapVirtualAffinity;
		USHORT LowFragHeapDataSlot;
		HANDLE CurrentTransactionHandle;
		PTEB_ACTIVE_FRAME ActiveFrame;
		PVOID FlsData;

		PVOID PreferredLanguages;
		PVOID UserPrefLanguages;
		PVOID MergedPrefLanguages;
		ULONG MuiImpersonation;

		union
		{
			USHORT CrossTebFlags;
			USHORT SpareCrossTebBits : 16;
		};
		union
		{
			USHORT SameTebFlags;
			struct
			{
				USHORT SafeThunkCall : 1;
				USHORT InDebugPrint : 1;
				USHORT HasFiberData : 1;
				USHORT SkipThreadAttach : 1;
				USHORT WerInShipAssertCode : 1;
				USHORT RanProcessInit : 1;
				USHORT ClonedThread : 1;
				USHORT SuppressDebugMsg : 1;
				USHORT DisableUserStackWalk : 1;
				USHORT RtlExceptionAttached : 1;
				USHORT InitialThread : 1;
				USHORT SessionAware : 1;
				USHORT LoadOwner : 1;
				USHORT LoaderWorker : 1;
				USHORT SpareSameTebBits : 2;
			};
		};

		PVOID TxnScopeEnterCallback;
		PVOID TxnScopeExitCallback;
		PVOID TxnScopeContext;
		ULONG LockCount;
		LONG WowTebOffset;
		PVOID ResourceRetValue;
		PVOID ReservedForWdf;
		ULONGLONG ReservedForCrt;
		GUID EffectiveContainerId;
	} TEB, *PTEB;


	typedef struct _OBJECT_ATTRIBUTES {
		ULONG           Length;
		HANDLE          RootDirectory;
		PUNICODE_STRING ObjectName;
		ULONG           Attributes;
		PVOID           SecurityDescriptor;
		PVOID           SecurityQualityOfService;
	}  OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;


	typedef struct _IO_STATUS_BLOCK
	{
		union
		{
			NTSTATUS Status;
			PVOID Pointer;
		} DUMMYUNIONNAME;

		ULONG_PTR Information;
	} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;


	typedef enum _FILE_INFORMATION_CLASS
	{
		FileDirectoryInformation = 1,
		FileFullDirectoryInformation,   // 2
		FileBothDirectoryInformation,   // 3
		FileBasicInformation,           // 4
		FileStandardInformation,        // 5
		FileInternalInformation,        // 6
		FileEaInformation,              // 7
		FileAccessInformation,          // 8
		FileNameInformation,            // 9
		FileRenameInformation,          // 10
		FileLinkInformation,            // 11
		FileNamesInformation,           // 12
		FileDispositionInformation,     // 13
		FilePositionInformation,        // 14
		FileFullEaInformation,          // 15
		FileModeInformation,            // 16
		FileAlignmentInformation,       // 17
		FileAllInformation,             // 18
		FileAllocationInformation,      // 19
		FileEndOfFileInformation,       // 20
		FileAlternateNameInformation,   // 21
		FileStreamInformation,          // 22
		FilePipeInformation,            // 23
		FilePipeLocalInformation,       // 24
		FilePipeRemoteInformation,      // 25
		FileMailslotQueryInformation,   // 26
		FileMailslotSetInformation,     // 27
		FileCompressionInformation,     // 28
		FileObjectIdInformation,        // 29
		FileCompletionInformation,      // 30
		FileMoveClusterInformation,     // 31
		FileQuotaInformation,           // 32
		FileReparsePointInformation,    // 33
		FileNetworkOpenInformation,     // 34
		FileAttributeTagInformation,    // 35
		FileTrackingInformation,        // 36
		FileIdBothDirectoryInformation, // 37
		FileIdFullDirectoryInformation, // 38
		FileValidDataLengthInformation, // 39
		FileShortNameInformation,       // 40
		FileIoCompletionNotificationInformation, // 41
		FileIoStatusBlockRangeInformation,       // 42
		FileIoPriorityHintInformation,           // 43
		FileSfioReserveInformation,              // 44
		FileSfioVolumeInformation,               // 45
		FileHardLinkInformation,                 // 46
		FileProcessIdsUsingFileInformation,      // 47
		FileNormalizedNameInformation,           // 48
		FileNetworkPhysicalNameInformation,      // 49
		FileIdGlobalTxDirectoryInformation,      // 50
		FileIsRemoteDeviceInformation,           // 51
		FileUnusedInformation,                   // 52
		FileNumaNodeInformation,                 // 53
		FileStandardLinkInformation,             // 54
		FileRemoteProtocolInformation,           // 55

		//
		//  These are special versions of these operations (defined earlier)
		//  which can be used by kernel mode drivers only to bypass security
		//  access checks for Rename and HardLink operations.  These operations
		//  are only recognized by the IOManager, a file system should never
		//  receive these.
		//
		FileRenameInformationBypassAccessCheck,  // 56
		FileLinkInformationBypassAccessCheck,    // 57
		FileVolumeNameInformation,               // 58
		FileIdInformation,                       // 59
		FileIdExtdDirectoryInformation,          // 60
		FileReplaceCompletionInformation,        // 61
		FileHardLinkFullIdInformation,           // 62
		FileIdExtdBothDirectoryInformation,      // 63
		FileMaximumInformation

	} FILE_INFORMATION_CLASS, *PFILE_INFORMATION_CLASS;

	typedef struct _FILE_DISPOSITION_INFORMATION
	{
		BOOLEAN NeedDeleteFile;
	} FILE_DISPOSITION_INFORMATION, *PFILE_DISPOSITION_INFORMATION;


	EXTERN_C NTSYSAPI
		NTSTATUS
		NTAPI
		RtlAdjustPrivilege(
			ULONG Privilege,
			BOOLEAN Enable,
			BOOLEAN CurrentThread,
			PBOOLEAN Enabled
		);

	EXTERN_C NTSYSAPI ULONG
		NTAPI
		RtlNtStatusToDosError(
			IN NTSTATUS status
		);

	EXTERN_C NTSYSAPI ULONG NTAPI RtlDetermineDosPathNameType_U( IN PCWSTR Path );

	EXTERN_C NTSYSAPI
		BOOLEAN
		NTAPI
		RtlDosPathNameToNtPathName_U(
			IN PCWSTR DosName,
			OUT PUNICODE_STRING NtName,
			OUT PCWSTR *DosFilePath OPTIONAL,
			OUT PUNICODE_STRING NtFilePath OPTIONAL
		);

	EXTERN_C NTSYSAPI
		VOID
		NTAPI
		RtlFreeUnicodeString(
			PUNICODE_STRING UnicodeString
		);

	EXTERN_C NTSYSAPI NTSTATUS NTAPI NtCreateFile(
		_Out_     PHANDLE FileHandle,
		_In_      ACCESS_MASK DesiredAccess,
		_In_      POBJECT_ATTRIBUTES ObjectAttributes,
		_Out_     PIO_STATUS_BLOCK IoStatusBlock,
		_In_opt_  PLARGE_INTEGER AllocationSize,
		_In_      ULONG FileAttributes,
		_In_      ULONG ShareAccess,
		_In_      ULONG CreateDisposition,
		_In_      ULONG CreateOptions,
		_In_opt_  PVOID EaBuffer,
		_In_      ULONG EaLength
	);

	EXTERN_C NTSYSAPI NTSTATUS NTAPI NtSetInformationFile(
		_In_ HANDLE FileHandle,
		_Out_ PIO_STATUS_BLOCK IoStatusBlock,
		_In_ PVOID FileInformation,
		_In_ ULONG Length,
		_In_ FILE_INFORMATION_CLASS FileInformationClass);

	EXTERN_C NTSYSAPI NTSTATUS
		NTAPI
		NtClose(
			IN HANDLE hObject
		);

	enum
	{  
		RtlPathTypeUnknown, 
		RtlPathTypeUncAbsolute, 
		RtlPathTypeDriveAbsolute, 
		RtlPathTypeDriveRelative, 
		RtlPathTypeRooted, 
		RtlPathTypeRelative, 
		RtlPathTypeLocalDevice, 
		RtlPathTypeRootLocalDevice, 
	} RTL_PATH_TYPE;


#ifndef SYMLINK_FLAG_RELATIVE
	#define SYMLINK_FLAG_RELATIVE  1
#endif
	typedef struct _REPARSE_DATA_BUFFER {
		ULONG  ReparseTag;
		USHORT ReparseDataLength;
		USHORT Reserved;
		union {
			struct {
				USHORT SubstituteNameOffset;
				USHORT SubstituteNameLength;
				USHORT PrintNameOffset;
				USHORT PrintNameLength;
				ULONG Flags;
				WCHAR PathBuffer[1];
			} SymbolicLinkReparseBuffer;
			struct {
				USHORT SubstituteNameOffset;
				USHORT SubstituteNameLength;
				USHORT PrintNameOffset;
				USHORT PrintNameLength;
				WCHAR PathBuffer[1];
			} MountPointReparseBuffer;
			struct {
				UCHAR  DataBuffer[1];
			} GenericReparseBuffer;
		} DUMMYUNIONNAME;
	} REPARSE_DATA_BUFFER, *PREPARSE_DATA_BUFFER;

#ifdef _ATL_XP_TARGETING

	//XP��֧��CreateSymbolicLinkW��ֱ��ʹ��NT APIʵ����Ϊ


	EXTERN_C _LTLIMP BOOLEAN
		WINAPI
		__crtCreateSymbolicLinkW(
			_In_ LPCWSTR lpSymlinkFileName,
			_In_ LPCWSTR lpTargetFileName,
			_In_ DWORD dwFlags
		)
	{
		if (lpSymlinkFileName == nullptr || lpTargetFileName == nullptr || (dwFlags&SYMBOLIC_LINK_FLAG_DIRECTORY) != dwFlags)
		{
			//��������
			SetLastError(ERROR_INVALID_PARAMETER);
			return FALSE;
		}


		if (!ImpersonateSelf(SecurityImpersonation))
			return FALSE;

		BOOLEAN Enabled = FALSE;

		LSTATUS lStatus = ERROR_SUCCESS;

		if (auto Status = RtlAdjustPrivilege(/*SE_CREATE_SYMBOLIC_LINK_PRIVILEGE*/35, TRUE, TRUE, &Enabled))
		{
			lStatus = RtlNtStatusToDosError(Status);
		}
		else
		{
			//auto& pReparseData = _calloc_crt_t(byte, MAXIMUM_REPARSE_DATA_BUFFER_SIZE);

			__crt_scoped_stack_ptr_tag<wchar_t> lpFullTargetFileName = nullptr;

			UNICODE_STRING NtName = {}, NtSymlinkFileName = {};
			bool bRelative = false;

			switch (RtlDetermineDosPathNameType_U(lpTargetFileName))
			{
			case RtlPathTypeUnknown:
			case RtlPathTypeRooted:
			case RtlPathTypeRelative:
				//
				bRelative = true;
				NtName.Buffer = (wchar_t*)lpTargetFileName;
				NtName.Length = NtName.MaximumLength = wcslen(lpTargetFileName) * sizeof(wchar_t);

				break;
			case RtlPathTypeDriveRelative:
				if (auto cchFull = GetFullPathNameW(lpTargetFileName, 0, 0, nullptr))
				{
					lpFullTargetFileName = (wchar_t*)_malloca(cchFull * sizeof(wchar_t));
					if (!lpFullTargetFileName._p)
					{
						lStatus = ERROR_NOT_ENOUGH_MEMORY;
						goto _End;
					}

					lpTargetFileName = lpFullTargetFileName._p;
				}

				//case RtlPathTypeUncAbsolute:
				//case RtlPathTypeDriveAbsolute:
				//case RtlPathTypeLocalDevice:
				//case RtlPathTypeRootLocalDevice:
			default:
				if (!RtlDosPathNameToNtPathName_U(lpTargetFileName, &NtName, nullptr, nullptr))
				{
					lStatus = ERROR_INVALID_PARAMETER;
					goto _End;
				}
				break;
			}

			{
				auto cbTargetFileName = wcslen(lpTargetFileName) * sizeof(wchar_t);

				auto cBuffer = NtName.Length + cbTargetFileName + UFIELD_OFFSET(REPARSE_DATA_BUFFER, SymbolicLinkReparseBuffer.PathBuffer);


				auto& pReparseData = _malloca_crt_t(BYTE, cBuffer);

				if (!pReparseData._p)
				{
					lStatus = ERROR_NOT_ENOUGH_MEMORY;
					goto _End;
				}

				memset(pReparseData._p, 0, cBuffer);

				if (bRelative)
					((REPARSE_DATA_BUFFER*)pReparseData._p)->SymbolicLinkReparseBuffer.Flags |= SYMLINK_FLAG_RELATIVE;


				((REPARSE_DATA_BUFFER*)pReparseData._p)->ReparseTag = IO_REPARSE_TAG_SYMLINK;

				((REPARSE_DATA_BUFFER*)pReparseData._p)->ReparseDataLength = cBuffer - UFIELD_OFFSET(REPARSE_DATA_BUFFER, GenericReparseBuffer);

				auto& SymbolicLinkReparseBuffer = ((REPARSE_DATA_BUFFER*)pReparseData._p)->SymbolicLinkReparseBuffer;


				SymbolicLinkReparseBuffer.SubstituteNameOffset = SymbolicLinkReparseBuffer.PrintNameLength = wcslen(lpTargetFileName) * sizeof(wchar_t);
				SymbolicLinkReparseBuffer.SubstituteNameLength = NtName.Length;

				memcpy(SymbolicLinkReparseBuffer.PathBuffer, lpTargetFileName, SymbolicLinkReparseBuffer.PrintNameLength);
				memcpy((byte*)(SymbolicLinkReparseBuffer.PathBuffer) + SymbolicLinkReparseBuffer.PrintNameLength, NtName.Buffer, NtName.Length);




				if (RtlDosPathNameToNtPathName_U(lpSymlinkFileName, &NtSymlinkFileName, nullptr, nullptr))
				{
					HANDLE hFile;

					OBJECT_ATTRIBUTES ObjectAttributes = { sizeof(OBJECT_ATTRIBUTES),nullptr,&NtSymlinkFileName ,/*OBJ_CASE_INSENSITIVE*/0x40 };
					IO_STATUS_BLOCK IoStatusBlock;

					Status = NtCreateFile(&hFile, FILE_WRITE_ATTRIBUTES | SYNCHRONIZE | DELETE, &ObjectAttributes, &IoStatusBlock, nullptr, FILE_ATTRIBUTE_NORMAL, 0, /*FILE_CREATE*/2, (dwFlags&SYMBOLIC_LINK_FLAG_DIRECTORY) ? 0x200021 : 0x200060, nullptr, 0);
					if (Status < 0)
					{
						lStatus = RtlNtStatusToDosError(Status);
					}
					else
					{
						DWORD cRet;

						if (!DeviceIoControl(hFile, FSCTL_SET_REPARSE_POINT, pReparseData._p, cBuffer, NULL, NULL, &cRet, NULL))
						{
							lStatus = GetLastError();

							if (lStatus == ERROR_SUCCESS)
								lStatus = ERROR_INVALID_FUNCTION;

							//����ʧ����ɾ���������ļ�
							FILE_DISPOSITION_INFORMATION DispositionInformation;
							DispositionInformation.NeedDeleteFile = TRUE;
							NtSetInformationFile(hFile, &IoStatusBlock, &DispositionInformation, sizeof(DispositionInformation), FileDispositionInformation);
						}


						NtClose(hFile);
					}

					RtlFreeUnicodeString(&NtSymlinkFileName);
				}
				else
				{
					lStatus = ERROR_INVALID_PARAMETER;
				}


				if (!bRelative)
					RtlFreeUnicodeString(&NtName);

			}
		}

	_End:

		RevertToSelf();

		if (lStatus)
		{
			SetLastError(lStatus);
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
#endif
}