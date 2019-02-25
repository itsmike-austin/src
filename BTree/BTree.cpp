#include <BTree.h>

/* =====================================================================
 *                           PRIVATE METHODS
 * ===================================================================== */

/* ---------------------------------------------------------------------
 *                          OPERATION METHODS
 * --------------------------------------------------------------------- */

// - GetRoot -----------------------------------------------------------

template <class T> inline BTree<T>* BTree<T>::GetRoot() {

  BTree<T>* pTemp;
  BTree<T>* pBase   = this;
  bool     bDoMore = true;

  do {
    if ( (pTemp=pBase->GetParent()) ) {
      pBase = pTemp;
    }else{
      bDoMore = false;
    }
  }while( bDoMore );

  return pBase;
}

/* ---------------------------------------------------------------------
 *                          ACCESSOR METHODS
 * --------------------------------------------------------------------- */

// - GetParent ---------------------------------------------------------

template <class T> inline BTree<T>* BTree<T>::GetParent()
{
  return m_Parent;
}

// - PutParent ---------------------------------------------------------

template <class T> inline BTree<T>* BTree<T>::PutParent(BTree<T>* pParent)
{
  BTree<T>* pTemp = m_Parent;
  m_Parent = pParent;
  return pTemp;
}

// - GetLessThan -------------------------------------------------------

template <class T> inline BTree<T>* BTree<T>::GetLessThan()
{
  return m_Less;
}

// - PutLessThan -------------------------------------------------------

template <class T> inline BTree<T>* BTree<T>::PutLessThan(BTree<T>* pLess)
{
  BTree<T>* pTemp = m_Less;
  m_Less = pLess;
  return pTemp;
}

// - GetGreaterThan ----------------------------------------------------

template <class T> inline BTree<T>* BTree<T>::GetGreaterThan()
{
  return m_Great;
}

// - PutGreaterThan ----------------------------------------------------

template <class T> inline BTree<T>* BTree<T>::PutGreaterThan(BTree<T>* pGreat)
{
  BTree<T>* pTemp = m_Great;
  m_Great = pGreat;
  return pTemp;
}

// - GetUnlockedValue --------------------------------------------------

template <class T> inline T* BTree<T>::GetUnlockedValue()
{
  return m_Data;
}

// - PutUnlockedValue --------------------------------------------------

template <class T> inline T* BTree<T>::PutUnlockedValue(T* pValue)
{
  T* pTemp = m_Data;
  m_Data = pValue;
  return pTemp;
}

template <class T> unsigned long BTree<T>::GetLittleEndian(unsigned long lBigEndian)
{
  static unsigned short uTestValue = 0x8040;
  char*  pValue = (char*)&uTestValue;

  if ( 0x80 == (unsigned char)*pValue ) return lBigEndian;

  return _lrotl(((lBigEndian & 0xFF00FF00) >> 8) |
		((lBigEndian & 0x00FF00FF) << 8),16);
}


#if 0
{
  if ( 4 == sizeof lBigEndian )
    {
      return
	_lrotl(((lBigEndian & 0xFF00FF00) >> 8) |
	       ((lBigEndian & 0x00FF00FF) << 8),16);
    }
  else
    {
      char*    cp;
      unsigned _int64 Base = lBigEndian;
      unsigned _int32 LowPart  = (unsigned _int32)(lBigEndian & 0x00000000FFFFFFFF);
      unsigned _int32 HighPart = (unsigned _int32)(lBigEndian & 0xFFFFFFFF00000000 >> 32);
      LowPart = _lrotl(((LowPart & 0xFF00FF00) >> 8) |
		       ((LowPart & 0x00FF00FF) << 8),16);
      HighPart = _lrotl(((HighPart & 0xFF00FF00) >> 8) |
			((HighPart & 0x00FF00FF) << 8),16);
      cp = (char*)&Base;
      memcpy((void*)cp,(void*)&HighPart,sizeof LowPart);
      cp += sizeof LowPart;
      memcpy((void*)cp,(void*)&LowPart,sizeof LowPart);

      return Base;
    }
}
#endif

template <class T> unsigned short BTree<T>::GetLittleEndian(unsigned short sBigEndian)
{
  static unsigned short uTestValue = 0x8040;
  char*  pValue = (char*)&uTestValue;

  if ( 0x80 == (unsigned char)*pValue ) return sBigEndian;

  unsigned char pLow = *((unsigned char*)&sBigEndian);

  sBigEndian <<= 4;

  *(((unsigned char*)&sBigEndian)+1) = pLow;

  return sBigEndian;
}

#if defined(_MT)

// - GetCriticalSection ------------------------------------------------

template <class T> inline LPCRITICAL_SECTION BTree<T>::GetCriticalSection()
{
  return m_cs;
}

// - PutCriticalSection ------------------------------------------------

template <class T> inline void BTree<T>::PutCriticalSection(LPCRITICAL_SECTION pCs)
{
  m_cs = pCs;
}

// - GetCritAutoAlloc ---------------------------------------------------

template <class T> inline bool BTree<T>::GetCritAutoAlloc()
{
  return m_CritAutoAlloc;
}

// - PutCritAutoAlloc --------------------------------------------------

template <class T> inline void BTree<T>::PutCritAutoAlloc(bool bFlag)
{
  m_CritAutoAlloc = bFlag;
}

#endif

/* ---------------------------------------------------------------------
 *                          MANAGEMENT METHODS
 * --------------------------------------------------------------------- */

// - GetSortList -------------------------------------------------------

