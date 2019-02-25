/* *************************************************************************
 * These includes are used in most modules. They are generally built as
 * pre-compiled headers to expedite compilation.
 * -------------------------------------------------------------------------
 * (c) ItsInc. 1999, 2001, 2005, 2006
 * ************************************************************************* */

#if defined(_WIN32) || defined(_WIN64)
#pragma once
#endif

#ifndef _ITS_STD_INCS_H
#define _ITS_STD_INCS_H

#ifndef _UNICODE
#define _UNICODE
#define  UNICODE
#endif

#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#endif

#endif
