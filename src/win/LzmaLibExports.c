/* LzmaLibExports.c -- LZMA library DLL Entry point
2023-03-05 : Igor Pavlov : Public domain */

#include "Precomp.h"
#include "7zTypes.h"

#include "7zWindows.h"

LZMA_DLLEXPORT BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved);
LZMA_DLLEXPORT BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
  UNUSED_VAR(hInstance)
  UNUSED_VAR(dwReason)
  UNUSED_VAR(lpReserved)
  return TRUE;
}