template <class T> inline BTree<T>** BTree<T>::GetSortList()
{
  BTree<T>** pList;
  BTree<T>*  pTemp;
  int        nCount;
  int        nItemCount;
  bool       bDoMore = true;
  BTree<T>*  pRoot = this->GetRoot();
  
  if ( !(nItemCount=pRoot->GetCount()) ) return NULL;

  pList = new BTree<T>*[nItemCount];

  nCount = 0;

  // Start with the smallest entry
  //

  pTemp = pRoot;

  while( pTemp->GetLessThan() && pTemp->m_Searched == 0 ) {
    pTemp = pTemp->GetLessThan();
  }

  do {

    // Find out where to go
    //

    if ( !pTemp->GetLessThan()    &&
	 !pTemp->GetGreaterThan() &&
	 !pTemp->m_Searched       ) {                    // End leaf

      pList[nCount++] = pTemp;
      pTemp->m_Searched = true;

      if ( pTemp->GetParent() ) pTemp = pTemp->GetParent();

    }else if ( pTemp->GetLessThan()              &&
	       !pTemp->GetLessThan()->m_Searched ) {     // < leaf

      pTemp = pTemp->GetLessThan();

    }else if ( pTemp->GetGreaterThan()              &&
	       !pTemp->GetGreaterThan()->m_Searched ) {  // > leaf w/o < leaf

      pList[nCount++] = pTemp;
      pTemp->m_Searched = true;

      pTemp = pTemp->GetGreaterThan();

    }else if ( !pTemp->m_Searched ) {                     // singleton

      pList[nCount++] = pTemp;
      pTemp->m_Searched = true;

      if( pTemp->GetParent() ) pTemp = pTemp->GetParent();

    }else if ( pTemp->m_Searched  &&
	       pTemp->GetParent() ) {                     // upline signal

      pTemp = pTemp->GetParent();

    }else if ( !pTemp->GetParent() &&
	       pTemp->m_Searched ) {                      // terminator
      bDoMore = false;
    }

  }while( bDoMore && nCount < nItemCount );

  // Sort completed, clear entries for next sort operation
  //

  for( int i=0 ; i < nItemCount ; ++i ) pList[i]->m_Searched = false;

  return pList;
}

// - AddNode -----------------------------------------------------------

template <class T> inline BTree<T>** BTree<T>::AddNode(BTree<T>** pList,
						       int        nRoot,
						       int        nGreatCount,
						       int        nLessCount)
{
  int nLessCnt;
  int nGreatCnt;
  int nLess;
  int nGreat;

  if ( nLessCount )
    {
      nLess = (nLessCount > 3 ? nRoot - (nLessCount/2) :
	       nLessCount > 1 ? nRoot - 2 :
	       nRoot - 1);

      pList[nRoot]->PutLessThan(pList[nLess]);
      pList[nLess]->PutParent(pList[nRoot]);

      nLessCnt  = nLess - (nRoot - nLessCount);
      nGreatCnt = nRoot - nLess - 1;

      if ( nLessCnt  ) AddNode(pList,nLess,0,nLessCnt);
      if ( nGreatCnt ) AddNode(pList,nLess,nGreatCnt,0);
    }

  if ( nGreatCount )
    {
      nGreat = (nGreatCount > 3 ? nRoot+(nGreatCount/2) :
		nGreatCount > 1 ? nRoot+2 :
		nRoot+1);

      pList[nRoot]->PutGreaterThan(pList[nGreat]);
      pList[nGreat]->PutParent(pList[nRoot]);

      nLessCnt  = nGreat - nRoot - 1;
      nGreatCnt = nRoot + nGreatCount - nGreat;
      
      if ( nLessCnt  ) AddNode(pList,nGreat,0,nLessCnt);
      if ( nGreatCnt ) AddNode(pList,nGreat,nGreatCnt,0);
    }

  return pList;
}

// - Balance -----------------------------------------------------------

template <class T> inline BTree<T>* BTree<T>::Balance(BTree<T>** pList,int nItemCount )
{
  int i;

  // Calculate the basic positions for the tree
  //
  
  int nRoot       = nItemCount / 2;
  int nGreatCount = nItemCount - nRoot - 1;
  int nLessCount  = nRoot;

  // Clear the old values from the tree
  //

  for( i=0 ; i < nItemCount ; ++i ) {
    pList[i]->PutParent(NULL);
    pList[i]->PutGreaterThan(NULL);
    pList[i]->PutLessThan(NULL);
  }

  // Build the new tree
  //

  AddNode(pList,nRoot,nGreatCount,nLessCount);

  pList[nRoot]->m_ItemCount = nItemCount;

  return pList[nRoot];
}

// - AddStreamNode -----------------------------------------------------

