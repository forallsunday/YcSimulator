/*
 * @file sysTypes.h
 * @brief
 *    功能:
 *      <li>定义一些系统级数据类型和一些关键宏</li>
 */

#ifndef __SYSTYPES_H__
#define __SYSTYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

/*宏定义*/

#define FAST		register
#define IMPORT		extern
#define LOCAL		static

#if    !defined(FALSE) || (FALSE!=0)
#undef  FALSE
#define FALSE   (0)
#endif

#ifndef __cplusplus

#if    !defined(false) || (false!=0)
#undef  false
#define false   (0)
#endif

#if    !defined(true) || (true!=1)
#undef  true
#define true    (1)
#endif

#else

#define false	false
#define true	true

#endif /* __cplusplus */

#if    !defined(TRUE) || (TRUE!=1)
#undef  TRUE
#define TRUE    (1)
#endif

#if    !defined(OK) || (OK!=0)
#undef  OK
#define OK      (0)
#endif

#if    !defined(ERROR) || (ERROR!=(-1))
#undef  ERROR
#define ERROR   (-1)
#endif

#if !defined(EOF) || (EOF!=(-1))
#define EOF     (-1)
#endif

#ifndef NULL
#define NULL    (0)
#endif

#define FAILURE (1)

#ifndef FAIL
#define FAIL	(-1)
#endif

#ifndef SUCC
#define SUCC	(0)
#endif

#define NONE    (-1)    /* for times when NULL won't do */
#define EOS     ('\0')    /* C string terminator */

/* timeout defines */

#define NO_WAIT         (0)
#define WAIT_FOREVER    (-1)

/* 对齐操作宏定义 */
#define ROUND_UP(x, align)      (((int) (x) + ((align) - 1)) & ~((align) - 1))
#define ROUND_DOWN(x, align)    ((int)(x) & ~((align) - 1))
#define ALIGNED(x, align)       (((int)(x) & ((align) - 1)) == 0)

/*该宏定义计算数组元素的大小 */
#define NELEMENTS(array)        (sizeof (array) / sizeof ((array) [0]))

#define LSB(x)      ((x) & 0xff)             /* 取低字节宏 */
#define MSB(x)      (((x) >> 8) & 0xff)      /* 取高字节宏 */
#define LSW(x)      ((x) & 0xffff)           /* 取低字宏 */
#define MSW(x)      (((x) >> 16) & 0xffff)   /* 取高字宏 */

/* 32位字按字倒序宏*/
#define WORDSWAP(x) (MSW(x) | (LSW(x) << 16))

/* 32位字按字节倒序宏*/
#define LLSB(x)     ((x) & 0xff)
#define LNLSB(x)    (((x) >> 8) & 0xff)
#define LNMSB(x)    (((x) >> 16) & 0xff)
#define LMSB(x)     (((x) >> 24) & 0xff)
#define LONGSWAP(x) ((LLSB(x) << 24)|(LNLSB(x) << 16)|(LNMSB(x) << 8)|(LMSB(x)))

#define OFFSET(structure, member)   /* byte offset of member in structure*/\
        ((int) &(((structure *) 0) -> member))

#define MEMBER_SIZE(structure, member)  /* size of a member of a structure */\
        (sizeof (((structure *) 0) -> member))

#define NELEMENTS(array)        /* number of elements in an array */ \
        (sizeof (array) / sizeof ((array) [0]))

#define FOREVER for (;;)

// #define max(x, y)   (((x) < (y)) ? (y) : (x))
// #define min(x, y)   (((x) < (y)) ? (x) : (y))

#define _STACK_ALIGN_SIZE       (16)      /* stack alignment */
#define _ALLOC_ALIGN_SIZE       (16)      /* allocation alignment */

#define MEM_ROUND_UP(x)         ROUND_UP((x), _ALLOC_ALIGN_SIZE)
#define MEM_ROUND_DOWN(x)       ROUND_DOWN((x), _ALLOC_ALIGN_SIZE)
#define STACK_ROUND_UP(x)       ROUND_UP((x), _STACK_ALIGN_SIZE)
#define STACK_ROUND_DOWN(x)     ROUND_DOWN((x), _STACK_ALIGN_SIZE)
#define MEM_ALIGNED(x)          ALIGNED((x), _ALLOC_ALIGN_SIZE)

