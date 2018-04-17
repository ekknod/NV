#include "utils/nv_math.h"
#include <math.h>

#define DEG2RAD( x  )  ( (float)(x) * (float)(3.14159265358979323846f / 180.f) )
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / 3.14159265358979323846f) )

namespace nv { namespace math {

    static void __SinCos(float radians, float *sine, float *cosine)
    {
        *sine = (float)sin(radians);
        *cosine = (float)cos(radians);
    }

    static void __AngleVectors(const vec3 &angles, vec3 *forward)
    {
        float sp, sy, cp, cy;
        __SinCos(DEG2RAD(angles.x), &sp, &cp);
        __SinCos(DEG2RAD(angles.y), &sy, &cy);

        forward->x = cp * cy;
        forward->y = cp * sy;
        forward->z = -sp;
    }

    static float __Dot(const vec3 & v1, const vec3 & v2)
    {
        return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
    }

    static float __LengthSqr(const vec3 & v)
    {
        return (v.x * v.x + v.y * v.y + v.z * v.z);
    }

    void ClampAngles(vec3 &v)
    {
        if( v.x > 89.0f && v.x <= 180.0f ) {
            v.x = 89.0f;
        }
        if( v.x > 180.0f ) {
            v.x = v.x - 360.0f;
        }
        if( v.x < -89.0f ) {
            v.x = -89.0f;
        }
        v.y = fmodf(v.y + 180, 360) - 180;
        v.z = 0;
    }

    void VectorNormalize(vec3 &vec)
    {
        float radius;
        radius = 1.f / (float)(sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z) + 1.192092896e-07f);
        vec.x *= radius;
        vec.y *= radius;
        vec.z *= radius;
    }

    void VectorAngles(vec3 &forward, vec3 &angles)
    {
        float tmp, yaw, pitch;

        if( forward.y == 0.f && forward.x == 0.f ) {
            yaw = 0;
            if( forward.z > 0 ) {
                pitch = 270;
            } else {
                pitch = 90.f;
            }
        } else {
            yaw = (float)(atan2(forward.y, forward.x) * 180.f / 3.14159265358979323846f);
            if( yaw < 0 ) {
                yaw += 360.f;
            }
            tmp = (float)sqrt(forward.x * forward.x + forward.y * forward.y);
            pitch = (float)(atan2(-forward.z, tmp) * 180.f / 3.14159265358979323846f);
            if( pitch < 0 ) {
                pitch += 360.f;
            }
        }
        angles.x = pitch;
        angles.y = yaw;
        angles.z = 0.f;
    }

    float GetFov(const vec3 &viewAngle, const vec3 &aimAngle)
    {
        vec3 ang, aim;

        __AngleVectors(viewAngle, &aim);
        __AngleVectors(aimAngle, &ang);
        return RAD2DEG( acos(__Dot(aim, ang) / __LengthSqr(aim) ));
    }

    float GetDistance(const vec3 &pos, const vec3 &target_pos)
    {
        vec3 diff;

        diff = {
            pos.x - target_pos.x,
            pos.y - target_pos.y,
            pos.z - target_pos.z
        };
        return (float)sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
    }

    float GetDistanceFov(const vec3& pos, const vec3& target_pos, const vec3& viewAngle, const vec3& aimAngle)
    {
        float f;
        f = GetFov(viewAngle, aimAngle);
        f = f + ((GetDistance(pos, target_pos) * 0.002f) * f);
        return f;
    }

}}