template <class T> inline BTree<T>** BTree<T>::AddStreamNode(BTree<T>** pList,
							     int        nRoot,
							     int        nGreatCount,
							     int        nLessCount)
{
  int nLessCnt;
  int nGreatCnt;
  int nLess;
  int nGreat;

  if ( nLessCount )
    {
      nLess = (nLessCount > 3 ? nRoot - (nLessCount/2) :
	       nLessCount > 1 ? nRoot - 2 :
	       nRoot - 1);

      pList[nRoot]->PutLessThan(pList[nLess]);
      pList[nRoot]->pTreePtr->Less = nLess;
      pList[nLess]->PutParent(pList[nRoot]);
      pList[nLess]->pTreePtr->Parent = nRoot;

      nLessCnt  = nLess - (nRoot - nLessCount);
      nGreatCnt = nRoot - nLess - 1;

      if ( nLessCnt  ) AddStreamNode(pList,nLess,0,nLessCnt);
      if ( nGreatCnt ) AddStreamNode(pList,nLess,nGreatCnt,0);
    }

  if ( nGreatCount )
    {
      nGreat = (nGreatCount > 3 ? nRoot+(nGreatCount/2) :
		nGreatCount > 1 ? nRoot+2 :
		nRoot+1);

      pList[nRoot]->PutGreaterThan(pList[nGreat]);
      pList[nRoot]->pTreePtr->Greater = nGreat;
      pList[nGreat]->PutParent(pList[nRoot]);
      pList[nGreat]->pTreePtr->Parent = nRoot;

      nLessCnt  = nGreat - nRoot - 1;
      nGreatCnt = nRoot + nGreatCount - nGreat;
      
      if ( nLessCnt  ) AddStreamNode(pList,nGreat,0,nLessCnt);
      if ( nGreatCnt ) AddStreamNode(pList,nGreat,nGreatCnt,0);
    }

  return pList;
}

// - StreamBalance -----------------------------------------------------

template <class T> inline BTree<T>* BTree<T>::StreamBalance(BTree<T>** pList,
							    int nItemCount )
{
  int i;

  // Calculate the basic positions for the tree
  //
  
  int nRoot       = nItemCount / 2;
  int nGreatCount = nItemCount - nRoot - 1;
  int nLessCount  = nRoot;

  TreePtr pTree;

  // Clear the old values from the tree and initialize
  // the new pseudo tree
  //

  for( i=0 ; i < nItemCount ; ++i ) {
    pList[i]->PutParent(NULL);
    pList[i]->PutGreaterThan(NULL);
    pList[i]->PutLessThan(NULL);
    pTree = new PseudoTreeStruct;
    pTree->Parent  = -1;
    pTree->Greater = -1;
    pTree->Less    = -1;
    pList[i]->pTreePtr = pTree;
  }

  // Build the list
  //

  AddStreamNode(pList,nRoot,nGreatCount,nLessCount);

  return pList[nRoot];
}

/* =====================================================================
 *                           PUBLIC METHODS
 * ===================================================================== */

/* ---------------------------------------------------------------------
 *                            Constructors
 * --------------------------------------------------------------------- */

#if !defined(_MT)

// - Empty Constructor -------------------------------------------------

template <class T> BTree<T>::BTree() :
  m_Less(NULL),
  m_Great(NULL),
  m_Parent(NULL),
  m_Data(NULL),
  m_ItemCount(1),
  m_Searched(false),
  pTreePtr(NULL)
{}

// - Reference Constructor ---------------------------------------------

template <class T> BTree<T>::BTree(T& rValue) :
  m_Less(NULL),
  m_Great(NULL),
  m_Parent(NULL),
  m_Data((T*)rValue),
  m_ItemCount(1),
  m_Searched(false),
  pTreePtr(NULL)
{}

// - Pointer Constructor -----------------------------------------------

template <class T> BTree<T>::BTree(T* pValue) :
  m_Less(NULL),
  m_Great(NULL),
  m_Parent(NULL),
  m_Data(pValue),
  m_ItemCount(1),
  m_Searched(false),
  pTreePtr(NULL)
{}

#else

// - Empty Constructor -------------------------------------------------

template <class T> BTree<T>::BTree() :
  m_Less(NULL),
  m_Great(NULL),
  m_Parent(NULL),
  m_Data(NULL),
  m_ItemCount(1),
  m_Searched(false),
  pTreePtr(NULL)
{
  m_cs = new CRITICAL_SECTION;
  if ( m_cs )
    {
      InitializeCriticalSection(m_cs);
      m_CritAutoAlloc = true;
    }
}


// - Reference Constructor ---------------------------------------------

template <class T> BTree<T>::BTree(T& rValue,LPCRITICAL_SECTION p_cs) :
  m_Less(NULL),
  m_Great(NULL),
  m_Parent(NULL),
  m_Data(&rValue),
  m_ItemCount(1),
  m_Searched(false),
  m_cs(p_cs),
  m_CritAutoAlloc(false),
  pTreePtr(NULL)
{}

// - Pointer Constructor -----------------------------------------------

template <class T> BTree<T>::BTree(T* pValue,LPCRITICAL_SECTION p_cs) :
  m_Less(NULL),
  m_Great(NULL),
  m_Parent(NULL),
  m_Data(pValue),
  m_ItemCount(1),
  m_Searched(false),
  m_cs(p_cs),
  m_CritAutoAlloc(false),
  pTreePtr(NULL)
{}

#endif

/* ---------------------------------------------------------------------
 *                            Destructor
 * --------------------------------------------------------------------- */

// XXX: Looks like this needs work.
//

template <class T> BTree<T>::~BTree()
{
#if defined(_MT)
  if ( NULL == m_Parent &&
       NULL == m_Less   &&
       NULL == m_Parent &&
       m_CritAutoAlloc  &&
       m_cs )
    {
      DeleteCriticalSection(m_cs);
      delete m_cs;
      m_cs = NULL;
    }
#endif
}


/* ---------------------------------------------------------------------
 *                        Public Accessor Methods
 * --------------------------------------------------------------------- */

// - GetValue ----------------------------------------------------------

template <class T> inline T* BTree<T>::GetValue()
{
#if defined(_MT)
  EnterCriticalSection(m_cs);
#endif

  T* pTemp = m_Data;

#if defined(_MT)
  LeaveCriticalSection(m_cs);
#endif

  return pTemp;
}

