#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
VOID bCheckNumericLimits() {
	xASSERT(CHAR_BIT      == 8);         /* number of bits in a char */

	xASSERT(SCHAR_MIN   == (-128));      /* minimum signed char value */
	xASSERT(SCHAR_MAX     == 127);       /* maximum signed char value */
	xASSERT(UCHAR_MAX     == 0xff);      /* maximum unsigned char value */

	#ifndef _CHAR_UNSIGNED
		xASSERT(CHAR_MIN    == SCHAR_MIN);   /* mimimum char value */
		xASSERT(CHAR_MAX    == SCHAR_MAX);   /* maximum char value */
	#else
		xASSERT(CHAR_MIN    == 0);
		xASSERT(CHAR_MAX    == UCHAR_MAX);
	#endif  /* _CHAR_UNSIGNED */

	xASSERT(MB_LEN_MAX    == 5);             /* max. # bytes in multibyte char */
	xASSERT(SHRT_MIN      == (-32768));        /* minimum (signed) short value */
	xASSERT(SHRT_MAX      == 32767);         /* maximum (signed) short value */
	xASSERT(USHRT_MAX     == 0xffff);        /* maximum unsigned short value */
	xASSERT(INT_MIN       == (-2147483647 - 1)); /* minimum (signed) int value */
	xASSERT(INT_MAX       == 2147483647);    /* maximum (signed) int value */
	xASSERT(UINT_MAX      ==  0xffffffff);    /* maximum unsigned int value */
	xASSERT(LONG_MIN      == (-2147483647L - 1)); /* minimum (signed) long value */
	xASSERT(LONG_MAX      == 2147483647L);   /* maximum (signed) long value */
	xASSERT(ULONG_MAX     == 0xffffffffUL);  /* maximum unsigned long value */
	xASSERT(LLONG_MAX     == 9223372036854775807i64);       /* maximum signed long long int value */
	xASSERT(LLONG_MIN     == (-9223372036854775807i64 - 1));  /* minimum signed long long int value */
	xASSERT(ULLONG_MAX    == 0xffffffffffffffffui64);       /* maximum unsigned long long int value */

	xASSERT(_I8_MIN       == (-127i8 - 1));    /* minimum signed 8 bit value */
	xASSERT(_I8_MAX       == 127i8);         /* maximum signed 8 bit value */
	xASSERT(_UI8_MAX      == 0xffui8);       /* maximum unsigned 8 bit value */

	xASSERT(_I16_MIN      == (-32767i16 - 1)); /* minimum signed 16 bit value */
	xASSERT(_I16_MAX      == 32767i16);      /* maximum signed 16 bit value */
	xASSERT(_UI16_MAX     == 0xffffui16);    /* maximum unsigned 16 bit value */

	xASSERT(_I32_MIN      == (-2147483647i32 - 1)); /* minimum signed 32 bit value */
	xASSERT(_I32_MAX      == 2147483647i32); /* maximum signed 32 bit value */
	xASSERT(_UI32_MAX     == 0xffffffffui32); /* maximum unsigned 32 bit value */

		/* minimum signed 64 bit value */
	xASSERT(_I64_MIN      == (-9223372036854775807i64 - 1));
		/* maximum signed 64 bit value */
	xASSERT(_I64_MAX      == 9223372036854775807i64);
		/* maximum unsigned 64 bit value */
	xASSERT(_UI64_MAX     == 0xffffffffffffffffui64);

	#if     _INTEGRAL_MAX_BITS >= 128
		/* minimum signed 128 bit value */
	xASSERT(_I128_MIN     == (-170141183460469231731687303715884105727i128 - 1));
		/* maximum signed 128 bit value */
	xASSERT(_I128_MAX     == 170141183460469231731687303715884105727i128);
		/* maximum unsigned 128 bit value */
	xASSERT(_UI128_MAX    == 0xffffffffffffffffffffffffffffffffui128);
	#endif

	#ifndef SIZE_MAX
	#ifdef _WIN64 
	xASSERT(SIZE_MAX == _UI64_MAX);
	#else
	xASSERT(SIZE_MAX == UINT_MAX);
	#endif
	#endif

	#if __STDC_WANT_SECURE_LIB__
		/* While waiting to the C standard committee to finalize the decision on RSIZE_MAX and rsize_t,
		* we define RSIZE_MAX as SIZE_MAX
		*/
	#ifndef RSIZE_MAX
	xASSERT(RSIZE_MAX == SIZE_MAX);
	#endif
	#endif

	#ifdef  _POSIX_
		xASSERT(_POSIX_ARG_MAX      == 4096);
		xASSERT(_POSIX_CHILD_MAX    == 6);
		xASSERT(_POSIX_LINK_MAX     == 8);
		xASSERT(_POSIX_MAX_CANON    == 255);
		xASSERT(_POSIX_MAX_INPUT    == 255);
		xASSERT(_POSIX_NAME_MAX     == 14);
		xASSERT(_POSIX_NGROUPS_MAX  == 0);
		xASSERT(_POSIX_OPEN_MAX     == 16);
		xASSERT(_POSIX_PATH_MAX     == 255);
		xASSERT(_POSIX_PIPE_BUF     == 512);
		xASSERT(_POSIX_SSIZE_MAX    == 32767);
		xASSERT(_POSIX_STREAM_MAX   == 8);
		xASSERT(_POSIX_TZNAME_MAX   == 3);

		xASSERT(ARG_MAX             == 14500);       /* 16k heap, minus overhead */
		xASSERT(LINK_MAX            == 1024);
		xASSERT(MAX_CANON           == _POSIX_MAX_CANON);
		xASSERT(MAX_INPUT           == _POSIX_MAX_INPUT);
		xASSERT(NAME_MAX            == 255);
		xASSERT(NGROUPS_MAX         == 16);
		xASSERT(OPEN_MAX            == 32);
		xASSERT(PATH_MAX            == 512);
		xASSERT(PIPE_BUF            == _POSIX_PIPE_BUF);
		xASSERT(SSIZE_MAX           == _POSIX_SSIZE_MAX);
		xASSERT(STREAM_MAX          == 20);
		xASSERT(TZNAME_MAX          == 10);
	#endif  /* POSIX */
}
//---------------------------------------------------------------------------
