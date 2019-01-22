#include <windows.h>
#include "utils/nv_windows.h"
#include "interfaces/nv_engine.h"

//
// fake GetStereoApi function
//
unsigned int __declspec(dllexport) GetStereoApi()
{
    return 1;
}

//
// src/features/nv_aimlock.cc
//
namespace nv { namespace features {
    void AimLock();
}}

static unsigned int __main_thread()
{
    while( 1 ) {
        nv::features::AimLock();
    }
    return 1;
}

static unsigned int __main_init()
{
    void *threadHandle;

    if( nv::windows::Init() == false ) {
        return 0;
    }

    if( nv::engine::Init() == false ) {
        return 0;
    }

    threadHandle = nv::windows::CreateThread(__main_thread, 0);
    if( threadHandle != 0 ) {
        nv::windows::CloseHandle(threadHandle);
    } else {
        return 0;
    }
    return 1;
}

//
// main
//
int __stdcall DllMain(HMODULE hMod, DWORD rea, LPVOID res)
{
    BOOL status;

    status = 0;
    switch( rea ) {
        case DLL_PROCESS_ATTACH:
            status = __main_init();
            break;

        case DLL_PROCESS_DETACH:
            status = 1;
            break;
    }
    return status;
}
