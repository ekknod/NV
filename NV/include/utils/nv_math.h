#ifndef NV_MATH_H
#define NV_MATH_H

#include "nv_vector.h"

namespace nv { namespace math {
    void ClampAngles(vec3 &v);
    void VectorNormalize(vec3 &vec);
    void VectorAngles(vec3 &forward, vec3 &angles);
    float GetFov(const vec3 &viewAngle, const vec3 &aimAngle);
    float GetDistance(const vec3 &pos, const vec3 &target_pos);
    float GetDistanceFov(const vec3& pos, const vec3& target_pos, const vec3& viewAngle, const vec3& aimAngle);
}}

#endif
