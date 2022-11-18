#include "pch.h"
#include "il2cpp-appdata.h"
#include "util.h"

// IL2CPP APIs
#define DO_API(a, r, n, p) r (*n) p
#include "il2cpp-api-functions.h"
#undef DO_API

// Application-specific functions
#define DO_APP_FUNC(a, r, n, p) r (*n) p
namespace app {
#include "il2cpp-functions.h"
}
#undef DO_APP_FUNC

VOID InitIl2Cpp()
{
    // Get base address of IL2CPP module
    TCHAR szFileName[MAX_PATH];
    GetModuleFileName(NULL, szFileName, MAX_PATH);
    uintptr_t baseAddress = (UINT64)GetModuleHandleA("UserAssembly.dll");

    // Define IL2CPP API function addresses
    #define DO_API(a, r, n, p) n = (r(*) p)(baseAddress + util::GetLongValue("Offset", #n, a))
    #include "il2cpp-api-functions.h"
    #undef DO_API

    // Define function addresses
    #define DO_APP_FUNC(a, r, n, p) n = (r(*) p)(baseAddress + util::GetLongValue("Offset", #n, a))
    #include "il2cpp-functions.h"
    #undef DO_APP_FUNC
}
