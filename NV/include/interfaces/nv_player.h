#ifndef NV_PLAYER_H
#define NV_PLAYER_H

#include "utils/nv_vector.h"

namespace nv { namespace engine {
class Player {
public:
    int GetTeamNum() const;
    int GetHealth() const;
    int GetIndex() const;
    int GetLifeState() const;
    int GetShotsFired() const;
    vec3 GetOrigin() const;
    vec3 GetVecView() const;
    vec3 GetEyePosition() const;
    vec3 GetVecPunch() const;
    vec3 GetBonePos(int id) const;
    bool IsDormant() const;
    bool IsValid() const;
private:
    unsigned long GetBoneMatrix() const;
};}}

#endif
