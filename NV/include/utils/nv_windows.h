#ifndef NV_WINDOWS_H
#define NV_WINDOWS_H

namespace nv { namespace windows {

    extern void (__stdcall *CloseHandle)(void *handle);
    extern short (__stdcall *GetKey)(int vKey);

    void            EncryptedString(char *out, unsigned long length);

    void            *CreateThread(void *pFunc, void *pParam);
    bool            Init();

}}

#endif
