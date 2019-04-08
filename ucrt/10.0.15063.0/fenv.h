//
// fenv.h
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// Floating point environment library.
//
#pragma once
#define _FENV

#include <corecrt.h>
#include <float.h>

_CRT_BEGIN_C_HEADER



#define FE_TONEAREST  _RC_NEAR
#define FE_UPWARD     _RC_UP
#define FE_DOWNWARD   _RC_DOWN
#define FE_TOWARDZERO _RC_CHOP

#define FE_ROUND_MASK _MCW_RC

_ACRTIMP int __cdecl fegetround(void);
_ACRTIMP int __cdecl fesetround(_In_ int _Round);



#if !defined _M_CEE

    typedef unsigned long fexcept_t;

    typedef struct fenv_t
    {
        unsigned long _Fe_ctl, _Fe_stat;
    } fenv_t;



    #define FE_INEXACT   _SW_INEXACT       // _EM_INEXACT     0x00000001 inexact (precision)
    #define FE_UNDERFLOW _SW_UNDERFLOW     // _EM_UNDERFLOW   0x00000002 underflow
    #define FE_OVERFLOW  _SW_OVERFLOW      // _EM_OVERFLOW    0x00000004 overflow
    #define FE_DIVBYZERO _SW_ZERODIVIDE    // _EM_ZERODIVIDE  0x00000008 zero divide
    #define FE_INVALID   _SW_INVALID       // _EM_INVALID     0x00000010 invalid

    #define FE_ALL_EXCEPT (FE_DIVBYZERO | FE_INEXACT | FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW)

    _ACRTIMP int __cdecl fegetenv(_Out_ fenv_t* _Env);
    _ACRTIMP int __cdecl fesetenv(_In_ fenv_t const* _Env);
    _ACRTIMP int __cdecl feclearexcept(_In_ int _Flags);
    _ACRTIMP _Success_(return == 0) int __cdecl feholdexcept(_Out_ fenv_t* _Env);
    _ACRTIMP int __cdecl fetestexcept(_In_ int _Flags);
    _ACRTIMP int __cdecl fegetexceptflag(_Out_ fexcept_t* _Except, _In_ int _TestFlags);
    _ACRTIMP int __cdecl fesetexceptflag(_In_ fexcept_t const* _Except, _In_ int _SetFlags);

    #if !defined __midl // MIDL does not support compound initializers
        // In the original implementation (_Fenv0), the global variable was zero
        // initialized, indicating no exceptions are masked.  In the current
        // implementation (_Fenv1), the global variable is initialized with all
        // exceptions masked, which is the actual initial environment.
        #if defined _M_IX86
            __declspec(selectany) extern const fenv_t _Fenv1 = { 0x3f3f103f, 0 };
        #elif defined _M_X64
            __declspec(selectany) extern const fenv_t _Fenv1 = { 0x3f00003f, 0 };
        #else
            __declspec(selectany) extern const fenv_t _Fenv1 = { 0x0000003f, 0 };
        #endif
    #endif

    #define FE_DFL_ENV (&_Fenv1)



    // feraiseexcept is defined inline in this header so that it is compiled
    // with the same /arch setting as is specified in the consuming application,
    // rather than the /arch:IA32 setting with which the CRT sources are built.
    // optimizer has to be turned off to avoid optimizing out since the function
    // doesn't have side effects.
    //
    // feupdateenv is inline because it calls feraiseexcept.
    #if _CRT_FUNCTIONS_REQUIRED
        #if !defined(_BEGIN_PRAGMA_OPTIMIZE_DISABLE)
            #define _BEGIN_PRAGMA_OPTIMIZE_DISABLE(flags, bug, reason) \
                __pragma(optimize(flags, off))
            #define _BEGIN_PRAGMA_OPTIMIZE_ENABLE(flags, bug, reason) \
                __pragma(optimize(flags, on))
            #define _END_PRAGMA_OPTIMIZE() \
                __pragma(optimize("", on))
        #endif
        _BEGIN_PRAGMA_OPTIMIZE_DISABLE("", MSFT:4499495, "If optimizations are on, the floating-point exception might not get triggered (because the compiler optimizes it out), breaking the function.")
        __inline int __CRTDECL feraiseexcept(_In_ int _Except)
        {
            static struct
            {
                int    _Except_Val;
                double _Num;
                double _Denom;
            } const _Table[] =
            {  // Raise exception by evaluating num / denom:
                {FE_INVALID,   0.0,    0.0    },
                {FE_DIVBYZERO, 1.0,    0.0    },
                {FE_OVERFLOW,  1e+300, 1e-300 },
                {FE_UNDERFLOW, 1e-300, 1e+300 },
                {FE_INEXACT,   2.0,    3.0    }
            };

            double _Ans = 0.0;
            int _N;

            if ((_Except &= FE_ALL_EXCEPT) == 0)
            {
                return 0;
            }

            // Raise the exceptions not masked:
            for (_N = 0; _N < sizeof(_Table) / sizeof(_Table[0]); ++_N)
            {
                if ((_Except & _Table[_N]._Except_Val) != 0)
                {
                    _Ans = _Table[_N]._Num / _Table[_N]._Denom;

                    // x87 exceptions are raised immediately before execution of the
                    // next floating point instruction.  If we're using /arch:IA32,
                    // force the exception to be raised immediately:
                    #if defined _M_IX86 && _M_IX86_FP == 0
                    __asm fwait;
                    #endif
                }
            }

            return 0;
        }
        _END_PRAGMA_OPTIMIZE()

        __inline int __CRTDECL feupdateenv(_In_ const fenv_t *_Penv)
        {
            int _Except = fetestexcept(FE_ALL_EXCEPT);

            if (fesetenv(_Penv) != 0 || feraiseexcept(_Except) != 0)
            {
                return 1;
            }

            return 0;
        }
    #endif // _CRT_FUNCTIONS_REQUIRED

#endif // !defined _M_CEE && !defined _CORECRT_BUILD

_CRT_END_C_HEADER