// - PutValue ----------------------------------------------------------

template <class T> inline T* BTree<T>::PutValue(T* pValue)
{
  T* pTemp = NULL;
#if defined(_MT)
  EnterCriticalSection(m_cs);
#endif

  if ( NULL == m_Data )
    {
      m_Data = pValue;
    }
  else
    {
      pTemp = (T*)-1;
    }

#if defined(_MT)
  LeaveCriticalSection(m_cs);
#endif

  return pTemp;
}

/* ---------------------------------------------------------------------
 *                     Object Methods
 * --------------------------------------------------------------------- */

// - Find --------------------------------------------------------------

template <class T> inline BTree<T>* BTree<T>::Find(T* pValue)
{
  int       nCompRc;
  BTree<T>* pTemp   = NULL;
  BTree<T>* pBase   = NULL;
  bool      bDoMore = true;

  if ( pValue ) {

#if defined(_MT)
    EnterCriticalSection(m_cs);
#endif

    pBase = ((pTemp=this->GetRoot()) ? pTemp : this);

    do {

      nCompRc = pBase->Compare(pBase->GetUnlockedValue(),pValue);

      if ( nCompRc < 0 && (pTemp=pBase->GetLessThan()) ) {
	  pBase = pTemp;

      }else if ( nCompRc < 0 ) {
	pBase = NULL;
	bDoMore = false;

      }else if ( nCompRc > 0 && (pTemp=pBase->GetGreaterThan()) ) {
	pBase = pTemp;

      }else if ( nCompRc > 0 ) {
	pBase = NULL;
	bDoMore = false;

      }else{
	bDoMore = false;
      }
    }while( bDoMore );

#if defined(_MT)
    LeaveCriticalSection(m_cs);
#endif
  }
  return pBase;
}

// - Find --------------------------------------------------------------

template <class T> inline BTree<T>* BTree<T>::Find(BTree<T>* pNode)
{
  int       nCompRc;
  BTree<T>* pTemp   = NULL;
  BTree<T>* pBase   = pNode;
  bool      bDoMore = true;
  T*        pNodeValue;

  if ( pNode ) {

#if defined(_MT)
    EnterCriticalSection(m_cs);
#endif

    pNodeValue = pNode->GetUnlockedValue();

    pBase = ((pTemp=this->GetRoot()) ? pTemp : this);

    do {

      nCompRc = pBase->Compare(pBase->GetUnlockedValue(),pNodeValue);

      if ( nCompRc < 0 && (pTemp=pBase->GetLessThan()) ) {
	pBase = pTemp;

      }else if ( nCompRc < 0 ) {
	pBase = NULL;
	bDoMore = false;

      }else if ( nCompRc > 0 && (pTemp=pBase->GetGreaterThan()) ) {
	pBase = pTemp;

      }else if ( nCompRc > 0 ) {
	pBase = NULL;
	bDoMore = false;

      }else{
	bDoMore = false;
      }
    }while( bDoMore );

#if defined(_MT)
    LeaveCriticalSection(m_cs);
#endif
  }
  return pBase;
}

// - Insert ------------------------------------------------------------

template <class T> BTree<T>* BTree<T>::Insert(BTree<T>* pNewValue)
{
  int       nCompRc;
  BTree<T>* pTemp;
  BTree<T>* pBase   = NULL;
  BTree<T>* pRoot;
  bool      bDoMore = true;
  T*        pValue;

  if ( pNewValue ) {

#if defined(_MT)
    EnterCriticalSection(m_cs);

    if ( m_CritAutoAlloc && (NULL == pNewValue->GetCriticalSection()) ) {
      pNewValue->PutCriticalSection(m_cs);
      pNewValue->PutCritAutoAlloc(m_CritAutoAlloc);
    }
#endif

    pValue = pNewValue->GetUnlockedValue();

    pRoot = pBase = ((pTemp=this->GetRoot()) ? pTemp : this);

    do {

      nCompRc = pBase->Compare(pBase->GetUnlockedValue(),pValue);

      if ( nCompRc < 0 && (pTemp=pBase->GetLessThan()) ) {
	pBase = pTemp;

      }else if ( nCompRc < 0 ) {
	pBase->PutLessThan(pNewValue);
	pNewValue->PutParent(pBase);
	pBase = pNewValue;
	++pRoot->m_ItemCount;
	bDoMore = false;

      }else if ( nCompRc > 0 && (pTemp=pBase->GetGreaterThan()) ) {
	pBase = pTemp;

      }else if ( nCompRc > 0 ) {
	pBase->PutGreaterThan(pNewValue);
	pNewValue->PutParent(pBase);
	pBase   = pNewValue;
	++pRoot->m_ItemCount;
	bDoMore = false;

      }else{
	pBase = NULL;
	bDoMore = false;
      }

    }while( bDoMore );

#if defined(_MT)
    LeaveCriticalSection(m_cs);
#endif
  }
  return pBase;
}

// - Insert ------------------------------------------------------------

template <class T> BTree<T>* BTree<T>::Insert(T* pNewValue)
{
  BTree* pValue = new BTree(pNewValue);

  return Insert(pValue);
}

// - InsertBalanced ----------------------------------------------------

