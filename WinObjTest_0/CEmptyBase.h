/* ************************************************************
 * Classes can be derrived from empty base to assure that
 * pointers to methods are sized appropriately. This header
 * should be included by other headers prior to defining
 * method typedefs. This assures that compilers such as g++ and
 * Microsoft correctly size the method pointers. These compilers
 * will incorrectly assume pointer sizes for methods when
 * typedefs are not defined after a class definition. Forward
 * declarations are required.
 *
 * To repair forward declaration issues:
 *
 * typedef -return- (CEmptyBase::*FunctionPointer)(-args)
 * eg:
 * typedef unsigned long (CEmptyBase::*FcnPtr)(long,long,long);
 *
 * Foreign method pointers can use reinterpret_cast to instance
 * the appropriate class.
 *
 * eg:
 * FcnPtr a = reinterpret_cast<FcnPtr>(joe::bob);
 *
 * Extending CEmptyBase with a method interface pointer
 * allows for dynamic casting of methods through superclassing.
 * Language purists will warn that the compiler can reconstruct
 * and copy using (X const X&). Please check your compiler to
 * assure no memory reorganization when dynamic casting. I have
 * never experienced assmebly that initiates (X const X&)
 * conversion when dynamic casting, but the language
 * specification allows for this possibility. (Damn purists
 * never do any real work!)
 *
 * The following example is incorrect:
 *
 * class Test;                    // Forward definition
 * typedef void (Test::*Pfn)();   // Use before definition of
 *                                // Test will result in
 *                                // invalid sizeof(Pfn)
 *
 * void DumpIt() {
 *   Pfn a;          // MS defined as __m64:__m64 (__m128)
 * }
 *
 * All successfive uses of Pfn will effectively be _m128
 *
 * The following example is correct;
 *
 * typedef void (CEmptyBase::*Pfn)();
 *
 * class Test;
 * typedef void (Test::*ACall)(); // Currently __m128
 *                                // Should not be used
 *                                // in external classes
 *
 * class Test : public CEmptyBase
 * {
 *   public:
 *     Pfn   m_MethodPtr;
 *     ACall m_CallMethodPtr;     // Forces resize (Both
 *
 *     void SomeCall()    { std::cout << "hi" << std::endl; }
 *     void DoBlindCall() { (this->*m_MethodPtr)(); }
 * };
 *
 * int main()
 * {
 *    Test a;
 *    a.m_MethodPtr = reinterpret_cast<Pfn>(&Test::SomeCall);
 *    a.DoBlindCall();
 *    return 0;
 * }
 *
 * Alternatively
 *
 * int main()
 * {
 *   Test a;
 *
 *   // Superclass style     : portable
 *   //
 *
 *   a.m_MethodPtr     = reinterpret_cast<Pfn>(&Test::SomeCall);
 *
 *   // ACall External Style : can cause failures
 *   //
 *
 *   a.m_CallMethodPtr = reinterpret_cast<ACall>(a.m_MethodPtr);
 *
 *   // ACll Cast Style      : can cause failures
 *   //
 *
 *   a.m_CallMethodPtr = (ACall)&Test::SomeCall;
 *
 *   return 0;
 * }
 * ------------------------------------------------------------
 * (c) ItsInc. 1999, 2001, 2005, 2006
 * ************************************************************ */

#if defined(_WIN32) || defined(_WIN64)
#pragma once
#endif

#ifndef _CEMPTY_BASE_H
#define _CEMPTY_BASE_H

#include "StdAfx.h"
#include <ItsStdDefs.h>
#include <ItsStdIncs.h>

// Empty base class used for superclassing callback methods
//

class CCallbackClass {};

// EmptyBase used for superclassing classes
//

class CEmptyBase : public CCallbackClass {};

#endif
