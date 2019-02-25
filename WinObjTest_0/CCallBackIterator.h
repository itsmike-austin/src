#if defined(_WIN32) || defined(_WIN64)
#pragma once
#endif

#ifndef __CCALLBACK_ITERATOR_H
#define __CCALLBACK_ITERATOR_H

#include <CCallBack.h>

class CCallBackIterator
{
 private:
  CCallBack** m_CallbackList;
  int         m_Entry;
  int         m_Length;

 public:
  CCallBackIterator();
  CCallBackIterator(CCallBack** ppCallList,int nCallListSize);

  CCallBack* begin();
  int        length();
  int        left();

  CCallBack* operator()();
};

#endif