template <class T> BTree<T>* BTree<T>::InsertBalanced(T* pNewValue)
{
  int        nCount;
  BTree<T>*  pData;
  BTree<T>** pList;
  BTree<T>*  pRoot;
  BTree<T>*  pReturn = NULL;

  // Insert the new value
  //

  if ( pNewValue ) {
    pData = Insert(pNewValue); 

    // Get the sorted list
    //
    
    if ( pData ) {
      pReturn = pData;

      pList = GetSortList();

      // Balance the tree
      //

      if ( pList ) {
	nCount = GetCount();

	if ( nCount ) {
	  pRoot = Balance(pList,nCount);

	  if ( pRoot ) {
	    pReturn = pRoot;
	  }
	}

	// Cleanup and return
	//
	
	delete pList;
      }
    }
  }
  return pReturn;
}
	    
// - InsertBalanced ----------------------------------------------------

template <class T> BTree<T>* BTree<T>::InsertBalanced(BTree<T>* pNewValue)
{
  int        nCount;
  BTree<T>*  pData;
  BTree<T>** pList;
  BTree<T>*  pRoot;
  BTree<T>*  pReturn;

  // Insert the new value
  //

  if ( pNewValue ) {
    pData = Insert(pNewValue);

    // Get the sorted list
    //

    if ( pData ) {
      pReturn = pData;

      pList = GetSortList();

      // Balance the tree
      //

      if ( pList ) {
	nCount = GetCount();

	if ( nCount ) {
	  pRoot = Balance(pList,nCount);

	  if ( pRoot ) {
	    pReturn = pRoot;
	  }
	}

	// Cleanup and return
	//

	delete pList;
      }
    }
  }
  return pReturn;
}

// - Replace ------------------------------------------------------------

template <class T> inline BTree<T>* BTree<T>::Replace(BTree<T>* pOld,BTree<T>* pNew)
{
  BTree<T>* pTemp;

#if defined(_MT)
  EnterCriticalSection(m_cs);
#endif

  pTemp = Find(pOld);

  if ( NULL != pTemp && NULL != pNew->GetValue() && pOld != this )
    {
      Delete(pTemp);
      pTemp = InsertBalanced(pNew);
    }

#if defined(_MT)
  LeaveCriticalSection(m_cs);
#endif

  return pTemp;
}

// - Delete ------------------------------------------------------------

template <class T> inline BTree<T>* BTree<T>::Delete(T* pValue)
{
  int        nCompRc;
  BTree<T>*  pTemp;
  BTree<T>*  pParent;
  BTree<T>*  pBase;
  BTree<T>*  pLess;
  BTree<T>*  pGreat;
  BTree<T>*  pPtr;
  BTree<T>*  pRoot;
  //  BTree<T>** pList;
  bool       bDoMore;
  int        nItemCount;

#if defined(_MT)
  bool       bDeleteCrit = false;
  LPCRITICAL_SECTION lpCs;
#endif

  if ( pValue ) {

#if defined(_MT)
    lpCs = GetCriticalSection();
    EnterCriticalSection(lpCs);
#endif

    pParent = NULL;
    pBase   = NULL;
    pLess   = NULL;
    pGreat  = NULL;
    bDoMore = true;

    // XXX: Note: This method needs an additional rule
    //            to determine when to sort the list as
    //            two pieces (before deleted item, after del item)
    //            with a call to Balance() versus when to
    //            insert the stragglers and call BalanceTree()
    //

    // Get the root value for this tree
    //

    pRoot = pBase = ((pTemp=this->GetRoot()) ? pTemp : this);

    nItemCount = pRoot->GetCount();

    do {

      // Determine if this is the guy
      //

      nCompRc = pBase->Compare(pBase->GetUnlockedValue(),pValue);

      if ( nCompRc < 0 && (pTemp=pBase->GetLessThan()) ) {
	pBase = pTemp;                  // Get the left leg

      }else if ( nCompRc < 0 ) {
	//	pBase   = pValue;
	bDoMore = false;                // Error ... not found

      }else if ( nCompRc > 0 && (pTemp=pBase->GetGreaterThan()) ) {
	pBase = pTemp;
	//	pBase   = pValue;               // Get the right leg
	// bDoMore = false;

      }else if ( nCompRc > 0 ) {
	//	pBase   = pValue;               // Error ... not found
	bDoMore = false;

      }else{                            // Equal

	// Check to see if this is the root of all evil
	//

	pParent = pBase->GetParent();
	pLess   = pBase->GetLessThan();
	pGreat  = pBase->GetGreaterThan();

	// Removing the root node with both less and
	// greater elements
	//

	if ( !pParent && pLess && pGreat ) {
	  pGreat->PutParent(NULL);
	  pLess->PutParent(NULL);

	  // Insert the less than value to rebuild the tree
	  //

	  BTree<T>** pList  = pLess->GetSortedList();
	  int        nCount = pLess->GetCount();

	  for( int i=0 ; i < nCount ; ++i ) {
	    pGreat->Insert(pList[i]);
	  }

	  // Adjust the number of items in the tree
	  //

	  pGreat->PutCount((--nItemCount >= 0 ? nItemCount : 0));

	  // Rebalance the tree and send back the node
	  //

	  pPtr = pGreat->BalanceTree();

	  // Delete the old root
	  //

	  T* pValue = pBase->GetUnlockedValue();
	  if ( pValue ) delete pValue;
	  delete pBase;

	  bDoMore = false;

	  // Removing the root node with only less than
	  //

	}else if ( !pParent && pLess ) {

	  pLess->PutParent(NULL);

	  pLess->PutCount((--nItemCount >= 0 ? nItemCount : 0));

	  T* pValue = pBase->GetUnlockedValue();
	  if ( pValue ) delete pValue;
	  delete pBase;

	  pPtr = pLess;

	  bDoMore = false;

	  // Removing root node with only greater than
	  //

	}else if ( !pParent && pGreat ) {

	  pGreat->PutParent(NULL);

	  pGreat->PutCount((--nItemCount >= 0 ? nItemCount : 0));

	  T* pValue = pBase->GetUnlockedValue();
	  if ( pValue ) delete pValue;
	  delete pBase;

	  pPtr = pGreat;

	  bDoMore = false;

	  // Deleting from an empty list
	  //

	}else if ( !pParent ) {
	  pPtr = NULL;

	  T* pValue = pBase->GetUnlockedValue();
	  if ( pValue ) delete pValue;

#if defined(_MT)
	  bDeleteCrit = pBase->GetCritAutoAlloc();
#endif
	  delete pBase;
	  bDoMore = false;

	  // Removing a center node with less and greater than
	  //

	}else if ( pParent && pLess && pGreat ) {

	  if ( pBase == pParent->GetGreaterThan() ) {
	    pParent->PutGreaterThan(pGreat);
	  }else{
	    pParent->PutLessThan(pGreat);
	  }

	  pGreat->PutParent(pParent);
	  pLess->PutParent(NULL);

	  pTemp = pParent->GetRoot();
	  pTemp->Insert(pLess);

	  pTemp->PutCount((--nItemCount >= 0 ? nItemCount : 0));

	  pPtr = pTemp->BalanceTree();

	  T* pValue = pBase->GetUnlockedValue();
	  if ( pValue ) delete pValue;
	  delete pBase;

	  bDoMore = false;

	  // Removing a center node with less than
	  //

	}else if ( pParent && pLess ) {

	  if ( pBase == pParent->GetGreaterThan() ) {
	    pParent->PutGreaterThan(pLess);
	  }else{
	    pParent->PutLessThan(pLess);
	  }

	  pLess->PutParent(pParent);

	  pRoot->PutCount((--nItemCount >= 0 ? nItemCount : 0));

	  pPtr = pRoot;

	  T* pValue = pBase->GetUnlockedValue();
	  if ( pValue ) delete pValue;
	  delete pBase;

	  bDoMore = false;

	  // Removing a ceter node with greater than
	  //

	}else if ( pParent && pGreat ) {

	  if ( pBase == pParent->GetGreaterThan() ) {
	    pParent = PutGreaterThan(pGreat);
	  }else{
	    pParent->PutLessThan(pGreat);
	  }

	  pGreat->PutParent(pParent);

	  pRoot->PutCount((--nItemCount >= 0 ? nItemCount : 0));

	  pPtr = pRoot;

	  T* pValue = pBase->GetUnlockedValue();
	  if ( pValue ) delete pValue;
	  delete pBase;

	  bDoMore = false;

	}else{ // pParent && !pLess && !pGreat

	  if ( pBase == pParent->GetGreaterThan() ) {
	    pParent->PutGreaterThan(NULL);
	  }else{
	    pParent->PutLessThan(NULL);
	  }

	  pRoot->PutCount((--nItemCount >= 0 ? nItemCount : 0));

	  pPtr = pRoot;

	  T* pValue = pBase->GetUnlockedValue();
	  if ( pValue ) delete pValue;
	  delete pBase;

	  bDoMore = false;
	}
      }
    }while ( bDoMore );

#if defined(_MT)
    LeaveCriticalSection(lpCs);
    if ( bDeleteCrit ) delete lpCs;
#endif
  }
  return pPtr;
}

