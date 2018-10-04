#include "interfaces/nv_engine.h"
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>

namespace nv {
namespace interfaces {
    static void *__Open(const char *name);
    static void *__Get(void *registry, const char *name);
}

namespace netvars {
    bool Init();
}

namespace windows {
    static void __SetValue(const char *v, char *b)
    {
        memset(b, 0, 260);
        strcat(b, v);
    }
    void EncryptedString(char *str, unsigned long val);
}

namespace engine {

    //
    // struct for ingame console variables, used for a sensitivity
    //
    struct convar {
        char pad_0x0000[0x4];
        struct convar *pNext;
        __int32 bRegistered;
        char *pszName;
        char *pszHelpString;
        __int32 nFlags;
        char pad_0x0018[0x4];
        struct convar *pParent;
        char *pszDefaultValue;
        char *strString;
        __int32 stringLength;
        float fValue;
        __int32 nValue;
        __int32 bHasMin;
        float fMinVal;
        __int32 bHasMax;
        float fMaxVal;
        void *fnChangeCallback;
    };

    //
    // vtable addresses
    //
    static void      *address_engine;
    static void      *address_entity;
    static void      *address_client;
    static convar    *address_sensitivity;
    static convar    *address_teamates_are_enemies;
    //
    // ingame sensitivity
    //
    static float     start_sensitivity;

   
    static void *__Function(void *address, int index)
    {
        return (void*)((unsigned int*)*(unsigned int**)address)[index];
    }

    bool IsTeamCheckEnabled()
    {
        int temp, result;

        temp = *(int*)(&address_teamates_are_enemies->nValue);
        result = (int)(temp ^ (unsigned int)address_teamates_are_enemies);
        return *(int*)(&result) < 1;
    }

    float GetSensitivity()
    {
        int temp, result;

        temp = *(int*)(&address_sensitivity->fValue);
        result = (int)(temp ^ (unsigned int)address_sensitivity);
        return *(float*)(&result);
    }

    void SetSensitivity(float sensitivity)
    {
        typedef void(__thiscall* SetSensitivityFn)(void*, float);
        return ((SetSensitivityFn)__Function(address_sensitivity, 15))(address_sensitivity, sensitivity);
    }

    float GetStartSensitivity()
    {
        return start_sensitivity;
    }

    int GetLocalPlayer()
    {
        typedef int(__thiscall *GetLocalPlayerFn)(void*);
        return ((GetLocalPlayerFn)__Function(address_engine, 12))(address_engine);
    }

    vec3 GetViewAngle()
    {
        vec3 v;

        typedef void(__thiscall *GetViewAnglesFn)(void*, vec3&);
        ((GetViewAnglesFn)__Function(address_engine, 18))(address_engine, v);
        return v;
    }

    bool IsInGame()
    {
        typedef bool(__thiscall *IsInGameFn)(void*);
        return ((IsInGameFn)__Function(address_engine, 26))(address_engine);
    }

    Player *GetClientEntity(int id)
    {
        typedef Player*(__thiscall *GetClientEntityFn)(void*, int);
        return ((GetClientEntityFn)__Function(address_entity, 3))(address_entity, id);
    }

    void *GetAllClasses()
    {
        typedef void *(__thiscall *GetAllClassesFn)(void*);
        return ((GetAllClassesFn)__Function(address_client, 8))(address_client);
    }

    bool Init()
    {
        void *address;
        char buffer[260];

        //
        // engine
        //

        windows::__SetValue("elnijg*bln", buffer);
        windows::EncryptedString(buffer, 0x64240920);
        address = interfaces::__Open(buffer);
        if( address != 0 ) {
            windows::__SetValue("VGggmlaElklnp", buffer);
            windows::EncryptedString(buffer, 0x64240920);
            address_engine = interfaces::__Get(address, buffer);
            if( address_engine == 0 ) {
                return false;
            }
        } else {
            return false;
        }

        //
        // client
        //
        windows::__SetValue("cn`ejv[valfreoe(dne", buffer);
        windows::EncryptedString(buffer, 0x64240920);
        address = interfaces::__Open(buffer);
        if( address != 0 ) {
            windows::__SetValue("VAeialpCnv`t}Nmut", buffer);
            windows::EncryptedString(buffer, 0x64240920);
            address_entity = interfaces::__Get(address, buffer);
            if( address_entity == 0 ) {
                return false;
            }
            windows::__SetValue("VAeialp", buffer);
            windows::EncryptedString(buffer, 0x64240920);
            address_client = interfaces::__Get(address, buffer);
            if( address_client == 0 ) {
                return false;
            }
        } else {
            return false;
        }

        //
        // vstdlib
        //
        windows::__SetValue("vq}dhkf(dne", buffer);
        windows::EncryptedString(buffer, 0x64240920);
        address = interfaces::__Open(buffer);
        if( address != 0 ) {
            windows::__SetValue("VGggmlaEvc{", buffer);
            windows::EncryptedString(buffer, 0x64240920);
            address = interfaces::__Get(address, buffer);
            if( address == 0 ) {
                return false;
            }
            typedef struct convar* (__thiscall* FindVarFn)(void*, const char*);
            windows::__SetValue("sggsmvmpivp", buffer);
            windows::EncryptedString(buffer, 0x64240920);
            address_sensitivity = ((FindVarFn)__Function(address, 15))(address, buffer);
            if( address_sensitivity == 0 ) {
                return false;
            } else {
                start_sensitivity = GetSensitivity();
            }
            windows::__SetValue("mrVtacikavls[cvc_ggeikau", buffer);
            windows::EncryptedString(buffer, 0x64240920);
            address_teamates_are_enemies = ((FindVarFn)__Function(address, 15))(address, buffer);
            if( address_teamates_are_enemies == 0 ) {
                return false;
            }
        } else {
            return false;
        }

        return netvars::Init();
    }

}

namespace interfaces {

    struct interface_registry {
        void                      *(*create_interface)();
        const char                *name;
        struct interface_registry *next;
    };

    static void *__Open(const char *dll)
    {
        void *a;
        char buffer[260];

        a = GetModuleHandleA(dll);
        if( a == 0 ) {
            return 0;
        }
        windows::__SetValue("CplapgMhtg{feaa", buffer);
        windows::EncryptedString(buffer, 0x64240920);
        a = (void*)GetProcAddress((HMODULE)a, buffer);
        return a != 0 ? **(void***)(((((ULONG)a + 5) + *(ULONG*)((ULONG)a + 5)) + 4) + 6) : 0;
    }
    
    static void *__Get(void *registry, const char *name)
    {
        struct interface_registry *i;

        for( i = (struct interface_registry*)registry; i != 0; i = i->next ) {
            if ( strstr(i->name, name) && (strlen(i->name) - strlen(name)) < 5 ) {
                return i->create_interface();
            }
        }
        return 0;
    }

}

}
