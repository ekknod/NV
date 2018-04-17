#include "interfaces/nv_player.h"
#include "interfaces/nv_engine.h"

namespace nv {

namespace netvars {
    extern int netvar_team_num;
    extern int netvar_health;
    extern int netvar_life_state;
    extern int netvar_shots_fired;
    extern int netvar_vec_origin;
    extern int netvar_vec_view;
    extern int netvar_vec_punch;
    extern int netvar_studio_bone;
}

namespace engine {

    static void *__Function(void *address, int index)
    {
        return (void*)((unsigned int*)*(unsigned int**)address)[index];
    }

    int Player::GetTeamNum() const
    {
        return *(int*)(this + netvars::netvar_team_num);
    }

    int Player::GetHealth() const
    {
        return *(int*)(this + netvars::netvar_health);
    }

    int Player::GetIndex() const
    {
        typedef int(__thiscall *GetIndexFn)(void*);
        void *n;

        //
        // GetClientNetworkable
        //
        n = (void*)(this + 0x8);
        return ((GetIndexFn)__Function(n, 10))(n);
    }

    int Player::GetLifeState() const
    {
        return *(int*)(this + netvars::netvar_life_state);
    }

    int Player::GetShotsFired() const
    {
        return *(int*)(this + netvars::netvar_shots_fired);
    }

    vec3 Player::GetOrigin() const
    {
        return *(vec3*)(this + netvars::netvar_vec_origin);
    }
    
    vec3 Player::GetVecView() const
    {
        return *(vec3*)(this + netvars::netvar_vec_view);
    }

    vec3 Player::GetEyePosition() const
    {    
        return {
            GetVecView().x + GetOrigin().x,
            GetVecView().y + GetOrigin().y,
            GetVecView().z + GetOrigin().z
        };
    }

    vec3 Player::GetVecPunch() const
    {
        return *(vec3*)(this + netvars::netvar_vec_punch);
    }

    vec3 Player::GetBonePos(int id) const
    {
        return {
            *(float*)(GetBoneMatrix() + 0x30 * id + 0xC),
            *(float*)(GetBoneMatrix() + 0x30 * id + 0x1C),
            *(float*)(GetBoneMatrix() + 0x30 * id + 0x2C)
        };
    }

    bool Player::IsDormant() const
    {
        typedef bool(__thiscall *IsDormantFn)(void*);
        void *n;
        
        //
        // GetClientNetworkable
        //
        n = (void*)(this + 0x8);
        return ((IsDormantFn)__Function(n, 9))(n);
    }

    bool Player::IsValid() const
    {
        return GetHealth() > 0 && GetHealth() <= 1337 && !IsDormant() && GetLifeState() == 0;
    }

    unsigned long Player::GetBoneMatrix() const
    {
        return *(unsigned long*)(this + netvars::netvar_studio_bone);
    }

}}