/* 时间定义 */
#define MICROSECOND(X)          ((X)*1)
#define MILLISECOND(X)          ((X)*1000)
#define SECOND(X)               ((X)*1000000)

/* 为支持应用软件对齐要求增加宏定义 */
#ifndef _WRS_PACK_ALIGN
#define _WRS_PACK_ALIGN(x) __attribute__((packed, aligned(x)))
#endif /* _WRS_PACK_ALIGN */

#define T_VOID	    void
#define T_VVOID		volatile void

#define T_MODULE    static
#define T_INLINE    T_MODULE __inline__
#define T_EXTERN    extern
#define T_VOLATILE	volatile
#define T_CONST		const

#define ACOREOS_INLINE_ROUTINE  static __inline__

#ifndef _ASMLANGUAGE
/*类型定义*/
typedef int             STATUS;

typedef signed char     T_BYTE;     /*8-bit signed integer */
typedef unsigned char   T_UBYTE;    /*8-bit unsigned integer */

typedef	signed short    T_HWORD;    /*16-bit signed integer */
typedef	unsigned short  T_UHWORD;   /*16-bit unsigned integer */

typedef	signed int      T_WORD;     /*32-bit signed integer */
typedef unsigned int    T_UWORD;    /*32-bit unsigned integer */
typedef char            T_CHAR;

/*
*  VC 环境下:
*    typedef LONGLONG    T_DWORD;
*    typedef ULONGLONG   T_UDWORD;
*
*/
typedef	signed long long        T_DWORD;    /*64-bit signed integer */
typedef unsigned long long      T_UDWORD;   /*64-bit unsigned integer */

typedef	double                  T_DOUBLE;
typedef float                   T_FLOAT;

typedef unsigned int            T_BOOL;    /*8-bit unsigned integer */

typedef	volatile signed char    T_VBYTE;
typedef volatile unsigned char  T_VUBYTE;

typedef	volatile signed short   T_VHWORD;
typedef	volatile unsigned short T_VUHWORD;

typedef	volatile signed int     T_VWORD;
typedef volatile unsigned int   T_VUWORD;

/*
*  VC 环境下:
*    typedef volatile LONGLONG    T_VDWORD;
*    typedef volatile ULONGLONG   T_VUDWORD;
*
*/

typedef volatile signed long long		T_VDWORD;
typedef volatile unsigned long long		T_VUDWORD;

typedef	volatile double					T_VDOUBLE;
typedef volatile float				    T_VFLOAT;

typedef volatile unsigned int			T_VBOOL;

typedef unsigned char           UINT8;      /* unsigned 8-bit  integer */
typedef unsigned short          UINT16;     /* unsigned 16-bit integer */
typedef unsigned int            UINT32;     /* unsigned 32-bit integer */
typedef unsigned long long      UINT64;     /* unsigned 64-bit integer */
typedef signed char             INT8;       /* 8-bit  signed integer */
typedef signed short            INT16;      /* 16-bit signed integer */
typedef signed int              INT32;      /* 32-bit signed integer */
typedef signed long long        INT64;      /* 64 bit signed integer */
typedef float                   SINGLE;     /* single precision float */
typedef double                  DOUBLE;     /* double precision float */
typedef unsigned int            BOOL;       /* Boolean value   */
typedef unsigned int            boolean;
typedef unsigned long           ULONG;
typedef long           			LONG;
typedef unsigned int            UINT;
typedef int                     ARGINT;
typedef void                    VOID;
typedef void *                  OBJ_ID;

typedef unsigned int _RType;

/* 系统中的函数指针类型定义 */
typedef int             (*FUNCPTR) ();     /* ptr to function returning int */
typedef void            (*VOIDFUNCPTR)();
typedef double          (*DBLFUNCPTR) ();  /* ptr to function returning double*/
typedef float           (*FLTFUNCPTR) ();  /* ptr to function returning float */
typedef void            *(*VOIDPTRFUNCPTR) ();

typedef BOOL            (*PROCFUNCPTR) ( UINT32, UINT32 );     /* ptr to function returning int */
typedef void            (*SIGNAL_FUNCPTR) ();      /* ptr to function returning int */
typedef UINT32          (*USER_APPEND_ENTRY)(UINT32,UINT32);

typedef unsigned char   UCHAR;


#endif

#ifdef __cplusplus
}
#endif

#endif



