#ifndef NV_ENGINE_H
#define NV_ENGINE_H

#include "utils/nv_vector.h"

namespace nv { namespace engine {
    class         Player;
    bool          IsTeamCheckEnabled();
    float         GetSensitivity();
    void          SetSensitivity(float sensitivity);
    float         GetStartSensitivity();
    int           GetLocalPlayer();
    vec3          GetViewAngle();
    bool          IsInGame();
    Player        *GetClientEntity(int id);
    void          *GetAllClasses();
    bool          Init();

}}

#endif