// - Delete ------------------------------------------------------------

template <class T> inline BTree<T>* BTree<T>::Delete(BTree<T>* pNode)
{
  T*        pValue;
  BTree<T>* pPtr = NULL;

  if ( pNode && (pValue=pNode->GetUnlockedValue()) ) {
    pPtr = Delete(pValue);
  }
  return pPtr;
}

// - GetSortedItemList -------------------------------------------------

template <class T> T** BTree<T>::GetSortedItemList()
{
  int        i;
  BTree<T>** pSortList;
  T**        pItemList;
  int        nItemCount;

  nItemCount = this->GetCount();
  if ( !nItemCount ) return NULL;

  pSortList = GetSortList();
  if ( !pSortList ) return NULL;

  pItemList = new T*[nItemCount];
  if ( !pItemList ) {
    delete pSortList;
    return NULL;
  }

  for( i=0 ; i < nItemCount ; ++i ) {
    nItemList[i] = pSortList[i]->GetValue();
  }

  delete pSortList;

  return pItemList;
}

// - GetSortedList ------------------------------------------------------

template <class T> inline BTree<T>** BTree<T>::GetSortedList()
{
  BTree<T>** pList = NULL;
  BTree<T>** pListTemp;
  BTree<T>*  pTemp;
  int        nCount;
  //  int        nItemCount;
  bool       bDoMore = true;
  BTree<T>*  pRoot = this->GetRoot();
  BTree<T>*  pMaxEntry;

  // Get the maximum entry to terminate the construction
  //

  pTemp = pRoot;

  while( pTemp->m_Great ) pTemp = m_Great;

  pMaxEntry = pTemp;

  // Go to the starting point
  //

  nCount = 0;

  pTemp = pRoot;

  while( pTemp->m_Less ) pTemp = pTemp->m_Less;

  // Start counting
  //

  do {

    if ( !pTemp->m_Less    &&
	 !pTemp->m_Great   &&
	 !pTemp->m_Searched ) {

      pListTemp = new BTree<T>*[1+nCount];

      if ( pList ) {
	memcpy((void*)pListTemp,(void*)pList,nCount*sizeof*pList);
	delete pList;
      }
      pList = pListTemp;

      pList[nCount++] = pTemp;
      pTemp->m_Searched = true;

      // If this is the max entry or
      // a singleton, no parent, lt or gt entry
      // all processing has been completed
      //

      if ( pTemp == pMaxEntry || !pTemp->m_Parent ) {
	bDoMore = false;
      }else{
	pTemp = pTemp->m_Parent;
      }

    }else if ( pTemp->m_Less              &&
	       !pTemp->m_Less->m_Searched ) {
      pTemp = pTemp->m_Less;

    }else if ( pTemp->m_Great              &&
	       !pTemp->m_Great->m_Searched ) {

      pListTemp = new BTree<T>*[1+nCount];

      if ( pList ) {
	memcpy((void*)pListTemp,(void*)pList,nCount*sizeof*pList);
	delete pList;
      }

      pList = pListTemp;

      pList[nCount++] = pTemp;

      pTemp->m_Searched = true;

      pTemp = pTemp->m_Great;

    }else if ( !pTemp->m_Searched ) {

      pListTemp = new BTree<T>*[1+nCount];

      if ( pList ) {
	memcpy((void*)pListTemp,(void*)pList,nCount*sizeof*pList);
	delete pList;
      }

      pList[nCount++] = pTemp;
      pTemp->m_Searched = true;

      if ( pTemp->m_Parent ) pTemp = pTemp->m_Parent;

    }else if ( pTemp->m_Searched &&
	       pTemp->m_Parent   ) {

      pTemp = pTemp->m_Parent;

    }else{
      bDoMore = false; // Goofy condition
    }

  }while( bDoMore );

  pRoot->m_ItemCount = nCount;

  for( int i=0 ; i < nCount ; ++i ) pList[i]->m_Searched = false;

  return pList;
}

