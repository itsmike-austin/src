#include <BTreeBase.h>
#include <iostream.h>

class TestFunc
{
public:
  TestFunc(int i) : m_Value(i) {}
  void DoThis() {}
  int  GetValue() { return m_Value; }

private:
  int m_Value;
};

template <class T> inline int BTree<T>::Compare(T* pVal,T* pExtVal)
{
  if ( !pExtVal && !pVal )
    {
      return 0;
    }
  else if ( (pExtVal && !pVal) || (!pExtVal && pVal) )
    {
      return -1;
    }

  return (pExtVal->GetValue() == pVal->GetValue() ? 0 :
	  pExtVal->GetValue() >  pVal->GetValue() ? 1 :
	  -1);
}

typedef BTree<TestFunc> TreeList;

void main()
{
  CRITICAL_SECTION cs;
  TreeList*        pTree;
  TreeList*        pTemp;
  TestFunc*        pTempVal;
  InitializeCriticalSection(&cs);

  pTree = new TreeList(new TestFunc(0),&cs);

  for( int i=1 ; i < 5 ; ++i )
    {
      pTemp = pTree->Insert(new TreeList(new TestFunc(i),&cs));
      if ( NULL == pTemp )
	{
	  cerr << "Attempt to insert existing item" << endl;
	}
    }

  pTemp = pTree->BalanceTree();

  if ( NULL == pTree )
    {
      cerr << "Attempt to balance tree failed" << endl;
    }
  else
    {
      pTree = pTemp;
    }

  TreeList* pNewTree = new TreeList;

  if ( NULL == pNewTree )
    {
      cerr << "New tree allocation failed ... out of memory" << endl;
      pTree->DeleteTree();
      return;
    }

  pTempVal = pNewTree->PutValue(new TestFunc(0));

  if ( (TestFunc*)-1 == pTempVal )
    {
      cerr << "Invalid attempt to change value... Update is required" << endl;
      pTree->DeleteTree();
      pNewTree->DeleteTree();
      return;
    }

  TreeList* pFound = pTree->Find(pNewTree);

  if ( NULL == pFound )
    {
      cerr << "Attempt to find value failed" << endl;
    }

  pTemp = pTree->Insert(pNewTree);

  if ( NULL == pTemp )
    {
      cerr << "Attempt to insert duplicate value failed" << endl;
    }

  pTemp = pNewTree->DeleteTree();

  if ( NULL != pTemp )
    {
      cerr << "Attempt to delete the new tree failed" << endl;
    }

  TreeList* pOldItem = new TreeList(new TestFunc(4),&cs);
  TreeList* pNewItem = new TreeList(new TestFunc(6),&cs);

  // A replace will result in update to the existing item
  // plus rebalancing the tree. This could change the root
  //

  pTemp = pTree->Replace(pOldItem,pNewItem);

  if ( NULL == pTemp )
    {
      cerr << "Update item failed" << endl;
    }
  else
    {
      pTree = pTemp;
    }

  delete pOldItem;

  pTemp = pTree->DeleteTree();

  if ( NULL != pTemp )
    {
      cerr << "Attempt to delete primary tree failed" << endl;
    }
}
