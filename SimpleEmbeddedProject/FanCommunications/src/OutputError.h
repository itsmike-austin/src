/* ==========================================================================
 * OutputError:
 *    The OutputError module has a single method:
 *        OutputError: Used to send an error message to syslog
 *
 *        void OutputError(char* pSource):
 *             pSource should be a unique identifier to mark the specific
 *             location where the error occurred for debugging.
 *
 * --------------------------------------------------------------------------
 * (c) 2000 itsinc (mdb)
 *          Updated over time whenever additional errno members have appeared
 * ========================================================================== */

#ifndef _OUTPUT_ERROR_H
#define _OUTPUT_ERROR_H

#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <errno.h>

void OutputError(char* pMsg);

#endif
