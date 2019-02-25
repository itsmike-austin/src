/* *************************************************************************
 * These are the default versions for various elements if they are not
 * supplied through external defines.
 * -------------------------------------------------------------------------
 * (c) ItsInc. 1999, 2001, 2005, 2006
 * ************************************************************************* */

#if defined(_WIN32) || defined(_WIN64)
#pragma once
#endif

#ifndef _ITS_VERSION_H
#define _ITS_VERSION_H

#if defined(_WIN32) || defined(_WIN64)

// Internet Explorer Version
// Vista: should be 0x0700
//

#if !defined(_WIN32_IE)
#define _WIN32_IE    0x0600
#endif

// Windows Version
// 0x0501 (XP)
// Other versions (95/98/ME) Are not going to be supported.
//

#if !defined(_WINVER)
#define _WINVER      0x0400
#endif

// WindowsNT Version
// 0x0400: Windows NT 4.0
// 0x0500: Windows NT 5.0 (Server 2000)
// 0x0501: Windows NT 5.1 (XP)
// 0x0502: Windows NT 5.2 (Server 2003)
// Vista should be 0x0503
//

#if !defined(_WIN32_WINNT)
#define _WIN32_WINNT 0x0500
#endif

#endif

#endif
