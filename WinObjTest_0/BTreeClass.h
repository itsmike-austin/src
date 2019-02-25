#ifndef _BTREE_CLASS_H
#define _BTREE_CLASS_H

// XXX: This requires some work to get rid of the using statement!

#include <windows.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>

using namespace std;

typedef struct {
  int Parent;
  int Greater;
  int Less;
}PseudoTreeStruct,*TreePtr;

template <class T> class BTree
{
  friend ofstream& operator<<(ofstream&,BTree<T>&);
  friend ifstream& operator>>(ifstream&,BTree<T>**);

private:
  BTree<T> *m_Less;
  BTree<T> *m_Great;
  BTree<T> *m_Parent;

  T* m_Data;

  int  m_ItemCount;
  bool m_Searched;

#if defined(_MT)
  LPCRITICAL_SECTION m_cs;
  HANDLE             m_hSem;
  int                m_ThreadCount;
  bool               m_CritAutoAlloc;
#endif

  // Operation Methods
  //

  BTree<T>* GetRoot();

  // Object accessors
  //

  BTree<T>* GetParent();
  BTree<T>* PutParent(BTree<T>*);

  BTree<T>* GetLessThan();
  BTree<T>* PutLessThan(BTree<T>*);

  BTree<T>* GetGreaterThan();
  BTree<T>* PutGreaterThan(BTree<T>*);

  T*        GetUnlockedValue();
  T*        PutUnlockedValue(T*);

  static unsigned long  GetLittleEndian(unsigned long  lBigEndian);
  static unsigned short GetLittleEndian(unsigned short sBigEndian);

#if defined(_MT)
  bool      GetCritAutoAlloc();
  void      PutCritAutoAlloc(bool);

  LPCRITICAL_SECTION GetCriticalSection();
  void               PutCriticalSection(LPCRITICAL_SECTION);
#endif

  // Management Methods
  //

  BTree<T>** GetSortList();

  BTree<T>** AddNode(BTree<T>**,int,int,int);
  BTree<T>*  Balance(BTree<T>**,int);

  BTree<T>** AddStreamNode(BTree<T>**,int,int,int);
  BTree<T>*  StreamBalance(BTree<T>**,int);

public:

  // Constructor and destructors
  //

  BTree();

#if !defined(_MT)
  BTree(T&);
  BTree(T*);
#else
  BTree(T&,LPCRITICAL_SECTION);
  BTree(T*,LPCRITICAL_SECTION);
#endif

  ~BTree();

  // Attribute accessors
  //

  T* GetValue();
  T* PutValue(T*);

  // Object methods
  //

  BTree<T>*  Find(BTree<T>*);
//  BTree<T>*  Find(T*);
  T*         Find(T*);

  BTree<T>*  Insert(T*);
  BTree<T>*  Insert(BTree<T>*);
  BTree<T>*  InsertBalanced(T*);
  BTree<T>*  InsertBalanced(BTree<T>*);

  BTree<T>*  Replace(BTree<T>* pOld,BTree<T>* pNew);
  BTree<T>*  Delete(BTree<T>*);
  BTree<T>*  Delete(T*);

  T**        GetSortedItemList();
  BTree<T>** GetSortedList();

  BTree<T>*  BalanceTree();

  BTree<T>*  DeleteTree();
  void       DeleteLeaf(BTree<T>* pLeaf);

  int        GetCount();
  int        PutCount(int nCount);

  // PseudoTree structure for IO
  //

  TreePtr    pTreePtr;

  virtual int Compare(T*,T*);
};

#endif
