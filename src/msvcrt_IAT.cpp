#ifndef _LTL_Using_Dynamic_Lib
#define __Build_OBJ
#endif

#include "msvcrt_IAT.h"


#ifdef _M_X64

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_set_FMA3_enable);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_get_FMA3_enable);

#endif

//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(abort_advanced);
//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_set_abort_behavior_advanced);

//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_fstat64i32_downlevel);
//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_stat64i32_light);
//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_wstat64i32_light);

//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_stat32_advanced);
//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_stat32i64_advanced);
//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_stat64i32_advanced);
//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_stat64_advanced);

//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_wstat32_advanced);
//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_wstat32i64_advanced);
//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_wstat64i32_advanced);
//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_wstat64_advanced);

//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_purecall_advanced);

//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_set_purecall_handler_advanced);

//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_get_purecall_handler_advanced);


//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_set_invalid_parameter_handler_downlevel);

//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_get_invalid_parameter_handler_downlevel);

//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_set_thread_local_invalid_parameter_handler_downlevel);

//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_get_thread_local_invalid_parameter_handler_downlevel);

//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_set_abort_behavior_downlevel);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(imaxabs);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(imaxdiv);


//complex.h
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cacos);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cacosh);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(carg);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(casin);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(casinh);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(catan);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(catanh);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(ccos);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(ccosh);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cexp);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cimag);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(clog);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(clog10);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(conj);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cpow);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cproj);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(creal);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(csin);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(csinh);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(csqrt);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(ctan);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(ctanh);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(norm);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cabsf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cacosf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cacoshf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cargf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(casinf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(casinhf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(catanf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(catanhf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(ccosf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(ccoshf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cexpf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cimagf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(clogf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(clog10f);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(conjf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cpowf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cprojf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(crealf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(csinf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(csinhf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(csqrtf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(ctanf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(ctanhf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(normf);

//cabsl == cabs weak别名转发
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cacosl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cacoshl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cargl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(casinl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(casinhl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(catanl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(catanhl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(ccosl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(ccoshl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cexpl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cimagl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(clogl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(clog10l);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(conjl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cpowl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cprojl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(creall);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(csinl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(csinhl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(csqrtl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(ctanl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(ctanhl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(norml);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_Cbuild);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_Cmulcc);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_Cmulcr);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_FCbuild);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_FCmulcc);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_FCmulcr);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_LCbuild);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_LCmulcc);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_LCmulcr);


//fenv.h
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(fegetround);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(fesetround);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(fegetenv);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(fesetenv);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(feclearexcept);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(feholdexcept);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(fetestexcept);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(fegetexceptflag);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(fesetexceptflag);


//float.h
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(__fpe_flt_rounds);

//math.h
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_dclass);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_ldclass);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_fdclass);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_dsign);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_ldsign);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_fdsign);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_dpcomp);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_ldpcomp);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_fdtest);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_dtest);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_ldtest);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_fdpcomp);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_d_int);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_ld_int);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_fd_int);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_dscale);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_ldscale);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_fdscale);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_dunscale);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_ldunscale);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_fdunscale);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_dexp);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_ldexp);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_fdexp);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_dnorm);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_fdnorm);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_dpoly);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_ldpoly);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_fdpoly);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_dlog);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_ldlog);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_fdlog);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_dsin);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_ldsin);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_fdsin);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(acosh);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(asinh);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(atanh);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cbrt);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(erf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(erfc);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(exp2);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(expm1);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(fdim);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(fma);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(fmax);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(fmin);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(ilogb);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(lgamma);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(llrint);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(llround);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(log1p);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(log2);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(logb);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(lrint);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(lround);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(nan);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(nearbyint);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(remainder);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(remquo);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(rint);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(round);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(scalbln);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(scalbn);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(tgamma);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(trunc);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(acoshf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(asinhf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(atanhf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cbrtf);

extern "C" _Check_return_ float     __cdecl _chgsignf(_In_ float _X)
{
	/*

	X | x x x x x x x x | x x x x x x x x x x x x x x x x x x x x x x x
	符号        指数                          尾数
	1           8                             23

	*/

	*(unsigned long*)&_X ^= 0x80000000;

	return _X;
}
_LCRT_DEFINE_IAT_SYMBOL(_chgsignf);

extern "C" _Check_return_ float     __cdecl copysignf(_In_ float _Number, _In_ float _Sign)
{
	*(unsigned long*)&_Number = ((*(unsigned long*)&_Number)&~0x80000000) | ((*(unsigned long*)&_Sign) & 0x80000000);

	return _Number;
}
_LCRT_DEFINE_IAT_SYMBOL(copysignf);

extern "C" _Check_return_ float     __cdecl _copysignf(_In_ float _Number, _In_ float _Sign)
{
	*(unsigned long*)&_Number = ((*(unsigned long*)&_Number)&~0x80000000) | ((*(unsigned long*)&_Sign) & 0x80000000);

	return _Number;
}
_LCRT_DEFINE_IAT_SYMBOL(_copysignf);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(erff);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(erfcf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(expm1f);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(exp2f);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(fdimf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(fmaf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(fmaxf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(fminf);

#ifdef _M_IX86
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_hypotf);
#endif

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(ilogbf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(lgammaf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(llrintf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(llroundf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(log1pf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(log2f);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(logbf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(lrintf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(lroundf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(nanf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(nearbyintf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(nextafterf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(nexttowardf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(remainderf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(remquof);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(rintf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(roundf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(scalblnf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(scalbnf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(tgammaf);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(truncf);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(acoshl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(asinhl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(atanhl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(cbrtl);

//copysignl weak转发_copysign
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(erfl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(erfcl);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(exp2l);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(expm1l);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(fdiml);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(fmal);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(fmaxl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(fminl);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(ilogbl);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(lgammal);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(llrintl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(llroundl);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(log1pl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(log2l);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(logbl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(lrintl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(lroundl);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(nanl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(nearbyintl);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(remainderl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(remquol);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(rintl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(roundl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(scalblnl);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(scalbnl);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(tgammal);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(truncl);

//stdlib.h
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(lldiv);


#if _CRT_NTDDI_MIN < /*NTDDI_WIN6*/0x06000000

#ifndef _DLL
//VC-LTL-4.0.0.15以前版本会强制添加__declspec(dllimport)修饰，所以，为了兼容历史代码，给以下函数添加 IAT 符号。
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_lfind_s);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_lsearch_s);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(qsort_s);
#endif

#endif



//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_aligned_msize_downlevel);
//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_aligned_offset_recalloc_downlevel);
//_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_aligned_recalloc_downlevel);

_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_except1);

#ifdef _M_IX86
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_libm_sse2_tan_precise);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_libm_sse2_sqrt_precise);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_libm_sse2_sin_precise);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_libm_sse2_pow_precise);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_libm_sse2_log_precise);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_libm_sse2_log10_precise);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_libm_sse2_exp_precise);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_libm_sse2_cos_precise);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_libm_sse2_atan_precise);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_libm_sse2_asin_precise);
_LCRT_DEFINE_IAT_SYMBOL_EXTERN(_libm_sse2_acos_precise);

#endif