/****
* Copyright (C) 2007-2008 Advanced Micro Devices Inc.  All rights reserved.
*
*  The information and source code contained herein is the exclusive
*  property of Advanced Micro Devices and may not be disclosed, examined
*  or reproduced in whole or in part without explicit written authorization
*  from the company.
*
*  ammintrin.h - Definitions for AMD-specific intrinsics
*
****/

#pragma once

#if !defined(_M_IX86) && !defined(_M_X64)
#error This header is specific to X86 and X64 targets
#endif

#ifndef _INCLUDED_AMM
#define _INCLUDED_AMM
#ifndef __midl

#if !defined _M_IX86 && !defined _M_X64
    #error This header is specific to X86 and X64 targets
#endif

#if defined (_M_CEE_PURE)
  #error ERROR: This file is not supported in the pure mode!
#else  /* defined (_M_CEE_PURE) */

#if defined __cplusplus
extern "C" { /* Intrinsics use C name-mangling. */
#endif  /* defined __cplusplus */

/*
 * Vector integer comparison control macros
 */

#define _MM_PCOMCTRL_LT    0
#define _MM_PCOMCTRL_LE    1
#define _MM_PCOMCTRL_GT    2
#define _MM_PCOMCTRL_GE    3
#define _MM_PCOMCTRL_EQ    4
#define _MM_PCOMCTRL_NEQ   5
#define _MM_PCOMCTRL_FALSE 6
#define _MM_PCOMCTRL_TRUE  7

/*
 * MACRO functions for vector integer comparisons
 */

#define _mm_comlt_epu8(v1, v2)      _mm_com_epu8(v1, v2, _MM_PCOMCTRL_LT)
#define _mm_comle_epu8(v1, v2)      _mm_com_epu8(v1, v2, _MM_PCOMCTRL_LE)
#define _mm_comgt_epu8(v1, v2)      _mm_com_epu8(v1, v2, _MM_PCOMCTRL_GT)
#define _mm_comge_epu8(v1, v2)      _mm_com_epu8(v1, v2, _MM_PCOMCTRL_GE)
#define _mm_comeq_epu8(v1, v2)      _mm_com_epu8(v1, v2, _MM_PCOMCTRL_EQ)
#define _mm_comneq_epu8(v1, v2)     _mm_com_epu8(v1, v2, _MM_PCOMCTRL_NEQ)
#define _mm_comfalse_epu8(v1, v2)   _mm_com_epu8(v1, v2, _MM_PCOMCTRL_FALSE)
#define _mm_comtrue_epu8(v1, v2)    _mm_com_epu8(v1, v2, _MM_PCOMCTRL_TRUE)

#define _mm_comlt_epu16(v1, v2)     _mm_com_epu16(v1, v2, _MM_PCOMCTRL_LT)
#define _mm_comle_epu16(v1, v2)     _mm_com_epu16(v1, v2, _MM_PCOMCTRL_LE)
#define _mm_comgt_epu16(v1, v2)     _mm_com_epu16(v1, v2, _MM_PCOMCTRL_GT)
#define _mm_comge_epu16(v1, v2)     _mm_com_epu16(v1, v2, _MM_PCOMCTRL_GE)
#define _mm_comeq_epu16(v1, v2)     _mm_com_epu16(v1, v2, _MM_PCOMCTRL_EQ)
#define _mm_comneq_epu16(v1, v2)    _mm_com_epu16(v1, v2, _MM_PCOMCTRL_NEQ)
#define _mm_comfalse_epu16(v1, v2)  _mm_com_epu16(v1, v2, _MM_PCOMCTRL_FALSE)
#define _mm_comtrue_epu16(v1, v2)   _mm_com_epu16(v1, v2, _MM_PCOMCTRL_TRUE)

#define _mm_comlt_epu32(v1, v2)     _mm_com_epu32(v1, v2, _MM_PCOMCTRL_LT)
#define _mm_comle_epu32(v1, v2)     _mm_com_epu32(v1, v2, _MM_PCOMCTRL_LE)
#define _mm_comgt_epu32(v1, v2)     _mm_com_epu32(v1, v2, _MM_PCOMCTRL_GT)
#define _mm_comge_epu32(v1, v2)     _mm_com_epu32(v1, v2, _MM_PCOMCTRL_GE)
#define _mm_comeq_epu32(v1, v2)     _mm_com_epu32(v1, v2, _MM_PCOMCTRL_EQ)
#define _mm_comneq_epu32(v1, v2)    _mm_com_epu32(v1, v2, _MM_PCOMCTRL_NEQ)
#define _mm_comfalse_epu32(v1, v2)  _mm_com_epu32(v1, v2, _MM_PCOMCTRL_FALSE)
#define _mm_comtrue_epu32(v1, v2)   _mm_com_epu32(v1, v2, _MM_PCOMCTRL_TRUE)

#define _mm_comlt_epu64(v1, v2)     _mm_com_epu64(v1, v2, _MM_PCOMCTRL_LT)
#define _mm_comle_epu64(v1, v2)     _mm_com_epu64(v1, v2, _MM_PCOMCTRL_LE)
#define _mm_comgt_epu64(v1, v2)     _mm_com_epu64(v1, v2, _MM_PCOMCTRL_GT)
#define _mm_comge_epu64(v1, v2)     _mm_com_epu64(v1, v2, _MM_PCOMCTRL_GE)
#define _mm_comeq_epu64(v1, v2)     _mm_com_epu64(v1, v2, _MM_PCOMCTRL_EQ)
#define _mm_comneq_epu64(v1, v2)    _mm_com_epu64(v1, v2, _MM_PCOMCTRL_NEQ)
#define _mm_comfalse_epu64(v1, v2)  _mm_com_epu64(v1, v2, _MM_PCOMCTRL_FALSE)
#define _mm_comtrue_epu64(v1, v2)   _mm_com_epu64(v1, v2, _MM_PCOMCTRL_TRUE)

#define _mm_comlt_epi8(v1, v2)      _mm_com_epi8(v1, v2, _MM_PCOMCTRL_LT)
#define _mm_comle_epi8(v1, v2)      _mm_com_epi8(v1, v2, _MM_PCOMCTRL_LE)
#define _mm_comgt_epi8(v1, v2)      _mm_com_epi8(v1, v2, _MM_PCOMCTRL_GT)
#define _mm_comge_epi8(v1, v2)      _mm_com_epi8(v1, v2, _MM_PCOMCTRL_GE)
#define _mm_comeq_epi8(v1, v2)      _mm_com_epi8(v1, v2, _MM_PCOMCTRL_EQ)
#define _mm_comneq_epi8(v1, v2)     _mm_com_epi8(v1, v2, _MM_PCOMCTRL_NEQ)
#define _mm_comfalse_epi8(v1, v2)   _mm_com_epi8(v1, v2, _MM_PCOMCTRL_FALSE)
#define _mm_comtrue_epi8(v1, v2)    _mm_com_epi8(v1, v2, _MM_PCOMCTRL_TRUE)

#define _mm_comlt_epi16(v1, v2)     _mm_com_epi16(v1, v2, _MM_PCOMCTRL_LT)
#define _mm_comle_epi16(v1, v2)     _mm_com_epi16(v1, v2, _MM_PCOMCTRL_LE)
#define _mm_comgt_epi16(v1, v2)     _mm_com_epi16(v1, v2, _MM_PCOMCTRL_GT)
#define _mm_comge_epi16(v1, v2)     _mm_com_epi16(v1, v2, _MM_PCOMCTRL_GE)
#define _mm_comeq_epi16(v1, v2)     _mm_com_epi16(v1, v2, _MM_PCOMCTRL_EQ)
#define _mm_comneq_epi16(v1, v2)    _mm_com_epi16(v1, v2, _MM_PCOMCTRL_NEQ)
#define _mm_comfalse_epi16(v1, v2)  _mm_com_epi16(v1, v2, _MM_PCOMCTRL_FALSE)
#define _mm_comtrue_epi16(v1, v2)   _mm_com_epi16(v1, v2, _MM_PCOMCTRL_TRUE)

#define _mm_comlt_epi32(v1, v2)     _mm_com_epi32(v1, v2, _MM_PCOMCTRL_LT)
#define _mm_comle_epi32(v1, v2)     _mm_com_epi32(v1, v2, _MM_PCOMCTRL_LE)
#define _mm_comgt_epi32(v1, v2)     _mm_com_epi32(v1, v2, _MM_PCOMCTRL_GT)
#define _mm_comge_epi32(v1, v2)     _mm_com_epi32(v1, v2, _MM_PCOMCTRL_GE)
#define _mm_comeq_epi32(v1, v2)     _mm_com_epi32(v1, v2, _MM_PCOMCTRL_EQ)
#define _mm_comneq_epi32(v1, v2)    _mm_com_epi32(v1, v2, _MM_PCOMCTRL_NEQ)
#define _mm_comfalse_epi32(v1, v2)  _mm_com_epi32(v1, v2, _MM_PCOMCTRL_FALSE)
#define _mm_comtrue_epi32(v1, v2)   _mm_com_epi32(v1, v2, _MM_PCOMCTRL_TRUE)

#define _mm_comlt_epi64(v1, v2)     _mm_com_epi64(v1, v2, _MM_PCOMCTRL_LT)
#define _mm_comle_epi64(v1, v2)     _mm_com_epi64(v1, v2, _MM_PCOMCTRL_LE)
#define _mm_comgt_epi64(v1, v2)     _mm_com_epi64(v1, v2, _MM_PCOMCTRL_GT)
#define _mm_comge_epi64(v1, v2)     _mm_com_epi64(v1, v2, _MM_PCOMCTRL_GE)
#define _mm_comeq_epi64(v1, v2)     _mm_com_epi64(v1, v2, _MM_PCOMCTRL_EQ)
#define _mm_comneq_epi64(v1, v2)    _mm_com_epi64(v1, v2, _MM_PCOMCTRL_NEQ)
#define _mm_comfalse_epi64(v1, v2)  _mm_com_epi64(v1, v2, _MM_PCOMCTRL_FALSE)
#define _mm_comtrue_epi64(v1, v2)   _mm_com_epi64(v1, v2, _MM_PCOMCTRL_TRUE)

/* SSE5 intrinsics */

/* Float/double multiply-accumulate */
__m128 _mm_macc_ps(__m128, __m128, __m128);
__m128d _mm_macc_pd(__m128d, __m128d, __m128d);
__m128 _mm_macc_ss(__m128, __m128, __m128);
__m128d _mm_macc_sd(__m128d, __m128d, __m128d);
__m128 _mm_maddsub_ps(__m128, __m128, __m128);
__m128d _mm_maddsub_pd(__m128d, __m128d, __m128d);
__m128 _mm_msubadd_ps(__m128, __m128, __m128);
__m128d _mm_msubadd_pd(__m128d, __m128d, __m128d);
__m128 _mm_msub_ps(__m128, __m128, __m128);
__m128d _mm_msub_pd(__m128d, __m128d, __m128d);
__m128 _mm_msub_ss(__m128, __m128, __m128);
__m128d _mm_msub_sd(__m128d, __m128d, __m128d);
__m128 _mm_nmacc_ps(__m128, __m128, __m128);
__m128d _mm_nmacc_pd(__m128d, __m128d, __m128d);
__m128 _mm_nmacc_ss(__m128, __m128, __m128);
__m128d _mm_nmacc_sd(__m128d, __m128d, __m128d);
__m128 _mm_nmsub_ps(__m128, __m128, __m128);
__m128d _mm_nmsub_pd(__m128d, __m128d, __m128d);
__m128 _mm_nmsub_ss(__m128, __m128, __m128);
__m128d _mm_nmsub_sd(__m128d, __m128d, __m128d);

/* Integer multiply-accumulate */
__m128i _mm_maccs_epi16(__m128i, __m128i, __m128i);
__m128i _mm_macc_epi16(__m128i, __m128i, __m128i);
__m128i _mm_maccsd_epi16(__m128i, __m128i, __m128i);
__m128i _mm_maccd_epi16(__m128i, __m128i, __m128i);
__m128i _mm_maccs_epi32(__m128i, __m128i, __m128i);
__m128i _mm_macc_epi32(__m128i, __m128i, __m128i);
__m128i _mm_maccslo_epi32(__m128i, __m128i, __m128i);
__m128i _mm_macclo_epi32(__m128i, __m128i, __m128i);
__m128i _mm_maccshi_epi32(__m128i, __m128i, __m128i);
__m128i _mm_macchi_epi32(__m128i, __m128i, __m128i);
__m128i _mm_maddsd_epi16(__m128i, __m128i, __m128i);
__m128i _mm_maddd_epi16(__m128i, __m128i, __m128i);

/* Horizontal add/subtract */
__m128i _mm_haddw_epi8(__m128i);
__m128i _mm_haddd_epi8(__m128i);
__m128i _mm_haddq_epi8(__m128i);
__m128i _mm_haddd_epi16(__m128i);
__m128i _mm_haddq_epi16(__m128i);
__m128i _mm_haddq_epi32(__m128i);
__m128i _mm_haddw_epu8(__m128i);
__m128i _mm_haddd_epu8(__m128i);
__m128i _mm_haddq_epu8(__m128i);
__m128i _mm_haddd_epu16(__m128i);
__m128i _mm_haddq_epu16(__m128i);
__m128i _mm_haddq_epu32(__m128i);
__m128i _mm_hsubw_epi8(__m128i);
__m128i _mm_hsubd_epi16(__m128i);
__m128i _mm_hsubq_epi32(__m128i);

/* Vector conditional moves */
__m128i _mm_cmov_si128(__m128i, __m128i, __m128i);
__m128i _mm_perm_epi8(__m128i, __m128i, __m128i);

/* Vector shifts and rotates */
__m128i _mm_rot_epi8(__m128i, __m128i);
__m128i _mm_rot_epi16(__m128i, __m128i);
__m128i _mm_rot_epi32(__m128i, __m128i);
__m128i _mm_rot_epi64(__m128i, __m128i);
__m128i _mm_roti_epi8(__m128i, int);
__m128i _mm_roti_epi16(__m128i, int);
__m128i _mm_roti_epi32(__m128i, int);
__m128i _mm_roti_epi64(__m128i, int);
__m128i _mm_shl_epi8(__m128i, __m128i);
__m128i _mm_shl_epi16(__m128i, __m128i);
__m128i _mm_shl_epi32(__m128i, __m128i);
__m128i _mm_shl_epi64(__m128i, __m128i);
__m128i _mm_sha_epi8(__m128i, __m128i);
__m128i _mm_sha_epi16(__m128i, __m128i);
__m128i _mm_sha_epi32(__m128i, __m128i);
__m128i _mm_sha_epi64(__m128i, __m128i);

/* Vector integer comparisons */

__m128i _mm_com_epu8(__m128i, __m128i, int);
__m128i _mm_com_epu16(__m128i, __m128i, int);
__m128i _mm_com_epu32(__m128i, __m128i, int);
__m128i _mm_com_epu64(__m128i, __m128i, int);
__m128i _mm_com_epi8(__m128i, __m128i, int);
__m128i _mm_com_epi16(__m128i, __m128i, int);
__m128i _mm_com_epi32(__m128i, __m128i, int);
__m128i _mm_com_epi64(__m128i, __m128i, int);

/* Precision control */

__m128 _mm_frcz_ps(__m128);
__m128d _mm_frcz_pd(__m128d);
__m128 _mm_frcz_ss(__m128, __m128);
__m128d _mm_frcz_sd(__m128d, __m128d);

/* Control values for permute2 intrinsics */
#define _MM_PERMUTE2_COPY    0 /* just copy the selected value */
/* Note that using the constant 1 would have the same effect as 0 */
#define _MM_PERMUTE2_ZEROIF1 2 /* zero selected value if src3 bit is 1 */
#define _MM_PERMUTE2_ZEROIF0 3 /* zero selected value if src3 bit is 3 */

/* Permutation */
__m128 _mm_permute2_ps(__m128, __m128, __m128i, int);
__m128d _mm_permute2_pd(__m128d, __m128d, __m128i, int);


/* YMM versions */
__m256 _mm256_macc_ps(__m256, __m256, __m256);
__m256d _mm256_macc_pd(__m256d, __m256d, __m256d);
__m256 _mm256_maddsub_ps(__m256, __m256, __m256);
__m256d _mm256_maddsub_pd(__m256d, __m256d, __m256d);
__m256 _mm256_msubadd_ps(__m256, __m256, __m256);
__m256d _mm256_msubadd_pd(__m256d, __m256d, __m256d);
__m256 _mm256_msub_ps(__m256, __m256, __m256);
__m256d _mm256_msub_pd(__m256d, __m256d, __m256d);
__m256 _mm256_nmacc_ps(__m256, __m256, __m256);
__m256d _mm256_nmacc_pd(__m256d, __m256d, __m256d);
__m256 _mm256_nmsub_ps(__m256, __m256, __m256);
__m256d _mm256_nmsub_pd(__m256d, __m256d, __m256d);
__m256i _mm256_cmov_si256(__m256i, __m256i, __m256i);
__m256 _mm256_frcz_ps(__m256);
__m256d _mm256_frcz_pd(__m256d);
__m256 _mm256_permute2_ps(__m256, __m256, __m256i, int);
__m256d _mm256_permute2_pd(__m256d, __m256d, __m256i, int);

/* LWP intrinsics */
void __llwpcb(void *);
void *__slwpcb();
void __lwpval32(unsigned int, unsigned int, unsigned int);
unsigned char __lwpins32(unsigned int, unsigned int, unsigned int);
#if defined (_M_X64)
void __lwpval64(unsigned __int64, unsigned int, unsigned int);
unsigned char __lwpins64(unsigned __int64, unsigned int, unsigned int);
#endif  /* defined (_M_X64) */

/*BMI intrinsics */
unsigned int _bextr_u32(unsigned int, unsigned int, unsigned int);
unsigned int _andn_u32(unsigned int, unsigned int);
unsigned int _tzcnt_u32(unsigned int);
unsigned int _lzcnt_u32(unsigned int);
unsigned int _blsr_u32(unsigned int);
unsigned int _blsmsk_u32(unsigned int);
unsigned int _blsi_u32(unsigned int);
#if defined (_M_X64)
unsigned __int64 _bextr_u64(unsigned __int64, unsigned int, unsigned int);
unsigned __int64 _andn_u64(unsigned __int64, unsigned __int64);
unsigned __int64 _tzcnt_u64(unsigned __int64);
unsigned __int64 _lzcnt_u64(unsigned __int64);
unsigned __int64 _blsr_u64(unsigned __int64);
unsigned __int64 _blsmsk_u64(unsigned __int64);
unsigned __int64 _blsi_u64(unsigned __int64);
#endif  /* defined (_M_X64) */

/* TBM intrinsics */
unsigned int _bextri_u32(unsigned int, unsigned int);
unsigned int _blcfill_u32(unsigned int);
unsigned int _blsfill_u32(unsigned int);
unsigned int _blcs_u32(unsigned int);
unsigned int _tzmsk_u32(unsigned int);
unsigned int _blcic_u32(unsigned int);
unsigned int _blsic_u32(unsigned int);
unsigned int _t1mskc_u32(unsigned int);
unsigned int _blcmsk_u32(unsigned int);
unsigned int _blci_u32(unsigned int);
#if defined (_M_X64)
unsigned __int64 _bextri_u64(unsigned __int64, unsigned int);
unsigned __int64 _blcfill_u64(unsigned __int64);
unsigned __int64 _blsfill_u64(unsigned __int64);
unsigned __int64 _blcs_u64(unsigned __int64);
unsigned __int64 _tzmsk_u64(unsigned __int64);
unsigned __int64 _blcic_u64(unsigned __int64);
unsigned __int64 _blsic_u64(unsigned __int64);
unsigned __int64 _t1mskc_u64(unsigned __int64);
unsigned __int64 _blcmsk_u64(unsigned __int64);
unsigned __int64 _blci_u64(unsigned __int64);
#endif  /* defined (_M_X64) */

void _mm_monitorx(void const *, unsigned int, unsigned int);
void _mm_mwaitx(unsigned int, unsigned int, unsigned int);

void _mm_clzero(void const *);

#if defined __cplusplus
}; /* End "C" */
#endif  /* defined __cplusplus */

#endif  /* defined (_M_CEE_PURE) */
#endif  /* __midl */
#endif  /* _INCLUDED_AMM */
