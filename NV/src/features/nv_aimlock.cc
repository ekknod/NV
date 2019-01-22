#include "utils/nv_math.h"
#include "utils/nv_windows.h"
#include "interfaces/nv_engine.h"
#include "interfaces/nv_player.h"


namespace nv { namespace features {

    static vec3 __CalculateAngle(const engine::Player *player, const vec3 &coords)
    {
        vec3 pos, angle;

        pos = coords;
        pos = {
            pos.x - player->GetEyePosition().x,
            pos.y - player->GetEyePosition().y,
            pos.z - player->GetEyePosition().z
        };
        math::VectorNormalize(pos);
        math::VectorAngles(pos, angle);
        if( player->GetShotsFired() > 0 ) {
            angle = {
                angle.x - player->GetVecPunch().x * 2.0f,
                angle.y - player->GetVecPunch().y * 2.0f,
                angle.z - player->GetVecPunch().z * 2.0f
            };
        }
        math::ClampAngles(angle);
        return angle;
    }

    static float __GetBestFov(const engine::Player *player, const vec3 &viewAngle)
    {
        int            i, bone;
        float          fov, bestFov;
        vec3           bonePos, targetAngle;
        engine::Player *target;
        
        bestFov = 180.0f;
        for( i = 1; i < 32; i++ ) {
            target = engine::GetClientEntity(i);

            if( target == 0 || target->IsValid() == false ||
                player->GetIndex() == target->GetIndex() ) {
                continue;
            }

            if( engine::IsTeamCheckEnabled() && player->GetTeamNum() == target->GetTeamNum() ) {
                continue;
            }

            for( bone = 3; bone < 9; bone++ ) {
                bonePos = target->GetBonePos(bone);
                targetAngle = __CalculateAngle(player, bonePos);
                fov = math::GetDistanceFov(player->GetEyePosition(), bonePos, viewAngle, targetAngle);
                if( fov < bestFov ) {
                    bestFov = fov;
                }
            }
            
        }

        return bestFov;
    }

    void AimLock()
    {
        engine::Player *player;
        float          fov;

        if (engine::IsInGame()) {
            if (windows::GetKey(0x06) || windows::GetKey(0x01)) {
                player = engine::GetClientEntity(engine::GetLocalPlayer());
                if( player == 0 || player->IsValid() == false ) {
                    engine::SetSensitivity(engine::GetStartSensitivity());
                    return;
                }
                fov = __GetBestFov(player, engine::GetViewAngle());
                if( fov <= 3.0f ) {
                    engine::SetSensitivity(fov / 3.0f * engine::GetStartSensitivity());
                } else {
                    engine::SetSensitivity(engine::GetStartSensitivity());
                }
            } else {
                engine::SetSensitivity(engine::GetStartSensitivity());
            }
        }
    }

}}