// - BalanceTree -------------------------------------------------------

template <class T> inline BTree<T>* BTree<T>::BalanceTree()
{
  int        nItemCount = GetCount();
  BTree<T>** pSortList;
  BTree<T>*  pRoot;

  // We fail if there aren't any items in the current tree
  // This should be a nonsense condition since this is an
  // object method, 'c' remnant
  //

  if ( 0 == nItemCount ) return NULL;

  // Get the sorted object list
  //

  pSortList = GetSortList();
  if ( NULL == pSortList ) return NULL;

  // Balance the tree
  //

  pRoot = Balance(pSortList,nItemCount);

  // The list is a shell, clear it
  //

  delete pSortList;

  return pRoot;
}

// - DeleteTree --------------------------------------------------------

template <class T> inline BTree<T>* BTree<T>::DeleteTree()
{
  int        i;
  int        nCount;
  BTree<T>** pList;
  BTree<T>*  pRoot   = GetRoot();
  BTree<T>*  pRetVal = this;
  T*         pValue;

#if defined(_MT)
  bool bDelCsFlag = pRoot->GetCritAutoAlloc();
  LPCRITICAL_SECTION lpcs = pRoot->GetCriticalSection();
  EnterCriticalSection(lpcs);
#endif

  pList  = GetSortList();
  nCount = GetCount();

  if ( pList ) {
    for( i=0 ; i < nCount ; ++i ) {
      pValue = pList[i]->GetValue();
      if ( pValue ) delete pValue;

#if defined(_MT)
      if ( bDelCsFlag ) pList[i]->PutCritAutoAlloc( false );
#endif
      delete pList[i];
    }
    delete pList;
    pRetVal = NULL;
  }

#if defined(_MT)
  LeaveCriticalSection(lpcs);
  DeleteCriticalSection(lpcs);
  if ( bDelCsFlag ) delete lpcs;
#endif
  
  return pRetVal;
}

// - DeleteLeaf --------------------------------------------------------

template <class T> inline void BTree<T>::DeleteLeaf(BTree<T>* pLeaf)
{
#if defined(_MT)
  LPCRITICAL_SECTION lpCs = m_cs;
  EnterCriticalSection(lpCs);
#endif

  if ( pLeaf->m_Data ) delete pLeaf->m_Data;

  delete pLeaf;

#if defined(_MT)
  LeaveCriticalSection(lpCs);
#endif
}

// - PutCount ----------------------------------------------------------

template <class T> inline int BTree<T>::PutCount(int nCount)
{
  int nTemp = m_ItemCount;
  m_ItemCount = nCount;
  return nTemp;
}

// - GetCount ----------------------------------------------------------

template <class T> inline int BTree<T>::GetCount()
{
  BTree<T>* pRoot = this->GetRoot();
  return (pRoot ? pRoot->m_ItemCount : 0);
}

/* =====================================================================
 *                           EXTERNAL METHODS
 * ===================================================================== */

/* ---------------------------------------------------------------------
 *                     STREAM METHODS
 * --------------------------------------------------------------------- */

// - File Output Operator ----------------------------------------------

