#include <windows.h>
#include <msi.h>

extern UINT __stdcall TestAction(MSIHANDLE hHandle);

int main()
{
  MSIHANDLE j = (MSIHANDLE)0;

  TestAction(j);

  return 0;
}

