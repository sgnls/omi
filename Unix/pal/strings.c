/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "strings.h"

/* Strlcat and Strlcpy */
#define DEST char
#define SRC char
#define STRLCAT Strlcat
#define STRLCPY Strlcpy
#include "strlcat.h"
#include "strlcpy.h"
#undef STRLCAT
#undef STRLCPY
#undef DEST
#undef SRC

/* Wcslcat and Wcslcpy */
#define DEST wchar_t
#define SRC wchar_t
#define STRLCAT Wcslcat
#define STRLCPY Wcslcpy
#include "strlcat.h"
#include "strlcpy.h"
#undef STRLCAT
#undef STRLCPY
#undef DEST
#undef SRC

/* StrWcslcat and StrWcslcpy */
#define DEST char
#define SRC wchar_t
#define STRLCPY StrWcslcpy
#include "strlcpy.h"
#undef STRLCPY
#undef DEST
#undef SRC

/* WcsStrlcat and WcsStrlcpy */
#define DEST wchar_t
#define SRC char
#define STRLCPY WcsStrlcpy
#include "strlcpy.h"
#undef STRLCPY
#undef DEST
#undef SRC

/* TcsStrlcat and TcsStrlcpy */
#define DEST TChar
#define SRC char
#define STRLCAT TcsStrlcat
#define STRLCPY TcsStrlcpy
#include "strlcat.h"
#include "strlcpy.h"
#undef STRLCAT
#undef STRLCPY
#undef DEST
#undef SRC

/* StrTcslcat and StrTcslcpy */
#define DEST char
#define SRC TChar
#define STRLCAT StrTcslcat
#define STRLCPY StrTcslcpy
#include "strlcat.h"
#include "strlcpy.h"
#undef STRLCAT
#undef STRLCPY
#undef DEST
#undef SRC

_Post_satisfies_(*size == _String_length_(*result))
void TcsFromUInt64(_Pre_writable_size_(64) PAL_Char buf[64], PAL_Uint64 value, _Outptr_result_z_ const PAL_Char **result, _Out_opt_ size_t* size)
{
    PAL_Char* p;

    p = &buf[63];
    *p = PAL_T('\0');

    do
    {
        *--p = PAL_T('0') + value % 10;
    }
    while (value /= 10);

    *result = p;

    if(size)
    {
        *size = (PAL_Sint32)(&buf[63] - p);
    }
}

#if !defined(CONFIG_FAVORSIZE)

// The following defines string literals for the numbers 0 through 63. The
// first character is the length of the string. The subsequent characters
// are the string literal iteslf.
static const char* _numberStrings[] =
{
    "\0010",
    "\0011",
    "\0012",
    "\0013",
    "\0014",
    "\0015",
    "\0016",
    "\0017",
    "\0018",
    "\0019",
    "\00210",
    "\00211",
    "\00212",
    "\00213",
    "\00214",
    "\00215",
    "\00216",
    "\00217",
    "\00218",
    "\00219",
    "\00220",
    "\00221",
    "\00222",
    "\00223",
    "\00224",
    "\00225",
    "\00226",
    "\00227",
    "\00228",
    "\00229",
    "\00230",
    "\00231",
    "\00232",
    "\00233",
    "\00234",
    "\00235",
    "\00236",
    "\00237",
    "\00238",
    "\00239",
    "\00240",
    "\00241",
    "\00242",
    "\00243",
    "\00244",
    "\00245",
    "\00246",
    "\00247",
    "\00248",
    "\00249",
    "\00250",
    "\00251",
    "\00252",
    "\00253",
    "\00254",
    "\00255",
    "\00256",
    "\00257",
    "\00258",
    "\00259",
    "\00260",
    "\00261",
    "\00262",
    "\00263",
};

#endif /* !defined(CONFIG_FAVORSIZE) */

_Post_satisfies_(*size == _String_length_(*result))
void Uint64ToStr(_Pre_writable_size_(21) char buf[21], PAL_Uint64 value, _Outptr_result_z_ const char **result,  _Out_opt_ size_t* size)
{
    char* p;        
        
#if !defined(CONFIG_FAVORSIZE)

    if (value < 64)
    {
        if(size)
        {
            *size = _numberStrings[value][0];
        }
        *result = &_numberStrings[value][1];
    }

#endif /* !defined(CONFIG_FAVORSIZE)*/

    p = &buf[20];
    *p = '\0';

    do
    {
        *--p = '0' + value % 10;
    }
    while (value /= 10);

    if(size)
    {
        *size = &buf[20] - p;
    }

    *result = p;
}

_Use_decl_annotations_
const char* Uint32ToStr(char buf[11], PAL_Uint32 x, size_t* size)
{
    char* p;

#if !defined(CONFIG_FAVORSIZE)

    if (x < 64)
    {
        *size = _numberStrings[x][0];
        return &_numberStrings[x][1];
    }

#endif /* !defined(CONFIG_FAVORSIZE)*/

    p = &buf[10];
    *p = '\0';

    do
    {
        *--p = '0' + x % 10;
    }
    while (x /= 10);

    *size = &buf[10] - p;
    return p;
}

_Post_satisfies_(*size == _String_length_(*result))
void Sint64ToZStr(_Pre_writable_size_(64) TChar buf[64], PAL_Sint64 value, _Outptr_result_z_ const TChar **result, _Out_opt_ size_t* size)
{
    TChar* p;

    PAL_Boolean isNegative = PAL_FALSE;    
    if(value < 0)
    {
        isNegative = 1;
        value = -value;
    }

    p = &buf[63];
    *p = PAL_T('\0');

    do
    {
        *--p = PAL_T('0') + value % 10;
    }
    while (value /= 10);

    if(isNegative)
    {
        *--p = PAL_T('-');
    }

    if(size)
    {
        *size = (PAL_Sint32)(&buf[63] - p);
    }

    *result = p;
}


