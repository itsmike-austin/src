#include <CCallBackIterator.h>

CCallBackIterator::CCallBackIterator() :
  m_CallbackList(NULL),
  m_Entry(0),
  m_Length(0) {}

CCallBackIterator::CCallBackIterator(CCallBack** ppCallList,int nCallListSize) :
  m_CallbackList(ppCallList),
  m_Entry(0),
  m_Length(nCallListSize) {}

CCallBack* CCallBackIterator::begin()
{
  m_Entry = 0;
  return (NULL != m_CallbackList ? m_CallbackList[m_Entry] : NULL);
}

int CCallBackIterator::length() { return m_Length; }

int CCallBackIterator::left() { return (m_Length - m_Entry); }

CCallBack* CCallBackIterator::operator()()
{
  CCallBack* pCallback = (NULL != m_CallbackList && m_Entry < m_Length ?
			  m_CallbackList[m_Entry] : NULL);

  if ( NULL != pCallback ) ++m_Entry;

  return pCallback;
}