template <class T> ofstream& operator<<(ofstream& os,BTree<T>& tr)
{
  BTree<T>** pList;
  BTree<T>*  pRoot;
  TreePtr    pTp;
  int        nCount;

  // Make sure that the stream is open.
  //

  if ( !os.is_open() ) return os;

  // Serialize for output
  //

#if defined(_MT)
  EnterCriticalSection(tr.m_cs);
#endif

  // Get the item count
  //

  nCount = tr.GetCount();

  // Sort the data and build fill in the stream
  // balance data.
  //

  if ( NULL == (pList=tr.GetSortList()) ) {
    return os;

  }else if ( NULL == (pRoot=tr.StreamBalance(pList,nCount)) ) {
    delete pList;
    return os;
  }

  // Output the count of items in the tree
  //

  os << nCount << endl;

  for( int i=0 ; i < nCount ; ++i )
    {
      pTp = pList[i]->pTreePtr;
      os << pTp->Parent  << endl;
      os << pTp->Greater << endl;
      os << pTp->Less    << endl;
    }

  // Output the values to go with the tree and cleanup
  // the memory elements used for the pseudo tree
  //

  for( i=0 ; i < nCount ; ++i ) {
    os << *(pList[i]->GetValue()) << endl;
    delete pList[i]->pTreePtr;
    pList[i]->pTreePtr = NULL;
  }

  delete pList;

  // Done, so finish up
  //

#if defined(_MT)
  LeaveCriticalSection(tr.m_cs);
#endif

  return os;
}

// - File Input Operator -----------------------------------------------

template <class T> ifstream& operator>>(ifstream& is,BTree<T>** bt)
{
  int        nCount;
  BTree<T>** pList;
  BTree<T>*  pItem;
  TreePtr    pType;
  int        nRoot;

#if defined(_MT)
  LPCRITICAL_SECTION lpCs = new CRITICAL_SECTION;
  InitializeCriticalSection(lpCs);
  EnterCriticalSection(lpCs);
#endif

  // Make sure the stream is open for reading
  //

  if ( !is.is_open() ) {
#if defined(_MT)
    LeaveCriticalSection(lpCs);
    DeleteCriticalSection(lpCs);
#endif
    return is;
  }

  // Read the number of elements in this tree
  //

  is >> nCount;

  if ( !nCount ) {
#if defined(_MT)
    LeaveCriticalSection(lpCs);
    DeleteCriticalSection(lpCs);
#endif
    return is;
  }

  nRoot = nCount / 2;

  // Allocate space for the input list
  //

  pList = new BTree<T>*[nCount];

  // Read the pseudo tree into memory
  //

  for( int i=0 ; i < nCount ; ++i ) {
    pItem = new BTree<T>;
    pType = new PseudoTreeStruct;
#if defined(_MT)
    pItem->PutCriticalSection(lpCs);
    pItem->PutCritAutoAlloc(true);
#endif

    pList[i] = pItem;
    pItem->pTreePtr = pType;

    is >> pType->Parent;
    is >> pType->Greater;
    is >> pType->Less;
  }

  // Reconstruct the tree and clean up expended pseudo tree elements
  //

  // XXX: This requires rework.
  // XXX: Input all data in order
  // XXX: and then reconstruct the tree

  for( i=0 ; i < nCount ; ++i ) {
    T* pNewData = new T;
    is >> *pNewData;
    pList[i]->PutUnlockedValue(pNewData);

    pType = pList[i]->pTreePtr;

    pList[i]->PutParent(     (pType->Parent  != -1 ? pList[pType->Parent]  : NULL));
    pList[i]->PutGreaterThan((pType->Greater != -1 ? pList[pType->Greater] : NULL));
    pList[i]->PutLessThan(   (pType->Less    != -1 ? pList[pType->Less]    : NULL));

    delete pList[i]->pTreePtr;
    pList[i]->pTreePtr = NULL;
  }

  // Finish the cleanup and return the stream.
  //

  pList[nRoot]->m_ItemCount = nCount;

  *bt = pList[nRoot];

  delete pList;

#if defined(_MT)
  LeaveCriticalSection(lpCs);
#endif

  return is;
}

/* =====================================================================
 *                    REGRESSION TEST METHODS
 * ===================================================================== */

#if defined(_REGRESSION_TESTING)

/* ---------------------------------------------------------------------
 * Comparison method for integer testign
 * --------------------------------------------------------------------- */

// TEMPORARY VEGETABLE
//

template <class T> inline int BTree<T>::Compare(T* pVal,T* pExtVal)
{

  if ( !pExtVal && !pVal ) {
    return 0;
  }else if ( (pExtVal && !pVal) || (!pExtVal && pVal) ) {
    return -1;
  }

  int nRc;

  if ( *pExtVal < *pVal ) {
    nRc = -1;
  }else if ( *pExtVal > *pVal ) {
    nRc = 1;
  }else{
    nRc = 0;
  }

  return nRc;
}

typedef BTree<int> BtInt;

#define ITEMS 5

void main() {

  int   i;
  int** pData;

  pData = new int*[ITEMS];

  for( i=0 ; i < ITEMS ; ++i ) {
    pData[i] = new int;
    *pData[i] = i;
  }

  CRITICAL_SECTION cs;
  InitializeCriticalSection(&cs);

  BtInt* theRoot = new BtInt((int*)pData[0],&cs);

  for( i=1 ; i < ITEMS ; ++i ) {
    theRoot->Insert(new BtInt((int*)pData[i],&cs));
  }

  delete pData;

  BtInt* newRoot = theRoot->BalanceTree();

  int* pIdx = new int;
  *pIdx = 0;

  BtInt* pComp = new BtInt(pIdx,&cs);
  BtInt* pBase = newRoot->Find(pComp);

  ofstream out("junk.out",ios::binary|ios::out|ios::trunc);

  out << *newRoot;

  out.close();

  newRoot->DeleteTree();

  ifstream ins("junk.out",ios::in|ios::nocreate|ios::binary);

  ins >> &newRoot;

  ins.close();

  pBase = newRoot->Find(pComp);

  newRoot = newRoot->Delete(pComp);

  *pIdx = 0;

  newRoot->Find(pComp);

  newRoot->DeleteTree();
}

#endif
